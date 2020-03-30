extern "C" {
#include "kt.h"
#include <stdbool.h>
#include <inttypes.h>
}

#ifdef GPERFTOOLS
#include <gperftools/profiler.h>
#endif

#include "yche/log.h"
#include "yche/core_histogram.h"
#include "yche/search.h"

#ifndef MAX_NTHREADS
#define MAX_NTHREADS 272
#endif

#ifndef DYNAMIC_CHUNK
#define DYNAMIC_CHUNK 256
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int64_t edge_a;
    int64_t edge_b;
} tri_edges;


/******************************************************************************
 * PRIVATE FUNCTIONS
 *****************************************************************************/
static void p_construct_output(
        params_t const *const params,
        vault_t *const vault,
        int32_t ktmax,
        int32_t const *const supports) {
    if (params->outfile == NULL)
        return;

    int32_t const nvtxs = vault->ugraph->nvtxs;
    ssize_t const *const xadj = vault->ugraph->xadj;
    int32_t const *const adjncy = vault->ugraph->adjncy;

    vault->nedges = xadj[nvtxs];
    vault->ktmax = ktmax;
    vault->ktedges = static_cast<ktedge_t *>(gk_malloc(xadj[nvtxs] * sizeof(*vault->ktedges), "ktedges"));

#pragma omp parallel for schedule(dynamic, DYNAMIC_CHUNK)
    for (int32_t v = 0; v < nvtxs; ++v) {
        for (ssize_t e = xadj[v]; e < xadj[v + 1]; ++e) {
            /* -1 to revert the shift-by-one ordering */
            int32_t const v1 = vault->iperm[v];
            int32_t const v2 = vault->iperm[adjncy[e]];

            vault->ktedges[e].vi = gk_min(v1, v2);
            vault->ktedges[e].vj = gk_max(v1, v2);

            vault->ktedges[e].k = supports[e];
        }
    }
}


/**
* @brief Intersect two adjacency lists (`adj_u` and `adj_v`)
*
* @param adj_u The neighbors of vertex u.
* @param len_u The length of `adj_u`.
* @param adj_u_offset This is how far into the xadj we already are. This allows
*                     us to translate len_u into a global graph edge.
* @param adj_v The neighbors of vertex v.
* @param len_v The length of `adj_v`.
* @param[out] triangles An array of the edge IDs which complete the discovered
*                       triangles.
* @param max_triangles The maximum number of triangles which we should find in
*                      the intersection.
*
* @return The number of discovered triangles.
*/
static int32_t p_intersect_lists(
        int32_t *const adj_u,
        ssize_t const len_u,
        ssize_t const adj_u_offset,
        int32_t *const adj_v,
        ssize_t const len_v,
        ssize_t const adj_v_offset,
        tri_edges *const triangles,
        int32_t const max_triangles) {
    if (max_triangles == 0) {
        return 0;
    }

    int32_t num_found = 0;

    /* Linear merge to find intersections. We go in reverse because high-degree
     * vertices are placed at the end, and are thus more likely to be found in
     * the intersections. */
    int32_t u_ptr = len_u - 1;
    int32_t v_ptr = len_v - 1;
    while ((u_ptr >= 0) && (v_ptr >= 0)) {
        int32_t const u = adj_u[u_ptr];
        int32_t const v = adj_v[v_ptr];
        if (u < v) {
            --v_ptr;
        } else if (v < u) {
            --u_ptr;
        } else {
            triangles[num_found].edge_a = u_ptr + adj_u_offset;
            triangles[num_found].edge_b = v_ptr + adj_v_offset;
            ++num_found;
            if (num_found == max_triangles) {
                return num_found;
            }
            --u_ptr;
            --v_ptr;
        }
    }
    return num_found;
}

