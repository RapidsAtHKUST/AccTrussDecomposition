//
// Created by yche on 6/19/19.
//

#include <cassert>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "../util/timer.h"
#include "util/log/log.h"
#include "opt_pkt/parallel_all_edge_cnc.h"

void PKT_scan_serial(long numEdges, const int *EdgeSupport, int level, eid_t *curr, long *currTail, graph_t *g,
                     bool *local_removal_record, vector<eid_t> &off_end, vector<eid_t> &adj_relative_off,
                     bool *is_vertex_updated);

//Serially process sublevel in a level using marking
void PKT_processSubLevel_serial_marking(graph_t *g, eid_t *curr, long currTail, int *EdgeSupport,
                                        int level, eid_t *next, long *nextTail, MapType &X, bool *processed,
                                        Edge *edgeIdtoEdge, bool *local_removal_record,
                                        vector<eid_t> &off_end, vector<eid_t> &adj_relative_off,
                                        bool *is_vertex_updated) {
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
        if (vEnd - vStart > uEnd - uStart) {
            swap(u, v);
        }
        uStart = g->num_edges[u], uEnd = off_end[u + 1];
        vStart = g->num_edges[v], vEnd = off_end[v + 1];
        //Check the adj list of vertex v
        for (eid_t j = vStart; j < vEnd; j++) {
            vid_t w = g->adj[j];

            if (X[u].contains(w)) {
                eid_t e2 = g->eid[j + adj_relative_off[j]];  //<v,w>
                eid_t e3 = X[u][w]; //<u,w>

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
//        X[u].erase(v);    // Not necessary because of !processed[e3]
//        X[v].erase(u);    // Not necessary because of !processed[e3]
        local_removal_record[BranchFreeBinarySearch(g->adj, uStart, uEnd, v)] = true;
        local_removal_record[BranchFreeBinarySearch(g->adj, vStart, vEnd, u)] = true;
    }
}


/**   Serial PKT_marking Algorithm  ***/
void PKT_serial_marking(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {
    Timer convert_timer;
    auto edgeToIdMap = Convert(g, edgeIdToEdge, (g->m / 2));
    log_info("Hash Map Construction Cost: %.6lfs", convert_timer.elapsed());

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

    Timer iter_timer;

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
    //Computing truss now

    int level = 0;
    long todo = numEdges;
#pragma omp single
    {
        log_trace("Before Level-Processing: %.9lfs", iter_timer.elapsed());
        iter_timer.reset();
    }
    while (todo > 0) {
#pragma omp single
        {
            log_trace("Current Level: %d, Elapsed Time: %.9lfs", level, iter_timer.elapsed());
            iter_timer.reset();
        }

#if TIME_RESULTS
        startTime = timer();
#endif

        PKT_scan_serial(numEdges, EdgeSupport, level, curr, &currTail, g, local_removal_record, off_end,
                        adj_relative_off, is_vertex_updated);

#if TIME_RESULTS
        scanTime += timer() - startTime;
        startTime = timer();
#endif

        while (currTail > 0) {
            todo = todo - currTail;

            PKT_processSubLevel_serial_marking(g, curr, currTail, EdgeSupport, level, next, &nextTail, edgeToIdMap,
                                               processed, edgeIdToEdge, local_removal_record, off_end, adj_relative_off,
                                               is_vertex_updated);

            eid_t *tempCurr = curr;
            curr = next;
            next = tempCurr;

            currTail = nextTail;
            nextTail = 0;
        }

#if TIME_RESULTS
        procTime += timer() - startTime;
#endif

        level = level + 1;
    }

#if TIME_RESULTS
    log_info("Tri time: %9.3lf \nScan Time: %9.3lf \nProc Time: %9.3lf", triTime, scanTime, procTime);
    log_info("PKT-serial-Time-marking: %9.3lf", triTime + scanTime + procTime);
#endif

    //Free memory
    free(next);
    free(curr);
    free(processed);
    free(startEdge);
}