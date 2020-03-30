#pragma once

#include <util/search_util.h>
#include <util/jetbrains_fake.h>
#include <util/graph.h>

#include <x86intrin.h>

#define ENABLE_AVX2

inline void SetIntersectionScalarMergeDetail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                             vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (off_nei_u < uEnd && off_nei_v < vEnd) {
        while (true) {
            while (g->adj[off_nei_u] < g->adj[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= uEnd) { return; }
            }
            while (g->adj[off_nei_u] > g->adj[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= vEnd) { return; }
            }
            if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
                // write back
                intersection_res[beg++] = make_pair(off_nei_u, off_nei_v);

                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= uEnd || off_nei_v >= vEnd) { return; }
            }
        }
    }
}

#if defined(__SSE4_1__)
extern int lookup_dict2[16];
extern int lookup_dict3[4];

inline void SetInterMergeSSE4DetailOneFour(graph_t *g, uint32_t &off_nei_u, uint32_t uEnd, uint32_t &off_nei_v,
                                           uint32_t vEnd, vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (off_nei_u < uEnd && off_nei_v + 3 < vEnd) {
        __m128i u_elements = _mm_set1_epi32(g->adj[off_nei_u]);
        __m128i v_elements = _mm_loadu_si128((__m128i *) (g->adj + off_nei_v));

        while (true) {
            __m128i mask = _mm_cmpeq_epi32(u_elements, v_elements);
            int real_mask = _mm_movemask_ps((__m128) mask);  // possibilities: 0, 1, 2, 4, 8
            if (real_mask != 0) {
                intersection_res[beg++] = make_pair(off_nei_u, lookup_dict2[real_mask] + off_nei_v);
            }
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
}

inline void SetInterMergeSSE4DetailTwoTwo(graph_t *g, uint32_t &off_nei_u, uint32_t uEnd, uint32_t &off_nei_v,
                                          uint32_t vEnd, vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
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
            if (real_mask != 0) {
                // a0
                int a0_mask = real_mask & 0b11;
                if (a0_mask != 0) {
                    intersection_res[beg++] = make_pair(off_nei_u, lookup_dict3[a0_mask] + off_nei_v);
                }

                // a1
                int a1_mask = (real_mask >> 2) & 0b11;
                if (a1_mask != 0) {
                    intersection_res[beg++] = make_pair(off_nei_u + 1, lookup_dict3[a1_mask] + off_nei_v);
                }
            }
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
}

inline void SetIntersectionMergeSSE4Detail(graph_t *g, uint32_t off_nei_u, uint32_t uEnd, uint32_t off_nei_v,
                                           uint32_t vEnd, vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    auto size_ratio = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size_ratio > 2) {
        SetInterMergeSSE4DetailOneFour(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    } else {
        SetInterMergeSSE4DetailTwoTwo(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    }
    SetIntersectionScalarMergeDetail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

inline void SetIntersectionMergeSSE4(graph_t *g, uint32_t off_nei_u, uint32_t uEnd, uint32_t off_nei_v,
                                     uint32_t vEnd, vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (uEnd - off_nei_u > vEnd - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(uEnd, vEnd);
    }
    beg = 0;
    SetIntersectionMergeSSE4Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

#endif

#if defined(__AVX2__)

extern int lookup_dict[256];
extern int lookup_dict2[16];

inline void SetInterMergeAVX2DetailOneEight(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd,
                                            vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (off_nei_u < uEnd && off_nei_v + 7 < vEnd) {
        __m256i u_elements = _mm256_set1_epi32(g->adj[off_nei_u]);
        __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->adj + off_nei_v));

        while (true) {
            __m256i mask = _mm256_cmpeq_epi32(u_elements, v_elements);
            auto real_mask = _mm256_movemask_ps((__m256) mask);
            if (real_mask != 0) {
                intersection_res[beg++] = make_pair(off_nei_u, off_nei_v + lookup_dict[real_mask]);
            }
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
}


inline void SetInterMergeAVX2DetailTwoFour(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd,
                                           vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
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
            auto bits = real_mask & 0xf;
            if (bits) {
                intersection_res[beg++] = make_pair(off_nei_u, off_nei_v + lookup_dict2[bits]);
            }
            bits = (real_mask >> 4) & 0xf;
            if (bits) {
                intersection_res[beg++] = make_pair(off_nei_u + 1, off_nei_v + lookup_dict2[bits]);
            }

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
}

// The order of off_u and off_v in intersection_res is not important. No duplicated equals.
inline void SetIntersectionMergeAVX2Detail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                           vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {

    auto size_ratio = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size_ratio > 2) {
        SetInterMergeAVX2DetailOneEight(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    } else {
        SetInterMergeAVX2DetailTwoFour(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    }
    SetIntersectionScalarMergeDetail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

inline void SetIntersectionMergeAVX2(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                     vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (uEnd - off_nei_u > vEnd - off_nei_v) {
        swap(uEnd, vEnd);
        swap(off_nei_u, off_nei_v);
    }
    beg = 0;
    SetIntersectionMergeAVX2Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

#endif

#ifdef __AVX512F__

#ifndef U16_HELPER
#define U16_HELPER
inline std::uint16_t operator "" _u(unsigned long long value) {
    return static_cast<std::uint16_t>(value);
}

#endif

inline void SetInterMergeAVX512DetailOneSixteen(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd,
                                                vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (off_nei_u < uEnd && off_nei_v + 15 < vEnd) {
        __m512i u_elements = _mm512_set1_epi32(g->adj[off_nei_u]);
        __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));

        while (true) {
            __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements, v_elements);
            if (mask != 0) {
                if (mask > 0xff_u) {
                    intersection_res[beg++] = make_pair(off_nei_u, off_nei_v + 8 + lookup_dict[mask >> 8]);
                } else {
                    intersection_res[beg++] = make_pair(off_nei_u, off_nei_v + lookup_dict[mask]);
                }
            }
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
}

inline void SetInterMergeAVX512DetailFourFour(graph_t *g, eid_t &off_nei_u, eid_t uEnd, eid_t &off_nei_v, eid_t vEnd,
                                              vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    __m512i st = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);
    __m512i single_permutation = _mm512_set_epi32(3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0);

    if (off_nei_u + 3 < uEnd && off_nei_v + 3 < vEnd) {
        __m512i u_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_u));
        __m512i u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
        __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->adj + off_nei_v));
        __m512i v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

        while (true) {
            __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements_per, v_elements_per);
            if (mask != 0) {
                auto tmp = (mask >> (4 * 0)) & 0xf_u;
                if (tmp) { intersection_res[beg++] = make_pair(off_nei_u, off_nei_v + lookup_dict2[tmp]); }
                tmp = (mask >> (4 * 1)) & 0xf_u;
                if (tmp) { intersection_res[beg++] = make_pair(off_nei_u + 1, off_nei_v + lookup_dict2[tmp]); }
                tmp = (mask >> (4 * 2)) & 0xf_u;
                if (tmp) { intersection_res[beg++] = make_pair(off_nei_u + 2, off_nei_v + lookup_dict2[tmp]); }
                tmp = (mask >> (4 * 3)) & 0xf_u;
                if (tmp) { intersection_res[beg++] = make_pair(off_nei_u + 3, off_nei_v + lookup_dict2[tmp]); }
            }
// TODO: vectorize this part.
//                for (auto i = 0; i < 4; i++) {
//                    auto tmp = (mask >> (4 * i)) & 0xf_u;
//                    if (tmp) {
//                        intersection_res[beg++] = make_pair(off_nei_u + i, off_nei_v + lookup_dict2[tmp]);
//                    }
//                }
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
}

inline void SetIntersectionMergeAVX512Detail(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                             vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    auto size1 = (vEnd - off_nei_v) / (uEnd - off_nei_u);
    if (size1 > 2) {
        SetInterMergeAVX512DetailOneSixteen(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    } else {
        SetInterMergeAVX512DetailFourFour(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
    }
    SetIntersectionScalarMergeDetail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

inline void SetIntersectionMergeAVX512(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                       vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {

    if (uEnd - off_nei_u > vEnd - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(uEnd, vEnd);
    }
    beg = 0;
    SetIntersectionMergeAVX512Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
}

#endif

#if (defined(__AVX512F__) || defined(__AVX2__) || defined(__SSE4_1__)) && (defined(ENABLE_AVX2))
#define ENABLE_VEC
#endif

inline void SetInterSectionLookup(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                                  vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    if (uEnd - off_nei_u > vEnd - off_nei_v) {
        swap(uEnd, vEnd);
        swap(off_nei_u, off_nei_v);
    }
    beg = 0;
#if defined(ENABLE_VEC)
    if ((uEnd - off_nei_u) * 50 > (vEnd - off_nei_v)) {
#if defined(__AVX512F__)
        SetIntersectionMergeAVX512Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
#elif defined(__AVX2__)
        SetIntersectionMergeAVX2Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
#elif  defined(__SSE4_1__)
        SetIntersectionMergeSSE4Detail(g, off_nei_u, uEnd, off_nei_v, vEnd, intersection_res, beg);
#endif
    } else {
#endif
        while (true) {
#ifdef __AVX512F__
            off_nei_u = LinearSearchAVX512(g->adj, off_nei_u, uEnd, g->adj[off_nei_v]);
#else
            off_nei_u = LinearSearch(g->adj, off_nei_u, uEnd, g->adj[off_nei_v]);
#endif
            if (off_nei_u >= uEnd) {
                break;
            }
#ifdef __AVX512F__
            off_nei_v = GallopingSearchAVX512(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
#elif defined(__AVX2__) && defined(ENABLE_AVX2)
            off_nei_v = GallopingSearchAVX2(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
#else
            off_nei_v = GallopingSearch(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
#endif
            if (off_nei_v >= vEnd) {
                break;
            }
            if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
                intersection_res[beg++] = make_pair(off_nei_v, off_nei_u);
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= uEnd || off_nei_v >= vEnd) {
                    break;
                }
            }
        }
#if defined(ENABLE_VEC)
    }
#endif
}

// Assume `intersection_res` is large enough
inline void SetIntersection(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                            vector<pair<eid_t, eid_t >> &intersection_res, size_t &beg) {
    beg = 0;
#ifdef NAIVE_INTER
    unsigned int numElements = (uEnd - off_nei_u) + (vEnd - off_nei_v);
    for (unsigned int innerIdx = 0; innerIdx < numElements; innerIdx++) {
        if (off_nei_u >= uEnd) {
            break;
        } else if (off_nei_v >= vEnd) {
            break;
        } else if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
            intersection_res[beg++] = make_pair(off_nei_v, off_nei_u);
            off_nei_u++;
            off_nei_v++;
        } else if (g->adj[off_nei_u] < g->adj[off_nei_v]) {
            off_nei_u++;
        } else if (g->adj[off_nei_v] < g->adj[off_nei_u]) {
            off_nei_v++;
        }
    }
#else
    while (true) {
#if defined(__AVX2__) && defined(ENABLE_AVX2)
        off_nei_u = GallopingSearchAVX2(g->adj, off_nei_u, uEnd, g->adj[off_nei_v]);
#else
        off_nei_u = GallopingSearch(g->adj, off_nei_u, uEnd, g->adj[off_nei_v]);
#endif
        if (off_nei_u >= uEnd) {
            break;
        }
#if defined(__AVX2__) && defined(ENABLE_AVX2)
        off_nei_v = GallopingSearchAVX2(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
#else
        off_nei_v = GallopingSearch(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
#endif
        if (off_nei_v >= vEnd) {
            break;
        }
        if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
            intersection_res[beg++] = make_pair(off_nei_v, off_nei_u);
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= uEnd || off_nei_v >= vEnd) {
                break;
            }
        }
    }
#endif
}

inline void SetIntersection(graph_t *g, eid_t off_nei_u, eid_t uEnd, eid_t off_nei_v, eid_t vEnd,
                            vector<pair<eid_t, eid_t >> &intersection_res) {
#ifdef NAIVE_INTER
    unsigned int numElements = (uEnd - off_nei_u) + (vEnd - off_nei_v);
    for (unsigned int innerIdx = 0; innerIdx < numElements; innerIdx++) {
        if (off_nei_u >= uEnd) {
            break;
        } else if (off_nei_v >= vEnd) {
            break;
        } else if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
            intersection_res.emplace_back(off_nei_v, off_nei_u);
            off_nei_u++;
            off_nei_v++;
        } else if (g->adj[off_nei_u] < g->adj[off_nei_v]) {
            off_nei_u++;
        } else if (g->adj[off_nei_v] < g->adj[off_nei_u]) {
            off_nei_v++;
        }
    }
#else
    while (true) {
        off_nei_u = GallopingSearch(g->adj, off_nei_u, uEnd, g->adj[off_nei_v]);
        if (off_nei_u >= uEnd) {
            break;
        }
        off_nei_v = GallopingSearch(g->adj, off_nei_v, vEnd, g->adj[off_nei_u]);
        if (off_nei_v >= vEnd) {
            break;
        }
        if (g->adj[off_nei_u] == g->adj[off_nei_v]) {
            intersection_res.emplace_back(off_nei_v, off_nei_u);
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= uEnd || off_nei_v >= vEnd) {
                break;
            }
        }
    }
#endif
}