/**
* @brief Intersect two adjacency lists (`adj_u` and `adj_v`)
*
* @param adj_u The neighbors of vertex u.
* @param len_u The length of `adj_u`.
* @param adj_u_offset This is how far into the xadj we already are. This allows
*                     us to translate len_u into a global graph edge.
* @param adj_v The neighbors of vertex v.
* @param len_v The length of `adj_v`.
* @param[out] triangles An array of the edge IDs which complete the discovered
*                       triangles.
* @param max_triangles The maximum number of triangles which we should find in
*                      the intersection.
*
* @return The number of discovered triangles.
*/
static int32_t p_intersect_lists_galloping(
        int32_t *const adj_u,
        ssize_t const len_u,
        ssize_t const adj_u_offset,
        int32_t *const adj_v,
        ssize_t const len_v,
        ssize_t const adj_v_offset,
        tri_edges *const triangles,
        int32_t const max_triangles) {
    if (max_triangles == 0 || len_u == 0 || len_v == 0) {
        return 0;
    }

    int32_t size = 0;

    /* Linear merge to find intersections. We go in reverse because high-degree
     * vertices are placed at the end, and are thus more likely to be found in
     * the intersections. */
    uint32_t off_nei_u = 0;
    uint32_t off_nei_v = 0;
    while (true) {
        off_nei_u = GallopingSearch(adj_u, off_nei_u, len_u, adj_v[off_nei_v]);
        if (off_nei_u >= len_u) {
            break;
        }
        off_nei_v = GallopingSearch(adj_v, off_nei_v, len_v, adj_u[off_nei_u]);
        if (off_nei_v >= len_v) {
            break;
        }
        if (adj_u[off_nei_u] == adj_v[off_nei_v]) {
            triangles[size].edge_a = off_nei_u + adj_u_offset;
            triangles[size].edge_b = off_nei_v + adj_v_offset;
            size++;
            ++off_nei_u;
            ++off_nei_v;
            if (size == max_triangles || off_nei_u >= len_u || off_nei_v >= len_v) {
                break;
            }
        }
    }
    return size;
}


static void p_find_triangles(
        gk_graph_t const *const lgraph,
        gk_graph_t const *const ugraph,
        int64_t const *const lgraph_maps,
        int32_t const num_triangles,
        int32_t const *const supports,
        tri_edges *const triangle_buf,
        int32_t *const h_index,
        int32_t const u,
        int32_t const v) {
    int32_t found_triangles = 0;

    /*
     * For each triangle, we need to find vertex 'W' which completes the
     * triangle. There are three cases to consider:
     *   (1) (u, v, W) -> 'W' will be in ugraph[u] and ugraph[v].
     *   (2) (u, W, v) -> 'W' will be in ugraph[u] and lgraph[v].
     *   (3) (W, u, v) -> 'W' will be in lgraph[u] and lgraph[v].
     *
     *   After each triangle search, we return the edge index which completes
     *   triangle via (u, W).
     */

    /* XXX add software prefetching of adj[u] and adj[w]? */

    int32_t nnbrs_u = ugraph->xadj[u + 1] - ugraph->xadj[u];
    int32_t nnbrs_v = ugraph->xadj[v + 1] - ugraph->xadj[v];
    int32_t *adj_u = &(ugraph->adjncy[ugraph->xadj[u]]);
    int32_t *adj_v = &(ugraph->adjncy[ugraph->xadj[v]]);

    /* (u, v, W) */
    if (found_triangles != num_triangles) {
        int32_t const new_triangles = p_intersect_lists_galloping(
                adj_u, nnbrs_u, ugraph->xadj[u],
                adj_v, nnbrs_v, ugraph->xadj[v],
                &(triangle_buf[found_triangles]), num_triangles - found_triangles);

        /* Go through new edges and take min{(u-W), (v-W)} */
        for (int32_t t = 0; t < new_triangles; ++t) {
            /* two incident h-index values */
            int32_t const uw = supports[triangle_buf[t].edge_a];
            int32_t const vw = supports[triangle_buf[t].edge_b];

            /* keep minimum of two */
            h_index[t] = gk_min(uw, vw);
        }
        found_triangles += new_triangles;
    }

    /* (u, W, v) */
    if (found_triangles != num_triangles) {
        nnbrs_v = lgraph->xadj[v + 1] - lgraph->xadj[v];
        adj_v = &(lgraph->adjncy[lgraph->xadj[v]]);
        int32_t const new_triangles = p_intersect_lists_galloping(
                adj_u, nnbrs_u, ugraph->xadj[u],
                adj_v, nnbrs_v, lgraph->xadj[v],
                &(triangle_buf[found_triangles]), num_triangles - found_triangles);

        for (int32_t tx = 0; tx < new_triangles; ++tx) {
            int32_t const t = tx + found_triangles;
            /* translate edge */
            triangle_buf[t].edge_b = lgraph_maps[triangle_buf[t].edge_b];
            int32_t const uw = supports[triangle_buf[t].edge_a];
            int32_t const vw = supports[triangle_buf[t].edge_b];

            h_index[t] = gk_min(uw, vw);
        }

        found_triangles += new_triangles;
    }

    /* (W, u, v) */
    if (found_triangles != num_triangles) {
        nnbrs_u = lgraph->xadj[u + 1] - lgraph->xadj[u];
        adj_u = &(lgraph->adjncy[lgraph->xadj[u]]);
        int32_t const new_triangles = p_intersect_lists_galloping(
                adj_u, nnbrs_u, lgraph->xadj[u],
                adj_v, nnbrs_v, lgraph->xadj[v],
                &(triangle_buf[found_triangles]), num_triangles - found_triangles);

        /* we have to translate the edges in lgraph(u) to ugraph(W) */
        for (int32_t tx = 0; tx < new_triangles; ++tx) {
            int32_t const t = tx + found_triangles;
            /* translate edges */
            triangle_buf[t].edge_a = lgraph_maps[triangle_buf[t].edge_a];
            triangle_buf[t].edge_b = lgraph_maps[triangle_buf[t].edge_b];

            int32_t const uw = supports[triangle_buf[t].edge_a];
            int32_t const vw = supports[triangle_buf[t].edge_b];

            h_index[t] = gk_min(uw, vw);
        }

        found_triangles += new_triangles;
    }

    assert(found_triangles == num_triangles);
}


