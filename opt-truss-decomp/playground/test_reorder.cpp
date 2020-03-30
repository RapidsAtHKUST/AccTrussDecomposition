//
// Created by yche on 6/28/19.
//

#include "../reordering_utils/reorder_utils.h"
#include "util/log/log.h"

int main(int argc, char *argv[]) {
    graph_t g;

    //load the graph from file
    Graph yche_graph(argv[1]);
    g.adj = yche_graph.edge_dst;
    g.num_edges = yche_graph.node_off;
    g.n = yche_graph.nodemax;
    g.m = yche_graph.edgemax;
    vector<int32_t> new_vid_dict;
    vector<int32_t> old_vid_dict;

    string reorder_method(argv[2]);
    ReorderWrapper(g, string(argv[1]), reorder_method, new_vid_dict, old_vid_dict);
}