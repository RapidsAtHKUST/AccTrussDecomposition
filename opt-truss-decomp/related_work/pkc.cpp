/* ********************************************************************************************
 * PKC: Parallel k-core Decomposition on Multicore Platforms
 * Authors: Humayun Kabir and Kamesh Madduri  {hzk134, madduri}@cse.psu.edu 
 * Description: A parallel k-core decomposition algorithm for multicore processor. It is designed 
 *              for large sparse graphs.     
 * 
 * Please cite the following paper, if you are using PKC: 
 *     H. Kabir and K. Madduri, "Parallel k-core Decomposition on Multicore Platforms," in The 2nd 
 *     IEEE Workshop on Parallel and Distributed Processing for Computational Social Systems 
 *     (ParSocial 2017), June 2017, to appear.
 * ********************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <stdint.h>
#include <limits.h>
#include <omp.h>

#include <sstream>

#include "../util/util.h"
#include "util/serialization/pretty_print.h"
#include "util/log/log.h"
#include "util/graph/graph.h"

//Make a small graph once 98% vertices have been processed
#define frac 0.98

using namespace std;

//Number of threads used
int NUM_THREADS = 1;

//typedef unsigned int vid_t;
typedef unsigned int eid_t;

void read_env() {

#pragma omp parallel
    {
#pragma omp master
        NUM_THREADS = omp_get_num_threads();
    }

    printf("NUM_PROCS:     %d \n", omp_get_num_procs());
    printf("NUM_THREADS:   %d \n", NUM_THREADS);
}


/************************************************************************************************/
/********************************   SERIAL k-core   *********************************************/
/************************************************************************************************/

//BZ-algorithm to compute k-core
void BZ_kCores(graph_t *g, int *deg) {
    long n = g->n;

    //Two arrays of size n
    unsigned int *vert = (unsigned int *) malloc(n * sizeof(unsigned int));
    assert(vert != NULL);

    unsigned int *pos = (unsigned int *) malloc(n * sizeof(unsigned int));
    assert(pos != NULL);

    //Maximum degree
    int maxDeg = 0;

    //deg[i] -- contains degree of vertex i
    for (long i = 0; i < n; i++) {
        deg[i] = g->num_edges[i + 1] - g->num_edges[i];

        if (deg[i] > maxDeg)
            maxDeg = deg[i];
    }

    //Used for bin-sort -- is of size maxDeg + 1
    unsigned int *bin = (unsigned int *) calloc(maxDeg + 1, sizeof(unsigned int));

    //Sort the vertices by increasing degree using bin-sort 
    //Count number of vertices with each degree in 0...maxDeg 
    for (long i = 0; i < n; i++)
        bin[deg[i]]++;

    unsigned int start = 0;
    for (int d = 0; d < maxDeg + 1; d++) {
        unsigned int num = bin[d];
        bin[d] = start;  //Start index of vertex in vert with degree d
        start = start + num;
    }

    //Do bin-sort of the vertices
    //vert -- contains the vertices in sorted order of degree 
    //pos -- contains the positon of a vertex in vert array
    for (long i = 0; i < n; i++) {
        pos[i] = bin[deg[i]];
        vert[pos[i]] = i;
        bin[deg[i]]++;
    }

    for (int d = maxDeg; d >= 1; d--)
        bin[d] = bin[d - 1];
    bin[0] = 0;

    //kcores computation
    for (long i = 0; i < n; i++) {
        //Process the vertices in increasing order of degree
        vid_t v = vert[i];
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
            vid_t u = g->adj[j];
            if (deg[u] > deg[v]) {

                //Swap u with the first vertex in bin[du]
                unsigned int du = deg[u];
                unsigned int pu = pos[u];
                unsigned int pw = bin[du];
                unsigned int w = vert[pw];

                if (u != static_cast<vid_t>(w)) {
                    pos[u] = pw;
                    vert[pu] = w;
                    pos[w] = pu;
                    vert[pw] = u;
                }

                //Increase the starting index of bin du
                bin[du]++;

                //Decrease degree of u -- so u is in previous bin now
                deg[u]--;
            }
        }
    }

    free(vert);
    free(pos);
}


