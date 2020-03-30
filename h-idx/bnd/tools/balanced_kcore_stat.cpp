//
// Created by yche on 4/23/19.
//

#include <algorithm>

#include <sparsepp/spp.h>
#include <libpopcnt.h>

#include "util/boolarray.h"
#include "util/containers/union_find.h"
#include "util/containers/ThreadSafeDisjointSet.h"
#include "util/serialization/pretty_print.h"

#include "bnd/main.h"
#include "util/timer.h"
#include "util/log/log.h"
#include "util/serialization/core_histogram.h"
#include "bnd/reorder.h"

using spp::sparse_hash_map;

#define ARR

void StatCnt(Graph &leftGraph, Graph &rightGraph) {
    Timer timer;
    uint64_t complexity = 0;
    for (auto &v_nei:rightGraph) {
        complexity += v_nei.size() * v_nei.size();
    }
    log_info("Complexity: %s", FormatWithCommas(complexity).c_str());
    // From Left to Right.
    uint64_t all_two_hop = 0;
    uint64_t all_two_hop_cnt = 0;
    uint64_t bf_cnt = 0;
    uint64_t max_cnt = 0;
#pragma omp parallel
    {
#pragma omp single
        log_info("Left Graph Size: %s", FormatWithCommas(leftGraph.size()).c_str());

#ifdef ARR
        vector<int32_t> dup(leftGraph.size());

        BoolArray<uint64_t> bmp(leftGraph.size());
        size_t word_count = bmp.sizeInBytes() / sizeof(uint64_t);
        constexpr size_t bits_per_byte = 8;
#else
        sparse_hash_map<int32_t, int32_t> dup;
#endif

#pragma omp for reduction(+:all_two_hop) reduction(+:all_two_hop_cnt) reduction(+:bf_cnt) \
reduction(max:max_cnt) schedule(dynamic, 1)
        for (auto u = 0; u < leftGraph.size(); u++) {
            for (auto v: leftGraph[u]) {
                // only u < uu
                for (auto uu:rightGraph[v]) {
                    if (u != uu) {
                        dup[uu]++;
#ifdef ARR
                        if (dup[uu] == 1) {
                            bmp.set(uu);
                        }
#endif
                    }
                }
            }
#ifdef ARR
            for (size_t word_i = 0; word_i < word_count; word_i++) {
                auto word = bmp.getWord(word_i);
                if (word != 0) {
                    auto range_beg = word_i * sizeof(uint64_t) * bits_per_byte;
                    auto range_end = (word_i + 1) * sizeof(uint64_t) * bits_per_byte;
                    for (auto range_i = range_beg; range_i < range_end; range_i++) {
                        if (bmp.get(range_i)) {
                            uint64_t cnt = dup[range_i];
                            max_cnt = max(max_cnt, cnt);
                            all_two_hop++;
                            all_two_hop_cnt += cnt;
                            bf_cnt += cnt * (cnt - 1) / 2;
                            dup[range_i] = 0;
                        }
                    }
                }
            }
            bmp.reset();
#else
            for (auto &t: dup) {
                uint64_t cnt = t.second;
                if (cnt != 0) {
                    all_two_hop++;
                    all_two_hop_cnt += cnt;
                    bf_cnt += cnt * (cnt - 1) / 2;
                }
            }
            dup.clear();
#endif
        }
    }
    log_info("two-hop: %s, two-hop-cnt: %s, max-cnc-cnt: %s, bf-cnt: %s", FormatWithCommas(all_two_hop).c_str(),
             FormatWithCommas(all_two_hop_cnt).c_str(),
             FormatWithCommas(max_cnt).c_str(),
             FormatWithCommas(bf_cnt / 2).c_str());
    log_info("Elapsed Vertex-based Counting Time: %.6lf s", timer.elapsed());
}

unordered_map<int, pair<int, int>> GetCCHistogram(UnionFind &uf, int left_size, int right_size) {
    auto size = left_size + right_size;
    unordered_map<int, pair<int, int>> root_count_vec(size);

    for (int i = 0; i < left_size; i++) {
        root_count_vec[uf.FindRoot(i)].first++;
    }
    for (int i = left_size; i < size; i++) {
        root_count_vec[uf.FindRoot(i)].second++;
    }
    return root_count_vec;
}

