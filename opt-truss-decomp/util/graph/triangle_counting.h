#pragma once

#include "util/containers/boolarray.h"
#include "util/graph/graph.h"
#include "util/libpopcnt.h"
#include "util/intersection/set_inter_cnt_utils.h"

#define MAX_PACK_NUM (32768)
#define FIRST_RANGE_SIZE (32768)
using row_ptr_t = uint32_t;

template<typename OFF, typename WI, typename WC>
void PackWords(graph_t &g, OFF *row_ptrs_beg, int to_pack_num, vector<vector<WI>> &word_indexes,
               vector<vector<WC>> &words, Timer &tc_timer) {
    constexpr int word_in_bits = sizeof(WC) * 8;
    // Construct Words for Range [0, 32768), at most 512 words (given each word 64 bits)
#pragma omp for schedule(dynamic, 100)
    for (auto u = 0u; u < to_pack_num; u++) {
        auto prev_blk_id = -1;
        for (auto off = g.num_edges[u]; off < row_ptrs_beg[u]; off++) {
            auto v = g.adj[off];
            int cur_blk_id = v / word_in_bits;
            if (cur_blk_id != prev_blk_id) {
                prev_blk_id = cur_blk_id;
                word_indexes[u].emplace_back(cur_blk_id);
                words[u].emplace_back(0);
            }
            words[u].back() |= static_cast<WC>(1u) << (v % word_in_bits);
        }
    }
#pragma omp single
    {
        log_info("Finish Indexing: %.9lfs", tc_timer.elapsed());
    }
}

inline size_t CountTriBMPAndMergeWithPackDODG(graph_t &g, int max_omp_threads) {
    Timer tc_timer;
    int max_d = 0;
    size_t tc_cnt = 0;
    auto *row_ptrs_beg = (row_ptr_t *) malloc(sizeof(row_ptr_t) * (g.n + 1));

    auto *row_ptrs_end = g.num_edges;
    using word_t = uint64_t;
    constexpr int word_in_bits = sizeof(word_t) * 8;

    int to_pack_num = min<int>(g.n, MAX_PACK_NUM);
    vector<vector<uint16_t>> word_indexes(to_pack_num);   // MAX_PACK_NUM * bits-sizeof(word)
    vector<vector<word_t>> words(to_pack_num);

#pragma omp parallel num_threads(max_omp_threads)
    {
#pragma omp for reduction(max: max_d)
        for (auto u = 0u; u < g.n; u++) {
            row_ptrs_beg[u] = lower_bound(g.adj + g.num_edges[u], g.adj + g.num_edges[u + 1],
                                          min<int>(FIRST_RANGE_SIZE, g.n)) - g.adj;
            max_d = max<int>(max_d, g.num_edges[u + 1] - g.num_edges[u]);
        }
#pragma omp single
        {
            if (to_pack_num > 0) {
                log_info("Stop Deg at [%d, %d]", g.num_edges[1] - g.num_edges[0],
                         g.num_edges[to_pack_num] - g.num_edges[to_pack_num - 1]);
            }
            log_info("finish init row_ptrs_end, max d: %d, time: %.9lfs", max_d, tc_timer.elapsed());
        }

        PackWords(g, row_ptrs_beg, to_pack_num, word_indexes, words, tc_timer);

#pragma omp for schedule(dynamic, 100) reduction(+:tc_cnt)
        for (auto u = 0u; u < g.n; u++) {
            static thread_local BoolArray<word_t> bitmap(FIRST_RANGE_SIZE);
            static thread_local vector<word_t> buffer(FIRST_RANGE_SIZE / word_in_bits);
            //  Index for First Range.
            if (g.num_edges[u] < row_ptrs_beg[u]) {
                if (u < to_pack_num) {
                    for (size_t i = 0; i < word_indexes[u].size(); i++) {
                        bitmap.setWord(word_indexes[u][i], words[u][i]);
                    }
                } else {
                    for (auto off = g.num_edges[u]; off < row_ptrs_beg[u]; off++) {
                        auto w = g.adj[off];
                        bitmap.set(w);
                    }
                }
            }
            auto du = row_ptrs_end[u + 1] - row_ptrs_beg[u];

            for (auto edge_idx = g.num_edges[u]; edge_idx < row_ptrs_end[u + 1]; edge_idx++) {
                auto v = g.adj[edge_idx];
                auto cn_count = 0;
                // First Range.
                if (g.num_edges[u] < row_ptrs_beg[u]) {
                    if (v < to_pack_num) {
                        auto num_words_v = word_indexes[v].size();
                        for (size_t i = 0; i < num_words_v; i++) {
                            buffer[i] = bitmap.getWord(word_indexes[v][i]);
                        }
                        for (size_t i = 0; i < num_words_v; i++) {
                            buffer[i] &= words[v][i];
                        }
                        cn_count += popcnt(&buffer.front(), sizeof(word_t) * num_words_v);
                    } else {
                        if (g.num_edges[v] < row_ptrs_beg[v]) {
                            cn_count += SetInterCntVecMerge(&g, g.num_edges[u], row_ptrs_beg[u], g.num_edges[v],
                                                            row_ptrs_beg[v]);
                        }
                    }
                }

                // Second Range.
                auto dv = row_ptrs_end[v + 1] - row_ptrs_beg[v];
                if (du > 0 && dv > 0) {
                    cn_count += SetInterCntVecMerge(&g, row_ptrs_beg[u], row_ptrs_end[u + 1],
                                                    row_ptrs_beg[v], row_ptrs_end[v + 1]);
                }
                tc_cnt += cn_count;
            }

            // Clear the Index.
            if (g.num_edges[u] < row_ptrs_beg[u]) {
                bitmap.reset();
            }
        }
    }
    free(row_ptrs_beg);
    log_info("Forward cost: %.3lf s, Mem Usage: %d KB", tc_timer.elapsed(), getValue());
    log_info("Triangle Cnt: %'zu", tc_cnt);
    return tc_cnt;
}

