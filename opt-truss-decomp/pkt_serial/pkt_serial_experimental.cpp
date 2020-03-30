#include <cassert>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "../util/timer.h"
#include "util/log/log.h"
#include "opt_pkt/parallel_all_edge_cnc.h"
#include "util/intersection/set_utils.h"

//#define NAIVE_SCAN

void PKT_scan_serial(long numEdges, const int *EdgeSupport, int level, eid_t *curr, long *currTail, graph_t *g,
                     bool *local_removal_record, vector<eid_t> &off_end, vector<eid_t> &adj_relative_off,
                     bool *is_vertex_updated) {
    // Removal: update adj_relative_off, move edges ahead, real removal
    for (auto u = 0; u < g->n; u++) {
        if (is_vertex_updated[u]) {
            is_vertex_updated[u] = false;
            auto write_idx = g->num_edges[u];
            for (auto i = g->num_edges[u]; i < off_end[u + 1]; i++) {
                if (local_removal_record[i]) {
                    local_removal_record[i] = false;
                } else {
                    // i is the original offset, (i - write_idx) is the advance step,
                    // so we sum original relative off with advance step
                    adj_relative_off[write_idx] = adj_relative_off[i] + (i - write_idx);
                    g->adj[write_idx++] = g->adj[i];
                }
            }
            off_end[u + 1] = write_idx;
        }
    }
#ifdef NAIVE_SCAN
    for (long i = 0; i < numEdges; i++) {
        if (EdgeSupport[i] == level) {
            curr[(*currTail)] = i;
            (*currTail) = (*currTail) + 1;
        }
    }
#else
    // Scan on the shrink graph.
    for (auto u = 0; u < g->n; u++) {
        // Switch between LinearSearch and BinarySearch, default threshold: 256.
        auto start = (off_end[u + 1] - g->num_edges[u] > 256)
                     ? GallopingSearch(g->adj, g->num_edges[u], off_end[u + 1], u)
                     : LinearSearch(g->adj, g->num_edges[u], off_end[u + 1], u);
        for (auto edge_idx = start; edge_idx < off_end[u + 1]; edge_idx++) {
            auto i = g->eid[edge_idx + adj_relative_off[edge_idx]];
            if (EdgeSupport[i] == level) {
                curr[(*currTail)] = i;
                (*currTail) = (*currTail) + 1;
            }
        }
    }
#endif
}

