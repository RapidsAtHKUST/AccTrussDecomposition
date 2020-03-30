#include <cstdlib>
#include <cassert>

#include <omp.h>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "util/log/log.h"
#include "opt_pkt/parallel_all_edge_cnc.h"
#include "../util/timer.h"
#include "util/intersection/set_utils.h"

extern int NUM_THREADS;

/**   Ros algorithms for truss decomposition
 *    Computes the support of each edge in parallel
 *    Computes k-truss in serial -- similar to WC algorithm
 *
 *    Ryan A. Rossi, "Fast Triangle Core Decomposition for Mining Large Graphs", in Proc.
 *    Pacific-Asia Conference on Advances in Knowledge Discovery and Data Mining (PAKDD), 2014
 *
 *    ****/
void Ros(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge) {

    long numEdges = g->m / 2;

#if TIME_RESULTS
    double supTime = 0.0, procTime = 0.0;
    double startTime = timer();
#endif
    int maxSupport = 0;
    size_t tc_cnt = 0;
    //parallel region
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
#if TIME_RESULTS
        if (tid == 0) {
            startTime = timer();
        }
#endif

        //Compute the support of each edge in parallel
        //Compute the support of each edge
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt) reduction(max:maxSupport)
        for (auto i = 0u; i < g->m; i++) {
            auto sup = ComputeSupport(g, EdgeSupport, tc_cnt, i);
            maxSupport = max(maxSupport, sup);
        }
#pragma omp single
        {
            log_trace("TC Cnt: %'zu", tc_cnt / 3);
            log_trace("Max Sup: %d", maxSupport);
        }

#if TIME_RESULTS
        if (tid == 0) {
            supTime = timer() - startTime;
        }
#endif
    }  //End of parallel region

    //Copmute k-truss using bin-sort
    //Sorted edges array according to increasing support
    eid_t *sortedEdges = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(sortedEdges != NULL);

    //Position of edge in sortedEdges
    eid_t *edgePos = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(edgePos != NULL);

    //number of bins is (maxSupport + 2)
    //the support is in: 0 ... maxSupport
    //number of values: maxSupport +1
    unsigned int *bin = (unsigned int *) malloc((maxSupport + 2) * sizeof(unsigned int));
    assert(bin != NULL);

    for (long i = 0; i < maxSupport + 2; i++)
        bin[i] = 0;

#if TIME_RESULTS
    startTime = timer();
#endif

    //Find number of edges for each support in: 0...maxSupport
    for (long i = 0; i < numEdges; i++) {
        bin[EdgeSupport[i]]++;
    }

    unsigned int start = 0;
    for (int support = 0; support < maxSupport + 1; support++) {
        unsigned int num = bin[support];
        bin[support] = start;
        start = start + num;
    }

    //Do bin-sort/bucket-sort of the edges
    //sortedEdges -- contains the edges in increasing order of support
    //edgePos -- contains the position of an edge in sortedEdges array
    for (long i = 0; i < numEdges; i++) {
        edgePos[i] = bin[EdgeSupport[i]];
        sortedEdges[edgePos[i]] = i;
        bin[EdgeSupport[i]]++;
    }

    for (int d = maxSupport; d >= 1; d--)
        bin[d] = bin[d - 1];
    bin[0] = 0;

    //STEP 3: Compute k-truss using support of each edge
    //an array to mark processed edges
    bool *proc = (bool *) malloc(numEdges * sizeof(bool));
    assert(proc != NULL);

    for (long i = 0; i < numEdges; i++) {
        proc[i] = false;
    }

    log_trace("Ktruss Comp Begin...");
    //k-truss computations
    //Edges are processed in increasing order of support
    int k = 0;
    Timer gtimer;
    eid_t off_nei_u, off_nei_v;
    vector<pair<eid_t, eid_t >> intersection_res;

    for (long i = 0; i < numEdges; i++) {
        eid_t e = sortedEdges[i];
        auto e_sup = EdgeSupport[e];
        if (e_sup > k) {
            log_info("Finish k: %d, Elapsed: %.9lfs, Deleted: %'lld", k, gtimer.elapsed(), i);
            k++;
            gtimer.reset();
        }
        Edge edge = edgeIdToEdge[e];
        vid_t u = edge.u;
        vid_t v = edge.v;

        intersection_res.clear();
        SetIntersection(g, g->num_edges[u], g->num_edges[u + 1], g->num_edges[v], g->num_edges[v + 1],
                        intersection_res);
        for (auto pair: intersection_res) {
            std::tie(off_nei_v, off_nei_u) = pair;
            eid_t e2 = g->eid[off_nei_v];  //<v,w>
            eid_t e3 = g->eid[off_nei_u];  //<u,w>

            if (!proc[e2] && !proc[e3]) {  //if e, e2, e3 forms a triangle
                for (int numAdj = 0; numAdj < 2; numAdj++) {
                    eid_t edgeId = e2;
                    if (numAdj == 1)
                        edgeId = e3;

                    if (EdgeSupport[edgeId] > EdgeSupport[e]) {
                        int supportEid = EdgeSupport[edgeId];
                        unsigned int posEid = edgePos[edgeId];

                        unsigned int startPos = bin[supportEid]; //First position with support supportEid
                        unsigned int firstEdgeId = sortedEdges[startPos];

                        //Swap firstEdgeId and edgeId
                        if (firstEdgeId != edgeId) {
                            edgePos[edgeId] = startPos;
                            sortedEdges[posEid] = firstEdgeId;
                            edgePos[firstEdgeId] = posEid;
                            sortedEdges[startPos] = edgeId;
                        }

                        //Increase the starting index of bin[ supportEid ]
                        bin[supportEid]++;

                        //Decrease support of edgeId -- so edgeId is in previous bin now
                        EdgeSupport[edgeId] = EdgeSupport[edgeId] - 1;
                    }
                }
            }
        }
        proc[e] = true;
    }  //end of for loop
    log_info("Finish k: %d, Elapsed: %.9lfs", k, gtimer.elapsed());

#if TIME_RESULTS
    procTime = timer() - startTime;
    log_trace("support time: %9.3lf, proc time: %9.3lf", supTime, procTime);
    log_trace("Ros Time: %9.3lf", supTime + procTime);
#endif

    /*****     Free Memory    ******/
    free(proc);
    free(sortedEdges);
    free(edgePos);
    free(bin);

}


