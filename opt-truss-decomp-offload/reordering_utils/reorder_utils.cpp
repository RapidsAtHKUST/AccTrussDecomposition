#include "reorder_utils.h"

#include <cassert>
#include <random>
#include <omp.h>

#include "../util/timer.h"
#include "../util/log.h"
#include "../util/md5.h"
#include "../util/sort/parasort_cmp.h"
#include "../util/yche_serialization.h"
#include "../host/histogram.h"

void Reorder(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict) {
    Timer timer;

    new_vid_dict = vector<int>(g.n);
    for (auto i = 0; i < g.n; i++) {
        new_vid_dict[old_vid_dict[i]] = i;
    }
    // new-deg
    vector<int> new_deg(g.n);
    for (auto new_id = 0; new_id < g.n; new_id++) {
        auto vertex = old_vid_dict[new_id];
        new_deg[new_id] = g.num_edges[vertex + 1] - g.num_edges[vertex];
        assert(new_deg[new_id] >= 0);
    }

    // verify permutation
    for (auto i = 0; i < std::min<int32_t>(5, static_cast<int32_t>(new_vid_dict.size())); i++) {
        log_info("old->new %d -> %d", i, new_vid_dict[i]);
    }
    vector<int> verify_map(new_vid_dict.size(), 0);
    int cnt = 0;

#pragma omp parallel
    {
#pragma omp for reduction(+:cnt)
        for (auto i = 0; i < new_vid_dict.size(); i++) {
            if (verify_map[new_vid_dict[i]] == 0) {
                cnt++;
                verify_map[new_vid_dict[i]] = 1;
            } else {
                assert(false);
            }
        }
#pragma omp single
        log_info("%d, %d", cnt, new_vid_dict.size());
        assert(cnt == new_vid_dict.size());
    }
    // 1st CSR: new_off, new_neighbors
    vector<uint32_t> new_off(g.n + 1);
    new_off[0] = 0;
    assert(new_off.size() == g.n + 1);
    for (auto i = 0u; i < g.n; i++) { new_off[i + 1] = new_off[i] + new_deg[i]; }
    log_info("%zu", new_off[g.n]);
    assert(new_off[g.n] == g.m);

    vector<int> new_neighbors(g.m);

    log_info("init ordering structures time: %.9lf s", timer.elapsed_and_reset());

    // 2nd Parallel Transform
#pragma omp parallel
    {
#pragma omp for schedule(dynamic, 100)
        for (auto i = 0; i < g.n; i++) {
            auto origin_i = old_vid_dict[i];
            // transform
            auto cur_idx = new_off[i];
            for (auto my_old_off = g.num_edges[origin_i]; my_old_off < g.num_edges[origin_i + 1]; my_old_off++) {
                if (cur_idx > g.m) {
                    log_info("%d, i: %d", cur_idx, i);
                }
                assert(cur_idx <= g.m);
                assert(my_old_off <= g.m);
                assert(g.adj[my_old_off] < g.n);
                new_neighbors[cur_idx] = new_vid_dict[g.adj[my_old_off]];
                cur_idx++;
            }
            // sort the local ranges
            sort(begin(new_neighbors) + new_off[i], begin(new_neighbors) + new_off[i + 1]);
        }
    }
    log_info("parallel transform and sort: %.3lf s", timer.elapsed());

    memcpy(g.adj, &new_neighbors.front(), g.m * sizeof(int32_t));
    memcpy(g.num_edges, &new_off.front(), (g.n + 1) * sizeof(uint32_t));
}

void ReorderKCoreDegeneracy(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict) {
    Timer timer;
    vector<int> core_val(g.n, 0);
    PKC(&g, &core_val.front(), omp_get_max_threads());

    auto res = core_val_histogram(g.n, core_val);
    {
        stringstream ss;
        ss << res << "\n";
        log_info("Md5sum of PKC histogram: %s", md5(ss.str()).c_str());
    }
    old_vid_dict = vector<int>(g.n);
    for (auto i = 0; i < old_vid_dict.size(); i++) { old_vid_dict[i] = i; }
#ifdef DUAL_DEG_CORE
    sort(begin(old_vid_dict), end(old_vid_dict),
         [&core_val, &yche_graph](int l, int r) -> bool {
             return static_cast<int64_t>(yche_graph.degree[l]) * core_val[l] >
                    static_cast<int64_t>(yche_graph.degree[r]) * core_val[r];
         });
#else
    parasort(old_vid_dict.size(), &old_vid_dict.front(),
             [&core_val](int l, int r) -> bool {
                 return core_val[l] > core_val[r];
             }, omp_get_max_threads());
#endif
    log_info("PKC (k-core) time:  %.9lf s", timer.elapsed());

    Reorder(g, new_vid_dict, old_vid_dict);
}

