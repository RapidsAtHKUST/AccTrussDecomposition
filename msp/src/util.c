
#include "kt.h"



int32_t max_elem(
    int32_t const * const restrict array,
    int64_t N)
{
  assert(N > 0);

  int32_t max_val = array[0];

  #pragma omp parallel for schedule(static) reduction(max: max_val)
  for(int64_t i=0; i < N; ++i) {
    max_val = gk_max(max_val, array[i]);
  }

  return max_val;
}


ssize_t graph_max_degree(
    gk_graph_t const * const G)
{
  ssize_t degree = 0;

  #pragma omp parallel for schedule(static) reduction(max: degree)
  for(int32_t v=0; v < G->nvtxs; ++v) {
    degree = gk_max(degree, G->xadj[v+1] - G->xadj[v]);
  }

  return degree;
}


gk_graph_t * transpose_graph(
    gk_graph_t const * const G)
{
  int32_t const nvtxs  = G->nvtxs;
  int64_t const nedges = G->xadj[G->nvtxs];

  gk_graph_t * T = gk_graph_Create();
  T->nvtxs = nvtxs;
  T->xadj   = gk_zmalloc(nvtxs+1, "T->xadj");
  T->adjncy = gk_i32malloc(nedges,  "T->adjncy");

  /* get counts for xadj */
  par_memset(T->xadj, 0, (nvtxs+1) * sizeof(*T->xadj));
  #pragma omp parallel for schedule(static)
  for(int64_t e=0; e < nedges; ++e) {
    #pragma omp atomic
    T->xadj[G->adjncy[e]]++;
  }
  {
    int32_t v;
    MAKECSR(v, nvtxs, T->xadj);
  }

  /* fill in data */
  #pragma omp parallel
  for(int32_t v=0; v < nvtxs; ++v) {
    /* parallel because there should be no multi edges, thus each thread will
     * have unique u vertices */
    #pragma omp for schedule(static)
    for(ssize_t e = G->xadj[v]; e < G->xadj[v+1]; ++e) {
      int32_t const u = G->adjncy[e];
      T->adjncy[T->xadj[u]++] = v;
    }
  }
  {
    int32_t v;
    SHIFTCSR(v, nvtxs, T->xadj);
  }

#ifndef NDEBUG
  /* make sure each adjncy is sorted */
  for(int32_t v=0; v < nvtxs; ++v) {
    for(ssize_t e = T->xadj[v]+1; e < T->xadj[v+1]; ++e) {
      assert(T->adjncy[e] > T->adjncy[e-1]);
    }
  }
#endif

  return T;
}



void graph_add_island(
    gk_graph_t * graph)
{
  int32_t const nvtxs  = graph->nvtxs + 1;
  int32_t const nedges = graph->xadj[nvtxs-1];

  ssize_t * xadj = gk_zmalloc(nvtxs + 1, "island->xadj");

  /* copy data */
  xadj[0] = 0;
  for(int32_t v=0; v < nvtxs; ++v) {
    xadj[1+v] = graph->xadj[v];
  }

  /* shift adjncy values by 1 */
  #pragma omp parallel for schedule(static)
  for(ssize_t e=0; e < nedges; ++e) {
    ++(graph->adjncy[e]);
  }

  graph->nvtxs++;
  gk_free((void **) graph->xadj, LTERM);

  graph->xadj = xadj;
}





void * par_memset(
    void * const s,
    int const c,
    size_t const bytes)
{
  #pragma omp parallel
  {
    int const nthreads = omp_get_num_threads();
    int const tid      = omp_get_thread_num();

    /* block distribution */
    size_t const n_per_thread = (bytes + nthreads - 1)/nthreads;
    size_t const n_begin = gk_min(n_per_thread * tid, bytes);
    size_t const n_end = gk_min(n_begin + n_per_thread, bytes);

    char * const data = (char *) s;
    memset(data + n_begin, c, n_end - n_begin);
  }

  return s;
}


void par_memcpy(
    void       * const dest,
    void const * const src,
    size_t const bytes)
{
  #pragma omp parallel
  {
    int const nthreads = omp_get_num_threads();
    int const tid      = omp_get_thread_num();

    /* block distribution */
    size_t const n_per_thread = (bytes + nthreads - 1)/nthreads;
    size_t const n_begin = gk_min(n_per_thread * tid, bytes);
    size_t const n_end = gk_min(n_begin + n_per_thread, bytes);

    char * const restrict dest_data = (char *) dest;
    char * const restrict src_data  = (char *) src;
    memcpy(dest_data + n_begin, src_data + n_begin, n_end - n_begin);
  }
}



int64_t count_nnz(
    int64_t const N,
    int32_t const * const supports)
{
  int64_t nnz = 0;

  #pragma omp parallel for schedule(static) reduction(+:nnz)
  for(int64_t e = 0; e < N; ++e) {
    if(supports[e] > 0) {
      ++nnz;
    }
  }

  return nnz;
}


int64_t count_support(
    int64_t const N,
    int32_t const * const supports)
{
  int64_t total_support = 0;

  #pragma omp parallel for schedule(static) reduction(+:total_support)
  for(int64_t e = 0; e < N; ++e) {
    if(supports[e] > 0) {
      total_support += supports[e];
    }
  }

  return total_support;
}


void sort_triangles(
    triangle_t * const restrict tris,
    int32_t ntriangles)
{
  double sort_timer = 0;
  gk_startwctimer(sort_timer);

  /* tie breakers are u -> v -> w */
#define tri_lt(a,b) ( \
    ((a)->u < (b)->u) \
    || \
    (((a)->u == (b)->u) && ((a)->v < (b)->v)) \
    || \
    (((a)->u == (b)->u) && ((a)->v == (b)->v) && ((a)->w < (b)->w)) \
  )
  GK_MKQSORT(triangle_t, tris, ntriangles, tri_lt);
#undef tri_lt

  gk_stopwctimer(sort_timer);
#if 0
  printf("SORTING-SIZE: %d (%0.3fs)\n", ntriangles, sort_timer);
#endif
}


void gk_epairsorti(size_t n, epair_t * base)
{
#define idxkey_lt(a, b) ((a)->key < (b)->key)
  GK_MKQSORT(epair_t, base, n, idxkey_lt);
#undef idxkey_lt
}