static int32_t p_compute_hindex(
        int32_t const *const vals,
        int32_t *const buffer,
        int32_t const N) {
    for (int32_t i = 0; i < N + 1; ++i) {
        buffer[i] = 0;
    }

    for (int32_t i = 0; i < N; ++i) {
        int32_t idx = 0;
        if (vals[i] < N) {
            idx = vals[i];
        } else {
            idx = N;
        }
        ++buffer[idx];
    }

    int32_t sum = 0;
    for (int32_t i = N; i >= 0; --i) {
        sum += buffer[i];
        if (sum >= i) {
            return i;
        }
    }

    assert(false);
    return -1;
}


/**
* @brief Compute an edge's new h-index.
*
* @param lgraph The lower-triangular graph.
* @param ugraph The upper-triangular graph.
* @param lgraph_maps Mapping of lgraph edges to ugraph edges.
* @param supports The current supports (i.e., h-index values).
* @param triangle_buf Buffer which stores edge indices of found triangles.
* @param h_index The h-index of each adjacent triangle.
* @param h_index_buf Buffer for computing new h-index in linear time.
* @param edge_idx The index of the edge we are updating (in `ugraph`).
* @param vtx_u The ID of the origin vertex of edge_idx.
* @param[out] need_update We mark all adjacent triangles `1` if our h-index
*                         score changes.
*
* @return The new h-index value.
*/
static int32_t p_update_edge(
        gk_graph_t const *const lgraph,
        gk_graph_t const *const ugraph,
        int64_t const *const lgraph_maps,
        int32_t const *const supports,
        tri_edges *const triangle_buf,
        int32_t *const h_index,
        int32_t *const h_index_buf,
        int64_t const edge_idx,
        int32_t const u,
        char *const need_update) {
    int32_t const v = ugraph->adjncy[edge_idx];
    int32_t const num_triangles = ugraph->iadjwgt[edge_idx];

    p_find_triangles(lgraph, ugraph, lgraph_maps, num_triangles, supports,
                     triangle_buf, h_index, u, v);

    /* get the new h_index value */
    int32_t const new_h = p_compute_hindex(h_index, h_index_buf, num_triangles);

    /* tell neighboring edges that they need to be updated */
    if (new_h != supports[edge_idx]) {
        for (int32_t t = 0; t < num_triangles; ++t) {
            /* benign race condition since 'char' can be written atomically */
            need_update[triangle_buf[t].edge_a] = 1;
            need_update[triangle_buf[t].edge_b] = 1;
        }
    }

    return new_h;
}