void ReorderRandom(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict) {
    Timer timer;

    old_vid_dict = vector<int>(g.n);
    for (auto i = 0; i < old_vid_dict.size(); i++) { old_vid_dict[i] = i; }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(begin(old_vid_dict), end(old_vid_dict), gen);

    log_info("Random shuffling time:  %.9lf s", timer.elapsed());

    Reorder(g, new_vid_dict, old_vid_dict);
}

void ReorderDegDescending(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict) {
    Timer timer;

    old_vid_dict = vector<int>(g.n);
    for (auto i = 0; i < old_vid_dict.size(); i++) { old_vid_dict[i] = i; }

#ifdef TBB
    log_info("Use TBB parallel sort");
    tbb::parallel_sort(begin(old_vid_dict), end(old_vid_dict),
                       [&g](int l, int r) -> bool { return g.degree[l] > g.degree[r]; });
#else
    log_info("Use parallel sort (parasort)");
    parasort(old_vid_dict.size(), &old_vid_dict.front(),
             [&g](int l, int r) -> bool {
                 return g.num_edges[l + 1] - g.num_edges[l] > g.num_edges[r + 1] - g.num_edges[r];
             },
             omp_get_max_threads());
#endif
    log_info("Deg-descending time:  %.9lf s", timer.elapsed());

    Reorder(g, new_vid_dict, old_vid_dict);
}

void ReorderWithFileDict(graph_t &g, string dir, string reorder_method, vector<int32_t> &new_vid_dict,
                         vector<int32_t> &old_vid_dict) {
    string reorder_file_path = dir + "/" + reorder_method + ".dict";
    FILE *pFile = fopen(reorder_file_path.c_str(), "r");
    YcheSerializer serializer;
    serializer.read_array(pFile, new_vid_dict);
    fclose(pFile);
    log_info("Finish loading %s", reorder_file_path.c_str());

    old_vid_dict = vector<int>(g.n);
    assert(new_vid_dict.size() == old_vid_dict.size());
#pragma omp parallel for
    for (auto v = 0; v < g.n; v++) {
        old_vid_dict[new_vid_dict[v]] = v;
    }
    Reorder(g, new_vid_dict, old_vid_dict);
}

void ReorderWrapper(graph_t &g, string dir, string reorder_method, vector<int32_t> &new_vid_dict,
                    vector<int32_t> &old_vid_dict) {
    Timer timer;
    if (reorder_method == "deg") {
        // Counting on the Degree-Ordered-Directed-Graph (View).
        log_info("Re-ordering... Method: DODG");
        ReorderDegDescending(g, new_vid_dict, old_vid_dict);
    } else if (reorder_method == "kcore") {
        log_info("Re-ordering... Method: Kcore");
        ReorderKCoreDegeneracy(g, new_vid_dict, old_vid_dict);
    } else if (reorder_method == "random") {
        log_info("Re-ordering... Method: Random");
        ReorderRandom(g, new_vid_dict, old_vid_dict);
    } else if (reorder_method == "gro" || reorder_method == "cache" ||
               reorder_method == "bfsr" || reorder_method == "dfs" ||
               reorder_method == "hybrid" || reorder_method == "rcm-cache"
               || reorder_method == "slashburn") {
        log_info("Re-ordering... Method: %s", reorder_method.c_str());
        ReorderWithFileDict(g, dir, reorder_method, new_vid_dict, old_vid_dict);
    } else {
        log_info("Unknown Method: %s, Keep the orginal ordering...", reorder_method.c_str());
    }
    log_info("Total Reordering Time: %.9lf s", timer.elapsed());
}