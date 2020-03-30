//
// Created by yche on 5/20/19.
//

#include <omp.h>

#include <vector>
#include <chrono>

#include "graph_bin_input_helper.h"

#include "util/util.h"
#include "util/log/log.h"
#include "util/graph/pre_processing.h"
#include "util/serialization/yche_serialization.h"

using namespace std;
using namespace std::chrono;

using edge_type = pair<int32_t, int32_t>;
using edge_lst_type = vector<edge_type>;

edge_lst_type ReadEdgeList(string dir) {
    log_info("Path: %s", dir.c_str());
    edge_lst_type edges;
    string graphpath = dir + "/" + "undir_edge_list.bin";
    FILE *pFile = fopen(graphpath.c_str(), "r");
    YcheSerializer serializer;
    serializer.read_array(pFile, edges);
    fclose(pFile);
    log_info("edge#: %zu", edges.size());
    return edges;
}

void ReadEdgeList(string dir, edge_type *&edge_lst, uint32_t &num_edges) {
    log_info("Path: %s", dir.c_str());
    edge_lst_type edges;
    string graphpath = dir + "/" + "undir_edge_list.bin";
    int fd = open(graphpath.c_str(), O_RDONLY, S_IRUSR | S_IWUSR);
    size_t arr_size;
    pread(fd, &arr_size, sizeof(size_t), 0);
    num_edges = arr_size;
    log_info("edge#: %zu", arr_size);
    edge_lst = (edge_type *) malloc(sizeof(edge_type) * arr_size);
    pread(fd, edge_lst, sizeof(edge_type) * arr_size, sizeof(size_t));
}

void readDirectory(char *filename, int &nVtx, uint32_t &nEdge, int *&adj_lst, uint32_t *&xadj) {
    Graph yche_graph(filename);
    nVtx = yche_graph.nodemax;
    nEdge = yche_graph.edgemax / 2;
    adj_lst = yche_graph.edge_dst;
    xadj = yche_graph.node_off;
}

void readDirEdgeList(char *filename, int &nVtx, uint32_t &nEdge, int *&adj_lst, uint32_t *&xadj) {
    edge_type *edge_lst = nullptr;
    ReadEdgeList(filename, edge_lst, nEdge);
    auto edge_lst_buffer = (edge_type *) malloc(sizeof(edge_type) * nEdge);
    auto max_node_id = RemoveDuplicates(edge_lst, nEdge, edge_lst_buffer);
    auto num_vertices = max_node_id + 1;
    free(edge_lst_buffer);

    uint32_t *deg_lst;
    graph_t g{.n=num_vertices, .m = 0, .adj=nullptr, .num_edges=nullptr};
    ConvertEdgeListToCSR((uint32_t) nEdge, edge_lst, num_vertices, deg_lst, g.num_edges, g.adj,
                         omp_get_max_threads());
    g.m = g.num_edges[num_vertices];
#pragma omp parallel for schedule(dynamic, 1000)
    for (auto u = 0; u < num_vertices; u++) {
        sort(g.adj + g.num_edges[u], g.adj + g.num_edges[u + 1]);
    }

    nVtx = g.n;
    nEdge = g.m / 2;
    adj_lst = g.adj;
    xadj = g.num_edges;
}

