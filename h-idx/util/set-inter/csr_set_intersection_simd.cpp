//
// Created by yche on 11/4/17.
//

#include "csr_set_intersection_simd.h"
#include "csr_set_intersection_serial.h"

#include <immintrin.h>  //AVX

#if !defined(__INTEL_COMPILER)

#include <x86intrin.h>

#endif

#if defined(HAS_AVX512)

uint32_t BinarySearchForGallopingSearchAVX512(const int *array, uint32_t offset_beg, uint32_t offset_end, int val) {
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
    constexpr int parallelism = 16;
    __m512i pivot_element = _mm512_set1_epi32(val);
    for (; offset_beg + 15 < offset_end; offset_beg += parallelism) {
        __m512i elements = _mm512_loadu_si512(reinterpret_cast<const __m512i *>(array + offset_beg));
        __mmask16 mask = _mm512_cmplt_epi32_mask(elements, pivot_element);
        if (mask != 0xffff) { return offset_beg + _mm_popcnt_u32(mask); }
    }
    if (offset_beg < offset_end) {
        auto left_size = offset_end - offset_beg;
        __m512i elements = _mm512_loadu_si512(reinterpret_cast<const __m512i *>(array + offset_beg));
        __mmask16 mask = _mm512_cmplt_epi32_mask(elements, pivot_element);
        __mmask16 cmp_mask = ((__mmask16) 0xffff) >> (16 - left_size);
        mask &= cmp_mask;
        if (mask != cmp_mask) { return offset_beg + _mm_popcnt_u32(mask); }
    }
    return offset_end;
}

uint32_t GallopingSearchAVX512(int *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    if (array[offset_end - 1] < val) {
        return offset_end;
    }

    // front peeking
    __m512i pivot_element = _mm512_set1_epi32(val);
    auto left_size = offset_end - offset_beg;
    if (left_size >= 16) {
        __m512i elements = _mm512_loadu_si512(reinterpret_cast<const __m512i *>(array + offset_beg));
        __mmask16 mask = _mm512_cmplt_epi32_mask(elements, pivot_element);
        if (mask != 0xffff) { return offset_beg + _mm_popcnt_u32(mask); }
    } else {
        __m512i elements = _mm512_loadu_si512(reinterpret_cast<const __m512i *>(array + offset_beg));
        __mmask16 mask = _mm512_cmplt_epi32_mask(elements, pivot_element);
        __mmask16 cmp_mask = ((__mmask16) 0xffff) >> (16 - left_size);
        mask &= cmp_mask;
        if (mask != cmp_mask) { return offset_beg + _mm_popcnt_u32(mask); }
    }

    // galloping
    auto jump_idx = 16u;
    // pre-fetch
//    auto jump_times = 32 - _lzcnt_u32((offset_end - offset_beg) >> 4);
//    __m512i prefetch_idx = _mm512_set_epi64(16, 32, 64, 128, 256, 512, 1024, 2048);
//    __mmask8 mask = jump_times >= 8 ? (__mmask8) 0xff : (__mmask8) 0xff << (8 - jump_times);
//    _mm512_mask_prefetch_i64gather_ps(prefetch_idx, mask, array + offset_beg, 1, _MM_HINT_T0);

    while (true) {
        auto peek_idx = offset_beg + jump_idx;
        if (peek_idx >= offset_end) {
            return BinarySearchForGallopingSearchAVX512(array, (jump_idx >> 1) + offset_beg + 1, offset_end, val);
        }
        if (array[peek_idx] < val) {
            jump_idx <<= 1;
        } else {
            return array[peek_idx] == val ? peek_idx :
                   BinarySearchForGallopingSearchAVX512(array, (jump_idx >> 1) + offset_beg + 1, peek_idx + 1, val);
        }
    }
}

