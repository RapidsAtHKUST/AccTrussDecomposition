#ifndef KT_THREAD_SUPPORT_BUCKET_H
#define KT_THREAD_SUPPORT_BUCKET_H



/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "kt.h"
#include "kt_thread.h"


typedef struct {
    ssize_t prev_eid;
    ssize_t next_eid;
    int32_t support;
} slist_s;


/*
 * Support-based bucket.
 */
typedef struct {
    int32_t nsupports;
    int64_t nowned_edges;
    ssize_t *list_head;
    slist_s *slist;
} support_bucket_t;


support_bucket_t *sbucket_alloc(
        edge_t const *const edges,
        int32_t const *const supports,
        int64_t const global_nedges,
        thread_ws **thd_ws);

void sbucket_free(
        support_bucket_t *sbucket);


void sbucket_update_edge(
        support_bucket_t *const sbucket,
        int64_t const edge_id,
        int32_t const support,
        int32_t const ktruss);

int64_t sbucket_get_frontier(
        support_bucket_t *const sbuckets,
        int32_t const support,
        int64_t *frontier);

int64_t sbucket_count_support_size(
        support_bucket_t const *const sbucket,
        int32_t const support);

void sbucket_fill_edges(
        support_bucket_t const *const sbucket,
        int32_t const support,
        int64_t *const edge_ids);


#endif