void serial_scan(long n, int *deg, int level, vid_t *curr, long *currTail) {
    (*currTail) = 0;
    long i;
    for (i = 0; i < n; i++) {
        if (deg[i] == level) {
            curr[(*currTail)] = i;
            (*currTail)++;
        }
    }
}

void serial_processSubLevel(graph_t *g, vid_t *curr, long currTail,
                            int *deg, int level, vid_t *next, long *nextTail) {
    (*nextTail) = 0;
    for (long i = 0; i < currTail; i++) {
        vid_t v = curr[i];

        //Check the adj list of vertex v
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {

            vid_t u = g->adj[j];

            if (deg[u] > level) {
                deg[u] = deg[u] - 1;
                if (deg[u] == level) {
                    next[(*nextTail)] = u;
                    (*nextTail)++;
                }
            }
        }
    }
}


//Serial ParK to compute k-core decompsitions
void serial_ParK(graph_t *g, int *deg) {
    long n = g->n;

    vid_t *curr = (vid_t *) malloc(n * sizeof(vid_t));
    assert(curr != NULL);

    vid_t *next = (vid_t *) malloc(n * sizeof(vid_t));
    assert(next != NULL);

    vid_t *tempCurr;
    long todo = n;
    long currTail = 0, nextTail = 0;
    int level = 0;

    //deg[i] -- contains degree of vertex i
    for (long i = 0; i < n; i++) {
        deg[i] = g->num_edges[i + 1] - g->num_edges[i];
    }

    while (todo > 0) {

        serial_scan(n, deg, level, curr, &currTail);

        while (currTail > 0) {
            todo = todo - currTail;

            serial_processSubLevel(g, curr, currTail, deg, level, next, &nextTail);

            tempCurr = curr;
            curr = next;
            next = tempCurr;

            currTail = nextTail;
            nextTail = 0;
        }
        level = level + 1;
    }

    free(curr);
    free(next);
}

//Serial PKC_org for k-core decomposition
void serial_PKC_org(graph_t *g, int *deg) {
    long n = g->n;
    long visited = 0;

    int level = 0;

    vid_t *buff = (vid_t *) malloc(n * sizeof(vid_t));
    assert(buff != NULL);

    long start = 0, end = 0;
    for (long i = 0; i < n; i++) {
        deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
    }

    while (visited < n) {

        for (long i = 0; i < n; i++) {

            if (deg[i] == level) {
                buff[end] = i;
                end++;
            }
        }

        while (start < end) {

            vid_t v = buff[start];
            start++;

            //Check the adj list of vertex v
            for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                vid_t u = g->adj[j];

                if (deg[u] > level) {
                    deg[u] = deg[u] - 1;

                    if (deg[u] == level) {

                        buff[end] = u;
                        end++;
                    }

                }  //deg_u > level

            } //visit adjacencies
        }  //end of while loop

        visited = visited + end;

        start = 0;
        end = 0;
        level = level + 1;

    }   //end of #visited < n

    free(buff);
}


