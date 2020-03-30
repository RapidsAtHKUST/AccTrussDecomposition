```cpp

#ifdef __AVX2__
int intersect_shuffle_uint_vec256(int *set_a, int size_a,
            int *set_b, int size_b, int *set_c);
#endif
```

```cpp

#ifdef __AVX2__

int intersect_shuffle_uint_vec256(int *set_a, int size_a,
        int *set_b, int size_b, int *set_c)
{
    int i = 0, j = 0, size_c = 0;
    int qs_a = size_a - (size_a & 7);
    int qs_b = size_b - (size_b & 7);

    while (i < qs_a && j < qs_b) {
        __m256i v_a = _mm256_load_si256((__m256i*)(set_a + i));
        __m256i v_b = _mm256_load_si256((__m256i*)(set_b + j));

        int a_max = set_a[i + 7];
        int b_max = set_b[j + 7];
        if (a_max == b_max) {
            i += 8;
            j += 8;
            _mm_prefetch((char*) (set_a + i), _MM_HINT_NTA);
            _mm_prefetch((char*) (set_b + j), _MM_HINT_NTA);
        } else if (a_max < b_max) {
            i += 8;
            _mm_prefetch((char*) (set_a + i), _MM_HINT_NTA);
        } else {
            j += 8;
            _mm_prefetch((char*) (set_b + j), _MM_HINT_NTA);
        }

        __m256i cmp_mask1 = _mm256_cmpeq_epi32(v_a, v_b);
        __m256 rot1 = _mm256_permute_ps((__m256)v_b, cyclic_shift1);
        __m256i cmp_mask2 = _mm256_cmpeq_epi32(v_a, (__m256i)rot1);
        __m256 rot2 = _mm256_permute_ps((__m256)v_b, cyclic_shift2);
        __m256i cmp_mask3 = _mm256_cmpeq_epi32(v_a, (__m256i)rot2);
        __m256 rot3 = _mm256_permute_ps((__m256)v_b, cyclic_shift3);
        __m256i cmp_mask4 = _mm256_cmpeq_epi32(v_a, (__m256i)rot3);

        __m256 rot4 = _mm256_permute2f128_ps((__m256)v_b, (__m256)v_b, 1);

        __m256i cmp_mask5 = _mm256_cmpeq_epi32(v_a, (__m256i)rot4);
        __m256 rot5 = _mm256_permute_ps(rot4, cyclic_shift1);
        __m256i cmp_mask6 = _mm256_cmpeq_epi32(v_a, (__m256i)rot5);
        __m256 rot6 = _mm256_permute_ps(rot4, cyclic_shift2);
        __m256i cmp_mask7 = _mm256_cmpeq_epi32(v_a, (__m256i)rot6);
        __m256 rot7 = _mm256_permute_ps(rot4, cyclic_shift3);
        __m256i cmp_mask8 = _mm256_cmpeq_epi32(v_a, (__m256i)rot7);

        __m256i cmp_mask = _mm256_or_si256(
            _mm256_or_si256(
                _mm256_or_si256(cmp_mask1, cmp_mask2),
                _mm256_or_si256(cmp_mask3, cmp_mask4)
            ),
            _mm256_or_si256(
                _mm256_or_si256(cmp_mask5, cmp_mask6),
                _mm256_or_si256(cmp_mask7, cmp_mask8)
            )
        );
        int mask = _mm256_movemask_ps((__m256)cmp_mask);

        __m256i idx = _mm256_load_si256((const __m256i*)&shuffle_mask_avx[mask*8]);
        __m256i p = _mm256_permutevar8x32_epi32(v_a, idx);
        _mm256_storeu_si256((__m256i*)(set_c + size_c), p);

        size_c += _mm_popcnt_u32(mask);

    }

    while (i < size_a && j < size_b) {
        if (set_a[i] == set_b[j]) {
            set_c[size_c++] = set_a[i];
            i++; j++;
        } else if (set_a[i] < set_b[j]) {
            i++;
        } else {
            j++;
        }
    }

    return size_c;
}
#endif

```