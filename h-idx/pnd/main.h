#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <random>
#include <chrono>
#include <tuple>
#include <fstream>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <omp.h>

#include <util/log/log.h>
#include <util/serialization/pretty_print.h>
#include <util/util.h>
#include <util/md5.h>

#include "bucket.h"

//#define DUMP_Hs
//#define DUMP_K

#define PRIME 251231
using namespace std;
#define TEST_SIZE 100 // for partialAND exps

typedef long long lol;
typedef int vertex;
typedef uint32_t edge;
//typedef lol vertex; // for big graph runs, vertices are 32 bytes
//typedef lol edge; // for big graph runs, edges are 32 bytes

typedef chrono::duration<double> tms;
typedef tuple<vertex, vertex> couple;
typedef tuple<vertex, vertex, vertex> triple;

struct triangle_id {
    tuple<vertex, vertex, vertex> triple;
    vertex id;

    bool operator==(const triangle_id &other) const {
        if (triple == other.triple)
            return 1;
        else {
            return 0;
        }
    }

    triangle_id() {
        triple = make_tuple(-1, -1, -1);
        id = -1;
    }

};

namespace std {

    template<>
    struct hash<triangle_id> {
        std::size_t operator()(const triangle_id &t) const {
            return (get<0>(t.triple) * PRIME * PRIME + get<1>(t.triple)) * PRIME + get<2>(t.triple);
        }
    };

    template<>
    struct hash<couple> {
        std::size_t operator()(const couple &c) const {
            return (get<0>(c) * PRIME + get<1>(c));
        }
    };

    template<>
    struct hash<triple> {
        std::size_t operator()(const triple &c) const {
            return (get<0>(c) * PRIME * PRIME + get<1>(c) * PRIME + get<2>(c));
        }
    };

}

typedef vector<vector<vertex> > Graph;

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

inline vertex findInd(vertex a, vertex i, vertex *ordered_adj, edge *ordered_xadj) {
    for (vertex j = ordered_xadj[a]; j < ordered_xadj[a + 1]; j++)
        if (ordered_adj[j] == i)
            return j;
    return -1;
}

inline bool isSmaller(edge *xadj, vertex u, vertex v) {
    vertex deg_u = xadj[u + 1] - xadj[u];
    vertex deg_v = xadj[v + 1] - xadj[v];
    return (deg_u < deg_v || (deg_u == deg_v && u < v));
}

typedef tuple<int, int> eda;

inline bool kksort(eda i, eda j) { return (get<1>(i) > get<1>(j)); }

inline void print_Ks(edge nVtx, vertex *T, const char *vfile, int H = -1) {
    string st(vfile);
    if (H == -1)
        st += "_FINAL_K";
    else
        st += "_H_" + to_string(H);
    FILE *pp = fopen(st.c_str(), "w");
    for (edge i = 0; i < nVtx; i++)
        fprintf(pp, "%d\n", T[i]);
    fclose(pp);
}

inline void read_Ks(size_t sz, const char *fl, vertex **P) {
    string st(fl);
    *P = (vertex *) malloc(sizeof(vertex) * sz);
    FILE *fp = fopen(st.c_str(), "r");
    vertex num;
    for (size_t i = 0; i < sz; i++) {
        fscanf(fp, "%d", &num);
        if (num == -1)
            (*P)[i] = 0;
        else
            (*P)[i] = num;
    }
    fclose(fp);
}

inline void intersection2(vertex *adj, edge *xadj, vertex u, vertex v, vector<vertex> &intersection) {
    vertex i = xadj[u];
    vertex j = xadj[v];
    vertex gu = xadj[u + 1];
    vertex gv = xadj[v + 1];

    while (i < gu && j < gv) {
        if (adj[i] < adj[j])
            i++;
        else if (adj[j] < adj[i])
            j++;
        else {
            intersection.push_back(adj[i]);
            i++;
            j++;
        }
    }
}