//serial_PKC -- Make a graph with remaining vertices
void serial_PKC(graph_t *g, int *deg) {
    long n = g->n;
    long reduceN = 0;
    long Size = 0;
    long visited = 0;

    int *newDeg = NULL;
    unsigned int *mapIndexToVtx = NULL;
    vid_t *vertexToIndex = (vid_t *) malloc(n * sizeof(vid_t));

    graph_t g_small;
    g_small.num_edges = NULL;
    g_small.adj = NULL;
    g_small.eid = NULL;

    int level = 0;

    vid_t *buff = (vid_t *) malloc(n * sizeof(vid_t));
    assert(buff != NULL);

    long start = 0, end = 0;
    int useSmallQ = 0;

    for (long i = 0; i < n; i++) {
        deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
    }

    while (visited < n) {

        if ((useSmallQ == 0) && (visited >= (long) (n * frac))) {

            useSmallQ = 1;
            reduceN = n - visited;
            newDeg = (int *) malloc(reduceN * sizeof(int));
            mapIndexToVtx = (unsigned int *) malloc(reduceN * sizeof(unsigned int));
            g_small.n = reduceN;
            g_small.num_edges = (eid_t *) malloc((reduceN + 1) * sizeof(eid_t));
            g_small.num_edges[0] = 0;

            for (long i = 0; i < n; i++) {
                if (deg[i] >= level) {
                    buff[end] = i;
                    end++;
                }
            }

            Size = end;

            for (long i = 0; i < end; i++) {
                newDeg[i] = deg[buff[i]];
                mapIndexToVtx[i] = buff[i];
                vertexToIndex[buff[i]] = i;
            }

            end = 0;

            //Make a graph with reduceN vertices
            unsigned int edgeCount = 0;

            for (long i = 0; i < Size; i++) {
                unsigned int v = mapIndexToVtx[i];
                unsigned int prevEdgeCount = edgeCount;
                for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                    if (deg[g->adj[j]] >= level) {
                        edgeCount++;
                    }
                }
                g_small.num_edges[i] = prevEdgeCount;
            }
            g_small.m = edgeCount;
            g_small.num_edges[Size] = edgeCount;

            g_small.adj = (vid_t *) malloc(g_small.m * sizeof(vid_t));
            assert(g_small.adj != NULL);

            for (long i = 0; i < Size; i++) {

                unsigned int v = mapIndexToVtx[i];
                for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                    if (deg[g->adj[j]] >= level) {
                        g_small.adj[g_small.num_edges[i]] = vertexToIndex[g->adj[j]];
                        g_small.num_edges[i]++;
                    }
                }
            }


            for (long i = Size; i >= 1; i--) {
                g_small.num_edges[i] = g_small.num_edges[i - 1];
            }
            g_small.num_edges[0] = 0;

        }


        if (useSmallQ == 0) {

            for (long i = 0; i < n; i++) {
                if (deg[i] == level) {
                    buff[end] = i;
                    end++;
                }
            }

            //Get work from curr queue and also add work after the current size
            while (start < end) {

                vid_t v = buff[start];
                start++;

                for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                    vid_t u = g->adj[j];

                    int deg_u = deg[u];

                    if (deg_u > level) {
                        deg[u] = deg[u] - 1;

                        if (deg[u] == level) {
                            buff[end] = u;
                            end++;
                        }
                    }  //deg_u > level

                } //visit adjacencies
            }  //end of while loop
        } else {
            for (long i = 0; i < Size; i++) {
                if (newDeg[i] == level) {
                    buff[end] = i;
                    end++;
                }
            }

            //Get work from curr queue and also add work after the current size
            while (start < end) {

                vid_t v = buff[start];
                start++;

                for (eid_t j = g_small.num_edges[v]; j < g_small.num_edges[v + 1]; j++) {
                    vid_t u = g_small.adj[j];

                    int deg_u = newDeg[u];

                    if (deg_u > level) {
                        newDeg[u] = newDeg[u] - 1;

                        if (newDeg[u] == level) {
                            buff[end] = u;
                            end++;
                        }

                    }  //deg_u > level
                } //visit adjacencies
            }  //end of while loop
        }

        visited = visited + end;

        start = 0;
        end = 0;
        level = level + 1;

    }   //end of #visited < n

    free(buff);

    //copy core values from newDeg to deg
    for (long i = 0; i < Size; i++) {
        deg[mapIndexToVtx[i]] = newDeg[i];
    }

    free(newDeg);
    free(mapIndexToVtx);
    free(vertexToIndex);
    free_graph(&g_small);
}


/************************************************************************************************/
/********************************   PARALLEL k-core  ********************************************/
/************************************************************************************************/

