//
// Created by yche on 10/31/17.
//

#ifndef SCAN_QUERY__SET_INTERSECTION_H
#define SCAN_QUERY__SET_INTERSECTION_H

#include <unordered_set>
#include <xmmintrin.h>

#include "../util/fake_header.h"

#ifdef HASH_SPP

#include <sparsepp/spp.h>

#endif

#include "../util/graph.h"

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

int ComputeCNNaive(Graph *g, int u, int v);

int ComputeCNNaive(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end);

int ComputeCNNaiveStdMerge(Graph *g, int u, int v);

int ComputeCNNaiveStdMerge(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end);

int ComputeCNGallopingSingleDir(Graph *g, int u, int v);

int
ComputeCNGallopingSingleDir(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end);

int ComputeCNGallopingDoubleDir(Graph *g, int u, int v);

int ComputeCNHash(Graph *g, int u, int v, unordered_set<int> &neighbor_sets);

template<typename T>
int ComputeCNHash(Graph *g, uint32_t offset_beg, uint32_t offset_end, T &neighbor_sets) {
    auto cn_count = 0;
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (neighbor_sets.find(g->edge_dst[offset]) != neighbor_sets.end()) {
            cn_count++;
        }
    }
    return cn_count;
}

#ifdef HASH_SPP

int ComputeCNHashSPP(Graph *g, int u, int v, spp::sparse_hash_set<int> &neighbor_sets);

int ComputeCNHashSPP(Graph *g, uint32_t offset_beg, uint32_t offset_end, spp::sparse_hash_set<int> &neighbor_sets);

#endif

template<typename T>
int ComputeCNHashBitVec(Graph *g, int u, int v, T &neighbor_bits) {
    auto cn_count = 0;
    for (auto offset = g->node_off[v]; offset < g->node_off[v + 1]; offset++) {
        if (neighbor_bits[g->edge_dst[offset]]) {
            cn_count++;
        }
    }
    return cn_count;
}

template<typename T>
int ComputeCNHashBitVec(Graph *g, uint32_t offset_beg, uint32_t offset_end, T &neighbor_bits) {
    auto cn_count = 0;
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (neighbor_bits[g->edge_dst[offset]]) {
            cn_count++;
        }
    }
    return cn_count;
}

#ifndef INDEX_BIT_SCALE_LOG
#define INDEX_BIT_SCALE_LOG (12)
#endif

#define INDEX_RANGE (1 << INDEX_BIT_SCALE_LOG)

template<typename T, typename I>
int ComputeCNHashBitVec2DMemIdx(Graph *g, int u, int v, T &neighbor_bits, I &index_bits, uint32_t &idx) {
    auto cn_count = 0;
    for (auto offset = g->node_off[v]; offset < g->node_off[v + 1]; offset++) {
        if (g->edge_dst[offset] == u) {
            idx = offset;
        }
        if (index_bits[g->edge_dst[offset] >> INDEX_BIT_SCALE_LOG]) {
            if (neighbor_bits[g->edge_dst[offset]]) {
                cn_count++;
            }
        }
    }
    return cn_count;
}

template<typename T, typename I>
int ComputeCNHashBitVec2D(Graph *g, int u, int v, T &neighbor_bits, I &index_bits) {
    auto cn_count = 0;
    for (auto offset = g->node_off[v]; offset < g->node_off[v + 1]; offset++) {
        if (index_bits[g->edge_dst[offset] >> INDEX_BIT_SCALE_LOG]) {
            if (neighbor_bits[g->edge_dst[offset]]) {
                cn_count++;
            }
        }
    }
    return cn_count;
}

template<typename T, typename I>
int ComputeCNHashBitVec2D(Graph *g, uint32_t offset_beg, uint32_t offset_end, T &neighbor_bits, I &index_bits) {
    auto cn_count = 0;
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (index_bits[g->edge_dst[offset] >> INDEX_BIT_SCALE_LOG]) {
            if (neighbor_bits[g->edge_dst[offset]]) {
                cn_count++;
            }
        }
    }
    return cn_count;
}

#endif
