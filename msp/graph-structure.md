## IO

``` cpp
struct gk_option {
  char *name;       /*!< This field is the name of the option. */
  int has_arg;      /*!< This field says whether the option takes an argument.
                         It is an integer, and there are three legitimate values:
                         no_argument, required_argument and optional_argument.
                         */
  int *flag;        /*!< See the discussion on ::gk_option#val */
  int val;          /*!< These fields control how to report or act on the option
                         when it occurs.

                         If flag is a null pointer, then the val is a value which
                         identifies this option. Often these values are chosen
                         to uniquely identify particular long options.

                         If flag is not a null pointer, it should be the address
                         of an int variable which is the flag for this option.
                         The value in val is the value to store in the flag to
                         indicate that the option was seen. */
};
```

## Graph

```cpp
graph = gk_graph_Create();
    
graph->nvtxs = nvtxs;
    
graph->xadj   = gk_zmalloc(nvtxs+1, "gk_graph_Read: xadj");
graph->adjncy = gk_i32malloc(nedges, "gk_graph_Read: adjncy");
```

```cpp
/*-------------------------------------------------------------
 * The following data structure stores a sparse graph
 *-------------------------------------------------------------*/
typedef struct gk_graph_t {
  int32_t nvtxs;                /*!< The number of vertices in the graph */
  ssize_t *xadj;                /*!< The ptr-structure of the adjncy list */
  int32_t *adjncy;              /*!< The adjacency list of the graph */

  int32_t *iadjwgt;             /*!< The integer edge weights */
  float *fadjwgt;               /*!< The floating point edge weights */
  int32_t *ivwgts;              /*!< The integer vertex weights */
  float *fvwgts;                /*!< The floating point vertex weights */
  int32_t *ivsizes;             /*!< The integer vertex sizes */
  float *fvsizes;               /*!< The floating point vertex sizes */
  int32_t *vlabels;             /*!< The labels of the vertices */
} gk_graph_t;



```

```cpp

d_graph->xaii = gk_malloc((nvtxs+1) * sizeof(*d_graph->xaii), "xaii");
d_graph->aii  = gk_malloc((2*nedges+1) * sizeof(*d_graph->aii), "aii");
d_graph->ids  = gk_malloc((2*nedges+1) * sizeof(*d_graph->ids), "ids");
d_graph->supports = gk_malloc(nedges * sizeof(*d_graph->supports), "supports");

```