#pragma once

#include <cassert>

#include "util/cuda/cuda_util.h"
#include "util/graph/graph.h"

#define BITMAP_SCALE_LOG (9)
#define BITMAP_SCALE (1<<BITMAP_SCALE_LOG)  /*#bits in the first-level bitmap indexed by 1 bit in the second-level bitmap*/

#define INT_INVALID  (INT32_MAX)
#define LEVEL_SKIP_SIZE (16)
//#define LEGACY_SCAN
//#define SHRINK_ALL
using bmp_word_idx_type = uint32_t;
using bmp_word_type = uint32_t;

#define INBUCKET_BOOL
#ifndef INBUCKET_BOOL
using InBucketWinType = int;
#define InBucketTrue (1)
#define InBucketFalse (0)
#else
using InBucketWinType = bool;
#define InBucketTrue (true)
#define InBucketFalse (false)
#endif

__inline__ __device__
int get_sm_id() {
    int sm_id;
    asm("mov.u32 %0, %smid;" : "=r"(sm_id));
    return sm_id;
}

static __inline__ __device__ bool atomicCAS(bool *address, bool compare, bool val) {
    unsigned long long addr = (unsigned long long) address;
    unsigned pos = addr & 3;  // byte position within the int
    int *int_addr = (int *) (addr - pos);  // int-aligned address
    int old = *int_addr, assumed, ival;

    do {
        assumed = old;
        if (val)
            ival = old | (1 << (8 * pos));
        else
            ival = old & (~((0xFFU) << (8 * pos)));
        old = atomicCAS(int_addr, assumed, ival);
    } while (assumed != old);

    return (bool) (old & ((0xFFU) << (8 * pos)));
}

__global__ void construct_bsr_row_ptr_per_thread(uint32_t *d_offsets, int32_t *d_dsts,
                                                 uint32_t num_vertices, uint32_t *bmp_offs);

__global__ void construct_bsr_content_per_thread(uint32_t *d_offsets, int32_t *d_dsts,
                                                 uint32_t num_vertices,
                                                 uint32_t *bmp_offs,
                                                 bmp_word_idx_type *bmp_word_indices,
                                                 bmp_word_type *bmp_words);

__global__ void bmp_bsr_update_next(uint32_t *d_offsets, int32_t *d_dsts,
                                    uint32_t *d_bitmaps, uint32_t *d_bitmap_states,
                                    uint32_t *vertex_count, uint32_t conc_blocks_per_SM,
                                    eid_t *eid, int32_t *d_intersection_count_GPU,
                                    int val_size_bitmap, int val_size_bitmap_indexes,
                                    uint32_t *bmp_offs, bmp_word_idx_type *bmp_word_indices, bmp_word_type *bmp_words,
                                    int level, int *next, int *next_cnt, bool *inNext,
                                    InBucketWinType *in_bucket_window_, eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
                                    int bucket_level_end_);

__global__ void bmp_update_next(uint32_t *d_offsets, int32_t *d_dsts,
                                uint32_t *d_bitmaps, uint32_t *d_bitmap_states,
                                uint32_t *vertex_count, uint32_t conc_blocks_per_SM,
                                eid_t *eid, int32_t *d_intersection_count_GPU,
                                int val_size_bitmap, int val_size_bitmap_indexes,
                                int level, int *next, int *next_cnt, bool *inNext,
                                InBucketWinType *in_bucket_window_, eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
                                int bucket_level_end_);

struct CUDAContext {
    uint32_t max_threads_per_SM;
    uint32_t num_SMs;
    uint32_t shared_mem_size_per_block;
    uint32_t shared_mem_size_per_sm;

    CUDAContext() {
        /*get the maximal number of threads in an SM*/
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, 0); /*currently 0th device*/
        max_threads_per_SM = prop.maxThreadsPerMultiProcessor;
        log_info("Shared MemPerBlock: %zu, PerSM: %zu", prop.sharedMemPerBlock, prop.sharedMemPerMultiprocessor);
        shared_mem_size_per_block = prop.sharedMemPerBlock;
        shared_mem_size_per_sm = prop.sharedMemPerMultiprocessor;
        num_SMs = prop.multiProcessorCount;
    }

    uint32_t GetConCBlocks(uint32_t block_size) {
        auto conc_blocks_per_SM = max_threads_per_SM / block_size; /*assume regs are not limited*/
        log_info("#SMs: %d, con blocks/SM: %d", num_SMs, conc_blocks_per_SM);
        return conc_blocks_per_SM;
    }
};

struct CUDA_Edge {
    vid_t u;
    vid_t v;

    __host__ __device__
    CUDA_Edge() {
        this->u = 0;
        this->v = 0;
    }

    __host__ __device__
    CUDA_Edge(vid_t u, vid_t v) {
        this->u = u;
        this->v = v;
    }
};

extern void invoke_tc_bmp_gpu(graph_t *g, int *edge_sup);

int TrussDecompositionLevelsCPU(graph_t &g, int *&EdgeSupport, Edge *&edgeIdToEdge,
                                eid_t *&level_start_pos, eid_t *&edge_offsets_level, eid_t *&edge_off_org,
                                int *&edge_sup, Edge *&edge_lst);

