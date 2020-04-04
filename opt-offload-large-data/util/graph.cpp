#include "graph.h"

#include <cassert>

#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <chrono>
#include <fstream>

#include "jetbrains_fake.h"
#include "util.h"
#include "log.h"
#include "search_util.h"
#include "../host/parallel_all_edge_cnc.h"

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

//Populate eid and edge list
void getEidAndEdgeList(graph_t *g, Edge *idToEdge) {
    //Allocate space for eid -- size g->m
    g->eid = (eid_t *) malloc(g->m * sizeof(eid_t));

    //Edge upper_tri_start of each edge
    auto *num_edges_copy = (eid_t *) malloc((g->n + 1) * sizeof(eid_t));
    assert(num_edges_copy != nullptr);

#ifdef NAVIE_SERIAL_CONSTRUCT
    long edgeId = 0;
    for (vid_t i = 0; i < g->n; i++) {
        num_edges_copy[i] = g->num_edges[i];
    }
    //Number the edges as <u,v> -- such that u < v -- <u,v> and <v,u> are same edge
    for (vid_t u = 0; u < g->n; u++) {
        //now go through the adjacency of u
        for (eid_t j = g->num_edges[u]; j < g->num_edges[u + 1]; j++) {
            vid_t v = g->adj[j];
            if (u < v) {
                Edge e;
                e.u = u;
                e.v = v;

                g->eid[j] = edgeId;
                num_edges_copy[u]++;

                if (g->adj[num_edges_copy[v]] == u) {
                    g->eid[num_edges_copy[v]] = edgeId;
                    num_edges_copy[v]++;
                }

                idToEdge[edgeId] = e;
                edgeId++;
            }
        }
    }
#else
    auto *upper_tri_start = (eid_t *) malloc(g->n * sizeof(eid_t));

    num_edges_copy[0] = 0;
#pragma omp parallel
    {
#pragma omp for
        // Histogram (Count).
        for (vid_t u = 0; u < g->n; u++) {
            upper_tri_start[u] = (g->num_edges[u + 1] - g->num_edges[u] > 256)
                                 ? GallopingSearch(g->adj, g->num_edges[u], g->num_edges[u + 1], u)
                                 : LinearSearch(g->adj, g->num_edges[u], g->num_edges[u + 1], u);
            num_edges_copy[u + 1] = g->num_edges[u + 1] - upper_tri_start[u];
        }
        // Scan.
#pragma omp single
        {
            Timer local_timer;
            for (auto i = 0; i < g->n; i++) {
                num_edges_copy[i + 1] += num_edges_copy[i];
            }
            log_info("SCAN Time: %.9lf s", local_timer.elapsed());
        }

        // Transform.
        auto u = 0;
#pragma omp for schedule(dynamic, 6000)
        for (eid_t j = 0; j < g->m; j++) {
            u = FindSrc(g, u, j);
            if (j < upper_tri_start[u]) {
                auto v = g->adj[j];
                auto offset = BranchFreeBinarySearch(g->adj, g->num_edges[v], g->num_edges[v + 1], u);
                auto eid = num_edges_copy[v] + (offset - upper_tri_start[v]);
                g->eid[j] = eid;
                idToEdge[eid] = Edge(v, u);
            } else {
                g->eid[j] = num_edges_copy[u] + (j - upper_tri_start[u]);
            }
        }

#ifdef VERIFY_INPUT
        // verify eid.
#pragma omp for
        for (eid_t j = 0; j < g->m / 2; j++) {
            Edge edge = idToEdge[j];
            if (edge.u >= edge.v) {
                log_fatal("Edge List Order Not Correct...");
                exit(-1);
            }
            auto u = edge.u;
            auto v = edge.v;
            if (BranchFreeBinarySearch(g->adj, g->num_edges[v], g->num_edges[v + 1], u) == g->num_edges[v + 1]) {
                log_fatal("Not Found u: %d in v: %d", u, v);
                exit(-1);
            }
            if (BranchFreeBinarySearch(g->adj, g->num_edges[u], g->num_edges[u + 1], v) == g->num_edges[u + 1]) {
                log_fatal("Not Found v: %d in u: %d", v, u);
                exit(-1);
            }
        }
#pragma omp single
        log_debug("Pass EID checking...");
#endif
    }
    free(upper_tri_start);
#endif

    free(num_edges_copy);
}

Graph::Graph(char *dir_cstr) {
    dir = string(dir_cstr);

    ReadDegree();
    ReadAdjacencyList();
    CheckInputGraph();
}

using namespace std::chrono;

void Graph::ReadDegree() {
    auto start = high_resolution_clock::now();

    ifstream deg_file(dir + string("/b_degree.bin"), ios::binary);
    int int_size;
    deg_file.read(reinterpret_cast<char *>(&int_size), 4);

    deg_file.read(reinterpret_cast<char *>(&nodemax), 4);
    deg_file.read(reinterpret_cast<char *>(&edgemax), 4);
    log_info("int size: %d, n: %s, m: %s", int_size, FormatWithCommas(nodemax).c_str(),
             FormatWithCommas(edgemax).c_str());

    degree.resize(static_cast<unsigned long>(nodemax));
    deg_file.read(reinterpret_cast<char *>(&degree.front()), sizeof(int) * nodemax);

    auto end = high_resolution_clock::now();
    log_info("read degree file time: %.3lf s", duration_cast<milliseconds>(end - start).count() / 1000.0);
}

void Graph::ReadAdjacencyList() {
    auto start = high_resolution_clock::now();
    ifstream adj_file(dir + string("/b_adj.bin"), ios::binary);

    // csr representation
    node_off = (uint32_t *) malloc(sizeof(uint32_t) * (nodemax + 1));
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

void Graph::CheckInputGraph() {
    auto start = high_resolution_clock::now();

#pragma omp parallel for schedule(dynamic, 5000)
    for (auto i = 0u; i < nodemax; i++) {
        for (auto j = node_off[i]; j < node_off[i + 1]; j++) {
            if (edge_dst[j] == static_cast<int>(i)) {
                log_error("Self loop");
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
