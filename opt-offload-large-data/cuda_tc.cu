#include "util/graph/graph.h"
#include "util/util.h"
#include "util/cuda/cuda_util.h"
#include "util/cuda/primitives.cuh"
#include "util/timer.h"
#include "util/primitives/primitives.h"
#include "cuda_extern_functions.cuh"

#define BSR_OPT
//#define CPU_BUILD_BSR
#ifdef CPU_BUILD_BSR
#include "cuda_tc_pack_vertex_cpu.h"
#endif

__global__ void bmp_kernel(uint32_t *d_offsets, /*card: |V|+1*/
                           int32_t *d_dsts, /*card: 2*|E|*/
                           uint32_t *d_bitmaps, /*the global bitmaps*/
                           uint32_t *d_bitmap_states, /*recording the usage of the bitmaps on the SM*/
                           uint32_t *vertex_count, /*for sequential block execution*/
                           uint32_t conc_blocks_per_SM, /*#concurrent blocks per SM*/
                           uint32_t *eid, /*card: 2*|E|*/
                           int32_t *d_intersection_count_GPU) /*card: |E|*/
{
    const uint32_t tid = threadIdx.x + blockDim.x * threadIdx.y; /*threads in a warp are with continuous threadIdx.x */
    const uint32_t tnum = blockDim.x * blockDim.y;
    const uint32_t num_nodes = gridDim.x; /*#nodes=#blocks*/
    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/
    const uint32_t val_size_bitmap = (num_nodes + elem_bits - 1) / elem_bits;
    const uint32_t val_size_bitmap_indexes = (val_size_bitmap + BITMAP_SCALE - 1) >> BITMAP_SCALE_LOG;

    __shared__ uint32_t node_id, sm_id, bitmap_ptr;
    __shared__ uint32_t start_src, end_src, start_src_in_bitmap, end_src_in_bitmap;

    extern __shared__ uint32_t bitmap_indexes[];

    if (tid == 0) {
        node_id = atomicAdd(vertex_count, 1); /*get current vertex id*/
        start_src = d_offsets[node_id];
        end_src = d_offsets[node_id + 1];
        start_src_in_bitmap = d_dsts[start_src] / elem_bits;
        end_src_in_bitmap = (start_src == end_src) ? d_dsts[start_src] / elem_bits : d_dsts[end_src - 1] / elem_bits;
    } else if (tid == tnum - 1) {
        uint32_t temp = 0;
        asm("mov.u32 %0, %smid;" : "=r"(sm_id));
        /*get current SM*/
        while (atomicCAS(&d_bitmap_states[sm_id * conc_blocks_per_SM + temp], 0, 1) != 0)
            temp++;
        bitmap_ptr = temp;
    }
    /*initialize the 2-level bitmap*/
    for (uint32_t idx = tid; idx < val_size_bitmap_indexes; idx += tnum)
        bitmap_indexes[idx] = 0;
    __syncthreads();

    uint32_t *bitmap = &d_bitmaps[val_size_bitmap * (conc_blocks_per_SM * sm_id + bitmap_ptr)];

    /*construct the source node neighbor bitmap*/
    for (uint32_t idx = start_src + tid; idx < end_src; idx += tnum) {
        uint32_t src_nei = d_dsts[idx];
        const uint32_t src_nei_val = src_nei / elem_bits;
        atomicOr(&bitmap[src_nei_val], (0b1 << (src_nei & (elem_bits - 1)))); /*setting the bitmap*/
        atomicOr(&bitmap_indexes[src_nei_val >> BITMAP_SCALE_LOG],
                 (0b1 << ((src_nei >> BITMAP_SCALE_LOG) & (elem_bits - 1)))); /*setting the bitmap index*/
    }
    __syncthreads();

    /*loop the neighbors*/
    /* x dimension: warp-size
     * y dimension: number of warps
     * */
    auto du = d_offsets[node_id + 1] - d_offsets[node_id];
    for (uint32_t idx = start_src + threadIdx.y; idx < end_src; idx += blockDim.y) {
        /*each warp processes a node*/
        uint32_t private_count = 0;
        uint32_t src_nei = d_dsts[idx];
        auto dv = d_offsets[src_nei + 1] - d_offsets[src_nei];
        if (dv > du || ((du == dv) && node_id > src_nei))continue;
        uint32_t start_dst = d_offsets[src_nei];
        uint32_t end_dst = d_offsets[src_nei + 1];
        for (uint32_t dst_idx = start_dst + threadIdx.x; dst_idx < end_dst; dst_idx += blockDim.x) {
            uint32_t dst_nei = d_dsts[dst_idx];
            const uint32_t dst_nei_val = dst_nei / elem_bits;
            if ((bitmap_indexes[dst_nei_val >> BITMAP_SCALE_LOG] >> ((dst_nei >> BITMAP_SCALE_LOG) & (elem_bits - 1)))
                & 0b1 == 1)
                if ((bitmap[dst_nei_val] >> (dst_nei & (elem_bits - 1))) & 0b1 == 1)
                    private_count++;
        }
        __syncwarp();
        /*warp-wise reduction*/
        WARP_REDUCE(private_count);
        if (threadIdx.x == 0)
            d_intersection_count_GPU[eid[idx]] = private_count;
    }
    __syncthreads();

    /*clean the bitmap*/
    if (end_src_in_bitmap - start_src_in_bitmap + 1 <= end_src - start_src) {
        for (uint32_t idx = start_src_in_bitmap + tid; idx <= end_src_in_bitmap; idx += tnum) {
            bitmap[idx] = 0;
        }
    } else {
        for (uint32_t idx = start_src + tid; idx < end_src; idx += tnum) {
            uint32_t src_nei = d_dsts[idx];
            bitmap[src_nei / elem_bits] = 0;
        }
    }
    __syncthreads();

    /*release the bitmap lock*/
    if (tid == 0)
        atomicCAS(&d_bitmap_states[sm_id * conc_blocks_per_SM + bitmap_ptr], 1, 0);
}