inline size_t CountTriBMPAndMergeWithPack(graph_t &g, int max_omp_threads) {
    Timer tc_timer;
    int max_d = 0;
    size_t tc_cnt = 0;
    auto *row_ptrs_end = (row_ptr_t *) malloc(sizeof(row_ptr_t) * (g.n + 1));
    auto *row_ptrs_beg = (row_ptr_t *) malloc(sizeof(row_ptr_t) * (g.n + 1));
    size_t workload = 0;
    size_t workload_large_deg = 0;
    size_t workload_bmp = 0;

    using word_t = uint64_t;
    constexpr int word_in_bits = sizeof(word_t) * 8;

    int to_pack_num = min<int>(g.n, MAX_PACK_NUM);
    vector<vector<uint16_t>> word_indexes(to_pack_num);   // MAX_PACK_NUM * bits-sizeof(word)
    vector<vector<word_t>> words(to_pack_num);

#pragma omp parallel num_threads(max_omp_threads)
    {
#pragma omp for reduction(max: max_d)
        for (auto u = 0u; u < g.n; u++) {
            row_ptrs_end[u + 1] = lower_bound(g.adj + g.num_edges[u], g.adj + g.num_edges[u + 1], u) - g.adj;
            row_ptrs_beg[u] = lower_bound(g.adj + g.num_edges[u], g.adj + g.num_edges[u + 1],
                                          min<int>(FIRST_RANGE_SIZE, u)) - g.adj;
            max_d = max<int>(max_d, row_ptrs_end[u + 1] - g.num_edges[u]);
        }
#pragma omp single
        {
            log_info("Stop Deg at [%d, %d]", g.num_edges[1] - g.num_edges[0],
                     g.num_edges[to_pack_num] - g.num_edges[to_pack_num - 1]);
            log_info("finish init row_ptrs_end, max d: %d, time: %.9lfs", max_d, tc_timer.elapsed());
        }

        PackWords(g, row_ptrs_beg, to_pack_num, word_indexes, words, tc_timer);

#pragma omp for schedule(dynamic, 100) reduction(+:tc_cnt) reduction(+:workload)  reduction(+:workload_large_deg) \
reduction(+:workload_bmp)
        for (auto u = 0u; u < g.n; u++) {
            static thread_local BoolArray<word_t> bitmap(FIRST_RANGE_SIZE);
            static thread_local vector<word_t> buffer(FIRST_RANGE_SIZE / word_in_bits);
            //  Index for First Range.
            if (g.num_edges[u] < row_ptrs_beg[u]) {
                if (u < to_pack_num) {
                    for (size_t i = 0; i < word_indexes[u].size(); i++) {
                        bitmap.setWord(word_indexes[u][i], words[u][i]);
                    }
                } else {
                    for (auto off = g.num_edges[u]; off < row_ptrs_beg[u]; off++) {
                        auto w = g.adj[off];
                        bitmap.set(w);
                    }
                }
            }
            auto du = row_ptrs_end[u + 1] - row_ptrs_beg[u];

            for (auto edge_idx = g.num_edges[u]; edge_idx < row_ptrs_end[u + 1]; edge_idx++) {
                auto v = g.adj[edge_idx];
                auto cn_count = 0;
                // First Range.
                if (g.num_edges[u] < row_ptrs_beg[u]) {
                    if (v < to_pack_num) {
                        auto num_words_v = word_indexes[v].size();
                        for (size_t i = 0; i < num_words_v; i++) {
#ifdef WORKLOAD_STAT
                            workload++;
                            workload_bmp++;
                            workload_large_deg++;
#endif
                            buffer[i] = bitmap.getWord(word_indexes[v][i]);
                        }
                        for (size_t i = 0; i < num_words_v; i++) {
                            buffer[i] &= words[v][i];
                        }
                        cn_count += popcnt(&buffer.front(), sizeof(word_t) * num_words_v);
                    } else {
#ifdef WORKLOAD_STAT
                        auto dv = row_ptrs_beg[v] - g.num_edges[v];
                        workload += du + dv;
                        workload_large_deg += du + dv;
#endif
                        if (g.num_edges[v] < row_ptrs_beg[v]) {
                            cn_count += SetInterCntVecMerge(&g, g.num_edges[u], row_ptrs_beg[u], g.num_edges[v],
                                                            row_ptrs_beg[v]);
                        }
                    }
                }

                // Second Range.
                auto dv = row_ptrs_end[v + 1] - row_ptrs_beg[v];
                if (du > 0 && dv > 0) {
#ifdef WORKLOAD_STAT
                    workload += du + dv;
#endif
                    cn_count += SetInterCntVecMerge(&g, row_ptrs_beg[u], row_ptrs_end[u + 1],
                                                    row_ptrs_beg[v], row_ptrs_end[v + 1]);
                }
                tc_cnt += cn_count;
            }

            // Clear the Index.
            if (g.num_edges[u] < row_ptrs_beg[u]) {
                bitmap.reset();
            }
        }
    }
    free(row_ptrs_beg);
    free(row_ptrs_end);
    log_info("Forward cost: %.3lf s, Mem Usage: %d KB", tc_timer.elapsed(), getValue());
    log_info("Triangle Cnt: %'zu", tc_cnt);
#ifdef WORKLOAD_STAT
    log_info("Workload: %s, avg: %s", FormatWithCommas(workload).c_str(),
             FormatWithCommas(workload / (g.m / 2)).c_str());
    log_info("Workload (large-deg vid in [0, %d]): %s, BMP: %s, avg: %s", FIRST_RANGE_SIZE,
             FormatWithCommas(workload_large_deg).c_str(),
             FormatWithCommas(workload_bmp).c_str(),
             FormatWithCommas(workload_large_deg / (g.m / 2)).c_str());
#endif
    return tc_cnt;
}


inline size_t CountTriMergeDODG(graph_t &g, int max_omp_threads) {
    Timer tc_timer;
    int max_d = 0;
    size_t tc_cnt = 0;

#pragma omp parallel num_threads(max_omp_threads)
    {
#pragma omp for reduction(max: max_d)
        for (auto u = 0u; u < g.n; u++) {
            max_d = max<int>(max_d, g.num_edges[u + 1] - g.num_edges[u]);
        }
#pragma omp single
        {
            log_info("finish init row_ptrs_end, max d: %d, time: %.9lfs", max_d, tc_timer.elapsed());
        }
#pragma omp for schedule(dynamic, 100) reduction(+:tc_cnt)
        for (auto u = 0u; u < g.n; u++) {
            //  Index for First Range.
            for (auto edge_idx = g.num_edges[u]; edge_idx < g.num_edges[u + 1]; edge_idx++) {
                auto v = g.adj[edge_idx];
                tc_cnt += SetInterLookup(&g, g.num_edges[u], g.num_edges[u + 1],
                                                         g.num_edges[v], g.num_edges[v + 1]);
            }
        }
    }
    log_info("Forward Cost: %.9lfs", tc_timer.elapsed());
    return tc_cnt;
}