//Serially process sub-level in a level using intersection
void PKT_processSubLevel_serial_intersection(graph_t *g, const eid_t *curr, long currTail, int *EdgeSupport,
                                             int level, eid_t *next, long *nextTail, bool *processed,
                                             Edge *edgeIdtoEdge, bool *local_removal_record,
                                             vector<eid_t> &off_end, vector<eid_t> &adj_relative_off,
                                             bool *is_vertex_updated) {
    vector<pair<eid_t, eid_t >> intersection_res;
    auto serial_sup_updater = [EdgeSupport, &next, level, &nextTail](eid_t edge) {
        EdgeSupport[edge] = EdgeSupport[edge] - 1;
        if (EdgeSupport[edge] == level) {
            next[(*nextTail)] = edge;
            (*nextTail) = (*nextTail) + 1;
        }
    };

    for (long i = 0; i < currTail; i++) {
        //process edge <u,v>
        eid_t e1 = curr[i];

        Edge edge = edgeIdtoEdge[e1];

        vid_t u = edge.u;
        vid_t v = edge.v;

        eid_t uStart = g->num_edges[u], uEnd = off_end[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = off_end[v + 1];

        eid_t off_nei_u = uStart, off_nei_v = vStart;
        intersection_res.clear();
        if (uEnd - uStart > 0 && vEnd - vStart > 0) {
            SetIntersection(g, uStart, uEnd, vStart, vEnd, intersection_res);
            for (auto pair: intersection_res) {
                std::tie(off_nei_v, off_nei_u) = pair;
                eid_t e2 = g->eid[off_nei_v + adj_relative_off[off_nei_v]];  //<v,w>
                eid_t e3 = g->eid[off_nei_u + adj_relative_off[off_nei_u]];  //<u,w>
                //If e1, e2, e3 forms a triangle
                if ((!processed[e2]) && (!processed[e3])) {
                    //Decrease support of both e2 and e3
                    if (EdgeSupport[e2] > level && EdgeSupport[e3] > level) {
                        //Process e2
                        serial_sup_updater(e2);
                        //Process e3
                        serial_sup_updater(e3);
                    } else if (EdgeSupport[e2] > level) {
                        //process e2
                        serial_sup_updater(e2);
                    } else if (EdgeSupport[e3] > level) {
                        //process e3
                        serial_sup_updater(e3);
                    }
                }
            }
        }
        processed[e1] = true;
        is_vertex_updated[u] = true;
        is_vertex_updated[v] = true;
        local_removal_record[BranchFreeBinarySearch(g->adj, uStart, uEnd, v)] = true;
        local_removal_record[BranchFreeBinarySearch(g->adj, vStart, vEnd, u)] = true;
    }
}

/**   Serial PKT_intersection Algorithm  ***/
void PKT_serial_intersection(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {
    size_t tc_cnt = 0;
    long numEdges = g->m / 2;
    long n = g->n;

    /*
     * local_removal_record: 2m
     * off_end: n
     * adj_relative_off: 2m
     */
    bool *local_removal_record = (bool *) malloc(2 * numEdges * sizeof(bool));
    memset(local_removal_record, 0, 2 * numEdges * sizeof(bool));

    bool *is_vertex_updated = (bool *) malloc(g->n * sizeof(bool));
    memset(is_vertex_updated, 0, g->n * sizeof(bool));

    vector<eid_t> off_end(n + 1);
    memcpy(&off_end.front(), g->num_edges, sizeof(eid_t) * (n + 1));

    vector<eid_t> adj_relative_off(2 * numEdges, 0);

    //An array to mark processed array
    bool *processed = (bool *) malloc(numEdges * sizeof(bool));
    assert(processed != nullptr);

    long currTail = 0;
    long nextTail = 0;

    auto *curr = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(curr != nullptr);

    auto *next = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(next != nullptr);

    auto *startEdge = (eid_t *) malloc(n * sizeof(eid_t));
    assert(startEdge != nullptr);

    //Initialize the arrays
    for (eid_t e = 0; e < numEdges; e++) {
        processed[e] = false;
    }

    //Find the startEdge for each vertex
    for (vid_t i = 0; i < n; i++) {
        eid_t j = g->num_edges[i];
        eid_t endIndex = g->num_edges[i + 1];

        while (j < endIndex) {
            if (g->adj[j] > i)
                break;
            j++;
        }
        startEdge[i] = j;
    }

#if TIME_RESULTS
    double triTime = 0;
    double scanTime = 0;
    double procTime = 0;
    double startTime = timer();
#endif
    Timer iter_timer;
#pragma omp parallel for schedule(dynamic, 6000) reduction(+:tc_cnt)
    for (auto i = 0u; i < g->m; i++)
        ComputeSupport(g, EdgeSupport, tc_cnt, i);
#pragma omp single
    log_trace("TC Cnt: %'zu", tc_cnt / 3);

#if TIME_RESULTS
    triTime = timer() - startTime;
    startTime = timer();
#endif

    //Support computation is done
    //Computing support now
    int level = 0;
    long todo = numEdges;

    log_trace("Before Level-Processing: %.9lfs", iter_timer.elapsed());
    iter_timer.reset();
    while (todo > 0) {

        log_trace("Current Level: %d, Elapsed Time: %.9lfs", level, iter_timer.elapsed());
        iter_timer.reset();
#if TIME_RESULTS
        startTime = timer();
#endif

        PKT_scan_serial(numEdges, EdgeSupport, level, curr, &currTail,
                        g, local_removal_record, off_end, adj_relative_off, is_vertex_updated);

#if TIME_RESULTS
        scanTime += timer() - startTime;
        startTime = timer();
#endif

        while (currTail > 0) {
            todo -= currTail;

            PKT_processSubLevel_serial_intersection(g, curr, currTail, EdgeSupport, level, next, &nextTail, processed,
                                                    edgeIdToEdge, local_removal_record, off_end, adj_relative_off,
                                                    is_vertex_updated);
            swap(curr, next);
            currTail = nextTail;
            nextTail = 0;
        }

#if TIME_RESULTS
        procTime += timer() - startTime;
#endif
        level = level + 1;
    }

#if TIME_RESULTS
    log_info("Tri time: %9.3lf  Scan Time: %9.3lf  Proc Time: %9.3lf", triTime, scanTime, procTime);
    log_info("PKT-serial-Time-Intersection: %9.3lf", triTime + scanTime + procTime);
#endif

    //Free memory
    free(next);
    free(curr);
    free(processed);
    free(startEdge);

    free(local_removal_record);
}