__global__ void bmp_bsr_kernel(uint32_t *d_offsets, /*card: |V|+1*/
                               int32_t *d_dsts, /*card: 2*|E|*/
                               uint32_t *d_bitmaps, /*the global bitmaps*/
                               uint32_t *d_bitmap_states, /*recording the usage of the bitmaps on the SM*/
                               uint32_t *vertex_count, /*for sequential block execution*/
                               uint32_t conc_blocks_per_SM, /*#concurrent blocks per SM*/
                               uint32_t *eid, /*card: 2*|E|*/
                               int32_t *d_intersection_count_GPU, /*card: |E|*/
                               uint32_t *bmp_offs,
                               bmp_word_idx_type *bmp_word_indices,
                               bmp_word_type *bmp_words
) {
    const uint32_t tid = threadIdx.x + blockDim.x * threadIdx.y; /*threads in a warp are with continuous threadIdx.x */
    const uint32_t num_threads = blockDim.x * blockDim.y;
    const uint32_t num_nodes = gridDim.x; /*#nodes=#blocks*/
    constexpr uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/
    const uint32_t val_size_bitmap = (num_nodes + elem_bits - 1) / elem_bits;
    const uint32_t val_size_bitmap_indexes = (val_size_bitmap + BITMAP_SCALE - 1) >> BITMAP_SCALE_LOG;

    __shared__ uint32_t u, sm_id, bitmap_ptr;
    __shared__ uint32_t off_u, off_u_plus_one, start_src_in_bitmap, end_src_in_bitmap;

    extern __shared__ uint32_t bitmap_indexes[];

    if (tid == 0) {
        u = atomicAdd(vertex_count, 1); /*get current vertex id*/
        off_u = d_offsets[u];
        off_u_plus_one = d_offsets[u + 1];
        start_src_in_bitmap = d_dsts[off_u] / elem_bits;
        end_src_in_bitmap = (off_u == off_u_plus_one) ? d_dsts[off_u] / elem_bits :
                            d_dsts[off_u_plus_one - 1] / elem_bits;
    } else if (tid == num_threads - 1) {
        uint32_t temp = 0;
        asm("mov.u32 %0, %smid;" : "=r"(sm_id));
        /*get current SM*/
        while (atomicCAS(&d_bitmap_states[sm_id * conc_blocks_per_SM + temp], 0, 1) != 0)
            temp++;
        bitmap_ptr = temp;
    }
    /*initialize the 2-level bitmap*/
    for (uint32_t idx = tid; idx < val_size_bitmap_indexes; idx += num_threads)
        bitmap_indexes[idx] = 0;
    __syncthreads();

    uint32_t *bitmap = &d_bitmaps[val_size_bitmap * (conc_blocks_per_SM * sm_id + bitmap_ptr)];

    /*construct the source node neighbor bitmap*/
    for (uint32_t idx = off_u + tid; idx < off_u_plus_one; idx += num_threads) {
        uint32_t v = d_dsts[idx];
        const uint32_t src_nei_val = v / elem_bits;
        atomicOr(&bitmap[src_nei_val], (0b1 << (v & (elem_bits - 1)))); /*setting the bitmap*/
        atomicOr(&bitmap_indexes[src_nei_val >> BITMAP_SCALE_LOG],
                 (0b1 << ((v >> BITMAP_SCALE_LOG) & (elem_bits - 1)))); /*setting the bitmap index*/
    }
    __syncthreads();

    auto du = d_offsets[u + 1] - d_offsets[u];
    for (uint32_t idx = off_u + threadIdx.y; idx < off_u_plus_one; idx += blockDim.y) {
        uint32_t v = d_dsts[idx];

        /*each warp processes an edge (u, v), v: v */
        auto dv = d_offsets[v + 1] - d_offsets[v];
        if (dv > du || ((du == dv) && u > v))continue;

        uint32_t private_count = 0;
        auto size_nv = bmp_offs[v + 1] - bmp_offs[v];
        if (size_nv > 0) {
            for (uint32_t wi = bmp_offs[v] + threadIdx.x; wi < bmp_offs[v + 1]; wi += blockDim.x) {
                private_count += __popc(bmp_words[wi] & bitmap[bmp_word_indices[wi]]);
            }
        } else {
            for (uint32_t dst_idx = d_offsets[v] + threadIdx.x; dst_idx < d_offsets[v + 1]; dst_idx += blockDim.x) {
                uint32_t w = d_dsts[dst_idx];
                const uint32_t dst_nei_val = w / elem_bits;
                if ((bitmap_indexes[dst_nei_val >> BITMAP_SCALE_LOG]
                        >> ((w >> BITMAP_SCALE_LOG) & (elem_bits - 1))) & 0b1 == 1)
                    if ((bitmap[dst_nei_val] >> (w & (elem_bits - 1))) & 0b1 == 1)
                        private_count++;
            }
        }

        __syncwarp();
        /*warp-wise reduction*/
        WARP_REDUCE(private_count);
        if (threadIdx.x == 0)
            d_intersection_count_GPU[eid[idx]] = private_count;
    }
    __syncthreads();

    /*clean the bitmap*/
    if (end_src_in_bitmap - start_src_in_bitmap + 1 <= off_u_plus_one - off_u) {
        for (uint32_t idx = start_src_in_bitmap + tid; idx <= end_src_in_bitmap; idx += num_threads) {
            bitmap[idx] = 0;
        }
    } else {
        for (uint32_t idx = off_u + tid; idx < off_u_plus_one; idx += num_threads) {
            uint32_t src_nei = d_dsts[idx];
            bitmap[src_nei / elem_bits] = 0;
        }
    }
    __syncthreads();

    /*release the bitmap lock*/
    if (tid == 0)
        atomicCAS(&d_bitmap_states[sm_id * conc_blocks_per_SM + bitmap_ptr], 1, 0);
}

