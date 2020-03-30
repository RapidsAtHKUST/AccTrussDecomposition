#pragma once

#include <cassert>

#include <omp.h>

#include "util/graph.h"
#include "util/timer.h"
#include "primitives.h"
#include "cuda_extern_functions.cuh"

template<typename T, typename P, typename B>
void PackVertexCPU(graph_t *g, P &partition_id_lst, B &bitmap_in_partition_lst, int u, T &packed_num, T &block_num) {
    constexpr uint32_t word_in_bits = sizeof(bmp_word_type) * 8;

    auto prev_blk_id = -1;
    auto num_blks = 0;
    auto pack_num_u = 0;
    for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
        auto v = g->adj[off];
        int cur_blk_id = v / word_in_bits;
        if (cur_blk_id == prev_blk_id) {
            pack_num_u++;
        } else {
            prev_blk_id = cur_blk_id;
            num_blks++;
        }
    }

    prev_blk_id = -1;
    if ((g->num_edges[u + 1] - g->num_edges[u]) >= 16 && (g->num_edges[u + 1] - g->num_edges[u]) / num_blks > 2) {
        packed_num++;
        block_num += num_blks;
        for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
            auto v = g->adj[off];
            int cur_blk_id = v / word_in_bits;
            if (cur_blk_id == prev_blk_id) {
                pack_num_u++;
            } else {
                prev_blk_id = cur_blk_id;
                partition_id_lst[u].emplace_back(cur_blk_id);
                bitmap_in_partition_lst[u].emplace_back(0);
            }
            bitmap_in_partition_lst[u].back() |= static_cast<bmp_word_type>(1u) << (v % word_in_bits);
        }
    }
}

inline void ConstructBSRsCPU(graph_t *g, uint32_t *&bmp_offs,
                             bmp_word_idx_type *&bmp_word_indices, bmp_word_type *&bmp_words,
                             ZLCUDAMemStat &mem_stat, ZLCUDATimer &time_stat) {
    Timer pack_timer;
    size_t packed_vertex_num = 0;
    size_t word_num = 0;
    auto partition_id_lst = vector<vector<uint32_t>>(g->n);
    auto bitmap_in_partition_lst = vector<vector<bmp_word_type >>(g->n);
    ZLCudaMalloc(&bmp_offs, sizeof(uint32_t) * (g->n + 1), &mem_stat);
    memset(bmp_offs, 0, sizeof(uint32_t) * (g->n + 1));
    log_info("Init Memory Time: %.9lfs", pack_timer.elapsed());

    auto max_omp_threads = omp_get_max_threads();
    vector<uint32_t> histogram(CACHE_LINE_ENTRY * max_omp_threads);
#pragma omp parallel num_threads(max_omp_threads)
    {
#pragma omp for schedule(dynamic, 100) reduction(+:packed_vertex_num) reduction(+:word_num)
        for (auto u = 0; u < g->n; u++) {
            PackVertexCPU(g, partition_id_lst, bitmap_in_partition_lst, u, packed_vertex_num, word_num);
        }
        InclusivePrefixSumOMP(histogram, bmp_offs + 1, g->n, [&partition_id_lst](uint32_t it) {
            return partition_id_lst[it].size();
        }, max_omp_threads);
#pragma omp single
        {
            assert(bmp_offs[g->n] == word_num);
            log_info("#of Blocks: %'zu; #of Packed Vertices: %'zu", word_num, packed_vertex_num);
            ZLCudaMalloc(&bmp_word_indices, sizeof(bmp_word_idx_type) * word_num, &mem_stat);
            ZLCudaMalloc(&bmp_words, sizeof(bmp_word_type) * word_num, &mem_stat);
        }
        // Scatter values to BSR arrays.
#pragma omp for schedule(dynamic, 100)
        for (auto u = 0; u < g->n; u++) {
            auto size = bmp_offs[u + 1] - bmp_offs[u];
            if (size > 0) {
                memcpy(bmp_word_indices + bmp_offs[u], &partition_id_lst[u].front(), sizeof(bmp_word_idx_type) * size);
                memcpy(bmp_words + bmp_offs[u], &bitmap_in_partition_lst[u].front(), sizeof(bmp_word_type) * size);
            }
        }
    }
    log_info("Packing Time: %.9lfs", pack_timer.elapsed_and_reset());
}