inline void intersection3(vertex *adj, edge *xadj, vertex u, vertex v, vertex w, vector<vertex> &intersection) {
    vertex i = xadj[u];
    vertex j = xadj[v];
    vertex k = xadj[w];
    vertex gu = xadj[u + 1];
    vertex gv = xadj[v + 1];
    vertex gw = xadj[w + 1];
    while (i < gu && j < gv && k < gw) {
        vertex a = adj[i];
        vertex b = adj[j];
        vertex c = adj[k];
        if (a == b && a == c) {
            intersection.push_back(a);
            i++;
            j++;
            k++;
        } else {
            vertex m = max(a, max(b, c));
            if (a != m)
                i++;
            if (b != m)
                j++;
            if (c != m)
                k++;
        }
    }
}

inline void createOrdered(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, couple *el, edge *xel, vertex *ordered_adj,
                          edge *ordered_xadj) {
    edge xi = 0;
    vertex i = 0;
    xel[xi++] = 0;
    edge oxi = 0;
    vertex oi = 0;
    ordered_xadj[oxi++] = 0;
    for (vertex u = 0; u < nVtx; u++) {
        for (auto j = xadj[u]; j < xadj[u + 1]; j++) {
            vertex v = adj[j];
            if (isSmaller(xadj, u, v)) {
                ordered_adj[oi++] = v;
                couple c = make_tuple(u, v);
                el[i++] = c;
            }
        }
        ordered_xadj[oxi++] = oi;
        xel[xi++] = i;
    }
}


template<typename T>
void printMaxTruss(int nEdge, T P) {
    int max_truss = 0;
#pragma omp parallel for reduction(max:max_truss)
    for (auto i = 0; i < nEdge; i++) {
        max_truss = max(max_truss, P[i]);
    }
    log_info("Max Truss#: %d", max_truss);
}

template<typename T>
uint32_t LinearSearch(T *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    // linear search fallback
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (array[offset] >= val) {
            return offset;
        }
    }
    return offset_end;
}

template<typename T>
uint32_t BinarySearchForGallopingSearch(const T *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    while (offset_end - offset_beg >= 32) {
        auto mid = static_cast<uint32_t>((static_cast<unsigned long>(offset_beg) + offset_end) / 2);
        _mm_prefetch((char *) &array[(static_cast<unsigned long>(mid + 1) + offset_end) / 2], _MM_HINT_T0);
        _mm_prefetch((char *) &array[(static_cast<unsigned long>(offset_beg) + mid) / 2], _MM_HINT_T0);
        if (array[mid] == val) {
            return mid;
        } else if (array[mid] < val) {
            offset_beg = mid + 1;
        } else {
            offset_end = mid;
        }
    }

    // linear search fallback
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (array[offset] >= val) {
            return offset;
        }
    }
    return offset_end;
}

// Assuming (offset_beg != offset_end)
template<typename T>
uint32_t GallopingSearch(T *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    if (array[offset_end - 1] < val) {
        return offset_end;
    }
    // galloping
    if (array[offset_beg] >= val) {
        return offset_beg;
    }
    if (array[offset_beg + 1] >= val) {
        return offset_beg + 1;
    }
    if (array[offset_beg + 2] >= val) {
        return offset_beg + 2;
    }

    auto jump_idx = 4u;
    while (true) {
        auto peek_idx = offset_beg + jump_idx;
        if (peek_idx >= offset_end) {
            return BinarySearchForGallopingSearch(array, (jump_idx >> 1) + offset_beg + 1, offset_end, val);
        }
        if (array[peek_idx] < val) {
            jump_idx <<= 1;
        } else {
            return array[peek_idx] == val ? peek_idx :
                   BinarySearchForGallopingSearch(array, (jump_idx >> 1) + offset_beg + 1, peek_idx + 1, val);
        }
    }
}