void scan(long n, int *deg, int level,
          vid_t *curr, long *currTailPtr) {

    // Size of cache line
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    vid_t buff[BUFFER_SIZE];
    long index = 0;

#pragma omp for schedule(static)
    for (long i = 0; i < n; i++) {

        if (deg[i] == level) {

            buff[index] = i;
            index++;

            if (index >= BUFFER_SIZE) {
                long tempIdx = __sync_fetch_and_add(currTailPtr, BUFFER_SIZE);

                for (long j = 0; j < BUFFER_SIZE; j++) {
                    curr[tempIdx + j] = buff[j];
                }
                index = 0;
            }
        }

    }

    if (index > 0) {
        long tempIdx = __sync_fetch_and_add(currTailPtr, index);

        for (long j = 0; j < index; j++)
            curr[tempIdx + j] = buff[j];
    }

#pragma omp barrier

}


void processSubLevel(graph_t *g, vid_t *curr, long currTail,
                     int *deg, int level, vid_t *next, long *nextTailPtr) {

    // Size of cache line
    const long BUFFER_SIZE_BYTES = 2048;
    const long BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);

    vid_t buff[BUFFER_SIZE];
    long index = 0;

#pragma omp for schedule(static)
    for (long i = 0; i < currTail; i++) {
        vid_t v = curr[i];

        //Check the adj list of vertex v
        for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {

            vid_t u = g->adj[j];
            int deg_u = deg[u];

            if (deg_u > level) {

                int du = __sync_fetch_and_sub(&deg[u], 1);

                if (du == (level + 1)) {
                    buff[index] = u;
                    index++;

                    if (index >= BUFFER_SIZE) {
                        long tempIdx = __sync_fetch_and_add(nextTailPtr, BUFFER_SIZE);

                        for (long bufIdx = 0; bufIdx < BUFFER_SIZE; bufIdx++)
                            next[tempIdx + bufIdx] = buff[bufIdx];
                        index = 0;
                    }
                }
            }
        }
    }

    if (index > 0) {
        long tempIdx = __sync_fetch_and_add(nextTailPtr, index);;
        for (long bufIdx = 0; bufIdx < index; bufIdx++)
            next[tempIdx + bufIdx] = buff[bufIdx];
    }

#pragma omp barrier

#pragma omp for schedule(static)
    for (long i = 0; i < *nextTailPtr; i++) {
        vid_t u = next[i];
        if (deg[u] != level)
            deg[u] = level;
    }


#pragma omp barrier

}


//ParK to compute k core decompsitions in parallel
void ParK(graph_t *g, int *deg) {

    long n = g->n;

    vid_t *curr = (vid_t *) malloc(n * sizeof(vid_t));
    assert(curr != NULL);

    vid_t *next = (vid_t *) malloc(n * sizeof(vid_t));
    assert(next != NULL);

    long currTail = 0;
    long nextTail = 0;

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        long todo = n;
        int level = 0;

#pragma omp for schedule(static)
        for (long i = 0; i < n; i++) {
            deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
        }

        while (todo > 0) {

            scan(n, deg, level, curr, &currTail);

            while (currTail > 0) {
                todo = todo - currTail;

                processSubLevel(g, curr, currTail, deg, level, next, &nextTail);

                if (tid == 0) {
                    vid_t *tempCurr = curr;
                    curr = next;
                    next = tempCurr;

                    currTail = nextTail;
                    nextTail = 0;
                }

#pragma omp barrier

            }

            level = level + 1;

#pragma omp barrier

        }
    }

    free(curr);
    free(next);

}

