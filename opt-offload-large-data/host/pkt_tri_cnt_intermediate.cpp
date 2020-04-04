#include "pkt_tri_cnt_intermediate.h"

//Process a sub-level in a level using intersection based approach
void TriCntDetailSubLevel(graph_t *g, eid_t *curr,
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
                          long *nextTail,
#ifdef BMP_PROCESSED
                          BoolArray<word_type> &processed_,
#else
        bool *processed_,
#endif
                          Edge *edgeIdtoEdge, eid_t *off_end,
                          bool *is_vertex_updated,
                          IterHelper &iter_helper,
                          volatile eid_t &global_v_buff_size
) {
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    eid_t buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, long> local_write_buffer(buff, BUFFER_SIZE, next, nextTail);

    eid_t bkt_buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, size_t> local_bucket_buf(bkt_buff, BUFFER_SIZE, iter_helper.bucket_buf_,
                                                     &iter_helper.window_bucket_buf_size_);

    // 1st: Mark Processed.
#pragma omp for schedule(static)
    for (long i = 0; i < currTail; i++) {
        eid_t e1 = curr[i];

        Edge edge = edgeIdtoEdge[e1];
        vid_t u = edge.u;
        vid_t v = edge.v;
        eid_t uStart = g->num_edges[u], uEnd = off_end[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = off_end[v + 1];

        is_vertex_updated[u] = true;
        is_vertex_updated[v] = true;
    }
    iter_helper.MarkProcessed();    // processed, in_curr_

    // 2nd: Shrink.
    auto *local_buffer = (vid_t *) malloc(sizeof(vid_t) * V_BUFF_SIZE);
    iter_helper.ShrinkCSREID(&global_v_buff_size, local_buffer);
    free(local_buffer);

    // 3rd: Pre-Process: Indexing Words.
#pragma omp for schedule(dynamic, 100)
    for (auto u = 0; u < g->n; u++) {
        PackVertexIntermediate(g, off_end, iter_helper.partition_id_lst, iter_helper.bitmap_in_partition_lst, u);
    }
    static thread_local auto bool_arr = BoolArray<bmp_word_type>(g->n);
    auto last_u = -1;
    auto u = 0;

    // 4th: ComputeSupport.
#pragma omp for schedule(dynamic, 6000)
    for (auto i = 0u; i < g->num_edges[g->n]; i++)
        ComputeSupportWithPackIntermediate(g, off_end, *iter_helper.edge_sup_ptr_, i, bool_arr,
                                           iter_helper.partition_id_lst, iter_helper.bitmap_in_partition_lst,
                                           local_write_buffer, local_bucket_buf, InNext, level,
                                           iter_helper.bucket_level_end_, iter_helper.in_bucket_window_,
                                           iter_helper, last_u, u);
    if (last_u != -1) {
        for (auto offset = g->num_edges[last_u]; offset < off_end[last_u + 1]; offset++) {
            auto v = g->adj[offset];
            bool_arr.setWord(v / word_in_bits, 0);
        }
        last_u = -1;
    }
    // Should be careful to pass by reference in the previous local buffer usage.
    local_write_buffer.submit_if_possible();
    local_bucket_buf.submit_if_possible();
#pragma omp barrier
}
