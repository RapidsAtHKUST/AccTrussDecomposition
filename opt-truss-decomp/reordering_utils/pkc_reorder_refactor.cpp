#include <omp.h>

#include <util/timer.h>
#include <util/log/log.h>
#include <util/primitives/local_buffer.h>
#include <util/primitives/primitives.h>
#include <util/search/search_util.h>
#include <util/serialization/pretty_print.h>
#include <sstream>
#include <util/md5.h>
#include "reorder_utils.h"

#define frac 0.98

void free_graph_pkc(graph_t *g) {
    if (g->adj != nullptr)
        free(g->adj);

    if (g->num_edges != nullptr)
        free(g->num_edges);
}

inline int FindSrc(graph_t *g, int &tls_u, int u, uint32_t edge_idx) {
    // Init.
    if (edge_idx < g->num_edges[u]) {
        // Keep.
        tls_u = 0;
        u = 0;
    }
    if (edge_idx >= g->num_edges[u + 1]) {
        // update last_u, preferring galloping instead of binary search because not large range here
        u = GallopingSearch(g->num_edges, static_cast<uint32_t>(u) + 1, g->n + 1, edge_idx);
        // 1) first > , 2) has neighbor
        if (g->num_edges[u] > edge_idx) {
            while (g->num_edges[u] - g->num_edges[u - 1] == 0) { u--; }
            u--;
        } else {
            // g->num_edges[u] == i
            while (g->num_edges[u + 1] - g->num_edges[u] == 0) {
                u++;
            }
        }
    }
    return u;
}

uint32_t *relative_off_v = nullptr;
uint32_t *relative_off_e = nullptr;
uint32_t *identity = nullptr;
uint32_t *tmp_histogram = nullptr;
vector<uint32_t> histogram;

void CompactGraphPrimitive(graph_t *g, graph_t &g_small, int *&newDeg,
                           unsigned int *&mapIndexToVtx, vid_t *&vertexToIndex, unsigned int *cumNumEdges,
                           long &Size, const int *deg, long visited, int num_of_threads, int level) {
    auto n = g->n;
    long reduceN = n - visited;
#pragma omp single
    {
        log_info("ReduceN: %d", reduceN);
        newDeg = (int *) malloc(reduceN * sizeof(int));
        mapIndexToVtx = (unsigned int *) malloc(reduceN * sizeof(unsigned int));

        assert(g->m == g->num_edges[g->n]);
        // Auxiliaries.
        relative_off_v = (uint32_t *) malloc(n * sizeof(uint32_t));
        relative_off_e = (uint32_t *) malloc(g->m * sizeof(uint32_t));
        identity = (uint32_t *) malloc(n * sizeof(vid_t));
        tmp_histogram = (eid_t *) malloc((reduceN + 1) * sizeof(eid_t));

        g_small.n = reduceN;
        g_small.num_edges = (eid_t *) malloc((reduceN + 1) * sizeof(eid_t));
        g_small.num_edges[0] = 0;
        g_small.adj = (vid_t *) malloc(g->m * sizeof(uint32_t));
        Size = reduceN;
    }
    MemSetOMP(tmp_histogram, 0, (reduceN + 1));

    // In-place Selection: Keep the original vertex order.
    // 1st: Construct mapIndexToVtx: mapping to the original vertex ID.
    InitIdentity(identity, g->n);
    SelectNotFOMP(histogram, mapIndexToVtx, identity, relative_off_v, g->n, [deg, level](int u) {
        return deg[u] < level;
    });

    // Construct vertexToIndex, newDeg
    // Attention: Some slots left garbage (assuming vertexToIndex already allocated).
#pragma omp for
    for (size_t i = 0; i < reduceN; i++) {
        auto org_vtx = mapIndexToVtx[i];
        vertexToIndex[org_vtx] = i;
        newDeg[i] = deg[org_vtx];
    }

    SelectNotFOMP(histogram, g_small.adj, g->adj,
                  relative_off_e, g->m, [g, level, deg](size_t eid) {
                static thread_local vid_t u = 0;
                u = FindSrc(g, u, u, eid);
                auto v = g->adj[eid];
                return deg[u] < level || deg[v] < level;
            }, [vertexToIndex, g, level, deg](size_t eid) {
                static thread_local vid_t u = 0;
                u = FindSrc(g, u, u, eid);
                auto v = g->adj[eid];
                if (deg[u] < level || deg[v] < level) return true;
                __sync_fetch_and_add(&tmp_histogram[vertexToIndex[u] + 1], 1);
                return false;
            });
    InclusivePrefixSumOMP(histogram, g_small.num_edges + 1, g_small.n, [](size_t u) {
        return tmp_histogram[u + 1];
    });
#pragma omp single
    {
        g_small.m = g_small.num_edges[reduceN];
        log_info("%d, %d, %d", g_small.m, g_small.num_edges[reduceN], g->m - relative_off_e[g->num_edges[g->n] - 1]);
    };
    assert(g_small.num_edges[reduceN] == g->m - relative_off_e[g->num_edges[g->n] - 1]);
    // Mapping.
#pragma omp for
    for (size_t i = 0; i < g_small.m; i++) {
        auto v = g_small.adj[i];
        g_small.adj[i] = vertexToIndex[v];
    }
#pragma omp single
    {
        free(identity);
        free(relative_off_v);
        free(relative_off_e);
        free(tmp_histogram);
        log_info("n: %lld, m: %lld", g_small.n, g_small.m);
    }
}

