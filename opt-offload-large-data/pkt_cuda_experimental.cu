//
// Created by Bryan on 19/7/2019.
//

#include <omp.h>

#include <functional>
#include <iostream>
#include <unordered_map>
#include <climits>
#include <numeric>
#include <vector>

#include "util/util.h"
#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/timer.h"
#include "util/stat.h"
#include "util/containers/boolarray.h"
#include "util/cuda/primitives.cuh"
#include "util/serialization/pretty_print.h"
#include "cuda_extern_functions.cuh"

/*
 * Expensive operation: atomic update of a single address, totally synchronized.
 */
__inline__ __device__
void process_support(
        cuda_eid_t edge_idx, int level, int *EdgeSupport,
        int *next, int *next_cnt, bool *inNext,
        bool *in_bucket_window_, cuda_eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
        int bucket_level_end_) {
    auto cur = atomicSub(&EdgeSupport[edge_idx], 1);
    if (cur == (level + 1)) {
        auto insert_idx = atomicAdd(next_cnt, 1);
        next[insert_idx] = edge_idx;
        inNext[edge_idx] = true;
    }
    if (cur <= level) {
        atomicAdd(&EdgeSupport[edge_idx], 1);
    }

#ifndef LEGACY_SCAN
    // Update the Bucket.
    auto latest = cur - 1;
    if (latest > level && latest < bucket_level_end_) {
        auto old_token = atomicCAS(in_bucket_window_ + edge_idx, false, true);
        if (!old_token) {
            auto insert_idx = atomicAdd(window_bucket_buf_size_, 1);
            bucket_buf_[insert_idx] = edge_idx;
        }
    }
#endif
}

/*
 * Expensive operation: relatively random access of inCurr and processed and afterwards EdgeSupport.
 */
__inline__ __device__
void PeelTriangle(
        int level, bool *inCurr, int *next, int *next_cnt, bool *inNext, //next_cnt is init as 0
        int *EdgeSupport, bool *processed,
        bool *in_bucket_window_, cuda_eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
        int bucket_level_end_, cuda_eid_t e1_idx, cuda_eid_t e2_idx, cuda_eid_t e3_idx) {
    bool is_peel_e2 = !inCurr[e2_idx];
    bool is_peel_e3 = !inCurr[e3_idx];

    if (is_peel_e2 || is_peel_e3) {
        if ((!processed[e2_idx]) && (!processed[e3_idx])) {
            if (is_peel_e2 && is_peel_e3) {
                process_support(e2_idx, level, EdgeSupport, next, next_cnt, inNext,
                                in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_);
                process_support(e3_idx, level, EdgeSupport, next, next_cnt, inNext,
                                in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_);

            } else if (is_peel_e2) {
                if (e1_idx < e3_idx) {
                    process_support(e2_idx, level, EdgeSupport, next, next_cnt, inNext,
                                    in_bucket_window_, bucket_buf_, window_bucket_buf_size_,
                                    bucket_level_end_);
                }
            } else {
                if (e1_idx < e2_idx) {
                    process_support(e3_idx, level, EdgeSupport, next, next_cnt, inNext,
                                    in_bucket_window_, bucket_buf_, window_bucket_buf_size_,
                                    bucket_level_end_);
                }
            }
        }
    }
}

