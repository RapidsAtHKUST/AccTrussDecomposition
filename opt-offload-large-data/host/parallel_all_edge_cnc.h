#pragma once

#include <mutex>

#include "libpopcnt.h"

#include <util/search/search_util.h>
#include <util/serialization/pretty_print.h>
#include <util/timer.h>
#include <util/lemire/EWAHBoolArray/headers/boolarray.h>

inline int FindSrc(graph_t *g, int u, uint32_t edge_idx) {
    if (edge_idx >= g->num_edges[u + 1]) {
        // update last_u, preferring galloping instead of binary search because not large range here
        u = GallopingSearch(g->num_edges, static_cast<uint32_t>(u) + 1, g->n + 1, edge_idx);
        // 1) first > , 2) has neighbor
        if (g->num_edges[u] > edge_idx) {
            while (g->num_edges[u] - g->num_edges[u - 1] == 0) { u--; }
            u--;
        } else {
            // g->num_edges[u] == i
            while (g->num_edges[u + 1] - g->num_edges[u] == 0) {
                u++;
            }
        }
    }
    return u;
}

using bmp_word_type = uint64_t;
static constexpr uint32_t word_in_bits = sizeof(bmp_word_type) * 8;

template<typename T, typename P, typename B>
void PackVertex(graph_t *g, P &partition_id_lst,
                B &bitmap_in_partition_lst, int u, T &packed_num) {
    auto prev_blk_id = -1;
    auto num_blks = 0;
    auto pack_num_u = 0;
    for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
        auto v = g->adj[off];
        auto cur_blk_id = v / word_in_bits;
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
        for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
            auto v = g->adj[off];
            auto cur_blk_id = v / word_in_bits;
            if (cur_blk_id == prev_blk_id) {
                pack_num_u++;
            } else {
                prev_blk_id = cur_blk_id;
                num_blks++;
                partition_id_lst[u].emplace_back(cur_blk_id);
                bitmap_in_partition_lst[u].emplace_back(0);
            }
            bitmap_in_partition_lst[u].back() |= static_cast<bmp_word_type>(1u) << (v % word_in_bits);
        }
    }
}

template<typename P, typename B>
inline int ComputeSupportWithPack(graph_t *g, int *EdgeSupport, size_t &tc_cnt, uint32_t i,
                                  BoolArray<bmp_word_type> &bool_arr, P &partition_id_lst,
                                  B &bitmap_in_partition_lst) {
    static thread_local auto last_u = -1;
    static thread_local auto u = 0;
    u = FindSrc(g, u, i);
#ifdef RANGE_FILTERING
    static thread_local int min_ele = -1;
    static thread_local int max_ele = -1;
    static thread_local int range_gap = -1;
    constexpr uint32_t max_range_bits = 1024 * 32 * 8;
    static thread_local auto range_idx_arr = BoolArray<bmp_word_type>(max_range_bits);
#endif

    if (last_u != u) {
        // Clear.
        if (last_u != -1) {
            for (auto offset = g->num_edges[last_u]; offset < g->num_edges[last_u + 1]; offset++) {
                auto v = g->adj[offset];
                bool_arr.setWord(v / word_in_bits, 0);
            }
#ifdef RANGE_FILTERING
            range_idx_arr.reset();
#endif
        }
        // Set.
#ifdef RANGE_FILTERING
        min_ele = g->adj[g->num_edges[u]];
        max_ele = g->adj[g->num_edges[u + 1] - 1] + 1;
        range_gap = (max_ele - min_ele) / max_range_bits + 1;
#endif
        for (auto offset = g->num_edges[u]; offset < g->num_edges[u + 1]; offset++) {
            auto v = g->adj[offset];
#ifdef RANGE_FILTERING
            range_idx_arr.set((v - min_ele) / range_gap);
#endif
            bool_arr.set(v);
        }
        last_u = u;
    }

    auto v = g->adj[i];
    auto du = g->num_edges[u + 1] - g->num_edges[u];
    auto dv = g->num_edges[v + 1] - g->num_edges[v];
    auto local_cnt = 0;

    if (du > dv || ((du == dv) && (u < v))) {
        if (!partition_id_lst[v].empty()) {
            for (auto wi = 0; wi < partition_id_lst[v].size(); wi++) {
                auto res = bool_arr.getWord(partition_id_lst[v][wi]) & bitmap_in_partition_lst[v][wi];
                local_cnt += popcnt(&res, sizeof(bmp_word_type));
            }
        } else {
#ifdef RANGE_FILTERING
            auto off_beg = LinearSearch(g->adj, g->num_edges[v], g->num_edges[v + 1], min_ele);
            for (auto off = off_beg; off < g->num_edges[v + 1]; off++) {
                auto w = g->adj[off];
                if (w >= max_ele) {
                    break;
                }
                if (range_idx_arr.get((w - min_ele) / range_gap)) {
                    if (bool_arr.get(w))
                        local_cnt++;
                }
            }
#else
            for (auto off = g->num_edges[v]; off < g->num_edges[v + 1]; off++) {
                auto w = g->adj[off];
                if (bool_arr.get(w))
                    local_cnt++;
            }
#endif
        }

        // Symmetrically Assign.
        if (local_cnt > 0) {
            EdgeSupport[g->eid[i]] = local_cnt;
            tc_cnt += local_cnt;
        }
    }
    return local_cnt;
}