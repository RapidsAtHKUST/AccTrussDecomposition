#pragma once

#include "util/timer.h"

#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <unordered_map>
#include <vector>

#include <chrono>
#include <fstream>

#include "util/util.h"
#include "util/log/log.h"

using namespace std;

typedef int vid_t;
typedef unsigned int eid_t;
//typedef size_t eid_t;

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

template<typename T>
struct Graph {
    string dir;

    uint32_t nodemax;
    T edgemax;

    // csr representation
    T *node_off;
    int *edge_dst;

    vector<int> degree;

    explicit Graph(char *dir_cstr);

public:
    void ReadDegree();

    void CheckInputGraph();

    void ReadAdjacencyList();
};

template<typename T>
Graph<T>::Graph(char *dir_cstr) {
    dir = string(dir_cstr);
    // clear the 4 bytes
    edgemax = 0;
    ReadDegree();
    ReadAdjacencyList();
    CheckInputGraph();
}

using namespace std::chrono;

template<typename T>
void Graph<T>::ReadDegree() {
    auto start = high_resolution_clock::now();

    ifstream deg_file(dir + string("/b_degree.bin"), ios::binary);
    int int_size = 0;
    deg_file.read(reinterpret_cast<char *>(&int_size), 4);
    if (int_size != sizeof(T)) {
        log_warn("int_size != sizeof(T), %d, %d", int_size, sizeof(T));
    }

    deg_file.read(reinterpret_cast<char *>(&nodemax), sizeof(int));
    deg_file.read(reinterpret_cast<char *>(&edgemax), int_size);
    log_info("int size: %d, n: %s, m: %s", int_size, FormatWithCommas(nodemax).c_str(),
             FormatWithCommas(edgemax).c_str());

    degree.resize(static_cast<unsigned long>(nodemax));
    deg_file.read(reinterpret_cast<char *>(&degree.front()), sizeof(int) * nodemax);

    auto end = high_resolution_clock::now();
    log_info("read degree file time: %.3lf s", duration_cast<milliseconds>(end - start).count() / 1000.0);
}

template<typename T>
void Graph<T>::ReadAdjacencyList() {
    auto start = high_resolution_clock::now();
    ifstream adj_file(dir + string("/b_adj.bin"), ios::binary);

    // csr representation
    node_off = (T *) malloc(sizeof(T) * (nodemax + 1));
    edge_dst = static_cast<int *>(malloc(sizeof(int) * static_cast<uint64_t>(edgemax + 16)));

    string dst_v_file_name = dir + string("/b_adj.bin");
    auto dst_v_fd = open(dst_v_file_name.c_str(), O_RDONLY, S_IRUSR | S_IWUSR);
    int *buffer = (int *) mmap(0, static_cast<uint64_t >(edgemax) * 4u, PROT_READ, MAP_PRIVATE, dst_v_fd, 0);

    // prefix sum
    node_off[0] = 0;
    for (auto i = 0u; i < nodemax; i++) { node_off[i + 1] = node_off[i] + degree[i]; }

    auto end = high_resolution_clock::now();
    log_info("malloc, and sequential-scan time: %.3lf s", duration_cast<milliseconds>(end - start).count() / 1000.0);
    // load dst vertices into the array
#pragma omp parallel for schedule(dynamic, 1000)
    for (auto i = 0u; i < nodemax; i++) {
        // copy to the high memory bandwidth mem
        for (uint64_t offset = node_off[i]; offset < node_off[i + 1]; offset++) {
            edge_dst[offset] = buffer[offset];
        }
        // inclusive
        degree[i]++;
    }
    munmap(buffer, static_cast<uint64_t >(edgemax) * 4u);

#ifdef VERIFY_INPUT
    // Verify.
#pragma omp parallel for schedule(dynamic, 1000)
    for (auto u = 0u; u < nodemax; u++) {
        for (size_t offset = node_off[u]; offset < node_off[u + 1]; offset++) {
            auto v = edge_dst[offset];
            if (BranchFreeBinarySearch(edge_dst, node_off[v], node_off[v + 1], (int) u) == node_off[v + 1]) {
                log_fatal("CSR not correct...");
                exit(-1);
            }
        }
    }
    log_info("CSR verify pass");
#endif

    auto end2 = high_resolution_clock::now();
    log_info("read adjacency list file time: %.3lf s", duration_cast<milliseconds>(end2 - end).count() / 1000.0);
}

template<typename T>
void Graph<T>::CheckInputGraph() {
    auto start = high_resolution_clock::now();

#pragma omp parallel for schedule(dynamic, 5000)
    for (auto i = 0u; i < nodemax; i++) {
        for (auto j = node_off[i]; j < node_off[i + 1]; j++) {
            if (edge_dst[j] == static_cast<int>(i)) {
                log_error("Self loop of v: %d", i);
                exit(1);
            }
            if (j > node_off[i] && edge_dst[j] <= edge_dst[j - 1]) {
                log_error("Edges not sorted in increasing id order!\nThe program may not run properly!");
                exit(1);
            }
        }
    }
    auto end = high_resolution_clock::now();
    log_info("check input graph file time: %.3lf s", duration_cast<milliseconds>(end - start).count() / 1000.0);
}

double timer();