template<typename T>
void core_val_histogram(int n, T &core, bool is_print = false) {
    // core-value histogram
    int max_core_val = 0;
    vector<int32_t> histogram;
#pragma omp parallel
    {
#pragma omp for reduction(max:max_core_val)
        for (auto u = 0; u < n; u++) {
            max_core_val = max(max_core_val, core[u]);
        }
#pragma omp single
        {
            log_info("max value: %d", max_core_val);
            histogram = vector<int32_t>(max_core_val + 1, 0);
        }
#pragma omp for
        for (auto u = 0; u < n; u++) {
            auto core_val = core[u];
#pragma omp atomic
            histogram[core_val]++;
        }
    }
    if (is_print) {
        if (histogram.size() < 400) {
            stringstream ss;
            ss << pretty_print_array(&histogram.front(), histogram.size());
            log_info("values histogram: %s", ss.str().c_str());
        } else {
            {
                stringstream ss;
                ss << pretty_print_array(&histogram.front(), 100);
                log_info("first100 values histogram: %s", ss.str().c_str());
            }
            {

                stringstream ss;
                ss << pretty_print_array(&histogram.front() + histogram.size() - 100, 100);
                log_info("last100 values histogram: %s", ss.str().c_str());
            }
        }
    }
    {
        stringstream ss;
        ss << histogram << "\n";
        log_info("Md5sum of histogram: %s", md5(ss.str()).c_str());
    }


    auto &bins = histogram;
    auto bin_cnt = 0;
    int64_t acc = 0;
    auto thresh = n / 10;
    auto last = 0;

    for (auto i = 0; i < histogram.size(); i++) {
        if (bins[i] > 0) {
            bin_cnt++;
            acc += bins[i];
            if (acc > thresh || i == histogram.size() - 1) {
                log_info("bin[%d - %d]: %s", last, i, FormatWithCommas(acc).c_str());
                last = i + 1;
                acc = 0;
            }
        }
    }
    log_info("Reversed Bins...");
    last = histogram.size() - 1;
    acc = 0;
    for (int32_t i = histogram.size() - 1; i > -1; i--) {
        if (bins[i] > 0) {
            bin_cnt++;
            acc += bins[i];
            if (acc > thresh || i == 0) {
                log_info("bin[%d - %d]: %s", i, last, FormatWithCommas(acc).c_str());
                last = i + 1;
                acc = 0;
            }
        }
    }
    log_info("total bin counts: %d", bin_cnt);
}

inline vertex commons(vector<vertex> &a, vector<vertex> &b) {
    vertex i = 0, j = 0;
    vertex count = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])
            i++;
        else if (b[j] < a[i])
            j++;
        else {
            count++;
            i++;
            j++;
        }
    }
    return count;
}


inline bool hashUniquify(vector<vertex> &vertices) {
    unordered_map<vertex, bool> hermap;
    for (size_t i = 0; i < vertices.size(); i++) {
        int t = vertices[i];
        if (hermap.find(t) == hermap.end())
            hermap[t] = true;
        else {
            vertices.erase(vertices.begin() + i);
            i--;
        }
    }
    sort(vertices.begin(), vertices.end());
    return true;
}

void baseLocal12(vertex nVtx, vertex *adj, edge *xadj, vertex *P, const char *vfile);

void nmLocal12(vertex nVtx, vertex *adj, edge *xadj, vertex *P, const char *vfile);

void topKs(vertex nVtx, vertex *adj, edge *xadj, vertex *P, const char *vfile);

void kcore(vertex nVtx, vertex *adj, edge *xadj, vertex *K, const char *vfile);

void converge12onEgo(vertex nVtx, vertex *adj, edge *xadj, vertex *K, string kfile);

void baseLocal23(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T, const char *vfile);

void nmLocal23(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T);

void ktruss(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T, const char *vfile);

void converge23onEgo(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *K, string kfile);

void baseLocal34(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T, const char *vfile);

void nmLocal34(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T, const char *vfile);

void k34(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T, const char *vfile);

template<typename VtxType, typename EdgeType>
void readGraph(char *filename, VtxType *nVtx, EdgeType *nEdge, VtxType **adj, EdgeType **xadj);


