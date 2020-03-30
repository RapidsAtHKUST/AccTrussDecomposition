/* ********************************************************************************************
 *  PKT: Shared-memory Graph Truss Decomposition
 *  Authors: Humayun Kabir and Kamesh Madduri  {hzk134, madduri}@cse.psu.edu 
 *  Description: A parallel graph k-truss decomposition algorithm for shared-memory system. It 
 *  is designed for large sparse graphs.     
 * 
 *  Please cite the following paper, if you are using PKT: 
 *  H. Kabir and K. Madduri, "Shared-memory Graph Truss Decomposition", arXiv.org e-Print archive,
 *  https://arxiv.org/abs/1707.02000, July 2017
 * ********************************************************************************************/

#include <cstdio>
#include <cassert>
#include <omp.h>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "../util/timer.h"

#include "opt_pkt/parallel_all_edge_cnc.h"

#include "iter_stat_helper_legacy.h"
#include "pkt_support_update_utils_legacy.h"

/*******************************************************************************************************/
void PKT_scan(long numEdges, int *EdgeSupport, int level, eid_t *curr, long *currTail, bool *InCurr) {
    // Size of cache line
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    vid_t buff[BUFFER_SIZE];
    long index = 0;

#pragma omp for schedule(static)
    for (long i = 0; i < numEdges; i++) {
        if (EdgeSupport[i] == level) {
            buff[index] = i;
            InCurr[i] = true;
            index++;

            if (index >= BUFFER_SIZE) {
                long tempIdx = __sync_fetch_and_add(currTail, BUFFER_SIZE);

                for (long j = 0; j < BUFFER_SIZE; j++) {
                    curr[tempIdx + j] = buff[j];
                }
                index = 0;
            }
        }
    }

    if (index > 0) {
        long tempIdx = __sync_fetch_and_add(currTail, index);

        for (long j = 0; j < index; j++) {
            curr[tempIdx + j] = buff[j];
        }
    }

#pragma omp barrier

}

//Process a sublevel in a level using intersection based approach
void PKT_processSubLevel_intersection(graph_t *g, eid_t *curr, bool *InCurr, long currTail, int *EdgeSupport,
                                      int level, eid_t *next, bool *InNext, long *nextTail, bool *processed,
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

        eid_t uStart = g->num_edges[u], uEnd = g->num_edges[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = g->num_edges[v + 1];

        unsigned int numElements = (uEnd - uStart) + (vEnd - vStart);
        eid_t j_index = uStart, k_index = vStart;

        for (unsigned int innerIdx = 0; innerIdx < numElements; innerIdx++) {
            if (j_index >= uEnd) {
                break;
            } else if (k_index >= vEnd) {
                break;
            } else if (g->adj[j_index] == g->adj[k_index]) {

                eid_t e2 = g->eid[k_index];  //<v,w>
                eid_t e3 = g->eid[j_index];  //<u,w>


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
                j_index++;
                k_index++;
            } else if (g->adj[j_index] < g->adj[k_index]) {
                j_index++;
            } else if (g->adj[k_index] < g->adj[j_index]) {
                k_index++;
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
void PKT_intersection(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {
    log_trace("PKT_intersection");

    long numEdges = g->m / 2;
    long n = g->n;

    bool *processed = (bool *) malloc(numEdges * sizeof(bool));
    assert(processed != nullptr);

    long currTail = 0;
    long nextTail = 0;

    auto *curr = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(curr != nullptr);

    bool *InCurr = (bool *) malloc(numEdges * sizeof(bool));
    assert(InCurr != nullptr);

    auto *next = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(next != nullptr);

    bool *InNext = (bool *) malloc(numEdges * sizeof(bool));
    assert(InNext != nullptr);

    auto *startEdge = (eid_t *) malloc(n * sizeof(eid_t));
    assert(startEdge != nullptr);

    Timer iter_timer;
    Timer process_timer;
    size_t iter_num = 0;
    size_t local_iter_num = 0;
    log_trace("Begin Comp");
    size_t tc_cnt = 0;
    //parallel region
#pragma omp parallel
    {
        int tid = omp_get_thread_num();

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

#pragma omp barrier
#pragma omp single
        log_info("Before TC... %lld, %lld", g->n, g->m);

        IterStatTLS iter_stat_tls;
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
        for (auto i = 0u; i < g->m; i++)
        {
#ifdef BASELINE_TC
            ComputeSupportBaseLine(g, EdgeSupport, tc_cnt, i);
#else
            ComputeSupport(g, EdgeSupport, tc_cnt, i);
#endif
        }

#pragma omp single
        log_trace("TC Cnt: %'zu", tc_cnt / 3);
        iter_stat_tls.triTime = iter_stat_tls.local_timer.elapsed_and_reset();
        iter_timer.reset();
#pragma omp barrier

        //Support computation is done
        //Computing truss now
        int level = 0;
        long todo = numEdges;


        while (todo > 0) {
#pragma omp single
            {
                iter_stat_tls.PrintIterStat(iter_timer, todo, numEdges, level, iter_num, local_iter_num);
            }
            iter_stat_tls.ResetLocalTime();
            iter_stat_tls.RecordSyncTime();

            PKT_scan(numEdges, EdgeSupport, level, curr, &currTail, InCurr);
            iter_stat_tls.RecordSCANTime();

            while (currTail > 0) {
                todo = todo - currTail;

#ifdef HANDLE_SKEW
                PKT_processSubLevel_intersection_handling_skew(g, curr, InCurr, currTail, EdgeSupport, level, next,
                                                               InNext, &nextTail,
                                                               processed, edgeIdToEdge);
#else
                PKT_processSubLevel_intersection(g, curr, InCurr, currTail, EdgeSupport, level, next, InNext, &nextTail,
                                                 processed, edgeIdToEdge);
#endif

#pragma omp single
                {
                    swap(curr, next);
                    swap(InCurr, InNext);
                    iter_stat_tls.RecordIterNum(iter_num, local_iter_num);

                    currTail = nextTail;
                    nextTail = 0;
                }
#pragma omp barrier
            }
            iter_stat_tls.RecordProcessTime();
            level = level + 1;
#pragma omp barrier
        }
#pragma omp single
        iter_stat_tls.PrintFinalStat(level, 0);
    }  //End of parallel region

    //Free memory
    free(next);
    free(InNext);
    free(curr);
    free(InCurr);
    free(processed);
    free(startEdge);
}