int ComputeCNGallopingSingleDirAVX512(Graph *g, int u, int v) {

    auto cn_count = 0;
    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto
    off_u_end = g->node_off[u + 1], off_v_
    end = g->node_off[v + 1];

    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        off_nei_v = GallopingSearchAVX512(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNGallopingDoubleDirAVX512(Graph *g, int u, int v) {

    auto cn_count = 0;
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];
    while (true) {
        off_nei_u = GallopingSearchAVX512(g->edge_dst, off_nei_u, off_u_end, g->edge_dst[off_nei_v]);
        if (off_nei_u >= off_u_end) {
            return cn_count;
        }

        off_nei_v = GallopingSearchAVX512(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNAVX512(Graph *g, int u, int v) {

    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    auto cn_count = 0;
    constexpr int parallelism = 16;
    __m512i st = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);
    __m512i ssecountplus = _mm512_set1_epi32(1);
    int cn_countv[parallelism] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    __m512i ssecn_countv = _mm512_set1_epi32(0);
    auto size1 = (off_v_end - off_nei_v) / (off_u_end - off_nei_u);
    if (size1 > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 15 < off_v_end) {
            __m512i u_elements = _mm512_set1_epi32(g->edge_dst[off_nei_u]);
            __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));

            while (true) {
                __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements, v_elements);
                ssecn_countv = _mm512_mask_add_epi32(ssecn_countv, mask, ssecn_countv, ssecountplus);

                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 15]) {
                    off_nei_v += 16;
                    if (off_nei_v + 15 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm512_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
            _mm512_store_si512((__m512i *) cn_countv, ssecn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    } else {
        if (off_nei_u + 3 < off_u_end && off_nei_v + 3 < off_v_end) {
            __m512i u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
            __m512i u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
            __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//            __m512i v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
            __m512i single_permutation = _mm512_set_epi32(3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0);
            __m512i v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

            while (true) {
                __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements_per, v_elements_per);
                ssecn_countv = _mm512_mask_add_epi32(ssecn_countv, mask, ssecn_countv, ssecountplus);

                if (g->edge_dst[off_nei_u + 3] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//                    v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
                    v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

                } else if (g->edge_dst[off_nei_u + 3] < g->edge_dst[off_nei_v + 3]) {
                    off_nei_u += 4;
                    if (off_nei_u + 3 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
                } else {
                    off_nei_u += 4;
                    off_nei_v += 4;
                    if (off_nei_u + 3 >= off_u_end || off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//                    v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
                    v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);
                }
            }
            _mm512_store_si512((__m512i *) cn_countv, ssecn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNAVX512PopCnt(Graph *g, int u, int v) {

    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    auto cn_count = 0;
    constexpr int parallelism = 16;
    __m512i st = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);

    auto size1 = (off_v_end - off_nei_v) / (off_u_end - off_nei_u);
    if (size1 > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 15 < off_v_end) {
            __m512i u_elements = _mm512_set1_epi32(g->edge_dst[off_nei_u]);
            __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));

            while (true) {
                __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements, v_elements);
                cn_count += _mm_popcnt_u32(mask);

                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 15]) {
                    off_nei_v += 16;
                    if (off_nei_v + 15 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm512_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
        }
    } else {
        if (off_nei_u + 3 < off_u_end && off_nei_v + 3 < off_v_end) {
            __m512i u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
            __m512i u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
            __m512i v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//            __m512i v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
            __m512i single_permutation = _mm512_set_epi32(3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0);
            __m512i v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);

            while (true) {
                __mmask16 mask = _mm512_cmpeq_epi32_mask(u_elements_per, v_elements_per);
                cn_count += _mm_popcnt_u32(mask);

                if (g->edge_dst[off_nei_u + 3] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//                    v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
                    v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);
                } else if (g->edge_dst[off_nei_u + 3] < g->edge_dst[off_nei_v + 3]) {
                    off_nei_u += 4;
                    if (off_nei_u + 3 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
                } else {
                    off_nei_u += 4;
                    off_nei_v += 4;
                    if (off_nei_u + 3 >= off_u_end || off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm512_permutexvar_epi32(st, u_elements);
                    v_elements = _mm512_loadu_si512((__m512i *) (g->edge_dst + off_nei_v));
//                    v_elements_per = _mm512_permute4f128_epi32(v_elements, 0b00000000);
                    v_elements_per = _mm512_permutexvar_epi32(single_permutation, v_elements);
                }
            }
        }
    }
    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNPivotAVX512(Graph *g, int u, int v) {

    auto cn_count = 0;
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    constexpr int parallelism = 16;
    while (true) {
        // avx512(knc), g->edge_dst[off_nei_v] as the pivot
        while (off_nei_u + 15 < off_u_end) {
            __m512i pivot = _mm512_set1_epi32(g->edge_dst[off_nei_v]);
            __m512i inspected_ele = _mm512_loadu_si512(
                    reinterpret_cast<const __m512i *>(&g->edge_dst[off_nei_u]));
            __mmask16 cmp_res = _mm512_cmpgt_epi32_mask(pivot, inspected_ele);
            auto count = _mm_popcnt_u32(cmp_res);

            // update off_nei_u and du
            off_nei_u += count;
            if (count < parallelism) {
                break;
            }
        }
        if (off_nei_u + 15 >= off_u_end) {
            break;
        }

        // avx512(knc), g->edge_dst[off_nei_u] as the pivot
        while (off_nei_v + 15 < off_v_end) {
            __m512i pivot = _mm512_set1_epi32(g->edge_dst[off_nei_u]);
            __m512i inspected_ele = _mm512_loadu_si512(
                    reinterpret_cast<const __m512i *>(&g->edge_dst[off_nei_v]));
            __mmask16 cmp_res = _mm512_cmpgt_epi32_mask(pivot, inspected_ele);
            auto count = _mm_popcnt_u32(cmp_res);

            // update off_nei_u and du
            off_nei_v += count;
            if (count < parallelism) {
                break;
            }
        }
        if (off_nei_v + 15 >= off_v_end) {
            break;
        }

        // find possible equality
        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            ++cn_count;
            ++off_nei_u;
            ++off_nei_v;
        }
    }

    if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
            ++off_nei_v;
            if (off_nei_v >= off_v_end) {
                return cn_count;
            }
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

#endif

#if defined(HAS_AVX512) || defined(HAS_AVX2)

int ComputeCNAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end) {

    if (off_u_end - off_nei_u > off_v_end - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(off_u_end, off_v_end);
    }

    constexpr int parallelism = 8;
    auto cn_count = 0;
    int cn_countv[parallelism] = {0, 0, 0, 0, 0, 0, 0, 0};
    __m256i sse_cn_countv = _mm256_load_si256((__m256i *) (cn_countv));
    __m256i sse_countplus = _mm256_set1_epi32(1);
    __m256i per_u_order = _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0);
    __m256i per_v_order = _mm256_set_epi32(3, 2, 1, 0, 3, 2, 1, 0);

    auto size_ratio = (off_v_end - off_nei_v + 1) / (off_u_end - off_nei_u + 1);
    if (size_ratio > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 7 < off_v_end) {
            __m256i u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements, v_elements);
                mask = _mm256_and_si256(sse_countplus, mask);
                sse_cn_countv = _mm256_add_epi32(sse_cn_countv, mask);
                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 7]) {
                    off_nei_v += 8;
                    if (off_nei_v + 7 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
            _mm256_store_si256((__m256i *) cn_countv, sse_cn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    } else {
        if (off_nei_u + 1 < off_u_end && off_nei_v + 3 < off_v_end) {
            __m256i u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
            __m256i u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
            __m256i v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements_per, v_elements_per);
                mask = _mm256_and_si256(sse_countplus, mask);
                sse_cn_countv = _mm256_add_epi32(sse_cn_countv, mask);

                if (g->edge_dst[off_nei_u + 1] == g->edge_dst[off_nei_v + 3]) {
                    off_nei_u += 2;
                    off_nei_v += 4;
                    if (off_nei_u + 1 >= off_u_end || off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else if (g->edge_dst[off_nei_u + 1] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else {
                    off_nei_u += 2;
                    if (off_nei_u + 1 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                }
            }
        }
        _mm256_store_si256((__m256i *) cn_countv, sse_cn_countv);
        for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNAVX2(Graph *g, int u, int v) {

    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    constexpr int parallelism = 8;
    auto cn_count = 0;
    int cn_countv[parallelism] = {0, 0, 0, 0, 0, 0, 0, 0};
    __m256i sse_cn_countv = _mm256_load_si256((__m256i *) (cn_countv));
    __m256i sse_countplus = _mm256_set1_epi32(1);
    __m256i per_u_order = _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0);
    __m256i per_v_order = _mm256_set_epi32(3, 2, 1, 0, 3, 2, 1, 0);

    auto size_ratio = (off_v_end - off_nei_v) / (off_u_end - off_nei_u);
    if (size_ratio > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 7 < off_v_end) {
            __m256i u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements, v_elements);
                mask = _mm256_and_si256(sse_countplus, mask);
                sse_cn_countv = _mm256_add_epi32(sse_cn_countv, mask);
                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 7]) {
                    off_nei_v += 8;
                    if (off_nei_v + 7 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
            _mm256_store_si256((__m256i *) cn_countv, sse_cn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    } else {
        if (off_nei_u + 1 < off_u_end && off_nei_v + 3 < off_v_end) {
            __m256i u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
            __m256i u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
            __m256i v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements_per, v_elements_per);
                mask = _mm256_and_si256(sse_countplus, mask);
                sse_cn_countv = _mm256_add_epi32(sse_cn_countv, mask);

                if (g->edge_dst[off_nei_u + 1] == g->edge_dst[off_nei_v + 3]) {
                    off_nei_u += 2;
                    off_nei_v += 4;
                    if (off_nei_u + 1 >= off_u_end || off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else if (g->edge_dst[off_nei_u + 1] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else {
                    off_nei_u += 2;
                    if (off_nei_u + 1 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                }
            }
        }
        _mm256_store_si256((__m256i *) cn_countv, sse_cn_countv);
        for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNAVX2PopCnt(Graph *g, int u, int v) {

    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    auto cn_count = 0;
    __m256i per_u_order = _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0);
    __m256i per_v_order = _mm256_set_epi32(3, 2, 1, 0, 3, 2, 1, 0);

    auto size_ratio = (off_v_end - off_nei_v) / (off_u_end - off_nei_u);
    if (size_ratio > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 7 < off_v_end) {
            __m256i u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements, v_elements);
                cn_count += _popcnt32(_mm256_movemask_epi8(mask)) >> 2;
                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 7]) {
                    off_nei_v += 8;
                    if (off_nei_v + 7 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
        }
    } else {
        if (off_nei_u + 1 < off_u_end && off_nei_v + 3 < off_v_end) {
            __m256i u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
            __m256i u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
            __m256i v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
            __m256i v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);

            while (true) {
                __m256i mask = _mm256_cmpeq_epi32(u_elements_per, v_elements_per);
                cn_count += _popcnt32(_mm256_movemask_epi8(mask)) >> 2;

                if (g->edge_dst[off_nei_u + 1] == g->edge_dst[off_nei_v + 3]) {
                    off_nei_u += 2;
                    off_nei_v += 4;
                    if (off_nei_u + 1 >= off_u_end || off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else if (g->edge_dst[off_nei_u + 1] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm256_permutevar8x32_epi32(v_elements, per_v_order);
                } else {
                    off_nei_u += 2;
                    if (off_nei_u + 1 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm256_loadu_si256((__m256i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm256_permutevar8x32_epi32(u_elements, per_u_order);
                }
            }
        }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNPivotAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v, uint32_t off_v_end) {
    auto cn_count = 0;

    while (true) {
        // avx2, out_edges[off_nei_v] as the pivot
        __m256i pivot_u = _mm256_set1_epi32(g->edge_dst[off_nei_v]);
        while (off_nei_u + 7 < off_u_end) {
            __m256i inspected_ele = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&g->edge_dst[off_nei_u]));
            __m256i cmp_res = _mm256_cmpgt_epi32(pivot_u, inspected_ele);
            auto mask = _mm256_movemask_epi8(cmp_res);
            auto count = mask == 0xffffffff ? 8 : _popcnt32(mask) >> 2;
            // update off_nei_u and du
            off_nei_u += count;

            if (count < 8) {
                break;
            }
        }
        if (off_nei_u + 7 >= off_u_end) {
            break;
        }

        // avx2, out_edges[off_nei_u] as the pivot
        __m256i pivot_v = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
        while (off_nei_v + 7 < off_v_end) {
            __m256i inspected_ele = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&g->edge_dst[off_nei_v]));
            __m256i cmp_res = _mm256_cmpgt_epi32(pivot_v, inspected_ele);
            auto mask = _mm256_movemask_epi8(cmp_res);
            auto count = mask == 0xffffffff ? 8 : _popcnt32(mask) >> 2;

            // update off_nei_u and du
            off_nei_v += count;
            if (count < 8) {
                break;
            }
        }
        if (off_nei_v + 7 >= off_v_end) {
            break;
        }

        // find possible equality
        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            ++cn_count;
            ++off_nei_u;
            ++off_nei_v;
        }
    }

    if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
            ++off_nei_v;
            if (off_nei_v >= off_v_end) {
                return cn_count;
            }
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNPivotAVX2(Graph *g, int u, int v) {


    auto cn_count = 0;
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    while (true) {
        // avx2, out_edges[off_nei_v] as the pivot
        __m256i pivot_u = _mm256_set1_epi32(g->edge_dst[off_nei_v]);
        while (off_nei_u + 7 < g->node_off[u + 1]) {
            __m256i inspected_ele = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&g->edge_dst[off_nei_u]));
            __m256i cmp_res = _mm256_cmpgt_epi32(pivot_u, inspected_ele);
            auto mask = _mm256_movemask_epi8(cmp_res);
            auto count = mask == 0xffffffff ? 8 : _popcnt32(mask) >> 2;
            // update off_nei_u and du
            off_nei_u += count;

            if (count < 8) {
                break;
            }
        }
        if (off_nei_u + 7 >= g->node_off[u + 1]) {
            break;
        }

        // avx2, out_edges[off_nei_u] as the pivot
        __m256i pivot_v = _mm256_set1_epi32(g->edge_dst[off_nei_u]);
        while (off_nei_v + 7 < g->node_off[v + 1]) {
            __m256i inspected_ele = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&g->edge_dst[off_nei_v]));
            __m256i cmp_res = _mm256_cmpgt_epi32(pivot_v, inspected_ele);
            auto mask = _mm256_movemask_epi8(cmp_res);
            auto count = mask == 0xffffffff ? 8 : _popcnt32(mask) >> 2;

            // update off_nei_u and du
            off_nei_v += count;
            if (count < 8) {
                break;
            }
        }
        if (off_nei_v + 7 >= g->node_off[v + 1]) {
            break;
        }

        // find possible equality
        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            ++cn_count;
            ++off_nei_u;
            ++off_nei_v;
        }
    }

    if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
            ++off_nei_v;
            if (off_nei_v >= off_v_end) {
                return cn_count;
            }
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

uint32_t BinarySearchForGallopingSearchAVX2(const int *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    while (offset_end - offset_beg >= 16) {
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

    // linear search fallback, be careful with operator>> and operation+ priority
    __m256i pivot_element = _mm256_set1_epi32(val);
    for (; offset_beg + 7 < offset_end; offset_beg += 8) {
        __m256i elements = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(array + offset_beg));
        __m256i cmp_res = _mm256_cmpgt_epi32(pivot_element, elements);
        int mask = _mm256_movemask_epi8(cmp_res);
        if (mask != 0xffffffff) {
            return offset_beg + (_popcnt32(mask) >> 2);
        }
    }
    if (offset_beg < offset_end) {
        auto left_size = offset_end - offset_beg;
        __m256i elements = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(array + offset_beg));
        __m256i cmp_res = _mm256_cmpgt_epi32(pivot_element, elements);
        int mask = _mm256_movemask_epi8(cmp_res);
        int cmp_mask = 0xffffffff >> ((8 - left_size) << 2);
        mask &= cmp_mask;
        if (mask != cmp_mask) { return offset_beg + (_popcnt32(mask) >> 2); }
    }
    return offset_end;
}

// Assuming size > 0
uint32_t GallopingSearchAVX2(int *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    if (array[offset_end - 1] < val) {
        return offset_end;
    }

    // linear search
    __m256i pivot_element = _mm256_set1_epi32(val);
    if (offset_end - offset_beg >= 8) {
        __m256i elements = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(array + offset_beg));
        __m256i cmp_res = _mm256_cmpgt_epi32(pivot_element, elements);
        int mask = _mm256_movemask_epi8(cmp_res);
        if (mask != 0xffffffff) { return offset_beg + (_popcnt32(mask) >> 2); }
    } else {
        auto left_size = offset_end - offset_beg;
        __m256i elements = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(array + offset_beg));
        __m256i cmp_res = _mm256_cmpgt_epi32(pivot_element, elements);
        int mask = _mm256_movemask_epi8(cmp_res);
        int cmp_mask = 0xffffffff >> ((8 - left_size) << 2);
        mask &= cmp_mask;
        if (mask != cmp_mask) { return offset_beg + (_popcnt32(mask) >> 2); }
    }

    // galloping, should add pre-fetch later
    auto jump_idx = 8u;
    while (true) {
        auto peek_idx = offset_beg + jump_idx;
        if (peek_idx >= offset_end) {
            return BinarySearchForGallopingSearchAVX2(array, (jump_idx >> 1) + offset_beg + 1, offset_end, val);
        }
        if (array[peek_idx] < val) {
            jump_idx <<= 1;
        } else {
            return array[peek_idx] == val ? peek_idx :
                   BinarySearchForGallopingSearchAVX2(array, (jump_idx >> 1) + offset_beg + 1, peek_idx + 1, val);
        }
    }
}

