#include "util/cuda/cuda_util.h"
#include "cuda_extern_functions.cuh"

__global__ void construct_bsr_row_ptr_per_thread(uint32_t *d_offsets, int32_t *d_dsts,
                                                 uint32_t num_vertices, uint32_t *bmp_offs) {
    uint32_t u = blockIdx.x * blockDim.x + threadIdx.x;
    if (u >= num_vertices) return;

    constexpr int word_in_bits = sizeof(uint32_t) * 8;
    auto prev_blk_id = -1;
    auto num_blks = 0;
    for (auto off = d_offsets[u]; off < d_offsets[u + 1]; off++) {
        auto v = d_dsts[off];
        int cur_blk_id = v / word_in_bits;
        if (cur_blk_id != prev_blk_id) {
            prev_blk_id = cur_blk_id;
            num_blks++;
        }
    }
    if ((d_offsets[u + 1] - d_offsets[u]) >= 16 && (d_offsets[u + 1] - d_offsets[u]) / num_blks > 2) {
        bmp_offs[u] = num_blks;
    } else {
        bmp_offs[u] = 0;
    }
}

__global__ void construct_bsr_content_per_thread(uint32_t *d_offsets, int32_t *d_dsts, uint32_t num_vertices,
                                                 uint32_t *bmp_offs, bmp_word_idx_type *bmp_word_indices,
                                                 bmp_word_type *bmp_words) {
    uint32_t u = blockIdx.x * blockDim.x + threadIdx.x;
    if (u >= num_vertices) return;

    auto size = bmp_offs[u + 1] - bmp_offs[u];
    if (size == 0) return;

    auto curr_size = 0;
    auto write_off = bmp_offs[u];
    auto bmp_word_idx_ptr = bmp_word_indices + write_off;
    auto bmp_words_ptr = bmp_words + write_off;
    auto prev_blk_id = -1;
    constexpr int word_in_bits = sizeof(uint32_t) * 8;
    for (auto off = d_offsets[u]; off < d_offsets[u + 1]; off++) {
        auto v = d_dsts[off];
        int cur_blk_id = v / word_in_bits;
        if (cur_blk_id != prev_blk_id) {
            prev_blk_id = cur_blk_id;
            bmp_words_ptr[curr_size] = 0;
            bmp_word_idx_ptr[curr_size++] = cur_blk_id;
        }
        bmp_words_ptr[curr_size - 1] |= static_cast<bmp_word_type>(1u) << (v % word_in_bits);
    }
}