void CompactGraph(graph_t *g, graph_t &g_small, int *&newDeg, unsigned int *&mapIndexToVtx, vid_t *&vertexToIndex,
                  unsigned int *cumNumEdges,
                  long &Size, const int *deg, long visited, int num_of_threads, int level) {
    vector<vid_t> buffer;
    int tid = omp_get_thread_num();
    auto n = g->n;
    long reduceN = n - visited;
    long part = reduceN / num_of_threads;

    if (tid == 0) {
        newDeg = (int *) malloc(reduceN * sizeof(int));
        mapIndexToVtx = (unsigned int *) malloc(reduceN * sizeof(unsigned int));
        g_small.n = reduceN;
        g_small.num_edges = (eid_t *) malloc((reduceN + 1) * sizeof(eid_t));
        g_small.num_edges[0] = 0;
    }

#pragma omp barrier

    // 1st: Local Buffer.
#pragma omp for schedule(static)
    for (long i = 0; i < n; i++) {
        if (deg[i] >= level) {
            buffer.push_back(i);
        }
    }

    // 2nd: Select and Map.
    long begin = __sync_fetch_and_add(&Size, buffer.size());
    for (size_t i = 0; i < buffer.size(); i++) {
        newDeg[begin + i] = deg[buffer[i]];
        mapIndexToVtx[begin + i] = buffer[i];
        vertexToIndex[buffer[i]] = begin + i;
    }
#pragma omp barrier

    // 3rd: Vertex-Centric Edge List Histogram: Make a graph with reduceN vertices.
    unsigned int edgeCount = 0;
    long it_end = tid == num_of_threads - 1 ? Size : (tid + 1) * part;
    for (long i = tid * part; i < it_end; i++) {
        unsigned int v = mapIndexToVtx[i];
        unsigned int prevEdgeCount = edgeCount;
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
            if (deg[g->adj[j]] >= level) {
                edgeCount++;
            }
        }
        g_small.num_edges[i] = prevEdgeCount;
    }
    cumNumEdges[tid] = edgeCount;
#pragma omp barrier

    if (tid == 0) {
        long start = cumNumEdges[0];
        for (int i = 1; i < num_of_threads; i++) {
            unsigned int prevEdgeCount = start;
            start = start + cumNumEdges[i];
            cumNumEdges[i] = prevEdgeCount;
        }
        g_small.m = start;
        g_small.num_edges[Size] = start;

        g_small.adj = (vid_t *) malloc(g_small.m * sizeof(vid_t));
        cumNumEdges[0] = 0;
    }
#pragma omp barrier

    for (long i = tid * part; i < it_end; i++) {
        g_small.num_edges[i] = g_small.num_edges[i] + cumNumEdges[tid];

        unsigned int v = mapIndexToVtx[i];
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
            if (deg[g->adj[j]] >= level) {
                g_small.adj[g_small.num_edges[i]] = vertexToIndex[g->adj[j]];
                g_small.num_edges[i]++;
            }
        }
    }
#pragma omp barrier

    // Now fix num_edges array
    for (long i = it_end - 1; i >= tid * part + 1; i--) {
        g_small.num_edges[i] = g_small.num_edges[i - 1];
    }
    g_small.num_edges[tid * part] = cumNumEdges[tid];
#pragma omp barrier

#pragma omp single
    {
        log_info("n: %lld, m: %lld", g_small.n, g_small.num_edges[g_small.n]);
    };
}

void PeelVertex(graph_t *local_g, int *core_val, int level, long &visited) {
    size_t start = 0;
    vector<vid_t> buffer;

#pragma omp for schedule(static)
    for (long i = 0; i < local_g->n; i++) {
        if (core_val[i] == level) {
            buffer.push_back(i);
        }
    }

    //Get work from curr_queue queue and also add work after the current size
    while (start < buffer.size()) {
        vid_t v = buffer[start];
        start++;

        for (eid_t j = local_g->num_edges[v]; j < local_g->num_edges[v + 1]; j++) {
            vid_t u = local_g->adj[j];
            int deg_u = core_val[u];
            if (deg_u > level) {
                int du = __sync_fetch_and_sub(&core_val[u], 1);
                if (du == (level + 1)) {
                    buffer.push_back(u);
                }
                if (du <= level) {
                    __sync_fetch_and_add(&core_val[u], 1);
                }
            }
        }
    }
    __sync_fetch_and_add(&visited, buffer.size());
}