int ComputeCNGallopingSingleDirAVX2(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                                    uint32_t off_v_end) {
    auto cn_count = 0;
    if (off_u_end - off_nei_u > off_v_end - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(off_u_end, off_v_end);
    }
    // Handle degree is zero.
    if (off_nei_u >= off_u_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        off_nei_v = GallopingSearchAVX2(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNGallopingSingleDirAVX2(Graph *g, int u, int v) {

    auto cn_count = 0;
    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        off_nei_v = GallopingSearchAVX2(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNGallopingDoubleDirAVX2(Graph *g, int u, int v) {

    auto cn_count = 0;
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];
    while (true) {
        off_nei_u = GallopingSearchAVX2(g->edge_dst, off_nei_u, off_u_end, g->edge_dst[off_nei_v]);
        if (off_nei_u >= off_u_end) {
            return cn_count;
        }

        off_nei_v = GallopingSearchAVX2(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

#endif

int ComputeCNSSE4(Graph *g, int u, int v) {

    if (g->degree[u] > g->degree[v]) {
        auto tmp = u;
        u = v;
        v = tmp;
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    constexpr int parallelism = 4;
    auto cn_count = 0;
    int cn_countv[parallelism] = {0, 0, 0, 0};
    __m128i sse_cn_countv = _mm_load_si128((__m128i *) (cn_countv));
    __m128i sse_countplus = _mm_set1_epi32(1);
    const int per_u_order = 0b01010000;
    const int per_v_order = 0b01000100;

    auto size_ratio = (off_v_end - off_nei_v) / (off_u_end - off_nei_u);
    if (size_ratio > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 3 < off_v_end) {
            __m128i u_elements = _mm_set1_epi32(g->edge_dst[off_nei_u]);
            __m128i v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));

            while (true) {
                __m128i mask = _mm_cmpeq_epi32(u_elements, v_elements);
                mask = _mm_and_si128(sse_countplus, mask);
                sse_cn_countv = _mm_add_epi32(sse_cn_countv, mask);
                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
            _mm_store_si128((__m128i *) cn_countv, sse_cn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    } else {
        if (off_nei_u + 1 < off_u_end && off_nei_v + 1 < off_v_end) {
            __m128i u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
            __m128i u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
            __m128i v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
            __m128i v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);

            while (true) {
                __m128i mask = _mm_cmpeq_epi32(u_elements_per, v_elements_per);
                mask = _mm_and_si128(sse_countplus, mask);
                sse_cn_countv = _mm_add_epi32(sse_cn_countv, mask);

                if (g->edge_dst[off_nei_u + 1] == g->edge_dst[off_nei_v + 1]) {
                    off_nei_u += 2;
                    off_nei_v += 2;
                    if (off_nei_u + 1 >= off_u_end || off_nei_v + 1 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
                } else if (g->edge_dst[off_nei_u + 1] > g->edge_dst[off_nei_v + 1]) {
                    off_nei_v += 2;
                    if (off_nei_v + 1 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
                } else {
                    off_nei_u += 2;
                    if (off_nei_u + 1 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
                }
            }
        }
        _mm_store_si128((__m128i *) cn_countv, sse_cn_countv);
        for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

int ComputeCNSSE4(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                  uint32_t off_v_end) {
    if (off_u_end - off_nei_u > off_v_end - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(off_u_end, off_v_end);
    }

    constexpr int parallelism = 4;
    auto cn_count = 0;
    int cn_countv[parallelism] = {0, 0, 0, 0};
    __m128i sse_cn_countv = _mm_load_si128((__m128i *) (cn_countv));
    __m128i sse_countplus = _mm_set1_epi32(1);
    const int per_u_order = 0b01010000;
    const int per_v_order = 0b01000100;

    auto size_ratio = (off_v_end - off_nei_v + 1) / (off_u_end - off_nei_u + 1);
    if (size_ratio > 2) {
        if (off_nei_u < off_u_end && off_nei_v + 3 < off_v_end) {
            __m128i u_elements = _mm_set1_epi32(g->edge_dst[off_nei_u]);
            __m128i v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));

            while (true) {
                __m128i mask = _mm_cmpeq_epi32(u_elements, v_elements);
                mask = _mm_and_si128(sse_countplus, mask);
                sse_cn_countv = _mm_add_epi32(sse_cn_countv, mask);
                if (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v + 3]) {
                    off_nei_v += 4;
                    if (off_nei_v + 3 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                } else {
                    off_nei_u++;
                    if (off_nei_u >= off_u_end) {
                        break;
                    }
                    u_elements = _mm_set1_epi32(g->edge_dst[off_nei_u]);
                }
            }
            _mm_store_si128((__m128i *) cn_countv, sse_cn_countv);
            for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
        }
    } else {
        if (off_nei_u + 1 < off_u_end && off_nei_v + 1 < off_v_end) {
            __m128i u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
            __m128i u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
            __m128i v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
            __m128i v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);

            while (true) {
                __m128i mask = _mm_cmpeq_epi32(u_elements_per, v_elements_per);
                mask = _mm_and_si128(sse_countplus, mask);
                sse_cn_countv = _mm_add_epi32(sse_cn_countv, mask);

                if (g->edge_dst[off_nei_u + 1] == g->edge_dst[off_nei_v + 1]) {
                    off_nei_u += 2;
                    off_nei_v += 2;
                    if (off_nei_u + 1 >= off_u_end || off_nei_v + 1 >= off_v_end) {
                        break;
                    }
                    u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
                } else if (g->edge_dst[off_nei_u + 1] > g->edge_dst[off_nei_v + 1]) {
                    off_nei_v += 2;
                    if (off_nei_v + 1 >= off_v_end) {
                        break;
                    }
                    v_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_v));
                    v_elements_per = _mm_shuffle_epi32(v_elements, per_v_order);
                } else {
                    off_nei_u += 2;
                    if (off_nei_u + 1 >= off_u_end) {
                        break;
                    }
                    u_elements = _mm_loadu_si128((__m128i *) (g->edge_dst + off_nei_u));
                    u_elements_per = _mm_shuffle_epi32(u_elements, per_u_order);
                }
            }
        }
        _mm_store_si128((__m128i *) cn_countv, sse_cn_countv);
        for (int cn_countvplus : cn_countv) { cn_count += cn_countvplus; }
    }

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
                ++off_nei_u;
                if (off_nei_u >= off_u_end) {
                    return cn_count;
                }
            }
            while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
                ++off_nei_v;
                if (off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
            if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
                cn_count++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    return cn_count;
                }
            }
        }
    }
    return cn_count;
}

uint32_t LowerBoundSSE(const int *array, uint32_t offset_beg, uint32_t offset_end, int val) {
    constexpr int parallelism = 4;
    uint32_t blk_beg = 0;
    uint32_t blk_end = (offset_end - offset_beg) / parallelism;
    while (blk_end - blk_beg > 0) {
        uint32_t blk_mid = (blk_end + blk_beg) / 2;
        // 1st: full cmp
        __m128i elements = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(array + offset_beg + blk_mid * parallelism));
        __m128i pivots = _mm_set1_epi32(val);
        __m128i res = _mm_cmplt_epi32(elements, pivots);
        int mask = _mm_movemask_epi8(res);
        // case 1: all <
        if (mask == 0xffff) {
            blk_beg = blk_mid + 1;
        } else {
            blk_end = blk_mid;
        }
    }

    // linear search fallback
    for (auto offset = offset_beg + blk_end * parallelism;
         offset < min(offset_end, offset_beg + blk_end * parallelism + parallelism); offset++) {
        if (array[offset] >= val) {
            return offset;
        }
    }
    return offset_end;
}

int ComputeCNLowerBoundSSE(Graph *g, int u, int v) {
    auto cn_count = 0;
    if (g->degree[u] > g->degree[v]) {
        swap(u, v);
    }
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        off_nei_v = LowerBoundSSE(g->edge_dst, off_nei_v, off_v_end, g->edge_dst[off_nei_u]);
        if (off_nei_v >= off_v_end) {
            return cn_count;
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

// not useful, even slower
int ComputeCNPivotSSE4(Graph *g, int u, int v) {
    auto cn_count = 0;
    auto off_nei_u = g->node_off[u], off_nei_v = g->node_off[v];
    auto off_u_end = g->node_off[u + 1], off_v_end = g->node_off[v + 1];

    while (true) {
        // avx2, out_edges[off_nei_v] as the pivot
        __m128i pivot_u = _mm_set1_epi32(g->edge_dst[off_nei_v]);
        while (off_nei_u + 3 < g->node_off[u + 1]) {
            __m128i inspected_ele = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&g->edge_dst[off_nei_u]));
            __m128i cmp_res = _mm_cmpgt_epi32(pivot_u, inspected_ele);
            auto mask = _mm_movemask_epi8(cmp_res);
            auto count = mask == 0xffff ? 4 : _popcnt32(mask) >> 2;
            // update off_nei_u and du
            off_nei_u += count;

            if (count < 4) {
                break;
            }
        }
        if (off_nei_u + 3 >= g->node_off[u + 1]) {
            break;
        }

        // avx2, out_edges[off_nei_u] as the pivot
        __m128i pivot_v = _mm_set1_epi32(g->edge_dst[off_nei_u]);
        while (off_nei_v + 3 < g->node_off[v + 1]) {
            __m128i inspected_ele = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&g->edge_dst[off_nei_v]));
            __m128i cmp_res = _mm_cmpgt_epi32(pivot_v, inspected_ele);
            auto mask = _mm_movemask_epi8(cmp_res);
            auto count = mask == 0xffff ? 4 : _popcnt32(mask) >> 2;

            // update off_nei_u and du
            off_nei_v += count;
            if (count < 4) {
                break;
            }
        }
        if (off_nei_v + 3 >= g->node_off[v + 1]) {
            break;
        }

        // find possible equality
        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            ++cn_count;
            ++off_nei_u;
            ++off_nei_v;
        }
    }

    if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
            ++off_nei_v;
            if (off_nei_v >= off_v_end) {
                return cn_count;
            }
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}

