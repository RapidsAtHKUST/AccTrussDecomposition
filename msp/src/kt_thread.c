

#include "kt.h"
#include "kt_thread.h"
#include "kt_hmap.h"


/* Initial buffer size for messages. Will resize when necessary. */
#ifndef MSG_DEFAULT_BUFFER
#define MSG_DEFAULT_BUFFER 1000
#endif


/******************************************************************************
 * THREAD FUNCTIONS
 *****************************************************************************/

triangle_t * get_incoming_triangle_bucket(
    thread_ws * * ws,
    int const bucket_id,
    int32_t * num_triangles)
{
  int const tid = omp_get_thread_num();
  thread_ws * const my_ws = ws[tid];

  int32_t ntriangles = 0;
  /* Count the number of triangles in bucket (across all threads) */
  for(int t=0; t < my_ws->num_threads; ++t) {
    ntriangles += ws[t]->buckets[bucket_id].num_tri_msgs;
  }


  /* resize buffer if necessary */
  if(my_ws->len_tri_buffer < ntriangles) {
    my_ws->len_tri_buffer = ntriangles;
    gk_free((void **) &(my_ws->tri_buffer), LTERM);

    my_ws->tri_buffer = gk_malloc(ntriangles * sizeof(*my_ws->tri_buffer),
                                  "tri_buffer");
  }

  triangle_t * const restrict buffer = my_ws->tri_buffer;

  /* go over each thread's bucket */
  int32_t buffer_ptr = 0;
  for(int t=0; t < my_ws->num_threads; ++t) {
    /* copy incoming bucket */
    int32_t const num_msgs = ws[t]->buckets[bucket_id].num_tri_msgs;
    if(num_msgs > 0) {
      triangle_t const * const msgs = ws[t]->buckets[bucket_id].tri_msgs;
      for(int32_t m=0; m < num_msgs; ++m) {
        buffer[buffer_ptr++] = msgs[m];
      }

      /* now empty buffer */
      ws[t]->buckets[bucket_id].num_tri_msgs = 0;
    }
  }

  *num_triangles = ntriangles;
  return buffer;
}


pair_t * get_incoming_pair_bucket(
    thread_ws * * ws,
    int const bucket_id,
    int32_t * num_pairs)
{
  int const tid = omp_get_thread_num();
  thread_ws * const my_ws = ws[tid];

  int32_t npairs = 0;
  /* Count the number of pairs in bucket (across all threads) */
  for(int t=0; t < my_ws->num_threads; ++t) {
    npairs += ws[t]->buckets[bucket_id].num_pair_msgs;
  }


  /* resize buffer if necessary */
  if(my_ws->len_pair_buffer < npairs) {
    my_ws->len_pair_buffer = npairs;
    gk_free((void **) &(my_ws->pair_buffer), LTERM);

    my_ws->pair_buffer = gk_malloc(npairs * sizeof(*my_ws->pair_buffer),
                                   "pair_buffer");
  }

  pair_t * const restrict buffer = my_ws->pair_buffer;

  /* go over each thread's bucket */
  int32_t buffer_ptr = 0;
  for(int t=0; t < my_ws->num_threads; ++t) {
    /* copy incoming bucket */
    int32_t const num_msgs = ws[t]->buckets[bucket_id].num_pair_msgs;
    if(num_msgs > 0) {
      pair_t const * const msgs = ws[t]->buckets[bucket_id].pair_msgs;
      for(int32_t m=0; m < num_msgs; ++m) {
        buffer[buffer_ptr++] = msgs[m];
      }

      /* now empty buffer */
      ws[t]->buckets[bucket_id].num_pair_msgs = 0;
    }
  }

  *num_pairs = npairs;
  return buffer;
}