void TwoCoreConnect(Graph &leftGraph, Graph &rightGraph) {
    // CC Stats (from 2-2 bi-cliques).
    Timer timer;
    UnionFind uf(leftGraph.size() + rightGraph.size());
    uint64_t complexity = 0;
    for (auto &v_nei:rightGraph) {
        complexity += v_nei.size() * v_nei.size();
    }
    log_info("Complexity: %s", FormatWithCommas(complexity).c_str());

#pragma omp parallel
    {
        auto left_size = leftGraph.size();
#pragma omp single
        log_info("Left Graph Size: %s", FormatWithCommas(leftGraph.size()).c_str());

#ifdef ARR
        vector<int32_t> dup(leftGraph.size());

        BoolArray<uint64_t> bmp(leftGraph.size());
        size_t word_count = bmp.sizeInBytes() / sizeof(uint64_t);
        constexpr size_t bits_per_byte = 8;
#else
        sparse_hash_map<int32_t, int32_t> dup;
#endif

#pragma omp for schedule(dynamic, 1)
        for (auto u = 0; u < leftGraph.size(); u++) {
            for (auto v: leftGraph[u]) {
                for (auto uu:rightGraph[v]) {
                    if (u != uu) {
                        dup[uu]++;
#ifdef ARR
                        if (dup[uu] == 1) {
                            bmp.set(uu);
                        }
#endif
                    }
                }
            }
#ifdef ARR
            for (auto v: leftGraph[u]) {
                for (auto uu:rightGraph[v]) {
                    auto cnt = dup[uu];
                    if (cnt >= 2) {
                        uf.UnionThreadSafe(u, v + left_size);
                        break;
                    }
                }
            }
            for (size_t word_i = 0; word_i < word_count; word_i++) {
                auto word = bmp.getWord(word_i);
                if (word != 0) {
                    auto range_beg = word_i * sizeof(uint64_t) * bits_per_byte;
                    auto range_end = (word_i + 1) * sizeof(uint64_t) * bits_per_byte;
                    for (auto range_i = range_beg; range_i < range_end; range_i++) {
                        if (bmp.get(range_i)) {
                            if (dup[range_i] >= 2) {
                                uf.UnionThreadSafe(u, range_i);
                            }
                            dup[range_i] = 0;
                        }
                    }
                }
            }
            bmp.reset();
#else
            for (auto &t: dup) {
                auto uu = t.first;
                auto cnt = t.second;
                if (cnt >= 2) {
                    uf.UnionThreadSafe(u, uu);
                }
            }
            for (auto v: leftGraph[u]) {
                for (auto uu:rightGraph[v]) {
                    auto cnt = dup[uu];
                    if (cnt >= 2) {
                        uf.UnionThreadSafe(u, v + left_size);
                        break;
                    }
                }
            }
            dup.clear();
#endif
        }
    }
    auto histogram = GetCCHistogram(uf, leftGraph.size(), rightGraph.size());
    map<pair<int, int>, int> filtered;
    for (auto &t: histogram) {
        if (t.second.first >= 2 && t.second.second >= 2) {
            filtered[t.second]++;
        }
    }
    {
        stringstream ss;
        ss << filtered;
        log_info("Initial CC Histogram: %s", ss.str().c_str());
    }
    auto topk = 2;
    auto peek_num = 0;
    for (auto it = filtered.rbegin(); it != filtered.rend() && peek_num < topk; it++, peek_num++) {
        log_info("PeekId: %d, (%s, %s): %d", peek_num, FormatWithCommas(it->first.first).c_str(),
                 FormatWithCommas(it->first.second).c_str(), it->second);
    }
}

tuple<Graph, Graph, vector<vertex>, vector<vertex>> CompressGraph(
        Graph &leftGraph, Graph &rightGraph, vector<vertex> &prunedV1, vector<vertex> &prunedV2,
        vector<vertex> &prevLeftID, vector<vertex> &prevRightID) {
//    // prunedV1 and prunedV2 are used as dictionaries, from 'prev vid' to 'new vid'.
//    assert(leftGraph.size() == prunedV1.size() && prunedV1.size() == prevLeftID.size());
//    assert(rightGraph.size() == prunedV2.size() && prunedV2.size() == prevRightID.size());

    // Can be replaced with PrefixSum.
    vertex newLeftSize = 0;
    for (auto u = 0u; u < leftGraph.size(); u++) {
        if (prunedV1[u] != -1) {
            prunedV1[u] = newLeftSize++;
        }
    }

    vertex newRightSize = 0;
    for (auto u = 0u; u < rightGraph.size(); u++) {
        if (prunedV2[u] != -1) {
            prunedV2[u] = newRightSize++;
        }
    }

    // Construct New Graph.
    size_t numEdges = 0;
    size_t orgNumEdges = 0;
    Graph newLeftGraph(newLeftSize);
    vector<vertex> oldLeftVid(newLeftSize);

    Graph newRightGraph(newRightSize);
    vector<vertex> oldRightVid(newRightSize);
    log_debug("New Left Size: %zu, prev: %zu", newLeftSize, leftGraph.size());
    log_debug("New Right Size: %zu, prev: %zu", newRightSize, rightGraph.size());

#pragma omp parallel
    {
#pragma omp for schedule(dynamic, 500) reduction(+: numEdges) reduction(+:orgNumEdges)
        for (auto oldU = 0u; oldU < leftGraph.size(); ++oldU) {
            if (prunedV1[oldU] != -1) {
                int newU = prunedV1[oldU];
                oldLeftVid[newU] = prevLeftID[oldU];

                for (auto oldV: leftGraph[oldU]) {
                    if (prunedV2[oldV] != -1) {
                        newLeftGraph[newU].push_back(prunedV2[oldV]);
                        numEdges++;
                    }
                }
            }
            orgNumEdges += leftGraph[oldU].size();
        }

#pragma omp for schedule(dynamic, 500)
        for (auto oldV = 0u; oldV < rightGraph.size(); ++oldV) {
            if (prunedV2[oldV] != -1) {
                int newV = prunedV2[oldV];
                assert(newV < oldRightVid.size());
                oldRightVid[newV] = prevRightID[oldV];

                for (auto oldU: rightGraph[oldV]) {
                    if (prunedV1[oldU] != -1) {
                        newRightGraph[newV].push_back(prunedV1[oldU]);
                    }
                }
            }
        }
    }
    {
        log_info("Prev Edge: %s, Reduced Edge: %s, L/R: (%s, %s), Edge-Reduction-Ratio: %.6lf",
                 FormatWithCommas(orgNumEdges).c_str(),
                 FormatWithCommas(numEdges).c_str(),
                 FormatWithCommas(newLeftGraph.size()).c_str(),
                 FormatWithCommas(newRightGraph.size()).c_str(),
                 static_cast<double>(orgNumEdges - numEdges) / orgNumEdges);
    }
    return make_tuple(newLeftGraph, newRightGraph, oldLeftVid, oldRightVid);
}