//Each thread has its own queue -- parallel PKC_org for k-core decomposition
void PKC_org(graph_t *g, int *deg) {
    long n = g->n;
    long visited = 0;

#pragma omp parallel
    {
        int level = 0;

        vid_t *buff = (vid_t *) malloc((n * sizeof(vid_t)) / NUM_THREADS);
        assert(buff != NULL);

        long start = 0, end = 0;

#pragma omp for schedule(static)
        for (long i = 0; i < n; i++) {
            deg[i] = (g->num_edges[i + 1] - g->num_edges[i]);
        }

        while (visited < n) {

#pragma omp for schedule(static)
            for (long i = 0; i < n; i++) {

                if (deg[i] == level) {
                    buff[end] = i;
                    end++;
                }
            }

            //Get work from curr queue and also add work after the current size
            while (start < end) {

                vid_t v = buff[start];
                start++;

                for (eid_t j = g->num_edges[v]; j < g->num_edges[v + 1]; j++) {
                    vid_t u = g->adj[j];

                    int deg_u = deg[u];

                    if (deg_u > level) {
                        int du = __sync_fetch_and_sub(&deg[u], 1);

                        if (du == (level + 1)) {
                            buff[end] = u;
                            end++;
                        }

                        if (du <= level) {
                            __sync_fetch_and_add(&deg[u], 1);
                        }
                    }  //deg_u > level

                } //visit adjacencies
            }  //end of while loop

            __sync_fetch_and_add(&visited, end);

#pragma omp barrier
            start = 0;
            end = 0;
            level = level + 1;

        }   //end of #visited < n

        free(buff);

    }  //#end of parallel region

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
    free_graph(&g_small);
}

//MPM algorithm for k-core decomposition
#define AVOID_SCHEDNEXT 0

int KcoreMPM_async(graph_t *g, int *core) {

    long n = g->n;

    int max_degree = 0;

#pragma omp parallel
    {
        int max_degree_l = 0;


#pragma omp for
        for (long i = 0; i < n; i++) {
            core[i] = (g->num_edges[i + 1] - g->num_edges[i]);
            if (core[i] > max_degree_l) {
                max_degree_l = core[i];
            }
        }

#pragma omp critical
        if (max_degree_l > max_degree) {
            max_degree = max_degree_l;
        }
    }

    uint8_t *scheduled = (uint8_t *) malloc(n * sizeof(uint8_t));
    assert(scheduled != NULL);

#if !AVOID_SCHEDNEXT
    uint8_t *scheduled_next = (uint8_t *) malloc(n * sizeof(uint8_t));
    assert(scheduled_next != NULL);
#endif

#pragma omp parallel for schedule(static)
    for (long i = 0; i < n; i++) {
        scheduled[i] = 1;
#if !AVOID_SCHEDNEXT
        scheduled_next[i] = 0;
#endif
    }

    int num_changed = n;
    int iter = 0;
#pragma omp parallel
    {
        int tid = omp_get_thread_num();

        int *neigh_counts = (int *) malloc((max_degree + 1) * sizeof(int));
        assert(neigh_counts != NULL);

        while (num_changed > 0) {
#pragma omp barrier

#pragma omp master
            num_changed = 0;

#pragma omp barrier

#pragma omp for reduction(+:num_changed)
            for (vid_t i = 0; i < n; i++) {

                if (scheduled[i] == 1) {

#if !AVOID_SCHEDNEXT
                    scheduled[i] = 0;
#endif


                    //compute local_est
                    int core_i = core[i];

                    int local_est = 0;
                    for (int k = 1; k <= core_i; k++) {
                        neigh_counts[k] = 0;
                    }

                    for (eid_t j = g->num_edges[i];
                         j < g->num_edges[i + 1]; j++) {
                        vid_t v = g->adj[j];
                        int mincval = core_i;
                        if (core[v] < core_i) {
                            mincval = core[v];
                        }
                        neigh_counts[mincval]++;
                    }

                    eid_t cumul = 0;
                    for (eid_t k = core_i; k >= 1; k--) {
                        cumul += neigh_counts[k];
                        if (cumul >= k) {
                            local_est = k;
                            break;
                        }
                    }

                    if (local_est < core_i) {

                        core[i] = local_est;

                        num_changed++;

                        for (eid_t j = g->num_edges[i];
                             j < g->num_edges[i + 1];
                             j++) {
                            vid_t v = g->adj[j];
                            if (local_est <= core[v]) {

#if AVOID_SCHEDNEXT
                                scheduled[v] = 1;
#else
                                scheduled_next[v] = 1;
#endif
                            }
                        }

                    }
                }
            }

            // swap core and core_next, scheduled and scheduled_next
            if (tid == 0) {
                iter++;

#if !AVOID_SCHEDNEXT
                uint8_t *tmp_arr_sch = scheduled;
                scheduled = scheduled_next;
                scheduled_next = tmp_arr_sch;
#endif
            }

#pragma omp barrier
        }

        free(neigh_counts);
    }

    free(scheduled);
#if !AVOID_SCHEDNEXT
    free(scheduled_next);
#endif
    return 0;
}