void PKT_Shrink_all(
        graph_t &g, bool *&processed,
        int *&EdgeSupport, eid_t *&edge_offset_origin, CUDA_Edge *&edge_list,
        int *&new_EdgeSupport, eid_t *&new_edge_offset_origin, CUDA_Edge *&new_edge_list,
        bool *&reversed_processed, bool *&edge_deleted, eid_t *&scanned_processed,
        eid_t *&new_offset, eid_t *&new_eid, vid_t *&new_adj,
        InBucketWinType *&in_bucket_window_, eid_t *&bucket_buf_, eid_t *&new_bucket_buf_, uint32_t &window_bucket_buf_size_,
        uint32_t old_edge_num, uint32_t new_edge_num,
        ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat);

void ShrinkCSREid(
        graph_t &g, bool *&processed,
        int *&EdgeSupport, eid_t *&edge_offset_origin, CUDA_Edge *&edge_list,
        int *&new_EdgeSupport, eid_t *&new_edge_offset_origin, CUDA_Edge *&new_edge_list,
        bool *&reversed_processed, bool *&edge_deleted, eid_t *&scanned_processed,
        eid_t *&new_offset, eid_t *&new_eid, vid_t *&new_adj,
        InBucketWinType *&in_bucket_window_, eid_t *&bucket_buf_, eid_t *&new_bucket_buf_, uint32_t &window_bucket_buf_size_,
        uint32_t old_edge_num, uint32_t new_edge_num,
        ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat);

template<typename T>
__host__ __device__
void swap_ele(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename NeedleType, typename HaystackType>
__device__
int binary_search(
        NeedleType needle, HaystackType *haystacks,
        int hay_begin, int hay_end) {
    while (hay_begin <= hay_end) {
        int middle = hay_begin + (hay_end - hay_begin) / 2;
        if (needle > haystacks[middle])
            hay_begin = middle + 1;
        else if (needle < haystacks[middle])
            hay_end = middle - 1;
        else
            return middle;
    }
    return INT_INVALID;  //not found
}

__device__
inline int binary_search_eid(
        CUDA_Edge needle, CUDA_Edge *haystacks,
        int hay_begin, int hay_end) {
    while (hay_begin <= hay_end) {
        int middle = hay_begin + (hay_end - hay_begin) / 2;
        if ((needle.u > haystacks[middle].u) ||
            (needle.u == haystacks[middle].u && needle.v > haystacks[middle].v))
            hay_begin = middle + 1;
        else if ((needle.u < haystacks[middle].u) ||
                 (needle.u == haystacks[middle].u && needle.v < haystacks[middle].v))
            hay_end = middle - 1;
        else
            return middle;
    }
    assert(0);
    return -1;
}

template<typename DataType, typename CntType>
__global__
void filter(DataType *data, CntType count, bool *flags, DataType ref) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) flags[gtid] = (data[gtid] == ref);
}

template<typename DataType, typename CntType>
__global__
void filter_not_processed(DataType *data, CntType count, bool *flags, bool *processed) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) flags[gtid] = !processed[data[gtid]];
}

template<typename IndexType, typename DataType, typename CntType>
__global__
void random_access_set(IndexType *index, CntType count, DataType *random_ptr, DataType ref) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) random_ptr[index[gtid]] = ref;
}

template<typename DataType, typename CntType>
__global__
void init_asc(DataType *data, CntType count) {
    auto gtid = threadIdx.x + blockIdx.x * blockDim.x;
    if (gtid < count) data[gtid] = (DataType) gtid;
}

/*check whether the CSR and edge list still match*/
inline void check_CSR(graph_t *g, CUDA_Edge *edge_list) {
    for (uint32_t u = 0; u < g->n; u++) {
        auto range_start = g->num_edges[u];
        auto range_end = g->num_edges[u + 1];
        for (int v_idx = range_start; v_idx < range_end; v_idx++) {
            auto v = g->adj[v_idx];
            auto small_vertex = (u < v) ? u : v;
            auto large_vertex = (u < v) ? v : u;

            auto edge_idx = g->eid[v_idx];
            CUDA_Edge target = edge_list[edge_idx];
            if (target.u != small_vertex || target.v != large_vertex) {
                log_error("CSR and edge_list do not match");
                log_error("CSR: (%d, %d) is directed to edge_list[%d] (%d, %d).", u, v, edge_idx, target.u, target.v);
                exit(1);
            }
        }
    }
    log_info("The CSR passes!!!");
}

inline void InitBMP(graph_t *g, uint32_t *&d_bitmaps, uint32_t *&d_bitmap_states, uint32_t *&d_vertex_count,
                    ZLCUDAMemStat *mem_stat = nullptr) {
    CUDAContext context;
    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/
    const uint32_t num_words_bmp = (g->n + elem_bits - 1) / elem_bits;

    auto num_SMs = context.num_SMs;
    auto conc_blocks_per_SM = context.GetConCBlocks(1024);

    /*initialize the bitmaps*/
    ZLCudaMalloc((void **) &d_bitmaps, conc_blocks_per_SM * num_SMs * num_words_bmp * sizeof(uint32_t), mem_stat);
    cudaMemset(d_bitmaps, 0, conc_blocks_per_SM * num_SMs * num_words_bmp * sizeof(uint32_t));

    /*initialize the bitmap states*/
    ZLCudaMalloc((void **) &d_bitmap_states, num_SMs * conc_blocks_per_SM * sizeof(uint32_t), mem_stat);
    cudaMemset(d_bitmap_states, 0, num_SMs * conc_blocks_per_SM * sizeof(uint32_t));

    /*vertex count for sequential block execution*/
    ZLCudaMalloc((void **) &d_vertex_count, sizeof(uint32_t), mem_stat);
    cudaMemset(d_vertex_count, 0, sizeof(uint32_t));
}