template<typename T>
void CoreConnect(Graph &leftGraph, Graph &rightGraph, const T &leftCore, const T &rightCore, int K) {
    vector<vertex> prunedV1(leftGraph.size());
    vector<vertex> prunedV2(rightGraph.size());
    vector<vertex> identityV1(leftGraph.size());
    vector<vertex> identityV2(rightGraph.size());
    iota(identityV1.begin(), identityV1.end(), 0);
    iota(identityV2.begin(), identityV2.end(), 0);

    for (auto u = 0u; u < leftGraph.size(); u++) {
        if (leftCore[u] < K) {
            prunedV1[u] = -1;
        }
    }
    for (auto v = 0u; v < rightGraph.size(); v++) {
        if (rightCore[v] < K) {
            prunedV2[v] = -1;
        }
    }
    auto res = CompressGraph(leftGraph, rightGraph, prunedV1, prunedV2, identityV1, identityV2);

    TwoCoreConnect(std::get<0>(res), std::get<1>(res));
}

int main(int argc, char *argv[]) {
    edge nEdge = 0;
    Graph leftGraph, rightGraph;

    char *filename = argv[1];
#ifdef USE_LOG
    if (argc >= 3) {
        FILE *log_f;
        log_f = fopen(argv[2], "a+");
        log_set_fp(log_f);
    }

#endif
    readBipartite<vertex, vertex>(filename, &nEdge, leftGraph, rightGraph);

    Timer timer;
    // Construct the general graph for kcore-decomposition (right graph with large node id).
    auto generalGraph = ConstructGeneralGraph(leftGraph, rightGraph);
    log_info("General Graph: |V|: %s, |E|: %s", FormatWithCommas(generalGraph.size()).c_str(),
             FormatWithCommas(nEdge).c_str());
    vector<vertex> K(generalGraph.size());
    lol maxCore;
    log_info("Elapsed Transform Time: %.6lf s", timer.elapsed());

    // K-core Decomposition.
    timer.reset();
    base_kcore(generalGraph, false, nEdge, K, &maxCore, "tmp.txt", nullptr);
    log_debug("Left Core Info");
    core_val_histogram(leftGraph.size(), K, false);
    auto *ptr = &K.front() + leftGraph.size();
    log_debug("Right Core Info");
    core_val_histogram(rightGraph.size(), ptr, false);
    log_info("Elapsed K-core Time: %.6lf s", timer.elapsed());

    vector<int32_t> leftCore{begin(K), begin(K) + leftGraph.size()};
    vector<int32_t> rightCore{begin(K) + leftGraph.size(), end(K)};
    core_val_histogram(leftCore.size(), leftCore, false);
    core_val_histogram(rightCore.size(), rightCore, false);

    // Stat 2-hop, Butterfly.
    uint64_t l_d_square_sum = 0;
    uint64_t r_d_square_sum = 0;
    for (auto &u_nei:leftGraph) {
        l_d_square_sum += u_nei.size() * u_nei.size();
    }
    for (auto &v_nei:rightGraph) {
        r_d_square_sum += v_nei.size() * v_nei.size();
    }
    log_info("d^2 L/R : %s \t& %s", FormatWithCommas(l_d_square_sum).c_str(),
             FormatWithCommas(r_d_square_sum).c_str());

    if (l_d_square_sum < r_d_square_sum) {
        log_debug("swapped...");
        swap(leftGraph, rightGraph);
        swap(leftCore, rightCore);
    }
    StatCnt(leftGraph, rightGraph);
//#ifdef DEBUG
//    StatCnt(rightGraph, leftGraph);
//#endif

    // Two Core Connect.
    TwoCoreConnect(leftGraph, rightGraph);
//#ifdef DEBUG
//    TwoCoreConnect(rightGraph, leftGraph);
//#endif

    for (auto k = 3; k < maxCore; k++) {
        // Traversal.
        log_info("Cure K: %d", k);
        CoreConnect(leftGraph, rightGraph, leftCore, rightCore, k);
    }

    log_info("Elapsed 2-2 Biclique-Connectivity Time: %.6lf s", timer.elapsed());
    return 0;
}
