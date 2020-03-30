//
// Created by yche on 6/18/19.
//

#include <stdio.h>
#include <functional>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/timer.h"
#include "util/containers/boolarray.h"

#include "parallel_all_edge_cnc.h"
#include "pkt_support_update_utils.h"
#include "iter_helper.h"

using word_type = uint32_t;

//Process a sub-level in a level using marking based approach
void PKT_processSubLevel_marking(graph_t *g, eid_t *curr,
#ifndef BMP_QUEUE
        bool *InCurr,
#else
                                 BoolArray<word_type> &InCurr,
#endif
                                 long currTail, int *EdgeSupport, int level, eid_t *next,
#ifndef BMP_QUEUE
        bool *InNext,
#else
                                 BoolArray<word_type> &InNext,
#endif
                                 long *nextTail, MapType &X,
#ifndef BMP_PROCESSED
        bool *processed,
#else
                                 BoolArray<word_type> &processed,
#endif
                                 Edge *edgeIdtoEdge, eid_t *off_end,
                                 bool *is_vertex_updated, IterHelper &iter_helper
) {

    //Size of cache line
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    eid_t buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, long> local_write_buffer(buff, BUFFER_SIZE, next, nextTail);

    eid_t bkt_buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, size_t> local_bucket_buf(bkt_buff, BUFFER_SIZE, iter_helper.bucket_buf_,
                                                     &iter_helper.window_bucket_buf_size_);

    SupportUpdater sup_updater(EdgeSupport, InNext, level, local_write_buffer, local_bucket_buf,
                               iter_helper.bucket_level_end_, iter_helper.in_bucket_window_);


#pragma omp for schedule(dynamic, 4)
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

        static thread_local vector<pair<eid_t, eid_t >> intersection_res(1024 * 1024);
        size_t beg = 0;

        //Check the adj list of vertex v
        for (eid_t j = vStart; j < vEnd; j++) {
            vid_t w = g->adj[j];
            if (X[u].contains(w)) {
                intersection_res[beg++] = make_pair(j, X[u][w]); //  (v,w) and (u,w)
            }
        }

        for (auto iter = 0u; iter < beg; iter++) {
            eid_t e2, e3;
            std::tie(e2, e3) = intersection_res[iter];
            e2 = g->eid[e2];

            sup_updater.PeelTriangle(e1, e2, e3, processed, InCurr);
        }
#ifndef NO_SHRINK_GRAPH
        is_vertex_updated[u] = true;
        is_vertex_updated[v] = true;
#endif
    }

    sup_updater.SubmitLocalBufferNext();
    iter_helper.MarkProcessed();
}

/**   Computes the support of each edge in parallel
 *    Computes k-truss in parallel   ****/
void PKT_marking(graph_t *g, int *&EdgeSupport, Edge *&edgeIdToEdge) {
    log_trace("pkt-mark-shrink");
    Timer convert_timer;
    auto edgeToIdMap = Convert(g, edgeIdToEdge, (g->m / 2));
    log_info("Hash Map Construction Cost: %.6lfs", convert_timer.elapsed());

    IterHelper iter_helper(g, &EdgeSupport, &edgeIdToEdge);
    auto process_functor = [&iter_helper, &EdgeSupport, &edgeToIdMap, edgeIdToEdge, g](int level) {
        PKT_processSubLevel_marking(g, iter_helper.curr_, iter_helper.in_curr_, iter_helper.curr_tail_,
                                    EdgeSupport,
                                    level, iter_helper.next_, iter_helper.in_next_, &iter_helper.next_tail_,
                                    edgeToIdMap,
                                    iter_helper.processed_, edgeIdToEdge,
                                    iter_helper.off_end_,
                                    iter_helper.is_vertex_updated_, iter_helper);
    };
    AbstractPKT(g, EdgeSupport, edgeIdToEdge, iter_helper, process_functor);

    Timer hash_map_free;
    log_info("Parallel Free hash map");
#pragma omp parallel
    {
#pragma omp for
        for (auto i = 0u; i < edgeToIdMap.size(); i++) {
            spp::sparse_hash_map<vid_t, eid_t> tmp;
            edgeToIdMap[i].swap(tmp);
        }
    }
    log_info("Hash Map Free Cost: %.6lfs", hash_map_free.elapsed());
}