__global__
void sub_level_process(
        int level, int *curr, uint32_t curr_cnt, bool *inCurr,
        int *next, int *next_cnt, bool *inNext, //next_cnt is init as 0
        cuda_eid_t *offsets, vid_t *adj, cuda_eid_t *eid,
        CUDA_Edge *edge_list, int *EdgeSupport, bool *processed,
        bool *in_bucket_window_, cuda_eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
        int bucket_level_end_) {

    auto tid = threadIdx.x;
    auto tnum = blockDim.x;
    auto bid = blockIdx.x;
    auto bnum = gridDim.x;

    __shared__ int size;
    extern __shared__ int shared[];
    int *e1_arr = shared;
    int *e2_arr = shared + tnum * 2;
    int *e3_arr = shared + tnum * 2 * 2;
    if (tid == 0) {
        size = 0;
    }
    __syncthreads();
    /*block-wise process*/
    for (auto i = bid; i < curr_cnt; i += bnum) {
        auto e1_idx = curr[i];
        CUDA_Edge e1 = edge_list[e1_idx];
        vid_t u = e1.u;
        vid_t v = e1.v;

        int u_start = offsets[u], u_end = offsets[u + 1];
        int v_start = offsets[v], v_end = offsets[v + 1];

        if (u_end - u_start > v_end - v_start) {
            swap_ele(u, v);
            swap_ele(u_start, v_start);
            swap_ele(u_end, v_end);
        }

        /*u neighbor set is smaller than v neighbor*/
        for (auto t = u_start + tid; t < u_start + (u_end - u_start + tnum - 1) / tnum * tnum; t += tnum) {
            __syncthreads();
            if (size >= tnum) {
                for (auto i = tid; i < size; i += tnum) {
                    auto e1_idx = e1_arr[i];
                    auto e2_idx = eid[e2_arr[i]];
                    auto e3_idx = eid[e3_arr[i]];

                    PeelTriangle(level, inCurr,
                                 next, next_cnt, inNext, //next_cnt is init as 0
                                 EdgeSupport, processed,
                                 in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_,
                                 e1_idx, e2_idx, e3_idx);
                }
                __syncthreads();
                if (tid == 0) {
                    size = 0;
                }
                __syncthreads();
            }

            int match = t >= u_end ? INT_INVALID : binary_search(adj[t], adj, v_start, v_end - 1);
            if (match != INT_INVALID) {
                auto pos = atomicAdd(&size, 1);
                e1_arr[pos] = e1_idx;
                e2_arr[pos] = t;
                e3_arr[pos] = match;
            }
        }
    }
    __syncthreads();
    for (auto i = tid; i < size; i += tnum) {
        auto e1_idx = e1_arr[i];
        auto e2_idx = eid[e2_arr[i]];
        auto e3_idx = eid[e3_arr[i]];

        PeelTriangle(level, inCurr,
                     next, next_cnt, inNext, //next_cnt is init as 0
                     EdgeSupport, processed,
                     in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_,
                     e1_idx, e2_idx, e3_idx);
    }
}

__global__
void update_processed(int *curr, uint32_t curr_cnt, bool *inCurr, bool *processed) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < curr_cnt) {
        auto edge_off = curr[gtid];
        processed[edge_off] = true;
        inCurr[edge_off] = false;
    }
}

__global__
void output_edge_support(
        eid_t *output, int *curr, uint32_t curr_cnt,
        eid_t *edge_off_origin, eid_t start_pos) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < curr_cnt) {
        output[gtid + start_pos] = edge_off_origin[curr[gtid]];
    }
}

__global__
void warp_detect_deleted_edges(
        cuda_eid_t *old_offsets, uint32_t old_offset_cnt,
        cuda_eid_t *eid, bool *old_processed,
        cuda_eid_t *histogram, bool *focus) {

    __shared__ uint32_t cnts[WARPS_PER_BLOCK];

    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    auto gtnum = blockDim.x * gridDim.x;
    auto gwid = gtid >> WARP_BITS;
    auto gwnum = gtnum >> WARP_BITS;
    auto lane = threadIdx.x & WARP_MASK;
    auto lwid = threadIdx.x >> WARP_BITS;

    for (auto u = gwid; u < old_offset_cnt; u += gwnum) {
        if (0 == lane) cnts[lwid] = 0;
        __syncwarp();

        auto start = old_offsets[u];
        auto end = old_offsets[u + 1];
        for (auto v_idx = start + lane; v_idx < end; v_idx += WARP_SIZE) {
            auto target_edge_idx = eid[v_idx];
            focus[v_idx] = !old_processed[target_edge_idx];
            if (focus[v_idx])
                atomicAdd(&cnts[lwid], 1);
        }
        __syncwarp();

        if (0 == lane) histogram[u] = cnts[lwid];
    }
}

__global__
void filter_window(int *edge_sup, int count, bool *in_bucket, int low, int high) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) {
        auto v = edge_sup[gtid];
        in_bucket[gtid] = (v >= low && v < high);
    }
}

__global__
void filter_with_random_append(cuda_eid_t *bucket_buf, int count, int *EdgeSupport,
                               bool *in_curr, int *curr, int *curr_cnt, int ref) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) {
        auto edge_off = bucket_buf[gtid];
        if (EdgeSupport[edge_off] == ref) {
            in_curr[edge_off] = true;
            auto insert_idx = atomicAdd(curr_cnt, 1);
            curr[insert_idx] = edge_off;
        }
    }
}