void core_val_histogram(graph_t &g, const int *core) {
    // core-value histogram
    int max_core_val = 0;
    vector<int32_t> histogram;
#pragma omp parallel
    {
#pragma omp for reduction(max:max_core_val)
        for (auto u = 0; u < g.n; u++) {
            max_core_val = max(max_core_val, core[u]);
        }
#pragma omp single
        {
            log_info("max core: %d", max_core_val);
            histogram = vector<int32_t>(max_core_val + 1, 0);
        }
#pragma omp for
        for (auto u = 0; u < g.n; u++) {
            auto core_val = core[u];
#pragma omp atomic
            histogram[core_val]++;
        }
    }
    {
        stringstream ss;
        ss << histogram;
        log_info("core values histogram: %s", ss.str().c_str());
    }
}

/****************************** main function **********************************************************/
int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "%s <Graph file>\n", argv[0]);
        exit(1);
    }

    read_env();

    graph_t g;
    Graph yche_graph(argv[1]);
    g.adj = yche_graph.edge_dst;
    g.num_edges = yche_graph.node_off;
    g.n = yche_graph.nodemax;
    g.m = yche_graph.edgemax;
//    load_graph_from_file(argv[1], &g);
    long n = g.n;

    //set log file descriptor
#ifdef USE_LOG
    FILE *log_f;
    log_f = fopen(argv[2], "a+");
    log_set_fp(log_f);
#endif

    /* Contains the core number for each vertex */
    int *core = (int *) malloc(n * sizeof(int));
    assert(core != NULL);

    fprintf(stderr, "Computing k-core decomposition ... \n");

    double start_time = 0;

    /* Serial Algorithms */
#ifdef TEST_SEQ
    printf("Test the serial algorithms: \n");

    start_time = timer();
    BZ_kCores(&g, core);
    core_val_histogram(g, core);
    fprintf(stderr, "BZ time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");

    start_time = timer();
    serial_ParK(&g, core);
    core_val_histogram(g, core);
    fprintf(stderr, "Serial ParK time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");

    start_time = timer();
    serial_PKC_org(&g, core);
    core_val_histogram(g, core);
    fprintf(stderr, "Serial PKC-org time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");


    start_time = timer();
    serial_PKC(&g, core);
    core_val_histogram(g, core);
    fprintf(stderr, "Serial PKC time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");

    /* Parallel Algorithms */
    printf("Test Parallel Algorithms \n");

    start_time = timer();
    ParK(&g, core);
    core_val_histogram(g, core);

    fprintf(stderr, "ParK time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");

    start_time = timer();
    KcoreMPM_async(&g, core);
    fprintf(stderr, "MPM time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");

    start_time = timer();
    PKC_org(&g, core);
    fprintf(stderr, "PKC-org time: %9.3lf sec\n", timer() - start_time);
    fprintf(stderr, "done.\n");
#endif

    /* If the graph has atlest 1000 vertices use PKC  */
    if (n > 1000) {
        start_time = timer();
        PKC(&g, core, NUM_THREADS);
        core_val_histogram(g, core);
        fprintf(stderr, "PKC time: %9.3lf sec\n", timer() - start_time);
        fprintf(stderr, "done.\n");


    } else {
        {
            PKC_org(&g, core);

            stringstream ss;
            ss << pretty_print_array(core, g.n);
            log_info("core values: %s", ss.str().c_str());
        }
    }

/*******************************************************************************************/
    free(core);
//    free_graph(&g);

    return 0;
}

