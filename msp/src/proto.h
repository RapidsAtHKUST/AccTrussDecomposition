/*!
\file
\brief This file contains function prototypes
\date Started 5/12/2017
\author George
\version\verbatim $Id: proto.h 21158 2017-06-10 22:36:08Z karypis $ \endverbatim
*/

#ifndef _PROTO_H_
#define _PROTO_H_


/* util.c */


/**
* @brief Sort a list of triangle_t. u, v, and w are used as successive
*        tiebreakers.
*
* @param tris The triangles to sort.
* @param ntriangles The length of `tris`.
*/
void sort_triangles(
    triangle_t * const  tris,
    int32_t ntriangles);


/**
* @brief Transpose a graph. Each edge (u, v) is converted to (v, u). This will
*        only work on graphs without multi-edges.
*
* @param G The graph to transpose.
*
* @return The transposed graph.
*/
gk_graph_t * transpose_graph(
    gk_graph_t const * const G);



/**
* @brief Add an island vertex to the beginning of the graph (vertex 0).
*
* @param graph The graph to modify.
*/
void graph_add_island(
    gk_graph_t * graph);


/**
* @brief Returns the maximum-valued element in `array`.
*
* @param array The data.
* @param N The length (in elements) of `array`.
*
* @return The maximum value.
*/
int32_t max_elem(
    int32_t const * const  array,
    int64_t N);


/**
* @brief Returns the maximum degree of any vertex in a graph.
*
* @param G The graph.
*
* @return The maximum degree.
*/
ssize_t graph_max_degree(
    gk_graph_t const * const G);


/**
* @brief Count the number of entries that have positive support (> 0). Negative
*        supports indicate that the edge has been removed and its k-value is
*        finalized, so they are not included.
*
* @param N The total number of entries in the array.
* @param supports The array of supports.
*
* @return  The number of entries with have support greater than zero.
*/
int64_t count_nnz(
    int64_t const N,
    int32_t const * const supports);


/**
* @brief Count the total amount of support in the remaining graph. Negative
*        entries are not included in the sum.
*
* @param N The number of edges.
* @param supports The supports.
*
* @return sum(supports[:])
*/
int64_t count_support(
    int64_t const N,
    int32_t const * const supports);


/**
* @brief Performs a `memset()` in parallel. Parallelism is required to both
*        saturate the memory bandwidth of a system and to also spread data
*        across NUMA nodes.
*
* @param s The memory to set.
* @param c The value to assign to each each byte.
* @param bytes The length of `s`.
*
* @return Just returns `s`.
*/
void * par_memset(
    void * const s,
    int const c,
    size_t const bytes);


/**
* @brief Performs a `memcpy()` in parallel.
*
* @param dest The destination buffer.
* @param src The source buffer.
* @param bytes The length of `dest`.
*/
void par_memcpy(
    void       * const dest,
    void const * const src,
    size_t const bytes);



/* io.c */
vault_t *loadData(params_t *params);
void writeResults(params_t *params, vault_t *vault);

/* cmdline.c */
params_t *getcmdline_params(int argc, char *argv[]);

/* kt.c */
int32_t *gk_i32kvipermi(int32_t n, gk_i32kv_t *cand);
gk_graph_t *kt_PreprocessAndExtractUpper(params_t *params, vault_t *vault);
gk_graph_t *kt_TransposeUforJIK(params_t *params, gk_graph_t *graph);
void kt_CheckInitialSupport(params_t *params, vault_t *vault);
void kt_CheckKTrussDecomposition(params_t *params, vault_t *vault);
void kt_Sups2KTEdges(params_t *params, vault_t *vault, int32_t ktmax, int32_t *sups);
int64_t kt_ComputeEdgeSupport(params_t *params, vault_t *vault);
int64_t kt_ComputeEdgeSupportPar(params_t *params, vault_t *vault);
int64_t kt_serial(params_t *params, vault_t *vault);
int64_t kt_msp(params_t *params, vault_t *vault);

#ifdef __cplusplus
extern "C" {
#endif

int64_t kt_and(params_t *params, vault_t *vault);
#ifdef __cplusplus
}
#endif

#endif