void PKT_Scan(
        int *EdgeSupport, uint32_t edge_num, int level,
        int *curr, bool *inCurr, int &curr_cnt, cuda_eid_t *asc,
        bool *in_bucket_window_, cuda_eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_, int &bucket_level_end_,
        ZLCUDAMemStat *mem_stat, ZLCUDATimer *timer) {
    static bool is_first = true;
    if (is_first) {
        cudaMemset(inCurr, 0, edge_num * sizeof(bool));
#ifndef LEGACY_SCAN
        cudaMemset(in_bucket_window_, 0, edge_num * sizeof(bool));
#endif
        is_first = false;
    }
#ifdef LEGACY_SCAN
    /*filter and get the bool vector*/
    long grid_size = (edge_num + BLOCK_SIZE - 1) / BLOCK_SIZE;
    execKernel(filter, grid_size, BLOCK_SIZE, timer, false, EdgeSupport, edge_num, inCurr, level);
    curr_cnt = CUBSelect(asc, curr, inCurr, edge_num, timer, mem_stat);
#else
    if (level == bucket_level_end_) {
        // Clear the bucket_removed_indicator
        bucket_level_end_ += LEVEL_SKIP_SIZE;

        long grid_size = (edge_num + BLOCK_SIZE - 1) / BLOCK_SIZE;
        execKernel(filter_window, grid_size, BLOCK_SIZE, timer, false,
                   EdgeSupport, edge_num, in_bucket_window_, level, bucket_level_end_);
        *window_bucket_buf_size_ = CUBSelect(asc, bucket_buf_, in_bucket_window_, edge_num, timer, mem_stat);
    }
    // SCAN the window.
    if (*window_bucket_buf_size_ != 0) {
        curr_cnt = 0;
        long grid_size = (*window_bucket_buf_size_ + BLOCK_SIZE - 1) / BLOCK_SIZE;
        execKernel(filter_with_random_append, grid_size, BLOCK_SIZE, timer, false,
                   bucket_buf_, *window_bucket_buf_size_, EdgeSupport, inCurr, curr, &curr_cnt, level);
    } else {
        curr_cnt = 0;
    }
    log_debug("Level: %d, curr: %'d/%'d", level, curr_cnt, *window_bucket_buf_size_);
#endif
}

double set_inter_time = 0;
double process_update_time = 0;

void PKT_LevelZeroProcess(
        int *curr, int curr_cnt, bool *inCurr,
        bool *processed,
        ZLCUDAMemStat *mem_stat,
        ZLCUDATimer *time_stat) {
    int block_size = 256;
    int grid_size = (curr_cnt + block_size - 1) / block_size;
    execKernel(
            update_processed, grid_size, block_size, time_stat, false,
            curr, curr_cnt, inCurr, processed);
}

void PKT_SubLevelProcess(
        int *EdgeSupport, eid_t *edge_off_origin,
        CUDA_Edge *edge_list, cuda_eid_t *eids, uint32_t eids_cnt, int level,
        cuda_eid_t *num_edges, vid_t *adj,
        int *curr, int curr_cnt, bool *inCurr,
        int *next, int *next_cnt, bool *inNext,
        bool *processed, bool *in_bucket_window_,
        cuda_eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_, int &bucket_level_end_,
        ZLCUDAMemStat *mem_stat,
        ZLCUDATimer *time_stat) {
    int block_size = 256;
    static int shared_memory_size_per_block = block_size * sizeof(int) * 2 * 3;
    int grid_size = curr_cnt;  //each block process an edge
    Timer timer;

    /* 1st: Peeling */
    execKernelDynamicAllocation(
            sub_level_process, grid_size, block_size,
            shared_memory_size_per_block,
            time_stat, false,
            level, curr, curr_cnt, inCurr,
            next, next_cnt, inNext,
            num_edges, adj, eids,
            edge_list, EdgeSupport, processed,
            in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_);

    set_inter_time += timer.elapsed_and_reset();

    /* 2nd: Update the processed flags */
    grid_size = (curr_cnt + block_size - 1) / block_size;
    execKernel(
            update_processed, grid_size, block_size, time_stat, false,
            curr, curr_cnt, inCurr, processed);
    process_update_time += timer.elapsed_and_reset();
}