int64_t * get_incoming_edge_bucket(
    thread_ws * * ws,
    int const bucket_id,
    int64_t * num_edges,
    int const which)
{
  assert(which >= 0);
  assert(which < 2);

  int const tid = omp_get_thread_num();
  thread_ws * const my_ws = ws[tid];

  int64_t nedges = 0;
  /* Count the number of edges in bucket (across all threads) */
  for(int t=0; t < my_ws->num_threads; ++t) {
    if(which == 0) {
      nedges += ws[t]->buckets[bucket_id].num_edge_msgs;
    } else {
      nedges += ws[t]->buckets[bucket_id].num_edge_msgs2;
    }
  }

  /* resize buffer if necessary */
  if(which == 0) {
    if(my_ws->len_edge_buffer < nedges) {
      my_ws->len_edge_buffer = nedges;
      gk_free((void **) &(my_ws->edge_buffer), LTERM);

      my_ws->edge_buffer = gk_malloc(nedges * sizeof(*my_ws->edge_buffer),
                                     "edge_buffer");
    }
  } else {
    if(my_ws->len_edge_buffer2 < nedges) {
      my_ws->len_edge_buffer2 = nedges;
      gk_free((void **) &(my_ws->edge_buffer2), LTERM);

      my_ws->edge_buffer2 = gk_malloc(nedges * sizeof(*my_ws->edge_buffer2),
                                     "edge_buffer2");
    }
  }

  int64_t * const restrict buffer = (which == 0) ? \
      my_ws->edge_buffer : my_ws->edge_buffer2;

  if(which == 0) {
    /* go over each thread's bucket */
    int32_t buffer_ptr = 0;
    for(int t=0; t < my_ws->num_threads; ++t) {
      /* copy incoming bucket */
      int64_t const num_msgs = ws[t]->buckets[bucket_id].num_edge_msgs;
      int64_t const * const msgs = ws[t]->buckets[bucket_id].edge_msgs;
      for(int64_t m=0; m < num_msgs; ++m) {
        buffer[buffer_ptr++] = msgs[m];
      }

      /* now empty buffer */
      ws[t]->buckets[bucket_id].num_edge_msgs = 0;
    }
  } else {
    /* go over each thread's bucket */
    int32_t buffer_ptr = 0;
    for(int t=0; t < my_ws->num_threads; ++t) {
      /* copy incoming bucket */
      int64_t const num_msgs = ws[t]->buckets[bucket_id].num_edge_msgs2;
      int64_t const * const msgs = ws[t]->buckets[bucket_id].edge_msgs2;
      for(int64_t m=0; m < num_msgs; ++m) {
        buffer[buffer_ptr++] = msgs[m];
      }

      /* now empty buffer */
      ws[t]->buckets[bucket_id].num_edge_msgs2 = 0;
    }
  }

  *num_edges = nedges;
  return buffer;
}


void send_thread_tri_msg(
    triangle_t const * const triangle,
    int const bucket_dest,
    thread_ws * ws)
{
  assert(bucket_dest >= 0);
  assert(bucket_dest < ws->num_buckets);

  assert(triangle->u < triangle->v);
  assert(triangle->u < triangle->w);
  assert(triangle->v < triangle->w);
  assert(triangle->u >= 0);
  assert(triangle->v >= 0);
  assert(triangle->w >= 0);

  thread_msg * const restrict dest_msgs = &(ws->buckets[bucket_dest]);

  /* resize if necessary */
  if(dest_msgs->num_tri_msgs == dest_msgs->max_tri_msgs) {
    dest_msgs->max_tri_msgs *= 2;
    triangle_t * big = gk_malloc(dest_msgs->max_tri_msgs * sizeof(*big), "big");
    for(int32_t i=0; i < dest_msgs->num_tri_msgs; ++i) {
      big[i] = dest_msgs->tri_msgs[i];
    }

    gk_free((void **) &(dest_msgs->tri_msgs), LTERM);
    dest_msgs->tri_msgs = big;
  }

  /* append triangle to message queue */
  int32_t const idx = dest_msgs->num_tri_msgs;
  dest_msgs->tri_msgs[idx] = *triangle;
  ++(dest_msgs->num_tri_msgs);

#if VERBOSE
  printf("TRIANGLE thread %d -> %d (%d %d %d) = %zd %zd %zd\n",
      omp_get_thread_num(),
      bucket_dest, 1+triangle->u, 1+triangle->v, 1+triangle->w,
      triangle->uv, triangle->vw);
#endif
}


void send_thread_pair_msg(
    triangle_t const * const triangle,
    int const bucket_dest,
    thread_ws * ws)
{
  assert(triangle->v > 0);
  assert(triangle->w > 0);
  assert(triangle->v < triangle->w);

  pair_t tmp;
  tmp.v = triangle->v;
  tmp.w = triangle->w;
  tmp.vw = triangle->vw;

  send_thread_pair_msg_explicit(&tmp, bucket_dest, ws);
}




