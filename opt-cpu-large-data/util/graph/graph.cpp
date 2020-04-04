#include "graph.h"

#include <sys/time.h>

#include "opt_pkt/parallel_all_edge_cnc.h"

void free_graph(graph_t *g) {
    if (g->adj != nullptr)
        free(g->adj);

    if (g->num_edges != nullptr)
        free(g->num_edges);

    if (g->eid != nullptr)
        free(g->eid);
}

double timer() {
    struct timeval tp{};
    gettimeofday(&tp, nullptr);
    return ((double) (tp.tv_sec) + tp.tv_usec * 1e-6);
}