void invoke_tc_bmp_gpu(graph_t *g, int *edge_sup) {
    ZLCUDAMemStat mem_stat;
    ZLCUDATimer time_stat;
    auto timer_ptr = &time_stat;

    // 1st: Initialization of BMP, CSR and eid.
    Timer timer;
    Timer total_timer;
    uint32_t *d_bitmaps, *d_vertex_count;
    uint32_t *d_bitmap_states;
    InitBMP(g, d_bitmaps, d_bitmap_states, d_vertex_count, &mem_stat);

    cuda_graph_t g_cuda;
    g_cuda.n = g->n;
    g_cuda.m = g->m;
    int *edge_sup_gpu;

    ZLCudaMalloc(&g_cuda.adj, sizeof(vid_t) * g_cuda.m, &mem_stat);
    ZLCudaMalloc(&g_cuda.num_edges, sizeof(eid_t) * (g_cuda.n + 1), &mem_stat);
    ZLCudaMalloc(&g_cuda.eid, sizeof(eid_t) * g_cuda.m, &mem_stat);
    ZLCudaMalloc(&edge_sup_gpu, sizeof(int) * g_cuda.m / 2, &mem_stat);

    checkCudaErrors(cudaMemcpy(g_cuda.adj, g->adj, sizeof(vid_t) * g_cuda.m, cudaMemcpyHostToDevice));
#pragma omp parallel
    {
#pragma omp for
        for (auto i = 0; i < g_cuda.n + 1; i++) {
            g_cuda.num_edges[i] = g->num_edges[i];
        }
#pragma omp for
        for (cuda_eid_t i = 0; i < g_cuda.m; i++) {
            g_cuda.eid[i] = g->eid[i];
        }
    }
//    checkCudaErrors(cudaMemcpy(g_cuda.num_edges, g->num_edges, sizeof(eid_t) * (g_cuda.n + 1), cudaMemcpyHostToDevice));
//    checkCudaErrors(cudaMemcpy(g_cuda.eid, g->eid, sizeof(eid_t) * g_cuda.m, cudaMemcpyHostToDevice));
    log_info("Finish BMP/CSR/eid Initialization: %.9lfs", timer.elapsed_and_reset());

    // 2nd: BSRs Initialization.
#if defined(BSR_OPT)
#if !defined(CPU_BUILD_BSR)
    uint32_t *bmp_offs;
    ZLCudaMalloc(&bmp_offs, sizeof(uint32_t) * (g->n + 1));
    execKernel(construct_bsr_row_ptr_per_thread, (g_cuda.n + 127) / 128, 128,
               timer_ptr, true, g_cuda.num_edges, g_cuda.adj, g_cuda.n, bmp_offs);
    auto word_num = CUBScanExclusive(bmp_offs, bmp_offs, g_cuda.n, &time_stat, &mem_stat);
    bmp_offs[g_cuda.n] = word_num;
    log_info("Word Num: %d", word_num);
    bmp_word_idx_type *bmp_word_indices;
    bmp_word_type *bmp_words;
    ZLCudaMalloc(&bmp_word_indices, sizeof(bmp_word_idx_type) * word_num, &mem_stat);
    ZLCudaMalloc(&bmp_words, sizeof(bmp_word_type) * word_num, &mem_stat);
    execKernel(construct_bsr_content_per_thread, (g_cuda.n + 127) / 128, 128,
               timer_ptr, true, g_cuda.num_edges, g_cuda.adj, g_cuda.n, bmp_offs, bmp_word_indices, bmp_words);
#else
    /* Construct BSRs on the CPU */
    uint32_t *bmp_offs;
    bmp_word_idx_type *bmp_word_indices;
    bmp_word_type *bmp_words;
    ConstructBSRsCPU(g, bmp_offs, bmp_word_indices, bmp_words, mem_stat, time_stat);
#endif
#endif
    log_info("Finish BSR construction: %.9lfs", timer.elapsed_and_reset());

    // 3rd: Triangle Counting.
    log_info("Launch Kernel...");
    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/
    const uint32_t num_words_bmp = (g->n + elem_bits - 1) / elem_bits;
    const uint32_t num_word_bmp_idx = (num_words_bmp + BITMAP_SCALE - 1) / BITMAP_SCALE;
    uint32_t block_size = 1024; // maximally reduce the number of bitmaps
    dim3 t_dimension(WARP_SIZE, block_size / WARP_SIZE); /*2-D*/
    CUDAContext context;
    auto conc_blocks_per_SM = context.GetConCBlocks(block_size);
#ifndef BSR_OPT
    execKernelDynamicAllocation(bmp_kernel, g_cuda.n, t_dimension,
                                num_word_bmp_idx * sizeof(uint32_t), timer_ptr, true,
                                g_cuda.num_edges, g_cuda.adj, d_bitmaps, d_bitmap_states,
                                d_vertex_count, conc_blocks_per_SM, g_cuda.eid, edge_sup_gpu);
#else
    execKernelDynamicAllocation(bmp_bsr_kernel, g_cuda.n, t_dimension,
                                num_word_bmp_idx * sizeof(uint32_t), timer_ptr, true,
                                g_cuda.num_edges, g_cuda.adj, d_bitmaps, d_bitmap_states,
                                d_vertex_count, conc_blocks_per_SM, g_cuda.eid, edge_sup_gpu,
                                bmp_offs, bmp_word_indices, bmp_words);
#endif
    checkCudaErrors(cudaMemcpy(edge_sup, edge_sup_gpu, sizeof(int) * g_cuda.m / 2, cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaDeviceSynchronize());    // ensure the kernel execution finished
    log_info("Finish Support Initialization, Max mem size: %'lld Bytes, Time: %.9lfs.", mem_stat.get_max_use(),
             timer.elapsed_and_reset());

    // 4th: Free Memory.
    ZLCudaFree(d_bitmaps, &mem_stat);
    ZLCudaFree(d_bitmap_states, &mem_stat);
    ZLCudaFree(d_vertex_count, &mem_stat);

    ZLCudaFree(g_cuda.adj, &mem_stat);
    ZLCudaFree(g_cuda.num_edges, &mem_stat);
    ZLCudaFree(g_cuda.eid, &mem_stat);
    ZLCudaFree(edge_sup_gpu, &mem_stat);
    log_info("Free memory, Time: %.9lfs", timer.elapsed());
    log_info("End-To-End Time: %.9lfs", total_timer.elapsed());
}