#include "util/cuda/cuda_util.h"
#include "cuda_extern_functions.cuh"


__global__ void bmp_update_next(uint32_t *d_offsets, int32_t *d_dsts,
                                uint32_t *d_bitmaps, uint32_t *d_bitmap_states,
                                uint32_t *vertex_count, uint32_t conc_blocks_per_SM,
                                eid_t *eid, int32_t *d_intersection_count_GPU,
                                int val_size_bitmap, int val_size_bitmap_indexes,
                                int level, int *next, int *next_cnt, bool *inNext,
                                InBucketWinType *in_bucket_window_, eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
                                int bucket_level_end_
) {
    const uint32_t tid = threadIdx.x + blockDim.x * threadIdx.y; /*threads in a warp are with continuous threadIdx.x */
    const uint32_t tnum = blockDim.x * blockDim.y;
    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/

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
        if (threadIdx.x == 0) {
            auto edge_idx = eid[idx];
            if (private_count < level) {
                private_count = level;
            }
            d_intersection_count_GPU[edge_idx] = private_count;
            if (private_count == level) {
                auto insert_idx = atomicAdd(next_cnt, 1);
                next[insert_idx] = edge_idx;
                inNext[edge_idx] = true;
            }
#ifndef LEGACY_SCAN
            // Update the Bucket.
            auto latest = private_count;
            if (latest > level && latest < bucket_level_end_) {
                auto old_token = atomicCAS(in_bucket_window_ + edge_idx, InBucketFalse, InBucketTrue);
                if (!old_token) {
                    auto insert_idx = atomicAdd(window_bucket_buf_size_, 1);
                    bucket_buf_[insert_idx] = edge_idx;
                }
            }
#endif
        }
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

__global__ void bmp_bsr_update_next(uint32_t *d_offsets, int32_t *d_dsts,
                                    uint32_t *d_bitmaps, uint32_t *d_bitmap_states,
                                    uint32_t *vertex_count, uint32_t conc_blocks_per_SM,
                                    eid_t *eid, int32_t *d_intersection_count_GPU,
                                    int val_size_bitmap, int val_size_bitmap_indexes,
                                    uint32_t *bmp_offs, bmp_word_idx_type *bmp_word_indices, bmp_word_type *bmp_words,
                                    int level, int *next, int *next_cnt, bool *inNext,
                                    InBucketWinType *in_bucket_window_, eid_t *bucket_buf_, uint32_t *window_bucket_buf_size_,
                                    int bucket_level_end_
) {
    const uint32_t tid = threadIdx.x + blockDim.x * threadIdx.y; /*threads in a warp are with continuous threadIdx.x */
    const uint32_t num_threads = blockDim.x * blockDim.y;
    const uint32_t elem_bits = sizeof(uint32_t) * 8; /*#bits in a bitmap element*/

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
        if (threadIdx.x == 0) {
            auto edge_idx = eid[idx];
            auto prev = d_intersection_count_GPU[edge_idx];
            if (prev > level) {
                if (private_count < level) {
                    private_count = level;
                }
                d_intersection_count_GPU[edge_idx] = private_count;
                if (private_count == level) {
                    auto insert_idx = atomicAdd(next_cnt, 1);
                    next[insert_idx] = edge_idx;
                    inNext[edge_idx] = true;
                }
#ifndef LEGACY_SCAN
                // Update the Bucket.
                auto latest = private_count;
                if (latest > level && latest < bucket_level_end_) {
                    auto old_token = atomicCAS(in_bucket_window_ + edge_idx, InBucketFalse, InBucketTrue);
                    if (!old_token) {
                        auto insert_idx = atomicAdd(window_bucket_buf_size_, 1);
                        bucket_buf_[insert_idx] = edge_idx;
                    }
                }
#endif
            }
        }
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
