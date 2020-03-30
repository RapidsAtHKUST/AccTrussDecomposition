#pragma once

#include <vector>
#include <cstdint>

#include <omp.h>
#ifndef CACHE_LINE_ENTRY
#define CACHE_LINE_ENTRY (16)
#endif

using namespace std;

/*
 * Both Primitives Are Inclusive
 * histogram is for cache-aware thread-local histogram purpose
 * output should be different from the variables captured in function object f
 * size is the original size for the flagged prefix sum
 */

template<typename F>
void FlagPrefixSumOMP(vector<uint32_t> &histogram, uint32_t *output, size_t size, F f, int omp_num_threads) {
    static thread_local int tid = omp_get_thread_num();
    // 1st Pass: Histogram.
    auto avg = size / omp_num_threads;
    auto it_beg = avg * tid;
    auto histogram_idx = (tid + 1) * CACHE_LINE_ENTRY;
    histogram[histogram_idx] = 0;
    auto it_end = tid == omp_num_threads - 1 ? size : avg * (tid + 1);
    auto prev = 0u;
    for (auto it = it_beg; it < it_end; it++) {
        if (f(it)) {
            histogram[histogram_idx]++;
            output[it] = prev + 1;
        } else {
            output[it] = prev;
        }
        prev = output[it];
    }
#pragma omp barrier

    // 2nd Pass: single-prefix-sum & Add previous sum.
#pragma omp single
    {
        for (auto tid = 0; tid < omp_num_threads; tid++) {
            auto histogram_idx = (tid + 1) * CACHE_LINE_ENTRY;
            auto prev_histogram_idx = (tid) * CACHE_LINE_ENTRY;
            histogram[histogram_idx] += histogram[prev_histogram_idx];
        }
    }
    {
        auto prev_sum = histogram[tid * CACHE_LINE_ENTRY];
        for (auto it = it_beg; it < it_end; it++) {
            output[it] += prev_sum;
        }
#pragma omp barrier
    }
}

template<typename F>
void InclusivePrefixSumOMP(vector<uint32_t> &histogram, uint32_t *output, size_t size, F f, int omp_num_threads) {
    static thread_local int tid = omp_get_thread_num();
    // 1st Pass: Histogram.
    auto avg = size / omp_num_threads;
    auto it_beg = avg * tid;
    auto histogram_idx = (tid + 1) * CACHE_LINE_ENTRY;
    histogram[histogram_idx] = 0;
    auto it_end = tid == omp_num_threads - 1 ? size : avg * (tid + 1);
    auto prev = 0u;
    for (auto it = it_beg; it < it_end; it++) {
        auto value = f(it);
        histogram[histogram_idx] += value;
        prev += value;
        output[it] = prev;
    }
#pragma omp barrier

    // 2nd Pass: single-prefix-sum & Add previous sum.
#pragma omp single
    {
        for (auto tid = 0; tid < omp_num_threads; tid++) {
            auto histogram_idx = (tid + 1) * CACHE_LINE_ENTRY;
            auto prev_histogram_idx = (tid) * CACHE_LINE_ENTRY;
            histogram[histogram_idx] += histogram[prev_histogram_idx];
        }
    }
    {
        auto prev_sum = histogram[tid * CACHE_LINE_ENTRY];
        for (auto it = it_beg; it < it_end; it++) {
            output[it] += prev_sum;
        }
#pragma omp barrier
    }
}