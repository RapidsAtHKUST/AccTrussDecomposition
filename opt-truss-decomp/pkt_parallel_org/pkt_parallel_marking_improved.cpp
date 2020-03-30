//
// Created by yche on 6/18/19.
//

#include <cstdio>
#include <cassert>

#include <omp.h>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "../util/timer.h"

#include "opt_pkt/parallel_all_edge_cnc.h"
#include "pkt_support_update_utils_legacy.h"

//Process a sublevel in a level using marking based approach
void PKT_processSubLevel_marking(graph_t *g, eid_t *curr, bool *InCurr, long currTail, int *EdgeSupport, int level,
                                 eid_t *next, bool *InNext, long *nextTail, MapType &X, bool *processed,
                                 Edge *edgeIdtoEdge) {

    //Size of cache line
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    vid_t buff[BUFFER_SIZE];
    long index = 0;

    SupportUpdaterLegacy sup_updater(&index, buff, next, EdgeSupport, InNext, nextTail, level, BUFFER_SIZE);

#pragma omp for schedule(dynamic, 4)
    for (long i = 0; i < currTail; i++) {

        //process edge <u,v>
        eid_t e1 = curr[i];

        Edge edge = edgeIdtoEdge[e1];

        vid_t u = edge.u;
        vid_t v = edge.v;

        if (g->num_edges[v + 1] - g->num_edges[v] > g->num_edges[u + 1] - g->num_edges[u]) {
            swap(u, v);
        }
        //Check the adj list of vertex v
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
            vid_t w = g->adj[j];
            if (X[u].contains(w)) {
                eid_t e2 = g->eid[j];  //<v,w>
                eid_t e3 = X[u][w]; //<u,w>

                //If e1, e2, e3 forms a triangle
                if ((!processed[e2]) && (!processed[e3])) {

                    //Decrease support of both e2 and e3
                    if (EdgeSupport[e2] > level && EdgeSupport[e3] > level) {

                        //Process e2
                        sup_updater(e2);

                        //Process e3
                        sup_updater(e3);

                    } else if (EdgeSupport[e2] > level) {

                        //process e2 only if e1 < e3
                        if (e1 < e3 && InCurr[e3]) {
                            sup_updater(e2);
                        }
                        if (!InCurr[e3]) { //if e3 is not in curr array then decrease support of e2
                            sup_updater(e2);
                        }
                    } else if (EdgeSupport[e3] > level) {
                        //process e3 only if e1 < e2
                        if (e1 < e2 && InCurr[e2]) {
                            sup_updater(e3);
                        }
                        if (!InCurr[e2]) { //if e2 is not in curr array then decrease support of e3
                            sup_updater(e3);
                        }
                    }
                }
            }
        }
    }

    if (index > 0) {
        long tempIdx = __sync_fetch_and_add(nextTail, index);;
        for (long bufIdx = 0; bufIdx < index; bufIdx++)
            next[tempIdx + bufIdx] = buff[bufIdx];
    }

#pragma omp barrier

#pragma omp for schedule(static)
    for (long i = 0; i < currTail; i++) {
        eid_t e = curr[i];

        processed[e] = true;
        InCurr[e] = false;
    }

#pragma omp barrier


}


/**   Computes the support of each edge in parallel
 *    Computes k-truss in parallel   ****/
void PKT_marking(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {
    Timer convert_timer;
    auto edgeToIdMap = Convert(g, edgeIdToEdge, (g->m / 2));
    log_info("Hash Map Construction Cost: %.6lfs", convert_timer.elapsed());

    log_trace("PKT_marking");

    long numEdges = g->m / 2;
    long n = g->n;

    size_t tc_cnt = 0;
    bool *processed = (bool *) malloc(numEdges * sizeof(bool));
    assert(processed != NULL);

    long currTail = 0;
    long nextTail = 0;

    eid_t *curr = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(curr != NULL);

    bool *InCurr = (bool *) malloc(numEdges * sizeof(bool));
    assert(InCurr != NULL);

    eid_t *next = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(next != NULL);

    bool *InNext = (bool *) malloc(numEdges * sizeof(bool));
    assert(InNext != NULL);

    eid_t *startEdge = (eid_t *) malloc(n * sizeof(eid_t));
    assert(startEdge != NULL);

    Timer iter_timer;
    log_trace("Begin Comp");
    //parallel region
#pragma omp parallel
    {
        int tid = omp_get_thread_num();

        eid_t *X = (eid_t *) malloc(g->n * sizeof(eid_t));
        assert(X != NULL);

        for (vid_t i = 0; i < g->n; i++) {
            X[i] = 0;
        }

#pragma omp for schedule(static)
        for (eid_t e = 0; e < numEdges; e++) {
            //Initialize processed array with false
            processed[e] = false;

            InCurr[e] = false;
            InNext[e] = false;
        }


#pragma omp for schedule(static)
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
        double start = timer();
#endif

#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
        for (auto i = 0u; i < g->m; i++)
            ComputeSupport(g, EdgeSupport, tc_cnt, i);
#pragma omp single
        log_trace("TC Cnt: %'zu", tc_cnt / 3);


#if TIME_RESULTS
        triTime = timer() - start;
        start = timer();
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
            start = timer();
#endif

            PKT_scan(numEdges, EdgeSupport, level, curr, &currTail, InCurr);

#if TIME_RESULTS
            scanTime += timer() - start;
            start = timer();
#endif

            while (currTail > 0) {
                todo = todo - currTail;

                PKT_processSubLevel_marking(g, curr, InCurr, currTail, EdgeSupport, level, next, InNext, &nextTail, edgeToIdMap,
                                            processed, edgeIdToEdge);

                if (tid == 0) {
                    eid_t *tempCurr = curr;
                    curr = next;
                    next = tempCurr;

                    bool *tempInCurr = InCurr;
                    InCurr = InNext;
                    InNext = tempInCurr;


                    currTail = nextTail;
                    nextTail = 0;
                }

#pragma omp barrier
            }

#if TIME_RESULTS
            procTime += timer() - start;
#endif

            level = level + 1;
#pragma omp barrier

        }


#if TIME_RESULTS
        if (tid == 0) {
            log_info("Tri time: %9.3lfs, Scan Time: %9.3lfs, Proc Time: %9.3lfs", triTime, scanTime, procTime);
            log_info("PKT-intersection-Time: %9.3lfs", triTime + scanTime + procTime);
        }
#endif

        free(X);

    }  //End of parallel region

    //Free memory
    free(next);
    free(InNext);
    free(curr);
    free(InCurr);
    free(processed);
    free(startEdge);
}

