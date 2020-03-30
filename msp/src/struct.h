/*!
\file
\brief Data structures used in the program
\date Started 5/10/2017
\author George
\version\verbatim $Id: struct.h 21155 2017-06-09 21:36:55Z karypis $ \endverbatim
*/

#ifndef _STRUCT_KT_H_
#define _STRUCT_KT_H_


typedef struct
{
  int32_t vi; /* source vtx */
  int32_t vj; /* dest vtx */

  ssize_t eij; /* index of edge (vi, vj) */
  ssize_t eji; /* index of edge (vj, vi) */
} edge_t;



/*************************************************************************
* an edge in the k-truss decomposition
**************************************************************************/
typedef struct {
  int32_t vi, vj, k;
} ktedge_t;


typedef struct {
  int32_t key;
  int64_t val;
} epair_t;


/*************************************************************************
* the data vault
**************************************************************************/
typedef struct {
  gk_graph_t *graph;      /* the graph */
  gk_graph_t *ugraph;     /* the upper triangular graph */
  gk_graph_t *lgraph;     /* the lower triangular graph (with potentially indexing
                             information in U */

  int32_t *perm;        /* perm[old-vtx-num]  => new-vtx-num */
  int32_t *iperm;       /* iperm[new-vtx-num] => old-vtx-num */

  int64_t nedges;       /* the number of edges in ktedges */
  ktedge_t *ktedges;    /* the k-truss decomposition */
  int32_t ktmax;        /* the maximum k found in k-truss */

  /* timers */
  double timer_global;
  double timer_io;
  double timer_tcsetup;
  double timer_ktsetup;
  double timer_esupport;
  double timer_ktpeeling;
  double timer_1;
  double timer_2;
  double timer_3;
  double timer_4;
  double timer_5;
  double timer_6;
} vault_t;


/*************************************************************************
* run parameters
**************************************************************************/
typedef struct {
  int kttype;           /* The algorithm to use for k-truss */
  int iftype;           /* The format of the input file */

  int jbsize;           /* The size of the J block in words (query block) */
  int ibsize;           /* The size of the I block in words (database block) */

  int seed;             /* Seed for the random number generator */
  int dbglvl;           /* Debuging information */

  char *infile;         /* The file storing the input data */
  char *outfile;        /* The file storing the output data */
  char* logfile;        /* The file storing the log data */
} params_t;


typedef struct
{
  /* u < v < w */
  int32_t u;
  int32_t v;
  int32_t w;
  /* edge indices */
  int64_t uv;
  //int64_t uw;
  int64_t vw;
} triangle_t;


typedef struct
{
  int32_t v;
  int32_t w;
  int64_t vw;
} pair_t;


#endif
