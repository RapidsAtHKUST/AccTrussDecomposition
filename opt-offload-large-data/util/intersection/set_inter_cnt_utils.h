#pragma once

#include "util/search/search_util.h"
#include "util/jetbrains_fake.h"
#include "util/graph/graph.h"

#include <x86intrin.h>

inline int SetIntersectionScalarCntDetail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd) {
    int cnt = 0;
    if (off_nei_u < uEnd && off_nei_v < vEnd) {
        while (true) {
            while (g->adj[off_nei_u] < g->adj[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= uEnd) { return cnt; }
            }
            while (g->adj[off_nei_u] > g->adj[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= vEnd) { return cnt; }
            }
            if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
                // write back
                ++cnt;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= uEnd || off_nei_v >= vEnd) { return cnt; }
            }
        }
    }
    return cnt;
}


#if defined(__SSE4_1__)

/*
 * Set Intersection Count Begin (SSE4) ========================================
 */
inline int SetInterCntSSE4DetailOneFour(graph_t *g, uint32_t &off_nei_u, uint32_t uEnd,
                                        uint32_t &off_nei_v, uint32_t vEnd) {
    int cnt = 0;
    if (off_nei_u < uEnd && off_nei_v + 3 < vEnd) {
        __m128i u_elements = _mm_set1_epi32(g->adj[off_nei_u]);
        __m128i v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));

        while (true) {
            __m128i mask = _mm_cmpeq_epi32(u_elements, v_elements);
            int real_mask = _mm_movemask_ps((__m128) mask);  // possibilities: 0, 1, 2, 4, 8
            if (real_mask != 0)cnt++;
            if (g->adj[off_nei_u] > g->adj[off_nei_v + 3]) {
                off_nei_v += 4;
                if (off_nei_v + 3 >= vEnd) {
                    break;
                }
                v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));
            } else {
                off_nei_u++;
                if (off_nei_u >= uEnd) {
                    break;
                }
                u_elements = _mm_set1_epi32(g->adj[off_nei_u]);
            }
        }
    }
    return cnt;
}

inline int SetInterCntSSE4DetailTwoTwo(graph_t *g, uint32_t &off_nei_u, uint32_t uEnd,
                                       uint32_t &off_nei_v, uint32_t vEnd) {
    int cnt = 0;
    constexpr int per_u_order = 0b01010000;
    constexpr int per_v_order = 0b01000100;
    if (off_nei_u + 1 < uEnd && off_nei_v + 1 < vEnd) {
        __m128i u_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_u));
        __m128i u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
        __m128i v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));
        __m128i v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);

        while (true) {
            __m128i mask = _mm_cmpeq_epi32(u_elements_per, v_elements_per);
            int real_mask = _mm_movemask_ps((__m128) mask);
            // a1,a1,a0,a0 compared to b1,b0,b1,b0
            // possibilities: case (1): a1-b1, b0-b0: 0b1001; case (2): a1-b0: 0b0100; case (3) a0-b1: 0b0010
            // case (4): a0-b0: 0b0001, case(5): a1-b1: 0b1000
            cnt += _popcnt32(real_mask);
            if (g->adj[off_nei_u + 1] == g->adj[off_nei_v + 1]) {
                off_nei_u += 2;
                off_nei_v += 2;
                if (off_nei_u + 1 >= uEnd || off_nei_v + 1 >= vEnd) {
                    break;
                }
                u_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_u));
                u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
                v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));
                v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
            } else if (g->adj[off_nei_u + 1] > g->adj[off_nei_v + 1]) {
                off_nei_v += 2;
                if (off_nei_v + 1 >= vEnd) {
                    break;
                }
                v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));
                v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
            } else {
                off_nei_u += 2;
                if (off_nei_u + 1 >= uEnd) {
                    break;
                }
                u_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_u));
                u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
            }
        }
    }
    return cnt;
}

inline int SetInterCntSSE4Detail(graph_t *g, uint32_t off_nei_u, uint32_t uEnd, uint32_t off_nei_v, uint32_t vEnd) {
    int cnt = 0;
    auto size_ratio = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size_ratio > 2) {
        cnt += SetInterCntSSE4DetailOneFour(g, off_nei_u, uEnd, off_nei_v, vEnd);
    } else {
        cnt += SetInterCntSSE4DetailTwoTwo(g, off_nei_u, uEnd, off_nei_v, vEnd);
    }
    cnt += SetIntersectionScalarCntDetail(g, off_nei_u, uEnd, off_nei_v, vEnd);
    return cnt;
}
/*
 * Set Intersection Count End (SSE4) ========================================
 */

#if defined(__AVX2__)

/*
 * Set Intersection Count Begin (AVX2) ========================================
 */
inline int SetInterCntAVX2DetailOneEight(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd) {
    int cnt = 0;
    if (off_nei_u < uEnd && off_nei_v + 7 < vEnd) {
        __m256i u_elements = _mm256_set1_epi32(g->adj[off_nei_u]);
        __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));

        while (true) {
            __m256i mask = _mm256_cmpeq_epi32(u_elements, v_elements);
            auto real_mask = _mm256_movemask_ps((__m256) mask);
            if (real_mask != 0) { cnt++; }
            if (g->adj[off_nei_u] > g->adj[off_nei_v + 7]) {
                off_nei_v += 8;
                if (off_nei_v + 7 >= vEnd) {
                    break;
                }
                v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));
            } else {
                off_nei_u++;
                if (off_nei_u >= uEnd) {
                    break;
                }
                u_elements = _mm256_set1_epi32(g->adj[off_nei_u]);
            }
        }
    }
    return cnt;
}


