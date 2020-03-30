//
// Created by yche on 12/2/19.
//

#include "util/graph/graph.h"
#include "util/graph/pre_processing.h"
#include "util/graph/pre_processing_dodg.h"
#include "util/graph/triangle_counting.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph_t g;

    //load the graph from file
    Graph yche_graph(argv[1]);
    g.adj = yche_graph.edge_dst;
    g.num_edges = yche_graph.node_off;
    g.n = yche_graph.nodemax;
    g.m = yche_graph.edgemax;
    // TC.
    vector<int32_t> new_dict;
    vector<int32_t> old_dict;
    auto prev = g.adj;
    auto tmp = (int32_t *) malloc(g.m * sizeof(int32_t));
    ReorderDegDescending(g, new_dict, old_dict, tmp);
    free(prev);
    CountTriBMPAndMergeWithPack(g, omp_get_max_threads());
    log_debug("");

    // To DODG.
    auto edge_lst = (pair<int32_t, int32_t> *) malloc(g.m * sizeof(pair<int32_t, int32_t>));
#pragma omp parallel for schedule(dynamic, 1000)
    for (auto u = 0; u < g.n; u++) {
        for (auto off = g.num_edges[u]; off < g.num_edges[u + 1]; off++) {
            if (u < g.adj[off]) {
                // no duplicates
                edge_lst[off].first = u;
                edge_lst[off].second = g.adj[off];
            }
        }
    }

    {
        // 1st: Remove Multi-Edges and Self-Loops.
        Timer global_timer;
        Timer sort_timer;
        int32_t max_node_id = 0;
        auto num_edges = g.m;
#pragma omp parallel for reduction(max: max_node_id) schedule(dynamic, 32*1024)
        for (size_t i = 0u; i < num_edges; i++) {
            if (edge_lst[i].first > edge_lst[i].second) {
                swap(edge_lst[i].first, edge_lst[i].second);
            }
            max_node_id = max(max_node_id, max(edge_lst[i].first, edge_lst[i].second));
        }
        log_info("Populate File Time: %.9lfs", global_timer.elapsed());
        // In-Place Parallel Sort.
        ips4o::parallel::sort(edge_lst, edge_lst + num_edges, [](auto l, auto r) {
            if (l.first == r.first) {
                return l.second < r.second;
            }
            return l.first < r.first;
        });
        log_info("Sort Time: %.9lfs", sort_timer.elapsed());
        auto num_vertices = static_cast<uint32_t >(max_node_id) + 1;
        log_info("Pre-Process Edge List Time: %.9lf s", global_timer.elapsed());

        // 2nd: Convert Edge List to CSR.
        graph_t g{.n=num_vertices, .m = 0, .adj=nullptr, .num_edges=nullptr};
        uint32_t *deg_lst;
        g.adj = nullptr;
        auto max_omp_threads = omp_get_max_threads();
        ConvertEdgeListToDODGCSR((eid_t) num_edges, edge_lst, num_vertices, deg_lst, g.num_edges, g.adj,
                                 max_omp_threads, [&](size_t it) {
                    return !(edge_lst[it].first == edge_lst[it].second
                             || (it > 0 && edge_lst[it - 1] == edge_lst[it]));
                });
        g.m = g.num_edges[num_vertices];
        log_info("Undirected Graph G = (|V|, |E|): %lld, %lld", g.n, g.m);
        log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());

        // 3rd: Reordering.
        vector<int32_t> new_dict;
        vector<int32_t> old_dict;

        auto *tmp_mem_blocks = (int32_t *) malloc(g.m * sizeof(int32_t));
        auto *org = g.adj;
        ReorderDegDescendingDODG(g, new_dict, old_dict, tmp_mem_blocks, deg_lst);
        free(org);
        free(deg_lst);

        // 4th: Triangle Counting.
        log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
        size_t tc_cnt = 0;
        tc_cnt = CountTriBMPAndMergeWithPackDODG(g, max_omp_threads);
        log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
        log_info("There are %zu triangles in the input graph.", tc_cnt);
        printf("There are %zu triangles in the input graph.\n", tc_cnt);

        // 5th: Reverse Graph (DODG).
        graph_t rev_g;
        rev_g.adj = nullptr;
        rev_g.num_edges = nullptr;
        RevereseDODG(&g, &rev_g);
        tc_cnt = CountTriMergeDODG(rev_g, max_omp_threads);
        log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
        log_info("There are %zu triangles in the input graph.", tc_cnt);
        printf("There are %zu triangles in the input graph.\n", tc_cnt);

        auto sup = (int *) malloc(sizeof(int) * g.m);
        auto qr_sup = (int *) malloc(sizeof(int) * g.m);
        auto qp_sup = (int *) malloc(sizeof(int) * g.m);    // over the reversed graph.

        tc_cnt = 0;
        size_t sup_cnt = 0;
        size_t qr_sup_cnt = 0;
        size_t qp_sup_cnt = 0;
#pragma omp parallel
        {
            MemSetOMP(sup, 0, g.m);
            MemSetOMP(qr_sup, 0, g.m);
            MemSetOMP(qp_sup, 0, g.m);

            Timer timer;
            // SI Phase: Triangle Enumeration.
#pragma omp for schedule(dynamic, 1000) reduction(+:tc_cnt)
            for (auto p = 0; p < g.n; p++) {
                for (auto off_pq = g.num_edges[p]; off_pq < g.num_edges[p + 1]; off_pq++) {
                    auto q = g.adj[off_pq];
                    for (auto off_pr = g.num_edges[p]; off_pr < g.num_edges[p + 1]; off_pr++) {
                        // search whether (q, r) exists
                        auto r = g.adj[off_pr];
                        if (q != r && g.num_edges[q] != g.num_edges[q + 1]) {
                            auto it = BranchFreeBinarySearch(g.adj, g.num_edges[q], g.num_edges[q + 1], r);
                            if (it != g.num_edges[q + 1] && g.adj[it] == r) {
                                __sync_fetch_and_add(sup + off_pq, 1);
                                __sync_fetch_and_add(sup + off_pr, 1);
                                __sync_fetch_and_add(sup + it, 1);
                                __sync_fetch_and_add(qr_sup + it, 1);
                                tc_cnt++;
                                {
                                    auto qp = BranchFreeBinarySearch(rev_g.adj, rev_g.num_edges[q],
                                                                     rev_g.num_edges[q + 1], p);
                                    assert(rev_g.adj[qp] == p);
                                    __sync_fetch_and_add(qp_sup + qp, 1);
                                }
                            }
                        }
                    }
                }
            }
#pragma omp for reduction(+:sup_cnt) reduction(+:qr_sup_cnt), reduction(+:qp_sup_cnt)
            for (auto i = 0; i < g.m; i++) {
                sup_cnt += sup[i];
                qr_sup_cnt += qr_sup[i];
                qp_sup_cnt += qp_sup[i];
            }
#pragma omp single
            {
                log_info("Forward time: %.9lfs", timer.elapsed());
            }
        }
        log_info("There are %zu triangles in the input graph.", tc_cnt);
        log_info("There are %zu, %zu, %zu triangles in the input graph.", sup_cnt / 3, qr_sup_cnt, qp_sup_cnt);
    }
}