void send_thread_pair_msg_explicit(
    pair_t const * const pair,
    int const bucket_dest,
    thread_ws * ws)
{
  assert(bucket_dest >= 0);
  assert(bucket_dest < ws->num_buckets);

  thread_msg * const restrict dest_msgs = &(ws->buckets[bucket_dest]);

  /* resize if necessary */
  if(dest_msgs->num_pair_msgs == dest_msgs->max_pair_msgs) {
    dest_msgs->max_pair_msgs *= 2;
    pair_t * big = gk_malloc(dest_msgs->max_pair_msgs * sizeof(*big), "big");
    for(int32_t i=0; i < dest_msgs->num_pair_msgs; ++i) {
      big[i] = dest_msgs->pair_msgs[i];
    }

    gk_free((void **) &(dest_msgs->pair_msgs), LTERM);
    dest_msgs->pair_msgs = big;
  }

  /* append pair to message queue */
  int32_t const idx = dest_msgs->num_pair_msgs;
  dest_msgs->pair_msgs[idx] = *pair;
  ++(dest_msgs->num_pair_msgs);

#if VERBOSE
  printf("PAIR thread %d -> %d (%d %d)\n", omp_get_thread_num(), bucket_dest,
      pair->v, pair->w);
#endif

}


void send_thread_edge_msg(
    int64_t edge_id,
    int const bucket_dest,
    thread_ws * ws,
    int const which)
{
  assert(bucket_dest >= 0);
  assert(bucket_dest < ws->num_buckets);

  thread_msg * const restrict dest_msgs = &(ws->buckets[bucket_dest]);

  /* resize if necessary */
  if(which == 0) {
    if(dest_msgs->num_edge_msgs == dest_msgs->max_edge_msgs) {
      dest_msgs->max_edge_msgs *= 2;
      int64_t * big = gk_malloc(dest_msgs->max_edge_msgs * sizeof(*big), "big");
      for(int32_t i=0; i < dest_msgs->num_edge_msgs; ++i) {
        big[i] = dest_msgs->edge_msgs[i];
      }

      gk_free((void **) &(dest_msgs->edge_msgs), LTERM);
      dest_msgs->edge_msgs = big;
    }

    /* append pair to message queue */
    int32_t const idx = dest_msgs->num_edge_msgs;
    dest_msgs->edge_msgs[idx] = edge_id;
    ++(dest_msgs->num_edge_msgs);
  } else {
    if(dest_msgs->num_edge_msgs2 == dest_msgs->max_edge_msgs2) {
      dest_msgs->max_edge_msgs2 *= 2;
      int64_t * big = gk_malloc(dest_msgs->max_edge_msgs2 * sizeof(*big), "big");
      for(int32_t i=0; i < dest_msgs->num_edge_msgs2; ++i) {
        big[i] = dest_msgs->edge_msgs2[i];
      }

      gk_free((void **) &(dest_msgs->edge_msgs2), LTERM);
      dest_msgs->edge_msgs2 = big;
    }

    /* append pair to message queue */
    int32_t const idx = dest_msgs->num_edge_msgs2;
    dest_msgs->edge_msgs2[idx] = edge_id;
    ++(dest_msgs->num_edge_msgs2);
  }

#if VERBOSE
  printf("EDGE thread-%d -> bucket-%d edge-%zd \n", omp_get_thread_num(), bucket_dest,
      edge_id);
#endif
}


thread_ws * * alloc_thread_ws(
    gk_graph_t const * const lgraph,
    gk_graph_t const * const ugraph)
{
  int const nthreads = omp_get_max_threads();

  int64_t const nedges = ugraph->xadj[ugraph->nvtxs];
  ssize_t const max_degree =
      gk_max(graph_max_degree(lgraph), graph_max_degree(ugraph));
  int32_t const max_support = max_elem(ugraph->iadjwgt, nedges);

  printf("max_support: %d\n\n", max_support);

  thread_ws * * ws = gk_malloc(nthreads * sizeof(*ws), "ws");

  /* each thread has outgoing buffers for all threads */
  #pragma omp parallel
  {
    thread_ws * my_ws = gk_malloc(sizeof(*my_ws), "ws[tid]");
    my_ws->num_threads = nthreads;
    my_ws->num_buckets = nthreads * KT_BUCKETS_PER_THREAD;
    my_ws->buckets = gk_malloc(my_ws->num_buckets * sizeof(*(my_ws->buckets)), "messages");

    /* allocate message to each thread */
    for(int b=0; b < my_ws->num_buckets; ++b) {
      my_ws->buckets[b].max_tri_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_tri_msgs = 0;
      my_ws->buckets[b].tri_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(triangle_t), "triangles");

      my_ws->buckets[b].max_pair_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_pair_msgs = 0;
      my_ws->buckets[b].pair_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(pair_t), "pairs");

      my_ws->buckets[b].max_edge_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_edge_msgs = 0;
      my_ws->buckets[b].edge_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(int64_t), "edges");
    }

    /* buffer for finding triangles */
    my_ws->w_ids = gk_malloc(max_support * sizeof(*my_ws->w_ids), "w_ids");
    my_ws->uw_idxs = gk_malloc(max_support * sizeof(*my_ws->uw_idxs), "uw_idxs");
    my_ws->vw_idxs = gk_malloc(max_support * sizeof(*my_ws->vw_idxs), "vw_idxs");

