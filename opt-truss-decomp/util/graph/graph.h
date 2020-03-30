#pragma once

#include <unordered_map>
#include <vector>

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_hash_map.h>
#include <sparsepp/spp.h>

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
#ifdef NUMA_EID
    eid_t *eid2;
#endif
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

//Define a hash function for Edge
struct EdgeHasher {
    std::size_t operator()(const Edge &k) const {
//        std::hash<vid_t> unsignedHash;
//        return ((unsignedHash(k.u) >> 1) ^ (unsignedHash(k.v) << 1));

        // elegant pair function, from simrank...
        unsigned int combined_int;
        if (k.u >= k.v) {
            combined_int = k.u * k.u + k.u + k.v;
        } else {
            combined_int = k.v * k.v + k.u;
        }
        return std::hash<unsigned int>{}(combined_int);
    }
};

struct edgeEqual {
    bool operator()(const Edge &e1, const Edge &e2) const {
        return (e1.u == e2.u) && (e1.v == e2.v);
    }
};


//typedef unordered_map<Edge, long, EdgeHasher, edgeEqual> MapType;
//typedef tbb::concurrent_hash_map<Edge, long, EdgeHasher, edgeEqual> MapType;
//typedef tbb::concurrent_unordered_map<Edge, long, EdgeHasher, edgeEqual> MapType;
using MapType = vector<spp::sparse_hash_map<vid_t, eid_t >>;

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