void PKT_SubLevelTCBased(
        cuda_graph_t &g_cuda, bool *&processed,
        int *&EdgeSupport, eid_t *&edge_off_origin, CUDA_Edge *&edge_list,
        int *&new_EdgeSupport, eid_t *&new_edge_offset_origin, CUDA_Edge *&new_edge_list,
        bool *&reversed_processed, bool *&edge_deleted, cuda_eid_t *&scanned_processed,
        cuda_eid_t *&new_offset, cuda_eid_t *&new_eid, vid_t *&new_adj,
        uint32_t edge_num, uint32_t todo,
        int *curr, int curr_cnt, bool *inCurr,
        int *next, int *next_cnt, bool *inNext,
        int level, uint32_t *&bmp_offs, bmp_word_idx_type *&bmp_word_indices, bmp_word_type *&bmp_words,
        uint32_t *d_bitmaps, uint32_t *d_bitmap_states,
        int num_words_bmp, int num_words_bmp_idx, uint32_t *vertex_count, uint32_t conc_blocks_per_SM,
        bool *&in_bucket_window_, cuda_eid_t *&bucket_buf_, cuda_eid_t *&new_bucket_buf_,
        uint32_t &window_bucket_buf_size_, int bucket_level_end_,
        ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat) {
    auto block_size = 256;
    auto grid_size = (curr_cnt + block_size - 1) / block_size;

    /* Mark Processed */
    execKernel(update_processed, grid_size, block_size, time_stat, false, curr, curr_cnt, inCurr, processed);

    /* Shrink Edge Lists, CSR and update eid/edge_off_origin mappings */
    ShrinkCSREid(g_cuda, processed, EdgeSupport, edge_off_origin, edge_list,
                 new_EdgeSupport, new_edge_offset_origin, new_edge_list,
                 reversed_processed, edge_deleted, scanned_processed,
                 new_offset, new_eid, new_adj,
                 in_bucket_window_, bucket_buf_, new_bucket_buf_, window_bucket_buf_size_,
                 edge_num, todo, mem_stat, time_stat);

#ifndef DISABLE_BSR
    // 2nd: BSRs.
    ZLCudaMalloc(&bmp_offs, sizeof(uint32_t) * (g_cuda.n + 1), mem_stat);
    execKernel(construct_bsr_row_ptr_per_thread, (g_cuda.n + 127) / 128, 128,
               time_stat, true, g_cuda.num_edges, g_cuda.adj, g_cuda.n, bmp_offs);
    auto word_num = CUBScanExclusive(bmp_offs, bmp_offs, g_cuda.n, time_stat, mem_stat);
    bmp_offs[g_cuda.n] = word_num;
    log_info("Word Num: %d", word_num);
    ZLCudaMalloc(&bmp_word_indices, sizeof(bmp_word_idx_type) * word_num, mem_stat);
    ZLCudaMalloc(&bmp_words, sizeof(bmp_word_type) * word_num, mem_stat);
    execKernel(construct_bsr_content_per_thread, (g_cuda.n + 127) / 128, 128,
               time_stat, true, g_cuda.num_edges, g_cuda.adj, g_cuda.n, bmp_offs, bmp_word_indices, bmp_words);
#endif

    /* TC-based Support Updates */
    block_size = 1024;
    dim3 t_dimension(WARP_SIZE, block_size / WARP_SIZE); /*2-D*/
    cudaMemset(vertex_count, 0, sizeof(uint32_t));

#ifndef DISABLE_BSR
    execKernelDynamicAllocation(
            bmp_bsr_update_next,
            g_cuda.n, t_dimension,
            num_words_bmp_idx * sizeof(uint32_t), time_stat, true,
            g_cuda.num_edges, g_cuda.adj, d_bitmaps, d_bitmap_states,
            vertex_count, conc_blocks_per_SM, g_cuda.eid, EdgeSupport,
            num_words_bmp, num_words_bmp_idx,
            bmp_offs, bmp_word_indices, bmp_words,
            level, next, next_cnt, inNext,
            in_bucket_window_, bucket_buf_, &window_bucket_buf_size_, bucket_level_end_);
    ZLCudaFree(bmp_offs, mem_stat);
    ZLCudaFree(bmp_word_indices, mem_stat);
    ZLCudaFree(bmp_words, mem_stat);
#else
    execKernelDynamicAllocation(
            bmp_update_next,
            g_cuda.n, t_dimension,
            num_words_bmp_idx * sizeof(uint32_t), time_stat, true,
            g_cuda.num_edges, g_cuda.adj, d_bitmaps, d_bitmap_states,
            vertex_count, conc_blocks_per_SM, g_cuda.eid, EdgeSupport,
            num_words_bmp, num_words_bmp_idx,
            level, next, next_cnt, inNext,
            in_bucket_window_, bucket_buf_, &window_bucket_buf_size_, bucket_level_end_);
#endif
}

