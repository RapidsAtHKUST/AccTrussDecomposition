//
// Created by yche on 10/3/19.
//

#include "graph.h"

#include <cassert>

#include <chrono>

#include "util/util.h"
#include "util/log/log.h"
#include "util/search/search_util.h"
#include "util/primitives/primitives.h"
#include "opt_pkt/parallel_all_edge_cnc.h"

//Populate eid and edge list
void getEidAndEdgeList(graph_t *g, Edge *idToEdge) {
    //Allocate space for eid -- size g->m
    g->eid = (eid_t *) malloc(g->m * sizeof(eid_t));

    //Edge upper_tri_start of each edge
    auto *num_edges_copy = (eid_t *) malloc((g->n + 1) * sizeof(eid_t));
    assert(num_edges_copy != nullptr);

    auto *upper_tri_start = (eid_t *) malloc(g->n * sizeof(eid_t));

    num_edges_copy[0] = 0;
    auto num_threads = omp_get_max_threads();
    vector<eid_t> histogram(CACHE_LINE_ENTRY * num_threads);
#pragma omp parallel
    {
#pragma omp for
        // Histogram (Count).
        for (vid_t u = 0; u < g->n; u++) {
            upper_tri_start[u] = (g->num_edges[u + 1] - g->num_edges[u] > 256)
                                 ? GallopingSearch(g->adj, g->num_edges[u], g->num_edges[u + 1], u)
                                 : LinearSearch(g->adj, g->num_edges[u], g->num_edges[u + 1], u);
        }

#pragma omp single
        {
            if (g->n < 50) {
                stringstream ss;
                ss << pretty_print_array(upper_tri_start, g->n);
                log_info("N+(u): %s", ss.str().c_str());

                reset(ss);
                ss << pretty_print_array(num_edges_copy, g->n + 1);
                log_info("Histogram: %s", ss.str().c_str());
            }
        }
        Timer local_timer;
        // Scan.
        InclusivePrefixSumOMP(histogram, num_edges_copy + 1, g->n, [g, upper_tri_start](int u) {
            return g->num_edges[u + 1] - upper_tri_start[u];
        });
#pragma omp single
        {
            if (g->n < 50) {
                stringstream ss;
                ss << pretty_print_array(num_edges_copy, g->n + 1);
                log_info("EL SCAN Result: %s", ss.str().c_str());
            }
            log_info("SCAN Time: %.9lf s", local_timer.elapsed());
        }

        // Transform.
        auto u = 0;
#pragma omp for schedule(dynamic, 6000)
        for (eid_t j = 0u; j < g->m; j++) {
            u = FindSrc(g, u, j);
            if (j < upper_tri_start[u]) {
                auto v = g->adj[j];
                auto offset = BranchFreeBinarySearch(g->adj, g->num_edges[v], g->num_edges[v + 1], u);
                auto eid = num_edges_copy[v] + (offset - upper_tri_start[v]);
                g->eid[j] = eid;
                idToEdge[eid] = Edge(v, u);
            } else {
                g->eid[j] = num_edges_copy[u] + (j - upper_tri_start[u]);
            }
        }

        // Verify EID.
#pragma omp for
        for (eid_t j = 0; j < g->m / 2; j++) {
            Edge edge = idToEdge[j];
            if (edge.u >= edge.v) {
                log_fatal("Edge List Order Not Correct...");
                exit(-1);
            }
            auto u = edge.u;
            auto v = edge.v;
            if (BranchFreeBinarySearch(g->adj, g->num_edges[v], g->num_edges[v + 1], u) == g->num_edges[v + 1]) {
                log_fatal("Not Found u: %d in v: %d", u, v);
                exit(-1);
            }
            if (BranchFreeBinarySearch(g->adj, g->num_edges[u], g->num_edges[u + 1], v) == g->num_edges[u + 1]) {
                log_fatal("Not Found v: %d in u: %d", v, u);
                exit(-1);
            }
        }
#pragma omp single
        log_debug("Pass EID checking...");
    }
    free(upper_tri_start);

    free(num_edges_copy);
}