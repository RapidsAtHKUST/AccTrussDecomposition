#pragma once

#include <unordered_map>
#include <vector>

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_hash_map.h>

using namespace std;

//typedef unsigned int vid_t;
typedef int vid_t;
typedef unsigned int eid_t;

typedef struct {
    long n;
    long m;

    vid_t *adj;
    eid_t *num_edges;
    eid_t *eid;
} graph_t;

//Define an Edge data type
struct Edge {
    vid_t u;
    vid_t v;

    Edge() {
        this->u = 0;
        this->v = 0;
    }

    Edge(vid_t u, vid_t v) {
        this->u = u;
        this->v = v;
    }
};

void free_graph(graph_t *g);

void getEidAndEdgeList(graph_t *g, Edge *idToEdge);

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

double timer();