/******************************************************************************
 * PUBLIC FUNCTIONS
 *****************************************************************************/

int64_t kt_and(params_t *params, vault_t *vault) {
    log_trace("THREADS: %d", omp_get_max_threads());

    /*
     * Grab upper and lower trangular portion of graph.
     */
    gk_startwctimer(vault->timer_tcsetup);
    vault->ugraph = kt_PreprocessAndExtractUpper(params, vault);
    vault->lgraph = kt_TransposeUforJIK(params, vault->ugraph);
    gk_stopwctimer(vault->timer_tcsetup);

    int32_t const nvtxs = vault->ugraph->nvtxs;
    int64_t const nedges = vault->ugraph->xadj[nvtxs];

    /*
     * Compute initial supports and count the number of edges with support
     * greater than zero.
     */
    gk_startwctimer(vault->timer_esupport);
    vault->ugraph->iadjwgt = gk_i32malloc(nedges, "iadjwgt");
    par_memset(vault->ugraph->iadjwgt, 0, nedges * sizeof(*vault->ugraph->iadjwgt));
    int32_t *supports = gk_i32malloc(nedges, "supports");
    par_memset(supports, 0, nedges * sizeof(*supports));

    int64_t const ntriangles = kt_ComputeEdgeSupport(params, vault);
    par_memcpy(supports, vault->ugraph->iadjwgt, nedges * sizeof(*supports));

    int64_t const nz_edges = count_nnz(nedges, supports);
    gk_stopwctimer(vault->timer_esupport);

    log_trace("Found |V|=%'d |E|=%'lld |T|=%'lld NZ-SUPPORTS=%'lld (%0.1f%%)",
              nvtxs, nedges, ntriangles, nz_edges,
              100. * (double) nz_edges / (double) nedges);

    gk_graph_Free(&vault->lgraph);
    vault->lgraph = transpose_graph(vault->ugraph);

    /* Create a mapping of edge IDs to 'u' vertices in ugraph. */
    int32_t *u_vtxs = static_cast<int32_t *>(gk_malloc(nedges * sizeof(*u_vtxs), "u_vtxs"));
#pragma omp parallel for schedule(dynamic, DYNAMIC_CHUNK)
    for (int32_t v = 0; v < nvtxs; ++v) {
        for (ssize_t e = vault->ugraph->xadj[v]; e < vault->ugraph->xadj[v + 1]; ++e) {
            u_vtxs[e] = v;
        }
    }

    /* Create a mapping of edge IDs in lgraph to ugraph */
    int64_t *lgraph_maps = static_cast<int64_t *>(gk_malloc(nedges * sizeof(*lgraph_maps),
                                                            "lgraph_maps"));
#pragma omp parallel for schedule(dynamic, DYNAMIC_CHUNK)
    for (int32_t v = 0; v < nvtxs; ++v) {
        for (ssize_t le = vault->lgraph->xadj[v]; le < vault->lgraph->xadj[v + 1];
             ++le) {
            int32_t const u = vault->lgraph->adjncy[le];
            /* find corresponding edge in ugraph */
            for (ssize_t ue = vault->ugraph->xadj[u]; ue < vault->ugraph->xadj[u + 1];
                 ++ue) {
                if (vault->ugraph->adjncy[ue] == v) {
                    lgraph_maps[le] = ue;
                }
            }
        }
    }


    int32_t const max_support = max_elem(supports, nedges);

    int32_t *h_index[MAX_NTHREADS];
    int32_t *h_index_buf[MAX_NTHREADS];
    tri_edges *triangle_buf[MAX_NTHREADS];
#pragma omp parallel
    {
        int const tid = omp_get_thread_num();
        h_index[tid] = static_cast<int32_t *>(gk_malloc(max_support * sizeof(**h_index), "h_index"));
        h_index_buf[tid] = static_cast<int32_t *>(gk_malloc((max_support + 1) * sizeof(**h_index),
                                                            "h_index_buf"));
        triangle_buf[tid] = static_cast<tri_edges *>(gk_malloc(max_support * sizeof(**triangle_buf),
                                                               "tri_buf"));
    }

    /* Marks whether the edge has a neighboring triange which has updated */
    char *need_update = static_cast<char *>(gk_malloc(nedges * sizeof(*need_update), "need_update"));
    char *need_update_new = static_cast<char *>(gk_malloc(nedges * sizeof(*need_update),
                                                          "need_update_new"));

    /* reset update messages */
#pragma omp parallel for schedule(static)
    for (int64_t e = 0; e < nedges; ++e) {
        need_update[e] = 1;
        need_update_new[e] = 0;
    }

    gk_startwctimer(vault->timer_ktpeeling);
    bool done = false;

    log_info("with google perf start------------");

#ifdef GPERFTOOLS

    string temp(params->infile);
    ProfilerStart("and-improved.log");
#endif
    /*
     * Main loop.
     */
    double iter_timer;
    iter_timer = 0;
    int64_t total_changes = 0;
    while (!done) {
        int64_t nchanges = 0;
        gk_clearwctimer(iter_timer);
        gk_startwctimer(iter_timer);
#pragma omp parallel for schedule(dynamic, DYNAMIC_CHUNK) \
        reduction(+: nchanges)
        for (int64_t e = 0; e < nedges; ++e) {
            if (!need_update[e]) {
                continue;
            }

            int const tid = omp_get_thread_num();
            int32_t const new_support = p_update_edge(vault->lgraph, vault->ugraph,
                                                      lgraph_maps, supports, triangle_buf[tid], h_index[tid],
                                                      h_index_buf[tid],
                                                      e, u_vtxs[e], need_update_new);

            if (supports[e] != new_support) {
                /* benign race condition as long as writes to int32_t are atomic */
                supports[e] = new_support;
                ++nchanges;
            }

            /* reset update */
            need_update[e] = 0;
        } /* end omp for loop */
        gk_stopwctimer(iter_timer);
        total_changes += nchanges;
        log_info("iter/total changes: %'lld / %'lld, Time: %.6lfs", nchanges, total_changes, iter_timer);
        done = (nchanges == 0);

        /* swap need_update pointers */
        char *tmp = need_update_new;
        need_update_new = need_update;
        need_update = tmp;
    } /* end main loop */
    gk_stopwctimer(vault->timer_ktpeeling);

#ifdef GPERFTOOLS
    log_info("GperfToolsEnd");
    ProfilerStop();
#endif

    core_val_histogram(nedges, supports, [](int sup) { return sup; }, true);

    int32_t max_ktruss = 0;
#pragma omp parallel for reduction(max: max_ktruss)
    for (int64_t e = 0; e < nedges; ++e) {
        /* +2 because of the k-truss definition... */
        supports[e] += 2;
        max_ktruss = gk_max(max_ktruss, supports[e]);
    }
    log_info("MAX K-TRUSS: %d", max_ktruss);

    /* cleanup thread data */
#pragma omp parallel
    {
        int const tid = omp_get_thread_num();
        gk_free((void **) &h_index[tid], LTERM);
        gk_free((void **) &h_index_buf[tid], LTERM);
        gk_free((void **) &triangle_buf[tid], LTERM);
    }

    /* create the output of the decomposition */
    p_construct_output(params, vault, max_ktruss, supports);

    gk_free((void **) &need_update, LTERM);
    gk_free((void **) &need_update_new, LTERM);
    gk_free((void **) &lgraph_maps, LTERM);
    gk_free((void **) &supports, LTERM);
    gk_free((void **) &u_vtxs, LTERM);

    return (int64_t) ntriangles;
}

#ifdef __cplusplus
}
#endif
