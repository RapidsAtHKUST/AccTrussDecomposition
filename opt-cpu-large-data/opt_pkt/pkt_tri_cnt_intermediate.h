#pragma once

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/util.h"
#include "util/timer.h"
#include "util/stat.h"
#include "util/containers/boolarray.h"
#include "iter_helper.h"

inline int ComputeCNGallopingSingleDir(graph_t *g, uint32_t off_nei_u, uint32_t off_u_end,
                                       uint32_t off_nei_v, uint32_t off_v_end) {
    auto cn_count = 0;
    if (off_u_end - off_nei_u > off_v_end - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(off_u_end, off_v_end);
    }
    if (off_nei_u >= off_u_end) {
        return cn_count;
    }
    while (true) {
        while (g->adj[off_nei_u] < g->adj[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        off_nei_v = GallopingSearch(g->adj, off_nei_v, off_v_end, g->adj[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

template<typename P, typename B>
void PackVertexIntermediate(graph_t *g, const eid_t *off_end,
                            P &partition_id_lst, B &bitmap_in_partition_lst, int u) {
    auto prev_blk_id = -1;
    auto num_blks = 0;
    auto pack_num_u = 0;
    for (auto off = g->num_edges[u]; off < off_end[u + 1]; off++) {
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
    partition_id_lst[u].clear();
    bitmap_in_partition_lst[u].clear();
    if ((off_end[u + 1] - g->num_edges[u]) >= 16 && (off_end[u + 1] - g->num_edges[u]) / num_blks > 2) {
        // Need to clear first.
        for (auto off = g->num_edges[u]; off < off_end[u + 1]; off++) {
            auto v = g->adj[off];
            int cur_blk_id = v / word_in_bits;
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
inline int ComputeSupportWithPackIntermediate(graph_t *g, const eid_t *off_end, int *EdgeSupport, uint32_t i,
                                              BoolArray<bmp_word_type> &bool_arr,
                                              P &partition_id_lst, B &bitmap_in_partition_lst,
                                              LocalWriteBuffer<eid_t, long> &local_write_buffer,
                                              LocalWriteBuffer<eid_t, size_t> &local_bucket_buffer,
#ifndef BMP_QUEUE
        bool *InNext,
#else
                                              BoolArray<word_type> &InNext,
#endif
                                              int level, int bucket_level_end, bool *in_bucket_window,
                                              IterHelper &iter_helper, int &last_u, int &u) {
    u = FindSrc(g, u, i);
    if (i >= off_end[u + 1])return 0;
    if (last_u != u) {
        // Clear.
        if (last_u != -1) {
            for (auto offset = g->num_edges[last_u]; offset < off_end[last_u + 1]; offset++) {
                auto v = g->adj[offset];
                bool_arr.setWord(v / word_in_bits, 0);
            }
        }
        // Set.
        for (auto offset = g->num_edges[u]; offset < off_end[u + 1]; offset++) {
            auto v = g->adj[offset];
            bool_arr.set(v);
        }
        last_u = u;
    }

    auto v = g->adj[i];
    auto du = off_end[u + 1] - g->num_edges[u];
    auto dv = off_end[v + 1] - g->num_edges[v];
    auto local_cnt = 0;
    auto eid = g->eid[i];

    auto &edge_sup_ref = EdgeSupport[eid];

#ifndef BMP_QUEUE
    assert(edge_sup_ref > level || iter_helper.in_next_[eid]);
#else
    assert(edge_sup_ref > level || iter_helper.in_next_.get(eid));
#endif
    if (edge_sup_ref > level) {
        if (du > dv || ((du == dv) && (u < v))) {
            if (!partition_id_lst[v].empty()) {
                for (auto wi = 0u; wi < partition_id_lst[v].size(); wi++) {
                    auto res = bool_arr.getWord(partition_id_lst[v][wi]) & bitmap_in_partition_lst[v][wi];
                    local_cnt += popcnt(&res, sizeof(bmp_word_type));
                }
            } else {
                for (auto off = g->num_edges[v]; off < off_end[v + 1]; off++) {
                    auto w = g->adj[off];
                    if (bool_arr.get(w))
                        local_cnt++;
                }
            }

            if (local_cnt < level) {
                local_cnt = level;
            }

            // Update Queue and Bucket.
            if (local_cnt != edge_sup_ref) {
                if (local_cnt == level) {
                    // add to queue.
                    local_write_buffer.push(eid);
#ifndef BMP_QUEUE
                    InNext[eid] = true;
#else
                    InNext.set_atomic(eid);
#endif
                } else if (local_cnt > level && local_cnt < bucket_level_end) {
                    // add to bucket if possible
                    bool get_token = __sync_bool_compare_and_swap(&in_bucket_window[eid], false, true);
                    if (get_token) {
                        local_bucket_buffer.push(eid);
                    }
                }
                edge_sup_ref = local_cnt;
            }
        }
    }
    return local_cnt;
}
