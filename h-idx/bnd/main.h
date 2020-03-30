#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <string>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <vector>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <random>
#include <sys/stat.h>

#include "bucket.h"
#include "util/log/log.h"
#include "util/timer.h"
#include "util/util.h"

using namespace std;

template<typename VtxType>
void CheckSorted(vector<vector<VtxType>> &graph) {
    // CheckSorted.
    for (const auto &u_neis: graph) {
        auto v = -1;
        for (auto nei: u_neis) {
            if (v >= nei) {
                log_fatal("Not Sorted");
                exit(-1);
                return;
            }
            v = nei;
        }
    }
}

//#define K_VALUES // prints the K values in *_K_VALUES file
//#define EXPS // for the projection experiments
#define THRESHOLD 0.0 // subgraph density threshold
#define VERTEXUPPERBOUND 200 // for TIP variants, compute densities of subgraphs with at most this size, set to INT_MAX to compute all -- takes a lot of time
#define EDGEUPPERBOUND 3000 // for WING, compute densities of subgraphs with at most this size, set to INT_MAX to compute all -- takes a lot of time
#define LOWERBOUND 0 // show subgraphs with at least this size
#define PRIME 251231 // for hash function

typedef int vertex; //vertices are 4 bytes
typedef int edge; //edges are 4 bytes
typedef long long lol;
typedef chrono::duration<double> tms;
typedef unordered_multimap<int, int> mulmap;
typedef pair<vertex, vertex> vp;
typedef vector<vector<vertex> > Graph;
struct wv {
    int n;
    double w;
};
typedef vector<vector<wv>> Wraph;
typedef pair<int, int> llp;

namespace std {
    template<typename T>
    struct hash<pair<T, T >> {
        size_t operator()(const pair<T, T> &p) const { // hash function for a node pair
            unsigned int combined_int;
            // symmetric pairing, we can assume p.second >= p.first
            // combined_int = p.second*(p.second+1)/2 + p.first;

            // elegant pair function
            if (p.first >= p.second) {
                combined_int = p.first * p.first + p.first + p.second;
            } else {
                combined_int = p.second * p.second + p.first;
            }
            auto hash_value = std::hash<unsigned int>{}(combined_int);
            return hash_value;
        }
    };
}

struct subcore {
    bool visible;
    vertex rank;
    vertex K;
    int parent;
    int root;
    vector<int> children;
    vertex primarySize;
    vertex secondarySize;
    edge nEdge;
    double ed;

    subcore(vertex k) {
        K = k;
        rank = 0;
        parent = -1;
        root = -1;
        visible = true;
    }
};

struct helpers {
    helpers(vector<vp> *ael) {
        el = ael;
    }

    helpers() {}

    vector<vp> *el;
};

template<class T>
inline void hash_combine(std::size_t &seed, const T &v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    template<typename S, typename T>
    struct hash<pair<S, T>> {
        inline size_t operator()(const pair<S, T> &v) const {
            size_t seed = 0;
            ::hash_combine(seed, v.first);
            ::hash_combine(seed, v.second);
            return seed;
        }
    };
}

inline bool less_than(vertex u, vertex v, Graph &graph) {
    return (graph[u].size() < graph[v].size() || (graph[u].size() == graph[v].size() && u < v));
}

inline void print_time(FILE *fp, const string &str, tms t) {
    fprintf(fp, "%s %.6lf\n", str.c_str(), t.count());
    fflush(fp);
}

inline vertex find_ind(vector<vertex> &rg, vertex g) {
    for (vertex i = 0; i < rg.size(); i++)
        if (rg[i] == g)
            return i;
    printf("couldn't find\n");
    exit(1);
}

Graph ConstructGeneralGraph(Graph &leftGraph, Graph &rightGraph);

inline void prefixSum(vector<vertex> &xRight, Graph &rightGraph, vector<vp> &el) {
    vertex sum = 0;
    xRight.push_back(sum);
    for (vertex u = 0; u < rightGraph.size(); u++) {
        for (vertex v = 0; v < rightGraph[u].size(); v++) {
            vp p(u, rightGraph[u][v]);
            el.push_back(p);
        }
        sum += rightGraph[u].size();
        xRight.push_back(sum);
    }
}

inline bool hashUniquify(vector<vertex> &ch, bool fl = true, string variant = "NONE") {
    unordered_map<vertex, bool> hermap;
    for (size_t i = 0; i < ch.size(); i++) {
        int t = ch[i];
        if (hermap.find(t) == hermap.end()) {
            hermap[t] = true;
        } else {
            ch.erase(ch.begin() + i);
            i--;
        }
        if (fl &&
            ((variant == "WING" && i > EDGEUPPERBOUND) ||
             (variant == "TIP" && i > VERTEXUPPERBOUND) ||
             (variant == "CORE" && i > VERTEXUPPERBOUND) ||
             (variant == "TRUSS" && i > VERTEXUPPERBOUND)))
            return false;
    }

    if (fl)
        sort(ch.begin(), ch.end());
    return true;
}

inline void findRepresentative(vertex *child, vector<subcore> &skeleton) {
    vertex u = *child;
    if (skeleton[u].parent != -1) {
        vertex pr = skeleton[u].parent;
        while (skeleton[u].K == skeleton[pr].K) {

            u = pr;
            if (skeleton[u].parent != -1)
                pr = skeleton[u].parent;
            else
                break;
        }
    }
    *child = u;
}

inline void neighborsOfNeighbors(vector<vertex> &vset, Graph &graph, vector<vertex> &allNeighbors, edge *nEdge) {
    for (vertex i = 0; i < vset.size(); i++) {
        vertex u = vset[i];
        allNeighbors.insert(allNeighbors.end(), graph[u].begin(), graph[u].end());
        *nEdge += graph[u].size();
    }
    hashUniquify(allNeighbors);
}

