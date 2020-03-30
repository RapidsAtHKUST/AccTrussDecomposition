#ifndef KT_THREAD_H
#define KT_THREAD_H

#include "kt.h"
#include "kt_hmap.h"
#include <omp.h>


#define VERBOSE 0


/*
 * Use hash maps for triangle finding. Currently disabled.
 */
#ifndef USE_HMAP
#define USE_HMAP 0
#endif
#if USE_HMAP
#error "HMAP currently disabled for two-pass"
#endif


#ifndef KT_MAX_THREADS
#define KT_MAX_THREADS 512
#endif


/*
 * How many buckets to allocate, as a function of the number of threads.
 */
#ifndef KT_BUCKETS_PER_THREAD
#define KT_BUCKETS_PER_THREAD 2
#endif


typedef struct {
    /* first communication pass is all triangles */
    triangle_t *tri_msgs;
    int32_t num_tri_msgs;
    int32_t max_tri_msgs;

    /* second communication pass is only (v,w) edge of (u, v, w) triangle. */
    pair_t *pair_msgs;
    int32_t num_pair_msgs;
    int32_t max_pair_msgs;

    epair_t *epair_msgs;
    int32_t num_epair_msgs;
    int32_t max_epair_msgs;

    int64_t *edge_msgs;
    int64_t num_edge_msgs;
    int64_t max_edge_msgs;

    int64_t *edge_msgs2;
    int64_t num_edge_msgs2;
    int64_t max_edge_msgs2;
} thread_msg;


typedef struct {
    int num_threads;
    int num_buckets;

    thread_msg *buckets;

    kt_hmap_t *hmap;

    /* buffers for finding triangles */
    int32_t *w_ids;
    int64_t *uw_idxs;
    int64_t *vw_idxs;

    int32_t len_tri_buffer;
    triangle_t *tri_buffer;

    int32_t len_pair_buffer;
    pair_t *pair_buffer;

    int64_t len_epair_buffer;
    epair_t *epair_buffer;

    int64_t len_edge_buffer;
    int64_t *edge_buffer;

    int64_t len_edge_buffer2;
    int64_t *edge_buffer2;
} thread_ws;


/* XXX */
static inline int map_vtx_to_bucket(
        int32_t const vtx,
        thread_ws const *const ws) {
    return vtx % ws->num_buckets;
    //uint32_t const hashed = (uint32_t) vtx * 0xdeece66d + 0xb;
    //return (int32_t) (hashed % ws->num_buckets);
}


/* XXX */
static inline int map_edge_to_bucket(
        int64_t const edge_id,
        thread_ws const *const ws) {
    return edge_id % ws->num_buckets;
}


/**
* @brief Get an array of triangles which need to have their edges updated. This
*        array will be formed from all of the triangles in a given bucket,
*        collected from all incoming thread messages. The message queues will
*        be emptied after this call.
*
*        NOTE: This function sorts the returned triangles, but does not remove
*        duplicates.
*
*        NOTE: This should be called from within an OpenMP parallel region.
*
* @param ws Thread workspaces for each thread (which contain message queues).
* @param bucket_id Which bucket we are processing.
* @param[out] num_triangles The length of the returned array.
*
* @return An array of `triangle_t` which must be processed. This array should
*         NOT be freed.
*/
triangle_t *get_incoming_triangle_bucket(
        thread_ws **ws,
        int const bucket_id,
        int32_t *num_triangles);


/**
* @brief Get an array of pairs (edges)  which need to be updated. This
*        array will be formed from all of the pairs in a given bucket,
*        collected from all incoming thread messages. The message queues will
*        be emptied after this call.
*
*        NOTE: This function does NOT sort the returned pairs. That is not
*        needed in the two-pass algorithm because duplicate triangles are
*        already removed.
*
*        NOTE: This should be called from within an OpenMP parallel region.
*
* @param ws Thread workspaces for each thread (which contain message queues).
* @param bucket_id Which bucket we are processing.
* @param[out] num_triangles The length of the returned array.
*
* @return An array of `pair_t` which must be processed. This array should
*         NOT be freed.
*/
pair_t *get_incoming_pair_bucket(
        thread_ws **ws,
        int const bucket_id,
        int32_t *num_pairs);


int64_t *get_incoming_edge_bucket(
        thread_ws **ws,
        int const bucket_id,
        int64_t *num_edges,
        int const which);


void thread_time_stats(
        double const *const thread_times,
        int const num_threads,
        int const padding);


void send_thread_tri_msg(
        triangle_t const *const triangle,
        int const thd_dest,
        thread_ws *ws);

void send_thread_pair_msg(
        triangle_t const *const triangle,
        int const thd_dest,
        thread_ws *ws);

void send_thread_pair_msg_explicit(
        pair_t const *const pair,
        int const thd_dest,
        thread_ws *ws);


void send_thread_epair_msg(
        epair_t *const pair,
        int const bucket_dest,
        thread_ws *ws);

epair_t *get_incoming_epair_bucket(
        thread_ws **ws,
        int const bucket_id,
        int64_t *num_pairs);


void send_thread_edge_msg(
        int64_t edge_id,
        int const bucket_dest,
        thread_ws *ws,
        int const which);


thread_ws **alloc_thread_ws_big(
        gk_graph_t const *const graph);

thread_ws **alloc_thread_ws(
        gk_graph_t const *const lgraph,
        gk_graph_t const *const ugraph);

void free_thread_ws(
        thread_ws **ws);

#endif
