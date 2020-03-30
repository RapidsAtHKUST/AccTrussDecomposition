#include <cassert>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "../util/timer.h"
#include "util/log/log.h"
#include "opt_pkt/parallel_all_edge_cnc.h"
#include "util/intersection/set_utils.h"

void PKT_scan_serial(long numEdges, int *EdgeSupport, int level, eid_t *curr, long *currTail) {
    for (long i = 0; i < numEdges; i++) {
        if (EdgeSupport[i] == level) {
            curr[(*currTail)] = i;
            (*currTail) = (*currTail) + 1;
        }
    }
}

//Serially process sub-level in a level using intersection
void PKT_processSubLevel_serial_intersection(graph_t *g, eid_t *curr, long currTail, int *EdgeSupport,
                                             int level, eid_t *next, long *nextTail, bool *processed,
                                             Edge *edgeIdtoEdge) {
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

        eid_t uStart = g->num_edges[u], uEnd = g->num_edges[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = g->num_edges[v + 1];

        eid_t off_nei_u = uStart, off_nei_v = vStart;
        intersection_res.clear();
        if (uEnd - uStart > 0 && vEnd - vStart > 0) {
            SetIntersection(g, uStart, uEnd, vStart, vEnd, intersection_res);
            for (auto pair: intersection_res) {
                std::tie(off_nei_v, off_nei_u) = pair;
                eid_t e2 = g->eid[off_nei_v];  //<v,w>
                eid_t e3 = g->eid[off_nei_u];  //<u,w>
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
    }
}

/**   Serial PKT_intersection Algorithm  ***/
void PKT_serial_intersection(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {
    size_t tc_cnt = 0;
    long numEdges = g->m / 2;
    long n = g->n;

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

        PKT_scan_serial(numEdges, EdgeSupport, level, curr, &currTail);

#if TIME_RESULTS
        scanTime += timer() - startTime;
        startTime = timer();
#endif

        while (currTail > 0) {
            todo -= currTail;

            PKT_processSubLevel_serial_intersection(g, curr, currTail, EdgeSupport, level, next, &nextTail, processed,
                                                    edgeIdToEdge);
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
}
