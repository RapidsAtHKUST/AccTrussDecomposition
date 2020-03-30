#pragma once

#include <mutex>

#include "libpopcnt.h"

#include "util/search/search_util.h"
#include "util/intersection/intersection_util.h"
#include "util/serialization/pretty_print.h"
#include "util/timer.h"
#include "util/util.h"
#include "util/containers/boolarray.h"
#include "util/intersection/set_inter_cnt_utils.h"
#include "util/containers/radix_hash_map.h"

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

inline MapType Convert(graph_t *g, Edge *edgeIdToEdge, size_t size) {
    MapType edgeToIdMap(g->n);

    auto *mutex_arr = new mutex[g->n];
#pragma omp parallel for
    for (long i = 0; i < g->m; i++) {
        static thread_local auto u = 0;
        u = FindSrc(g, u, i);
        auto v = g->adj[i];
        {
            std::unique_lock<std::mutex> lLock{mutex_arr[u]};
            edgeToIdMap[u].emplace(v, g->eid[i]);
        }
    }

    delete[]mutex_arr;
    return edgeToIdMap;
}


using bmp_word_type = uint64_t;
static constexpr uint32_t word_in_bits = sizeof(bmp_word_type) * 8;


template<typename T, typename P, typename B, typename I>
void PackVertexVaryingWPT(graph_t *g, P &partition_id_lst,
                B &bitmap_in_partition_lst, int u, T &packed_num, I wpt) {
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
    if ((g->num_edges[u + 1] - g->num_edges[u]) >= 1 && (g->num_edges[u + 1] - g->num_edges[u]) / num_blks > wpt) {
        packed_num++;
        for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
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

template<typename T, typename P, typename B>
void PackVertex(graph_t *g, P &partition_id_lst,
                B &bitmap_in_partition_lst, int u, T &packed_num) {
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
        for (auto off = g->num_edges[u]; off < g->num_edges[u + 1]; off++) {
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
inline int ComputeSupportWithPack(graph_t *g, int *EdgeSupport, size_t &tc_cnt, uint32_t i,
                                  BoolArray<bmp_word_type> &bool_arr, P &partition_id_lst,
                                  B &bitmap_in_partition_lst) {
    static thread_local auto last_u = -1;
    static thread_local auto u = 0;
    static thread_local auto radix_filter = RadixFilter(g);
    u = FindSrc(g, u, i);
    auto du = g->num_edges[u + 1] - g->num_edges[u];
    if (du == 0)return 0;

    if (last_u != u) {
        // Construct our radix partitioning filter: RadixFilter.
        radix_filter.Construct(u);
        // Clear.
        if (last_u != -1) {
            for (auto offset = g->num_edges[last_u]; offset < g->num_edges[last_u + 1]; offset++) {
                auto v = g->adj[offset];
                bool_arr.setWord(v / word_in_bits, 0);
            }
        }
        // Set.
        for (auto offset = g->num_edges[u]; offset < g->num_edges[u + 1]; offset++) {
            auto v = g->adj[offset];
            bool_arr.set(v);
        }
        last_u = u;
    }

    auto v = g->adj[i];
    auto dv = g->num_edges[v + 1] - g->num_edges[v];
    auto local_cnt = 0;

    // du > dv here.
    if (du > dv || ((du == dv) && (u < v))) {
        if (!partition_id_lst[v].empty()) {
            for (auto wi = 0u; wi < partition_id_lst[v].size(); wi++) {
                auto res = bool_arr.getWord(partition_id_lst[v][wi]) & bitmap_in_partition_lst[v][wi];
                local_cnt += popcnt(&res, sizeof(bmp_word_type));
            }
        } else {
            // Avoid small-small lookup here.
            // Need to estimate costs between bmp and merge if we enable HYBRID_MERGE_BMP.
#ifdef HYBRID_MERGE_BMP
#if defined(__AVX512F__)
            constexpr int ratio = 16;
#elif defined(__AVX2__) || defined(__SSE4__)
            constexpr int ratio = 4;
#else
            constexpr int ratio = 2;
#endif
            if (du / dv < ratio) {
#if defined(__AVX512F__)
                local_cnt = SetIntersectionMergeAVX512Detail(g, g->num_edges[u], g->num_edges[u + 1], g->num_edges[v],
                                                             g->num_edges[v + 1]);
#eif defined(__AVX2__)
                local_cnt = SetInterCntAVX2Detail(g, g->num_edges[u], g->num_edges[u + 1], g->num_edges[v],
                                                  g->num_edges[v + 1]);
#elif defined(__SSE4_1__)
                local_cnt = SetInterCntSSE4Detail(g, g->num_edges[u], g->num_edges[u + 1], g->num_edges[v],
                                                  g->num_edges[v + 1]);
#else
                local_cnt = SetIntersectionScalarCntDetail(g, g->num_edges[u], g->num_edges[u + 1], g->num_edges[v],
                                                           g->num_edges[v + 1]);
#endif
            } else {
#endif
            for (auto off = g->num_edges[v]; off < g->num_edges[v + 1]; off++) {
                auto w = g->adj[off];
                // random access.
                if (radix_filter.PossibleExist(w)) {
                    if (bool_arr.get(w)) {
                        local_cnt++;
                    }
                }
            }
#ifdef HYBRID_MERGE_BMP
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

// ru < rv, u points to v
inline bool less_than(int u, int v, int du, int dv) {
    return du > dv || ((du == dv) && (u < v));
}

inline int ComputeSupportBaseLine(graph_t *g, int *EdgeSupport, size_t &tc_cnt, uint32_t uv) {
    static thread_local auto *X = (eid_t *) calloc(sizeof(eid_t), g->n);
    static thread_local auto u = 0;
    static thread_local auto du = -1;
    u = FindSrc(g, u, uv);
    static thread_local auto last_u = -1;
    if (last_u != u) {
        // clear previous
        if (last_u != -1) {
            for (eid_t j = g->num_edges[last_u]; j < g->num_edges[last_u + 1]; j++) {
                X[g->adj[j]] = 0;
            }
        }
        for (eid_t j = g->num_edges[u]; j < g->num_edges[u + 1]; j++) {
            X[g->adj[j]] = j + 1;       // avoid zero hit.
        }
        last_u = u;
        du = g->num_edges[last_u + 1] - g->num_edges[last_u];
    }

    vid_t v = g->adj[uv];
    auto dv = g->num_edges[v + 1] - g->num_edges[v];

    int uv_sup = 0;
    if (less_than(u, v, du, dv)) {
        for (eid_t vw = g->num_edges[v]; vw < g->num_edges[v + 1]; vw++) {
            vid_t w = g->adj[vw];
            auto dw = g->num_edges[w + 1] - g->num_edges[w];
            if (less_than(v, w, dv, dw) && X[w]) {  //This is a triangle, match here.
                eid_t e1 = g->eid[X[w] - 1], e3 = g->eid[vw];
                __sync_fetch_and_add(&EdgeSupport[e1], 1);
                uv_sup++;
                __sync_fetch_and_add(&EdgeSupport[e3], 1);
            }
        }
        auto e2 = g->eid[uv];
        __sync_fetch_and_add(&EdgeSupport[e2], uv_sup);
    }
    tc_cnt += 3 * uv_sup;
    return tc_cnt;
}

inline int ComputeSupport(graph_t *g, int *EdgeSupport, size_t &tc_cnt, uint32_t i) {
    static thread_local auto u = 0;
    u = FindSrc(g, u, i);
    static thread_local auto last_u = -1;
    static thread_local auto bits_vec = vector<bool>(g->n, false);

    if (last_u != u) {
        // clear previous
        if (last_u != -1) {
            for (auto offset = g->num_edges[last_u]; offset < g->num_edges[last_u + 1]; offset++) {
                bits_vec[g->adj[offset]] = false;
            }
        }
        for (auto offset = g->num_edges[u]; offset < g->num_edges[u + 1]; offset++) {
            bits_vec[g->adj[offset]] = true;
        }
        last_u = u;
    }
    auto v = g->adj[i];
    auto du = g->num_edges[u + 1] - g->num_edges[u];
    auto dv = g->num_edges[v + 1] - g->num_edges[v];
    if (du > dv || ((du == dv) && (u < v))) {
        auto cnt = ComputeCNHashBitVec(g, g->num_edges[v], g->num_edges[v + 1], bits_vec);
        EdgeSupport[g->eid[i]] += cnt;
        tc_cnt += cnt;
    }
    return EdgeSupport[g->eid[i]];
}

template<typename T>
vector<int32_t> core_val_histogram(int n, T &core, bool is_print = false) {
    Timer histogram_timer;
    // core-value histogram
    int max_core_val = 0;
    vector<int32_t> histogram;
#pragma omp parallel
    {
#pragma omp for reduction(max:max_core_val)
        for (auto u = 0; u < n; u++) {
            max_core_val = max(max_core_val, core[u]);
        }
#pragma omp single
        {
            log_info("max value: %d", max_core_val);
            histogram = vector<int32_t>(max_core_val + 1, 0);
        }
        vector<int32_t> local_histogram(histogram.size());

#pragma omp for
        for (auto u = 0; u < n; u++) {
            auto core_val = core[u];
            local_histogram[core_val]++;
        }

        // local_histogram[i] is immutable here.
        for (auto i = 0u; i < local_histogram.size(); i++) {
#pragma omp atomic
            histogram[i] += local_histogram[i];
        }
    }
    if (is_print) {
        if (histogram.size() < 400) {
            stringstream ss;
            ss << pretty_print_array(&histogram.front(), histogram.size());
            log_info("values histogram: %s", ss.str().c_str());
        } else {
            {
                stringstream ss;
                ss << pretty_print_array(&histogram.front(), 100);
                log_info("first100 values histogram: %s", ss.str().c_str());
            }
            {

                stringstream ss;
                ss << pretty_print_array(&histogram.front() + histogram.size() - 100, 100);
                log_info("last100 values histogram: %s", ss.str().c_str());
            }
        }
    }
    log_info("Histogram Time: %.9lf s", histogram_timer.elapsed());

    auto &bins = histogram;
    auto bin_cnt = 0;
    int64_t acc = 0;
    auto thresh = n / 10;
    auto last = 0;

    for (auto i = 0u; i < histogram.size(); i++) {
        if (bins[i] > 0) {
            bin_cnt++;
            acc += bins[i];
            if (acc > thresh || i == histogram.size() - 1) {
                log_info("bin[%d - %d]: %s", last, i, FormatWithCommas(acc).c_str());
                last = i + 1;
                acc = 0;
            }
        }
    }
    log_info("Reversed Bins...");
    last = histogram.size() - 1;
    acc = 0;
    for (int32_t i = histogram.size() - 1; i > -1; i--) {
        if (bins[i] > 0) {
            bin_cnt++;
            acc += bins[i];
            if (acc > thresh || i == 0) {
                log_info("bin[%d - %d]: %s", i, last, FormatWithCommas(acc).c_str());
                last = i + 1;
                acc = 0;
            }
        }
    }
    log_info("total bin counts: %d", bin_cnt);
    return histogram;
}