inline void intersection(vector<vertex> &a, vector<vertex> &b, vector<vertex> &c) {
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])
            i++;
        else if (b[j] < a[i])
            j++;
        else {
            c.push_back(a[i]);
            i++;
            j++;
        }
    }
}

inline void ff_vertex_ind_density(string file, Graph &graph) {
    FILE *fp = fopen(file.c_str(), "r");
    string temp = file + "_temp";
    FILE *tp = fopen(temp.c_str(), "w");
    int t;
    int ln = 0;
    double db;

    while (1) {
        fscanf(fp, "%d %d %d %d %d %lf %d %d", &t, &t, &t, &t, &t, &db, &t, &t);
        vector<int> vs;
        bool exit_flag = false;
        while (1) {
            if (fscanf(fp, "%d", &t) == EOF)
                exit_flag = true;
            if (t == -1)
                break;
            vs.push_back(t);
        }
        if (exit_flag)
            break;
        vector<vertex> neigsOfvs;
        int nedge = 0;
        neighborsOfNeighbors(vs, graph, neigsOfvs, &nedge);
        fprintf(tp, " %d %d %d %lf\n", vs.size(), neigsOfvs.size(), nedge,
                vs.size() == 0 ? -1.0 : ((double) nedge / (vs.size() * neigsOfvs.size())));
    }

    fclose(fp);
    fclose(tp);
    string paste = "paste " + file + " " + temp + " > " + file + temp;
    system(paste.c_str());
    string mv = "mv " + file + temp + " " + file;
    system(mv.c_str());
    string rm = "rm " + temp;
    system(rm.c_str());
}

inline bool incrementTCIfConnected(Graph &graph, Graph &orientedGraph, Graph &TC, vertex u, vertex v) {
    vertex a = u, b = v;
    if (less_than(b, a, graph))
        swap(a, b);
    for (size_t k = 0; k < orientedGraph[a].size(); k++)
        if (orientedGraph[a][k] == b) {
            TC[a][k]++;
            return true;
        }
    return false;
}

inline void indexEdges(Graph &graph, vector<vp> &el, vector<vertex> &xel, Graph &orientedGraph) {
    xel.push_back(0);
    orientedGraph.resize(graph.size());
    for (size_t u = 0; u < graph.size(); u++) {
        for (size_t j = 0; j < graph[u].size(); j++) {
            vertex v = graph[u][j];
            if (less_than(u, v, graph)) {
                orientedGraph[u].push_back(v);
                vp c(u, v);
                el.push_back(c);
            }
        }
        xel.push_back(el.size());
    }
}

inline vertex getEdgeId(vertex u, vertex v, vector<vertex> &xel, vector<vp> &el, Graph &graph) {

    vertex a = u, b = v;
    if (less_than(b, a, graph))
        swap(a, b);

    for (vertex i = xel[a]; i < xel[a + 1]; i++)
        if (el[i].second == b)
            return i;

    printf("getEdgeId returns -1\n");
    exit(1);
}

template<typename VtxType, typename EdgeType>
void
readBipartite(char *filename, EdgeType *nEdge, vector<vector<VtxType>> &leftGraph, vector<vector<VtxType>> &rightGraph);

void readWeightedBinary(char *filename, Wraph &wraph, edge *nEdge);

void writeRegularBinary(string filename, vertex nVtx, edge nEdge, Graph &graph);

void writeWeightedRegularBinary(string filename, vertex nVtx, edge nEdge, Wraph &wraph);

void
tipDecomposition(Graph &leftGraph, Graph &rightGraph, edge nEdge, vector<vertex> &K, bool hierarchy, lol *maxbicore,
                 string vfile, FILE *fp, lol *bCount);

void
wingDecomposition(Graph &leftGraph, Graph &rightGraph, edge nEdge, vector<vertex> &K, bool hierarchy, lol *maxbicore,
                  FILE *fp, lol *bCount);

void
wingDecompositionHrc(Graph &leftGraph, Graph &rightGraph, edge nEdge, vector<vertex> &K, bool hierarchy, lol *maxbicore,
                     string vfile, FILE *fp, lol *bCount);

void createSkeleton(vertex u, initializer_list<vertex> neighbors, vertex *nSubcores, vector<vertex> &K,
                    vector<subcore> &skeleton, vector<int> &component, vector<int> &unassigned, vector<llp> &relations);

void updateUnassigned(vertex t, vector<int> &component, int *cid, vector<llp> &relations, vector<int> &unassigned);

void buildHierarchy(vertex cn, vector<llp> &relations, vector<subcore> &skeleton, int *nSubcores, edge nEdge,
                    vertex rightnVtx, vertex leftnVtx = -1);

void presentNuclei(string variant, vector<subcore> &skeleton, vector<vertex> &component, edge nEdge, helpers &ax,
                   string vfile, Graph &leftGraph, Graph &rightGraph, vector<vertex> *xRight, FILE *fp);

void weighted_projection(Graph &left, Graph &right, string filename);

void base_kcore(Graph &graph, bool hierarchy, edge nEdge, vector<vertex> &K, lol *maxCore, string vfile, FILE *fp);

void
weighted_base_kcore(Wraph &wraph, bool hierarchy, edge nEdge, vector<vertex> &K, lol *maxCore, string vfile, FILE *fp);

void base_ktruss(Graph &graph, bool hierarchy, edge nEdge, vector<vertex> &K, lol *maxtruss, string vfile, FILE *fp);