#if USE_HMAP
    my_ws->hmap = alloc_hmap(max_degree);
#endif

    /* initially empty buffers */
    my_ws->tri_buffer = NULL;
    my_ws->pair_buffer = NULL;
    my_ws->edge_buffer = NULL;
    my_ws->edge_buffer2 = NULL;
    my_ws->len_tri_buffer = 0;
    my_ws->len_pair_buffer = 0;
    my_ws->len_edge_buffer = 0;
    my_ws->len_edge_buffer = 0;
    my_ws->len_edge_buffer2 = 0;

    /* store my workspace */
    ws[omp_get_thread_num()] = my_ws;
  } /* end omp parallel */

  return ws;
}



thread_ws * * alloc_thread_ws_big(
    gk_graph_t const * const graph)
{
  int const nthreads = omp_get_max_threads();

  int64_t const nedges = graph->xadj[graph->nvtxs];
  ssize_t const max_degree = graph_max_degree(graph);

  thread_ws * * ws = gk_malloc(nthreads * sizeof(*ws), "ws");

  /* each thread has outgoing buffers for all threads */
  #pragma omp parallel
  {
    thread_ws * my_ws = gk_malloc(sizeof(*my_ws), "ws[tid]");
    my_ws->num_threads = nthreads;
    my_ws->num_buckets = nthreads * KT_BUCKETS_PER_THREAD;
    my_ws->buckets = gk_malloc(my_ws->num_buckets * sizeof(*(my_ws->buckets)), "messages");

    /* allocate message to each thread */
    for(int b=0; b < my_ws->num_buckets; ++b) {
      my_ws->buckets[b].max_tri_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_tri_msgs = 0;
      my_ws->buckets[b].tri_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(triangle_t), "triangles");

      my_ws->buckets[b].max_pair_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_pair_msgs = 0;
      my_ws->buckets[b].pair_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(pair_t), "pairs");

      my_ws->buckets[b].max_epair_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_epair_msgs = 0;
      my_ws->buckets[b].epair_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(pair_t), "pairs");

      my_ws->buckets[b].max_edge_msgs = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_edge_msgs = 0;
      my_ws->buckets[b].edge_msgs =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(int64_t), "edges");

      my_ws->buckets[b].max_edge_msgs2 = MSG_DEFAULT_BUFFER;
      my_ws->buckets[b].num_edge_msgs2 = 0;
      my_ws->buckets[b].edge_msgs2 =
          gk_malloc(MSG_DEFAULT_BUFFER * sizeof(int64_t), "edges2");
    }

    /* buffer for finding triangles */
    my_ws->w_ids   = NULL;
    my_ws->uw_idxs = NULL;
    my_ws->vw_idxs = NULL;

    /* initially empty buffers */
    my_ws->tri_buffer = NULL;
    my_ws->pair_buffer = NULL;
    my_ws->epair_buffer = NULL;
    my_ws->edge_buffer = NULL;
    my_ws->edge_buffer2 = NULL;
    my_ws->len_tri_buffer = 0;
    my_ws->len_pair_buffer = 0;
    my_ws->len_epair_buffer = 0;
    my_ws->len_edge_buffer = 0;
    my_ws->len_edge_buffer2 = 0;

    /* store my workspace */
    ws[omp_get_thread_num()] = my_ws;
  } /* end omp parallel */

  return ws;
}