void ShrinkCSREid(
        cuda_graph_t &g, bool *&processed,
        int *&EdgeSupport, eid_t *&edge_offset_origin, CUDA_Edge *&edge_list,
        int *&new_EdgeSupport, eid_t *&new_edge_offset_origin, CUDA_Edge *&new_edge_list,
        bool *&reversed_processed, bool *&edge_deleted, cuda_eid_t *&scanned_processed,
        cuda_eid_t *&new_offset, cuda_eid_t *&new_eid, vid_t *&new_adj,
        bool *&in_bucket_window_, cuda_eid_t *&bucket_buf_, cuda_eid_t *&new_bucket_buf_,
        uint32_t &window_bucket_buf_size_,
        uint32_t old_edge_num, uint32_t new_edge_num,
        ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat) {
    static bool shrink_first_time = true;
    if (shrink_first_time) { //shrink first time, allocate the buffers
        shrink_first_time = false;
        Timer alloc_timer;
        ZLCudaMalloc(&new_adj, sizeof(vid_t) * new_edge_num * 2, mem_stat);
        ZLCudaMalloc(&new_eid, sizeof(eid_t) * new_edge_num * 2, mem_stat);
        ZLCudaMalloc(&new_offset, sizeof(eid_t) * (g.n + 1), mem_stat);

        ZLCudaMalloc(&edge_deleted, sizeof(bool) * old_edge_num * 2, mem_stat);
        log_info("Shrink Allocation Time: %.9lfs", alloc_timer.elapsed());
    }
    auto num_obj = mem_stat->get_num_obj();

    /*2. construct new CSR (offsets, adj) and rebuild the eid*/
    int block_size = 128;
    // Attention: new_offset gets the histogram.
    execKernel(warp_detect_deleted_edges, GRID_SIZE, block_size, time_stat, true,
               g.num_edges, g.n, g.eid, processed, new_offset, edge_deleted);

    eid_t total = CUBScanExclusive(new_offset, new_offset, g.n, time_stat, mem_stat);
    new_offset[g.n] = total;
    assert(total == new_edge_num * 2);
    cudaDeviceSynchronize();
    swap_ele(g.num_edges, new_offset);

    /*new adj and eid construction*/
    CUBSelect(g.adj, new_adj, edge_deleted, old_edge_num * 2, time_stat, mem_stat);
    CUBSelect(g.eid, new_eid, edge_deleted, old_edge_num * 2, time_stat, mem_stat);
    swap_ele(g.adj, new_adj);
    swap_ele(g.eid, new_eid);

    g.m = new_edge_num * 2;
    assert(num_obj == mem_stat->get_num_obj()); //the mem object num should be the same
}

void InitBMPsBSRs(cuda_graph_t &g_cuda, uint32_t *&d_bitmaps, uint32_t *&d_bitmap_states, uint32_t *&d_vertex_count,
                  uint32_t *&bmp_offs, bmp_word_idx_type *&bmp_word_indices, bmp_word_type *&bmp_words,
                  ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat) {
    // 1st: BMPs.
    InitBMP(&g_cuda, d_bitmaps, d_bitmap_states, d_vertex_count, mem_stat);
}

void PrepareCSRELEidQueues(graph_t *g, cuda_graph_t &g_cuda, Edge *edgeIdToEdge, CUDA_Edge *&edge_list,
                           int *&next_cnt, int *&curr, bool *&inCurr, int *&next, bool *&inNext, bool *&processed,
                           eid_t *edge_off_origin_cpu, eid_t *&edge_off_origin, cuda_eid_t *&identity_arr_asc,
                           ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat) {
    // 1st: CSR/Eid/Edge List.
    g_cuda.n = g->n;
    g_cuda.m = g->m;
    uint32_t edge_num = g_cuda.m / 2;

    ZLCudaMalloc(&g_cuda.adj, sizeof(vid_t) * g_cuda.m, mem_stat);
    ZLCudaMalloc(&g_cuda.num_edges, sizeof(cuda_eid_t) * (g_cuda.n + 1), mem_stat);
    ZLCudaMalloc(&g_cuda.eid, sizeof(cuda_eid_t) * g_cuda.m, mem_stat);
    ZLCudaMalloc(&edge_list, sizeof(CUDA_Edge) * edge_num, mem_stat);

    cudaMemcpy(g_cuda.adj, g->adj, sizeof(vid_t) * g_cuda.m, cudaMemcpyHostToDevice);
//    cudaMemcpy(g_cuda.num_edges, g->num_edges, sizeof(eid_t) * (g_cuda.n + 1), cudaMemcpyHostToDevice);
//    cudaMemcpy(g_cuda.eid, g->eid, sizeof(eid_t) * g_cuda.m, cudaMemcpyHostToDevice);
#pragma omp parallel
    {
#pragma omp for
        for (auto i = 0; i < g_cuda.n + 1; i++) {
            g_cuda.num_edges[i] = g->num_edges[i];
        }
        for (cuda_eid_t i = 0; i < g_cuda.m; i++) {
            g_cuda.eid[i] = g->eid[i];
        }
    }
    cudaMemcpy(edge_list, edgeIdToEdge, sizeof(CUDA_Edge) * edge_num, cudaMemcpyHostToDevice);

    // 2nd: Processed.
    ZLCudaMalloc(&processed, sizeof(bool) * edge_num, mem_stat);

    // 3rd: Queue Related.
    ZLCudaMalloc(&next_cnt, sizeof(uint32_t), mem_stat);
    ZLCudaMalloc(&curr, sizeof(int) * edge_num, mem_stat);
    ZLCudaMalloc(&next, sizeof(int) * edge_num, mem_stat);
    ZLCudaMalloc(&inCurr, sizeof(bool) * edge_num, mem_stat);
    ZLCudaMalloc(&inNext, sizeof(bool) * edge_num, mem_stat);

    // 4th: Keep the edge offset mapping.
    long grid_size = (edge_num + BLOCK_SIZE - 1) / BLOCK_SIZE;
    edge_off_origin = nullptr;
    ZLCudaMalloc(&edge_off_origin, sizeof(eid_t) * edge_num, mem_stat);
    if (edge_off_origin_cpu != nullptr) {
        cudaMemcpy(edge_off_origin, edge_off_origin_cpu, sizeof(eid_t) * edge_num, cudaMemcpyHostToDevice);
    } else {
        execKernel(init_asc, grid_size, BLOCK_SIZE, time_stat, false, edge_off_origin, edge_num);
    }
    // 5th: Introduce identity_arr_asc for the CUB Select invocations.
    identity_arr_asc = nullptr;
    ZLCudaMalloc(&identity_arr_asc, sizeof(cuda_eid_t) * edge_num, mem_stat);
    execKernel(init_asc, grid_size, BLOCK_SIZE, time_stat, false, identity_arr_asc, edge_num);
}

