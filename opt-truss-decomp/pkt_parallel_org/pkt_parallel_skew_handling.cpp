//
// Created by yche on 6/17/19.
//

#include <functional>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/intersection/set_utils.h"

//Process a sublevel in a level using intersection based approach
void PKT_processSubLevel_intersection_handling_skew
        (graph_t *g, eid_t *curr, bool *InCurr, long currTail, int *EdgeSupport,
         int level, eid_t *next, bool *InNext, long *nextTail, bool *processed,
         Edge *edgeIdtoEdge) {
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    vid_t buff[BUFFER_SIZE];
    long index = 0;

    auto update_functor = [&index, &buff, &next, EdgeSupport,
            InNext, nextTail, level](eid_t updated_edge) {
        int supE2 = __sync_fetch_and_sub(&EdgeSupport[updated_edge], 1);
        if (supE2 == (level + 1)) {
            buff[index] = updated_edge;
            InNext[updated_edge] = true;
            index++;
        }

        if (supE2 <= level) {
            __sync_fetch_and_add(&EdgeSupport[updated_edge], 1);
        }

        if (index >= BUFFER_SIZE) {
            long tempIdx = __sync_fetch_and_add(nextTail, BUFFER_SIZE);

            for (long bufIdx = 0; bufIdx < BUFFER_SIZE; bufIdx++)
                next[tempIdx + bufIdx] = buff[bufIdx];
            index = 0;
        }
    };

#pragma omp for schedule(dynamic, 4)
    for (long i = 0; i < currTail; i++) {

        //process edge <u,v>
        eid_t e1 = curr[i];

        Edge edge = edgeIdtoEdge[e1];

        vid_t u = edge.u;
        vid_t v = edge.v;

        eid_t uStart = g->num_edges[u], uEnd = g->num_edges[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = g->num_edges[v + 1];

        eid_t off_nei_u = uStart, off_nei_v = vStart;

        static thread_local vector<pair<eid_t, eid_t >> intersection_res;
        intersection_res.clear();
        if (uEnd - uStart > 0 && vEnd - vStart > 0) {
            SetIntersection(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res);
            for (auto pair: intersection_res) {
                std::tie(off_nei_v, off_nei_u) = pair;
                eid_t e2 = g->eid[off_nei_v];  //<v,w>
                eid_t e3 = g->eid[off_nei_u];  //<u,w>

                //If e1, e2, e3 forms a triangle
                if ((!processed[e2]) && (!processed[e3])) {
                    //Decrease support of both e2 and e3
                    if (EdgeSupport[e2] > level && EdgeSupport[e3] > level) {
                        //Process e2
                        update_functor(e2);

                        //Process e3
                        update_functor(e3);
                    } else if (EdgeSupport[e2] > level) {
                        //process e2 only if e1 < e3
                        if (e1 < e3 && InCurr[e3]) {
                            update_functor(e2);
                        }
                        if (!InCurr[e3]) { //if e3 is not in curr array then decrease support of e2
                            update_functor(e2);
                        }
                    } else if (EdgeSupport[e3] > level) {
                        //process e3 only if e1 < e2
                        if (e1 < e2 && InCurr[e2]) {
                            update_functor(e3);
                        }
                        if (!InCurr[e2]) { //if e2 is not in curr array then decrease support of e3
                            update_functor(e3);
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