void send_thread_epair_msg(
    epair_t * const pair,
    int const bucket_dest,
    thread_ws * ws)
{
  assert(bucket_dest >= 0);
  assert(bucket_dest < ws->num_buckets);

  thread_msg * const restrict dest_msgs = &(ws->buckets[bucket_dest]);

  /* resize if necessary */
  if(dest_msgs->num_epair_msgs == dest_msgs->max_epair_msgs) {
    dest_msgs->max_epair_msgs *= 2;
    epair_t * big = gk_malloc(dest_msgs->max_epair_msgs * sizeof(*big), "big");
    for(int32_t i=0; i < dest_msgs->num_epair_msgs; ++i) {
      big[i] = dest_msgs->epair_msgs[i];
    }

    gk_free((void **) &(dest_msgs->epair_msgs), LTERM);
    dest_msgs->epair_msgs = big;
  }

  /* append epair to message queue */
  int32_t const idx = dest_msgs->num_epair_msgs;
  dest_msgs->epair_msgs[idx] = *pair;
  ++(dest_msgs->num_epair_msgs);

#if VERBOSE
  printf("PAIR thread %d -> %d (%d %d)\n", omp_get_thread_num(), bucket_dest,
      pair->v, pair->w);
#endif
}


epair_t * get_incoming_epair_bucket(
    thread_ws * * ws,
    int const bucket_id,
    int64_t * num_pairs)
{
  int const tid = omp_get_thread_num();
  thread_ws * const my_ws = ws[tid];

  int32_t npairs = 0;
  /* Count the number of pairs in bucket (across all threads) */
  for(int t=0; t < my_ws->num_threads; ++t) {
    npairs += ws[t]->buckets[bucket_id].num_epair_msgs;
  }


  /* resize buffer if necessary */
  if(my_ws->len_epair_buffer < npairs) {
    my_ws->len_epair_buffer = npairs;
    gk_free((void **) &(my_ws->epair_buffer), LTERM);

    my_ws->epair_buffer = gk_malloc(npairs * sizeof(*my_ws->epair_buffer),
                                   "epair_buffer");
  }

  epair_t * const restrict buffer = my_ws->epair_buffer;

  /* go over each thread's bucket */
  int32_t buffer_ptr = 0;
  for(int t=0; t < my_ws->num_threads; ++t) {
    /* copy incoming bucket */
    int32_t const num_msgs = ws[t]->buckets[bucket_id].num_epair_msgs;
    if(num_msgs > 0) {
      epair_t const * const msgs = ws[t]->buckets[bucket_id].epair_msgs;
      for(int32_t m=0; m < num_msgs; ++m) {
        buffer[buffer_ptr++] = msgs[m];
      }

      /* now empty buffer */
      ws[t]->buckets[bucket_id].num_epair_msgs = 0;
    }
  }

  *num_pairs = npairs;
  return buffer;
}


void free_thread_ws(
    thread_ws * * ws)
{
  #pragma omp parallel
  {
    int const tid = omp_get_thread_num();
    for(int b=0; b < ws[tid]->num_buckets; ++b) {
      gk_free((void **) &(ws[tid]->buckets[b].tri_msgs), LTERM);
      gk_free((void **) &(ws[tid]->buckets[b].pair_msgs), LTERM);
      gk_free((void **) &(ws[tid]->buckets[b].edge_msgs), LTERM);
      gk_free((void **) &(ws[tid]->buckets[b].edge_msgs2), LTERM);
    }

#if USE_HMAP
    free_hmap(ws[tid]->hmap);
#endif

    gk_free((void **) &(ws[tid]->w_ids), LTERM);
    gk_free((void **) &(ws[tid]->uw_idxs), LTERM);
    gk_free((void **) &(ws[tid]->vw_idxs), LTERM);
    gk_free((void **) &(ws[tid]->tri_buffer), LTERM);
    gk_free((void **) &(ws[tid]->pair_buffer), LTERM);
    gk_free((void **) &(ws[tid]->edge_buffer), LTERM);
    gk_free((void **) &(ws[tid]->buckets), LTERM);
    gk_free((void **) &(ws[tid]), LTERM);
  }
  gk_free((void **) &(ws), LTERM);
}



void thread_time_stats(
    double const * const restrict thread_times,
    int const num_threads,
    int const padding)
{
  double total_thread_time = 0.;
  double min_time = thread_times[0];
  double max_time = thread_times[0];
  for(int t=0; t < num_threads; ++t) {
    double const curr_time = thread_times[t * padding];
    total_thread_time += curr_time;
    min_time = gk_min(curr_time, min_time);
    max_time = gk_max(curr_time, max_time);
  }
  double const avg_time = total_thread_time / num_threads;
  printf("\tmin: %0.3fs avg: %0.3fs max: %0.3fs imbalance(max/avg): %0.2fx\n",
      min_time, avg_time, max_time,
      max_time / avg_time);
}