int ComputeCNPivotSSE4(Graph *g, uint32_t off_nei_u, uint32_t off_u_end, uint32_t off_nei_v,
                       uint32_t off_v_end) {
    auto cn_count = 0;
    if (off_u_end - off_nei_u > off_v_end - off_nei_v) {
        swap(off_nei_u, off_nei_v);
        swap(off_u_end, off_v_end);
    }

    while (true) {
        // avx2, out_edges[off_nei_v] as the pivot
        __m128i pivot_u = _mm_set1_epi32(g->edge_dst[off_nei_v]);
        while (off_nei_u + 3 < off_u_end) {
            __m128i inspected_ele = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&g->edge_dst[off_nei_u]));
            __m128i cmp_res = _mm_cmpgt_epi32(pivot_u, inspected_ele);
            auto mask = _mm_movemask_epi8(cmp_res);
            auto count = mask == 0xffff ? 4 : _popcnt32(mask) >> 2;
            // update off_nei_u and du
            off_nei_u += count;

            if (count < 4) {
                break;
            }
        }
        if (off_nei_u + 3 >= off_u_end) {
            break;
        }

        // avx2, out_edges[off_nei_u] as the pivot
        __m128i pivot_v = _mm_set1_epi32(g->edge_dst[off_nei_u]);
        while (off_nei_v + 3 < off_v_end) {
            __m128i inspected_ele = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&g->edge_dst[off_nei_v]));
            __m128i cmp_res = _mm_cmpgt_epi32(pivot_v, inspected_ele);
            auto mask = _mm_movemask_epi8(cmp_res);
            auto count = mask == 0xffff ? 4 : _popcnt32(mask) >> 2;

            // update off_nei_u and du
            off_nei_v += count;
            if (count < 4) {
                break;
            }
        }
        if (off_nei_v + 3 >= off_v_end) {
            break;
        }

        // find possible equality
        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            ++cn_count;
            ++off_nei_u;
            ++off_nei_v;
        }
    }

    if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
        return cn_count;
    }
    while (true) {
        while (g->edge_dst[off_nei_u] < g->edge_dst[off_nei_v]) {
            ++off_nei_u;
            if (off_nei_u >= off_u_end) {
                return cn_count;
            }
        }

        while (g->edge_dst[off_nei_u] > g->edge_dst[off_nei_v]) {
            ++off_nei_v;
            if (off_nei_v >= off_v_end) {
                return cn_count;
            }
        }

        if (g->edge_dst[off_nei_u] == g->edge_dst[off_nei_v]) {
            cn_count++;
            ++off_nei_u;
            ++off_nei_v;
            if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                return cn_count;
            }
        }
    }
}