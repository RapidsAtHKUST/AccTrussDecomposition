//
// Created by yche on 11/4/17.
//

#ifndef SCAN_QUERY_CSR_SET_INTERSECTION_HYBRID_H
#define SCAN_QUERY_CSR_SET_INTERSECTION_HYBRID_H

#include "../util/graph.h"

#include "../util/fake_header.h"

#if defined(HAS_AVX512)

int ComputeCNHybridAVX512(Graph *g, int u, int v);

int ComputeCNHybridAVX512NoBlkMerge(Graph *g, int u, int v);

int ComputeCNHybridAVX512NoGalloping(Graph *g, int u, int v);

#endif

#if defined(HAS_AVX512) || defined(HAS_AVX2)

int ComputeCNHybridAVX2(Graph *g, int u, int v);

int ComputeCNHybridAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                        uint32_t off_v_end);

#endif

#endif //SCAN_QUERY_CSR_SET_INTERSECTION_HYBRID_H


int ComputeCNHybrid(Graph *g, int u, int v);

int ComputeCNHybrid(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                    uint32_t off_v_end);

int ComputeCNSSEHybrid(Graph *g, int u, int v);

int ComputeCNSSEHybrid(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                       uint32_t off_v_end);

