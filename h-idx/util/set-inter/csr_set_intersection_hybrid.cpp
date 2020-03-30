//
// Created by yche on 11/4/17.
//
#include "csr_set_intersection_hybrid.h"

#include "csr_set_intersection_serial.h"
#include "csr_set_intersection_simd.h"

#if defined(HAS_AVX512)

int ComputeCNHybridAVX512(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
        return ComputeCNGallopingSingleDirAVX512(g, u, v);
    } else {
        return ComputeCNAVX512(g, u, v);
    }
}

int ComputeCNHybridAVX512NoBlkMerge(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
        return ComputeCNGallopingSingleDirAVX512(g, u, v);
    } else {
    }
}

int ComputeCNHybridAVX512NoGalloping(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
    } else {
        return ComputeCNAVX512(g, u, v);
    }
}

#endif

#if defined(HAS_AVX512) || defined(HAS_AVX2)

int ComputeCNHybridAVX2(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
        return ComputeCNGallopingSingleDir(g, u, v);
    } else {
        return ComputeCNAVX2(g, u, v);
    }
}

int ComputeCNHybridAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                        uint32_t off_v_end) {
    auto du = off_u_end - off_nei_u + 1;
    auto dv = off_v_end - off_nei_v + 1;
    if (du / 50 > dv || dv / 50 > du) {
        return ComputeCNGallopingSingleDir(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    } else {
        return ComputeCNAVX2(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    }
}

#endif

int ComputeCNHybrid(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
        return ComputeCNGallopingSingleDir(g, u, v);
    } else {
        return ComputeCNNaiveStdMerge(g, u, v);
    }
}

int ComputeCNHybrid(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                    uint32_t off_v_end) {
    auto du = off_u_end - off_nei_u + 1;
    auto dv = off_v_end - off_nei_v + 1;
    if (du / 50 > dv || dv / 50 > du) {
        return ComputeCNGallopingSingleDir(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    } else {
        return ComputeCNNaiveStdMerge(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    }
}

int ComputeCNSSEHybrid(Graph *g, int u, int v) {
    if (g->degree[u] / 50 > g->degree[v] || g->degree[v] / 50 > g->degree[u]) {
        return ComputeCNGallopingSingleDir(g, u, v);
    } else {
        return ComputeCNSSE4(g, u, v);
    }
}

int ComputeCNSSEHybrid(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                       uint32_t off_v_end) {
    auto du = off_u_end - off_nei_u + 1;
    auto dv = off_v_end - off_nei_v + 1;
    if (du / 50 > dv || dv / 50 > du) {
        return ComputeCNGallopingSingleDir(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    } else {
        return ComputeCNSSE4(g, off_nei_u, off_u_end, off_nei_v, off_v_end);
    }
}