void PeelSubLevel(graph_t *local_g, int *core_val, int level, long &visited,
                  vid_t *&curr_queue, vid_t *&next_queue, uint32_t &curr_size, uint32_t &next_size) {
    constexpr int BUF_SIZE = 4096;
    vid_t local_buf[BUF_SIZE];
    vid_t local_buf2[BUF_SIZE];

    // Scan.
    LocalWriteBuffer<vid_t, uint32_t> lwb(local_buf, BUF_SIZE, curr_queue, &curr_size);
#pragma omp for schedule(static)
    for (long i = 0; i < local_g->n; i++) {
        if (core_val[i] == level) {
            lwb.push(i);
        }
    }
    lwb.submit_if_possible();
#pragma omp barrier

    // Iterative Computation.
    while (curr_size > 0) {
        LocalWriteBuffer<vid_t, uint32_t> lwb2(local_buf2, BUF_SIZE, next_queue, &next_size);
#pragma omp for schedule(static)
        for (auto i = 0; i < curr_size; i++) {
            vid_t v = curr_queue[i];
            for (eid_t j = local_g->num_edges[v]; j < local_g->num_edges[v + 1]; j++) {
                vid_t u = local_g->adj[j];
                int deg_u = core_val[u];
                if (deg_u > level) {
                    int du = __sync_fetch_and_sub(&core_val[u], 1);
                    if (du == (level + 1)) {
                        lwb2.push(u);
                    }
                    if (du <= level) {
                        __sync_fetch_and_add(&core_val[u], 1);
                    }
                }
            }
        }
        lwb2.submit_if_possible();
#pragma omp barrier
#pragma omp single
        {
            visited += curr_size;
            swap(curr_queue, next_queue);
            curr_size = next_size;
            next_size = 0;
        }
    }
}

//PKC -- Make a graph with remaining vertices, parallel k-core decomposition
void PKC(graph_t *g, int *deg, int num_of_threads) {
    long n = g->n;
    long Size = 0;
    long visited = 0;

    int *newDeg = nullptr;
    unsigned int *mapIndexToVtx = nullptr;
    auto *vertexToIndex = (vid_t *) malloc(n * sizeof(vid_t));
    unsigned int cumNumEdges[num_of_threads];

    graph_t g_small;
    g_small.num_edges = nullptr;
    g_small.adj = nullptr;

    auto curr_queue = (vid_t *) malloc(n * sizeof(vid_t));
    auto next_queue = (vid_t *) malloc(n * sizeof(vid_t));
    uint32_t curr_size = 0;
    uint32_t next_size = 0;

#pragma omp parallel num_threads(num_of_threads)
    {
        int level = 0;
        int useSmallQ = 0;

#pragma omp for schedule(static)
        for (long i = 0; i < n; i++) {
            deg[i] = g->num_edges[i + 1] - g->num_edges[i];
        }

        // Level-By-Level Iterative Peeling.
        while (visited < n) {
            // Graph Compaction.
            if ((useSmallQ == 0) && (visited >= (long) (n * frac))) {
                useSmallQ = 1;
                Timer timer;
//                CompactGraph(g, g_small, newDeg, mapIndexToVtx, vertexToIndex, cumNumEdges,
                CompactGraphPrimitive(g, g_small, newDeg, mapIndexToVtx, vertexToIndex, cumNumEdges,
                             Size, deg, visited, num_of_threads, level);
#pragma omp single
                log_info("ET: %.9lfs", timer.elapsed());
            }

            // Peeling.
            auto local_g = useSmallQ == 0 ? g : &g_small;
            auto &core_val = useSmallQ == 0 ? deg : newDeg;
//            PeelVertex(local_g, core_val, level, visited);
            PeelSubLevel(local_g, core_val, level, visited, curr_queue, next_queue, curr_size, next_size);
#pragma omp barrier
            level = level + 1;
        }

        // Copy core values from newDeg to deg.
#pragma omp for schedule(static)
        for (long i = 0; i < Size; i++) {
            deg[mapIndexToVtx[i]] = newDeg[i];
        }
    }
    log_info("Before Frees");
    free(curr_queue);
    free(next_queue);

    free(newDeg);
    free(mapIndexToVtx);
    free(vertexToIndex);
    free_graph_pkc(&g_small);
}