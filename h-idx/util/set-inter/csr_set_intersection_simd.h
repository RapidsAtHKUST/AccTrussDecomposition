//
// Created by yche on 11/4/17.
//

#ifndef SCAN_QUERY_CSR_SET_INTERSECTION_SIMD_H
#define SCAN_QUERY_CSR_SET_INTERSECTION_SIMD_H

#include "../util/graph.h"
#include "../util/fake_header.h"

#if defined(HAS_AVX512)

uint32_t BinarySearchForGallopingSearchAVX512(const int *array, uint32_t offset_beg, uint32_t offset_end, int val);

uint32_t GallopingSearchAVX512(int *array, uint32_t offset_beg, uint32_t offset_end, int val);

int ComputeCNGallopingSingleDirAVX512(Graph *g, int u, int v);

int ComputeCNGallopingDoubleDirAVX512(Graph *g, int u, int v);

int ComputeCNAVX512(Graph *g, int u, int v);

int ComputeCNAVX512PopCnt(Graph *g, int u, int v);

int ComputeCNPivotAVX512(Graph *g, int u, int v);

#endif

#if defined(HAS_AVX512) || defined(HAS_AVX2)

int ComputeCNAVX2(Graph *g, int u, int v);

int ComputeCNAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end);

// share the same logic with ComputeCNAVX2
int ComputeCNAVX2PopCnt(Graph *g, int u, int v);

int ComputeCNPivotAVX2(Graph *g, int u, int v);

int ComputeCNPivotAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end);

uint32_t BinarySearchForGallopingSearchAVX2(const int *array, uint32_t offset_beg, uint32_t offset_end, int val);

uint32_t GallopingSearchAVX2(int *array, uint32_t offset_beg, uint32_t offset_end, int val);

int ComputeCNGallopingSingleDirAVX2(Graph *g, int u, int v);

int ComputeCNGallopingSingleDirAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                                    uint32_t off_v_end);

int ComputeCNGallopingDoubleDirAVX2(Graph *g, int u, int v);

#endif

int ComputeCNLowerBoundSSE(Graph *g, int u, int v);

int ComputeCNSSE4(Graph *g, int u, int v);

int ComputeCNSSE4(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                  uint32_t off_v_end);

int ComputeCNPivotSSE4(Graph *g, int u, int v);

int ComputeCNPivotSSE4(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                       uint32_t off_v_end);

#endif //SCAN_QUERY_CSR_SET_INTERSECTION_SIMD_H
