#include <cassert>

#include <omp.h>

#include <util/log/log.h>
#include <util/timer.h>

#include "reorder_utils.h"

#define frac 0.98

void free_graph_pkc(graph_t *g) {
    if (g->adj != nullptr)
        free(g->adj);

    if (g->num_edges != nullptr)
        free(g->num_edges);
}

//PKC -- Make a graph with remaining vertices, parallel k-core decomposition
void PKC(graph_t *g, int *deg, int num_of_threads) {
    long n = g->n;
    long reduceN = 0;
    long Size = 0;
    long visited = 0;

    int *newDeg = nullptr;
    unsigned int *mapIndexToVtx = nullptr;
    auto *vertexToIndex = (vid_t *) malloc(n * sizeof(vid_t));
    unsigned int cumNumEdges[num_of_threads];
    unsigned int part = 0;

    graph_t g_small;
    g_small.num_edges = nullptr;
    g_small.adj = nullptr;

#pragma omp parallel num_threads(num_of_threads)
    {
        int level = 0;
        int tid = omp_get_thread_num();

        vector<vid_t> buffer;
        size_t start = 0;
        int useSmallQ = 0;

#pragma omp for schedule(static)
        for (long i = 0; i < n; i++) {
            deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
        }

        while (visited < n) {

            if ((useSmallQ == 0) && (visited >= (long) (n * frac))) {
                Timer timer;
                useSmallQ = 1;
                if (tid == 0) {
                    reduceN = n - visited;
                    newDeg = (int *) malloc(reduceN * sizeof(int));
                    mapIndexToVtx = (unsigned int *) malloc(reduceN * sizeof(unsigned int));
                    g_small.n = reduceN;
                    g_small.num_edges = (eid_t *) malloc((reduceN + 1) * sizeof(eid_t));
                    g_small.num_edges[0] = 0;

                    part = reduceN / num_of_threads;
                }
#pragma omp barrier

#pragma omp for schedule(static)
                for (long i = 0; i < n; i++) {
                    if (deg[i] >= level) {
                        buffer.push_back(i);
                    }
                }

                //Now add them atomically
                long begin = __sync_fetch_and_add(&Size, buffer.size());

                for (size_t i = 0; i < buffer.size(); i++) {
                    newDeg[begin + i] = deg[buffer[i]];
                    mapIndexToVtx[begin + i] = buffer[i];
                    vertexToIndex[buffer[i]] = begin + i;
                }

                buffer.clear();
#pragma omp barrier

                //Make a graph with reduceN vertices
                unsigned int edgeCount = 0;

                if (tid == num_of_threads - 1) {
                    for (long i = tid * part; i < Size; i++) {
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
                } else {

                    for (long i = tid * part; i < (tid + 1) * part; i++) {
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
                }

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
                if (tid == num_of_threads - 1) {

                    for (long i = tid * part; i < Size; i++) {
                        g_small.num_edges[i] = g_small.num_edges[i] + cumNumEdges[tid];

                        unsigned int v = mapIndexToVtx[i];
                        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                            if (deg[g->adj[j]] >= level) {
                                g_small.adj[g_small.num_edges[i]] = vertexToIndex[g->adj[j]];
                                g_small.num_edges[i]++;
                            }
                        }
                    }
                } else {
                    for (long i = tid * part; i < (tid + 1) * part; i++) {
                        g_small.num_edges[i] = g_small.num_edges[i] + cumNumEdges[tid];

                        unsigned int v = mapIndexToVtx[i];
                        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                            if (deg[g->adj[j]] >= level) {
                                g_small.adj[g_small.num_edges[i]] = vertexToIndex[g->adj[j]];
                                g_small.num_edges[i]++;
                            }
                        }
                    }
                }
#pragma omp barrier
                //Now fix num_edges array
                if (tid == num_of_threads - 1) {

                    for (long i = Size - 1; i >= tid * part + 1; i--) {
                        g_small.num_edges[i] = g_small.num_edges[i - 1];
                    }
                    g_small.num_edges[tid * part] = cumNumEdges[tid];

                } else {

                    for (long i = (tid + 1) * part - 1; i >= tid * part + 1; i--) {
                        g_small.num_edges[i] = g_small.num_edges[i - 1];
                    }
                    g_small.num_edges[tid * part] = cumNumEdges[tid];
                }
#pragma omp barrier
#pragma omp single
                log_info("Shrink Time: %.9lfs", timer.elapsed());
            }


            if (useSmallQ == 0) {

#pragma omp for schedule(static)
                for (long i = 0; i < n; i++) {
                    if (deg[i] == level) {
                        buffer.push_back(i);
                    }
                }

                //Get work from curr queue and also add work after the current size
                while (start < buffer.size()) {
                    vid_t v = buffer[start];
                    start++;

                    for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                        vid_t u = g->adj[j];

                        int deg_u = deg[u];

                        if (deg_u > level) {
                            int du = __sync_fetch_and_sub(&deg[u], 1);

                            if (du == (level + 1)) {
                                buffer.push_back(u);
                            }

                            if (du <= level) {
                                __sync_fetch_and_add(&deg[u], 1);
                            }
                        }  //deg_u > level

                    } //visit adjacencies
                }  //end of while loop
            } else {

#pragma omp for schedule(static)
                for (long i = 0; i < Size; i++) {
                    if (newDeg[i] == level) {
                        buffer.push_back(i);
                    }
                }

                //Get work from curr queue and also add work after the current size
                while (start < buffer.size()) {

                    vid_t v = buffer[start];
                    start++;

                    for (eid_t j = g_small.num_edges[v]; j < g_small.num_edges[v + 1]; j++) {
                        vid_t u = g_small.adj[j];

                        int deg_u = newDeg[u];

                        if (deg_u > level) {
                            int du = __sync_fetch_and_sub(&newDeg[u], 1);

                            if (du == (level + 1)) {
                                buffer.push_back(u);
                            }

                            if (du <= level) {
                                __sync_fetch_and_add(&newDeg[u], 1);
                            }
                        }  //deg_u > level
                    } //visit adjacencies
                }  //end of while loop
            }

            __sync_fetch_and_add(&visited, buffer.size());

#pragma omp barrier
            start = 0;
            buffer.clear();
            level = level + 1;

        }   //end of #visited < n

        //copy core values from newDeg to deg
#pragma omp for schedule(static)
        for (long i = 0; i < Size; i++) {
            deg[mapIndexToVtx[i]] = newDeg[i];
        }

    }  //#end of parallel region


    free(newDeg);
    free(mapIndexToVtx);
    free(vertexToIndex);
    free_graph_pkc(&g_small);
}