void PrepareBucket(bool *&in_bucket_window_,
                   cuda_eid_t *&bucket_buf_, uint32_t *&window_bucket_buf_size_, int todo, ZLCUDAMemStat *mem_stat) {
    ZLCudaMalloc(&in_bucket_window_, sizeof(bool) * (todo + sizeof(long long)), mem_stat);

    ZLCudaMalloc(&bucket_buf_, sizeof(cuda_eid_t) * todo, mem_stat);
    ZLCudaMalloc(&window_bucket_buf_size_, sizeof(uint32_t), mem_stat);
}

void PKT_cuda(
        graph_t *g, eid_t *edge_off_origin_cpu, int *&EdgeSupport, Edge *edgeIdToEdge, int shrink_factor,
        eid_t *output, eid_t *level_start_pos, ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat, int level) {
    extern double tc_time;
    Timer scan_timer, sub_process_timer, copy_timer, tc_timer, shrink_timer, prepare_timer;
    double scan_time = 0, sub_process_time = 0, copy_time = 0, shrink_time = 0, prepare_time = 0, penalty_tc_time = 0;
    // 1st: Prepare CSR/EL/Eid/Queues.
    cuda_graph_t g_cuda;
    CUDA_Edge *edge_list = nullptr;
    int *curr = nullptr, *next = nullptr;
    bool *inCurr = nullptr, *inNext = nullptr;
    int *curr_cnt_ptr = nullptr, *next_cnt = nullptr;
    bool *processed = nullptr;
    eid_t *edge_off_origin;
    cuda_eid_t *identity_arr_asc;

    ZLCudaMalloc(&curr_cnt_ptr, sizeof(uint32_t), mem_stat);
    auto &curr_cnt = *curr_cnt_ptr;
    curr_cnt = 0;
    PrepareCSRELEidQueues(g, g_cuda, edgeIdToEdge, edge_list,
                          next_cnt, curr, inCurr, next, inNext, processed,
                          edge_off_origin_cpu, edge_off_origin, identity_arr_asc, mem_stat, time_stat);
    uint32_t edge_num = g_cuda.m / 2;

    /* 2nd: Prepare for double buffered: CSR/EL/Eid/ES/offset-mapping/auxiliaries */
    cuda_eid_t *new_offset = nullptr;
    vid_t *new_adj = nullptr;
    CUDA_Edge *new_edge_list = nullptr;
    cuda_eid_t *new_eid = nullptr;
    int *new_EdgeSupport = nullptr;
    eid_t *new_edge_offset_origin = nullptr;
    bool *reversed_processed = nullptr;     // Auxiliaries for shrinking graphs.
    bool *edge_deleted = nullptr;           // Auxiliaries for shrinking graphs.
    cuda_eid_t *scanned_processed = nullptr;     // Auxiliaries for shrinking graphs.

    // Init Buckets.
    // Bucket Related.
    int bucket_level_end_ = level;
    bool *in_bucket_window_;
    cuda_eid_t *bucket_buf_;
    cuda_eid_t *new_bucket_buf_;
    uint32_t *window_bucket_buf_size_;
#ifndef LEGACY_SCAN
    PrepareBucket(in_bucket_window_, bucket_buf_, window_bucket_buf_size_, edge_num, mem_stat);
#endif
    // 3rd: Init Triangle-Counting-Based Support Update Data Structures (BMPs and BSRs).
    uint32_t *d_bitmaps, *d_bitmap_states, *d_vertex_count;
    uint32_t *bmp_offs = nullptr;
    bmp_word_idx_type *bmp_word_indexes = nullptr;
    bmp_word_type *bmp_words = nullptr;
    CUDAContext context;
    auto conc_blocks_per_SM = context.GetConCBlocks(1024);
    InitBMPsBSRs(g_cuda, d_bitmaps, d_bitmap_states, d_vertex_count,
                 bmp_offs, bmp_word_indexes, bmp_words, mem_stat, time_stat);
    prepare_time = prepare_timer.elapsed();

    // 4th: Init Others.
    double shrink_kernel_time = 0;
    ZLCUDATimer shrink_kernel_timer;
    auto todo = edge_num;
    const auto todo_original = edge_num;
    auto deleted_acc = 0;
    auto shrink_cnt = 0;
    bool shrink_first_time = true;  //if true, the identity_arr_asc array should not be freed since it is shared with edge_off_origin
    cudaDeviceSynchronize();

    time_stat->reset();
    vector <pair<int, double>> tc_stat;
    vector <pair<int, double>> shrink_stat;
    // Begin of Level-Processing, finding edges in k-truss but not in the (k+1)-truss.
    while (todo > 0) {
        log_trace("Level: %d, todo(origin): %d, todo(cur): %d., have: %d", level, todo_original, todo,
                  level_start_pos[level]);
        // 1st: Shrinking.
        if ((deleted_acc * 1.0 / todo_original) > (1.0 / shrink_factor)) { //need to shrink the graph
//        if (false) { //need to shrink the graph
            shrink_timer.reset();
            shrink_kernel_timer.reset();
            ShrinkCSREid(g_cuda, processed,
                         EdgeSupport, edge_off_origin, edge_list,
                         new_EdgeSupport, new_edge_offset_origin, new_edge_list,
                         reversed_processed, edge_deleted, scanned_processed,
                         new_offset, new_eid, new_adj,
                         in_bucket_window_, bucket_buf_, new_bucket_buf_, *window_bucket_buf_size_,
                         edge_num, todo, mem_stat, &shrink_kernel_timer);
            shrink_kernel_time += shrink_kernel_timer.elapsed();
            edge_num = todo;
            auto temp_shrink_time = shrink_timer.elapsed();

            shrink_stat.emplace_back(level, temp_shrink_time);
            shrink_time += temp_shrink_time;
            shrink_cnt++;
            deleted_acc = 0;

            shrink_first_time = false;
            log_trace("Shrink graph finished");
        }
        cudaDeviceSynchronize();

        // 2nd: Frontier Generation.
        scan_timer.reset();
        PKT_Scan(EdgeSupport,
                 todo_original,
                 level, curr, inCurr, curr_cnt, identity_arr_asc,
                 in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_, mem_stat, time_stat);
        cudaDeviceSynchronize();
        scan_time += scan_timer.elapsed();

        // 3rd: Iterative Sub-Level Processing.
        int level_acc_cnt = 0;
        while (curr_cnt > 0) {
            /* 1st: Copy this iteration results (edges to be marked as processed) to the output array */
            copy_timer.reset();
            todo -= curr_cnt;
            deleted_acc += curr_cnt;
            auto grid_size = (curr_cnt + BLOCK_SIZE - 1) / BLOCK_SIZE;
            execKernel(output_edge_support, grid_size, BLOCK_SIZE, time_stat, false, output, curr, curr_cnt,
                       edge_off_origin, level_start_pos[level] + level_acc_cnt);
            level_acc_cnt += curr_cnt;
            copy_time += copy_timer.elapsed();
            // No need to process the last level with PKT_SubLevelProcess.
            if (0 == todo) {
                break;
            }

            /* 2nd: Sub-Level Processing... */
            *next_cnt = 0;
            sub_process_timer.reset();
            cudaDeviceSynchronize();
            if (level == 0) {
                PKT_LevelZeroProcess(curr, curr_cnt, inCurr, processed, mem_stat, time_stat);
            } else {
                size_t task_size = curr_cnt * (size_t)(level + 1);
                size_t left_edge_size = todo;
                double estimated_tc_time = left_edge_size / (g->m / 2.0) * tc_time + penalty_tc_time;
                double estimated_process_throughput = 4.0 * pow(10, 9);
                double estimated_peel_time = task_size / estimated_process_throughput;
                if (estimated_tc_time > estimated_peel_time) {
                    PKT_SubLevelProcess(EdgeSupport, edge_off_origin,
                                        edge_list, g_cuda.eid, edge_num, level,
                                        g_cuda.num_edges, g_cuda.adj,
                                        curr, curr_cnt, inCurr,
                                        next, next_cnt, inNext,
                                        processed,
                                        in_bucket_window_, bucket_buf_, window_bucket_buf_size_, bucket_level_end_,
                                        mem_stat, time_stat);
                } else {
                    shrink_first_time = false;
                    tc_timer.reset();
                    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/
                    const uint32_t num_words_bmp = (g->n + elem_bits - 1) / elem_bits;
                    const uint32_t num_words_bmp_idx = (num_words_bmp + BITMAP_SCALE - 1) / BITMAP_SCALE;
                    PKT_SubLevelTCBased(g_cuda, processed,
                                        EdgeSupport, edge_off_origin, edge_list,
                                        new_EdgeSupport, new_edge_offset_origin, new_edge_list,
                                        reversed_processed, edge_deleted, scanned_processed,
                                        new_offset, new_eid, new_adj,
                                        edge_num, todo, curr, curr_cnt, inCurr, next, next_cnt, inNext,
                                        level, bmp_offs, bmp_word_indexes, bmp_words, d_bitmaps, d_bitmap_states,
                                        num_words_bmp, num_words_bmp_idx, d_vertex_count, conc_blocks_per_SM,
                                        in_bucket_window_, bucket_buf_, new_bucket_buf_, *window_bucket_buf_size_,
                                        bucket_level_end_,
                                        mem_stat, time_stat);
                    auto cost = tc_timer.elapsed();
                    if (estimated_tc_time * 1.2 < cost) {
                        penalty_tc_time += cost - estimated_tc_time;
                        log_info("Penalty TC-Time: %.9lfs", penalty_tc_time);
                    }
                    tc_stat.emplace_back(level, cost);
                    log_info("TC time: %.9lfs", cost);
                    edge_num = todo;
                    shrink_cnt++;
                    deleted_acc = 0;
                }
            }
            cudaDeviceSynchronize();

//            log_info("curr_cnt: %d, next_cnt: %d, todo: %d.", curr_cnt, *next_cnt, todo);
            swap(curr, next);
            swap(inCurr, inNext);
            curr_cnt = *next_cnt;
            sub_process_time += sub_process_timer.elapsed();
        }

        level_start_pos[level + 1] = level_start_pos[level] + level_acc_cnt;
        level++;
    }

    cudaDeviceSynchronize();
    float pkt_cuda_time = time_stat->elapsed();
    ZLCudaFree(processed, mem_stat);
    ZLCudaFree(next_cnt, mem_stat);
    ZLCudaFree(curr, mem_stat);
    ZLCudaFree(next, mem_stat);
    ZLCudaFree(inCurr, mem_stat);
    ZLCudaFree(inNext, mem_stat);

    ZLCudaFree(g_cuda.adj, mem_stat);
    ZLCudaFree(g_cuda.num_edges, mem_stat);
    ZLCudaFree(g_cuda.eid, mem_stat);
    ZLCudaFree(edge_list, mem_stat);
    ZLCudaFree(identity_arr_asc, mem_stat);
    if (!shrink_first_time) { //if false, the identity_arr_asc and edge_off_origin point to different array
        ZLCudaFree(edge_off_origin, mem_stat);

        /*free those double buffers*/
        ZLCudaFree(new_EdgeSupport, mem_stat);
        ZLCudaFree(new_edge_offset_origin, mem_stat);
        ZLCudaFree(new_edge_list, mem_stat);
        ZLCudaFree(new_offset, mem_stat);
        ZLCudaFree(new_adj, mem_stat);
        ZLCudaFree(new_eid, mem_stat);
        ZLCudaFree(reversed_processed, mem_stat);
        ZLCudaFree(edge_deleted, mem_stat);
        ZLCudaFree(scanned_processed, mem_stat);
    }
    log_info("PKT_CUDA kernel time: %.4f s.", pkt_cuda_time * 1.0 / 1000);
    log_info("Prepare CPU time: %.4f s.", prepare_time);
    log_info("Scan CPU time: %.4f s.", scan_time);

    log_info("Shrink kernel time: %.4f s.", shrink_kernel_time * 1.0 / 1000);
    log_info("Shrink CPU time: %.4f s.", shrink_time);
    log_info("Shrink cnt: %d.", shrink_cnt);
    stringstream ss;
    ss << shrink_stat;
    log_info("Shrink stat: %s.", ss.str().c_str());

    log_info("Sub process CPU time: %.4f s.", sub_process_time);
    log_info("Copy CPU time: %.4f s.", copy_time);
    log_info("Set Intersection time: %.4f s.", set_inter_time);
    stringstream ss2;
    ss2 << tc_stat;
    log_info("TC stat: %s", ss2.str().c_str());
    log_info("Update processed time: %.4f s.", process_update_time);
    log_info("Max mem size: %'lld Bytes.", mem_stat->get_max_use());
}