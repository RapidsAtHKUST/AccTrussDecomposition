#include <cassert>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "util/log/log.h"
#include "../util/timer.h"
#include "opt_pkt/parallel_all_edge_cnc.h"

/**   WC algorithm for truss decomposition
 *
 * J.Wang and J. Cheng, "Truss decomposition in massive networks", Proc. VLDB Endow., vol 5, no 9, pp.
 * 812-823, May 2012.
 *
 * */
void WCJames(graph_t *g, int *EdgeSupport, MapType &edgeToIdMap, Edge *edgeIdToEdge) {
    long m = g->m;

    auto *deg = (unsigned int *) malloc(g->n * sizeof(unsigned int));
    assert(deg != nullptr);

    for (long i = 0; i < g->n; i++) {
        deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
    }


    long numEdges = m / 2;
    int maxSupport = 0;

    size_t tc_cnt = 0;
    //STEP 1: Computer Support for each edge
    //Maximum support of an edge
#if TIME_RESULTS
    double procTime, supTime;
    double startTime = timer();
#endif
#pragma omp parallel
    {
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
        supTime = timer() - startTime;
#endif
    }
    log_trace("Finish Sup");

    //STEP 2: sort the edges in ascending order of their support -- using bin-sort
    auto *sortedEdges = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(sortedEdges != nullptr);

    auto *edgePos = (eid_t *) malloc(numEdges * sizeof(eid_t));
    assert(edgePos != nullptr);

    //number of bins is (maxSupport + 2)
    //the support is in: 0 ... maxSupport
    auto *bin = (unsigned int *) calloc(maxSupport + 2, sizeof(unsigned int));
    assert(bin != nullptr);

    for (long i = 0; i < maxSupport + 2; i++)
        bin[i] = 0;

#if TIME_RESULTS
    startTime = timer();
#endif

    //Find number of edges with each support in 0...maxSupport
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
    log_trace("Finish Sort");

    //STEP 3: Compute k-truss using support of each edge
    int k = 2;

    //k-truss computations
    long i = 0;
    long numEdgesDeleted = 0;

#ifdef NAIVE_ITER_WITH_PROC
    bool *proc = (bool *) malloc(numEdges * sizeof(bool));
    assert(proc != nullptr);

    for (long ii = 0; ii < numEdges; ii++) {
        proc[ii] = false;
    }
#endif

    Timer global_timer;
    auto sup_updater = [EdgeSupport, edgePos, bin, sortedEdges](eid_t edgeId, int k) {
        if (EdgeSupport[edgeId] > k - 2) {

            //swap edge <v,w> with the first edge in the bin[ EdgeSupport[edgeId] ]
            int supportWV = EdgeSupport[edgeId];
            unsigned int posWV = edgePos[edgeId];

            unsigned int startPos = bin[supportWV]; //First position with support supportWV
            unsigned int firstEdgeId = sortedEdges[startPos];

            //Swap firstEdgeId and edgeId
            if (firstEdgeId != edgeId) {
                edgePos[edgeId] = startPos;
                sortedEdges[posWV] = firstEdgeId;
                edgePos[firstEdgeId] = posWV;
                sortedEdges[startPos] = edgeId;
            }

            //Increase the starting index of bin[ supportWV ]
            bin[supportWV]++;

            //Decrease support of edgeId -- so edgeId is in previous bin now
            EdgeSupport[edgeId] = EdgeSupport[edgeId] - 1;
        }
    };

    while (numEdgesDeleted < numEdges) {
        //If edge sortedEdges[i] has support <= k-2
        while (i < numEdges && EdgeSupport[sortedEdges[i]] <= k - 2) {
            eid_t e = sortedEdges[i];

            Edge edge = edgeIdToEdge[e];
            vid_t u = edge.u;
            vid_t v = edge.v;

            //Make sure: deg(u) < deg(v)
            if (deg[v] < deg[u]) {
                //swap u and v
                vid_t temp = v;
                v = u;
                u = temp;
            }

            //Now, deg(u) < deg(v)
#ifdef NAIVE_ITER_WITH_PROC
            for (eid_t j = g->num_edges[u]; j < g->num_edges[u + 1]; j++) {
                vid_t w = g->adj[j];
                //If <u,w> is an edge
                if (!proc[g->eid[j]]) {
                    //If <v,w> is an edge
                    if (edgeToIdMap[v].contains(w)) {
                        //find edgeId of edge e(v,w), If edge support of  <v,w> > k-2 then deccrement it
                        sup_updater(edgeToIdMap[v][w], k);

                        //find edgeId of edge <u,w>, If edge support of  <u,w> > k-2 then decrement it
                        sup_updater(edgeToIdMap[u][w], k);
                    }  //<v,w> is an edge
                } //<u,w> is an edge
            } // w is in N(u)
#else
            for (auto pair: edgeToIdMap[u]) {
                auto w = pair.first;
                //If <v,w> is an edge
                if (edgeToIdMap[v].contains(w)) {
                    sup_updater(edgeToIdMap[v][w], k);
                    sup_updater(pair.second, k);
                }
            }
#endif

            i++;
            numEdgesDeleted++;

            //Delete edge 'e' from the graph
#ifdef NAIVE_ITER_WITH_PROC
            proc[edgeToIdMap[u][v]] = true;
#endif
            edgeToIdMap[u].erase(v);
            edgeToIdMap[v].erase(u);
        }
        log_trace("Finish k: %d, Elapsed: %.9lfs, Deleted: %'lld", k, global_timer.elapsed(), numEdgesDeleted);
        global_timer.reset();
        k++;
    }

#if TIME_RESULTS
    procTime = timer() - startTime;
    log_trace("Support Time: %9.3lfs, Proc Time: %9.3lfs", supTime, procTime);
    log_trace("WC Time: %9.3lf", supTime + procTime);
#endif

#ifdef NAIVE_ITER_WITH_PROC
    free(proc);
#endif
}