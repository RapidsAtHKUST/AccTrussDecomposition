#pragma once

#include <unordered_map>
#include <vector>

using namespace std;

typedef int vid_t;
typedef unsigned int eid_t;

typedef struct {
    long n;
    long m;

    vid_t *adj;
    eid_t *num_edges;
    eid_t *eid;
} graph_t;

struct Graph {
    string dir;

    uint32_t nodemax;
    uint32_t edgemax;

    // csr representation
    uint32_t *node_off;
    int *edge_dst;

    vector<int> degree;

    explicit Graph(char *dir_cstr);

public:
    void ReadDegree();

    void CheckInputGraph();

    void ReadAdjacencyList();
};