inline int SetInterCntAVX2DetailTwoFour(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd) {
    int cnt = 0;
    __m256i per_u_order = _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0);
    __m256i per_v_order = _mm256_set_epi32(3, 2, 1, 0, 3, 2, 1, 0);

    if (off_nei_u + 1 < uEnd && off_nei_v + 3 < vEnd) {
        __m256i u_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_u));
        __m256i u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
        __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));
        __m256i v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);

        while (true) {
            __m256i mask = _mm256_cmpeq_epi32(u_elements_per, v_elements_per);
            auto real_mask = _mm256_movemask_ps((__m256) mask);
            cnt += _popcnt32(real_mask);
            if (g->adj[off_nei_u + 1] == g->adj[off_nei_v + 3]) {
                off_nei_u += 2;
                off_nei_v += 4;
                if (off_nei_u + 1 >= uEnd || off_nei_v + 3 >= vEnd) {
                    break;
                }
                u_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_u));
                u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));
                v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
            } else if (g->adj[off_nei_u + 1] > g->adj[off_nei_v + 3]) {
                off_nei_v += 4;
                if (off_nei_v + 3 >= vEnd) {
                    break;
                }
                v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));
                v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
            } else {
                off_nei_u += 2;
                if (off_nei_u + 1 >= uEnd) {
                    break;
                }
                u_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_u));
                u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
            }
        }
    }
    return cnt;
}

// The order of off_u and off_v in intersection_res is not important. No duplicated equals.
inline int SetInterCntAVX2Detail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd) {
    int cnt = 0;
    auto size_ratio = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size_ratio > 2) {
        cnt += SetInterCntAVX2DetailOneEight(g, off_nei_u, uEnd, off_nei_v, vEnd);
    } else {
        cnt += SetInterCntAVX2DetailTwoFour(g, off_nei_u, uEnd, off_nei_v, vEnd);
    }
    cnt += SetIntersectionScalarCntDetail(g, off_nei_u, uEnd, off_nei_v, vEnd);
    return cnt;
}
/*
 * Set Intersection Count End (AVX2) ========================================
 */
#endif


#ifdef __AVX512F__

#ifndef U16_HELPER
#define U16_HELPER
inline std::uint16_t operator "" _u(unsigned long long value) {
    return static_cast<std::uint16_t>(value);
}
#endif

inline int SetInterCntAVX512DetailOneSixteen(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd) {
    int cnt = 0;
    if (off_nei_u < uEnd && off_nei_v + 15 < vEnd) {
        __m512i u_elements = _mm512_set1_epi32(g->adj[off_nei_u]);
        __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));

        while (true) {
            __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements, v_elements);
            if (mask != 0) { cnt++; }
            if (g->adj[off_nei_u] > g->adj[off_nei_v + 15]) {
                off_nei_v += 16;
                if (off_nei_v + 15 >= vEnd) {
                    break;
                }
                v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));
            } else {
                off_nei_u++;
                if (off_nei_u >= uEnd) {
                    break;
                }
                u_elements = _mm512_set1_epi32(g->adj[off_nei_u]);
            }
        }
    }
    return cnt;
}

inline int SetInterCntAVX512DetailFourFour(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd) {
    int cnt = 0;
    __m512i st = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);
    __m512i single_permutation = _mm512_set_epi32(3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0);

    if (off_nei_u + 3 < uEnd && off_nei_v + 3 < vEnd) {
        __m512i u_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_u));
        __m512i u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
        __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));
        __m512i v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

        while (true) {
            __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements_per, v_elements_per);
            cnt += _popcnt32(mask);
            if (g->adj[off_nei_u + 3] > g->adj[off_nei_v + 3]) {
                off_nei_v += 4;
                if (off_nei_v + 3 >= vEnd) {
                    break;
                }
                v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));
                v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

            } else if (g->adj[off_nei_u + 3] < g->adj[off_nei_v + 3]) {
                off_nei_u += 4;
                if (off_nei_u + 3 >= uEnd) {
                    break;
                }
                u_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_u));
                u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
            } else {
                off_nei_u += 4;
                off_nei_v += 4;
                if (off_nei_u + 3 >= uEnd || off_nei_v + 3 >= vEnd) {
                    break;
                }
                u_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_u));
                u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
                v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));
                v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);
            }
        }
    }
    return cnt;
}

inline int SetIntersectionMergeAVX512Detail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd) {
    int cnt = 0;
    auto size1 = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size1 > 4) {
        cnt += SetInterCntAVX512DetailOneSixteen(g, off_nei_u, uEnd, off_nei_v, vEnd);
    } else {
        cnt += SetInterCntAVX512DetailFourFour(g, off_nei_u, uEnd, off_nei_v, vEnd);
    }
    cnt += SetIntersectionScalarCntDetail(g, off_nei_u, uEnd, off_nei_v, vEnd);
    return cnt;
}

#endif

#endif
