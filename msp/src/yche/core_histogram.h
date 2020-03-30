#pragma once

#include <vector>
#include <sstream>

#include "log.h"
#include "pretty_print.h"
#include "util.h"

using namespace std;

template<typename T, typename F>
void core_val_histogram(int n, T &core, F f, bool is_print = false) {
    // core-value histogram
    int max_core_val = 0;
    vector<int32_t> histogram;
#pragma omp parallel
    {
#pragma omp for reduction(max:max_core_val)
        for (auto u = 0; u < n; u++) {
            max_core_val = max(max_core_val, f(core[u]));
        }
#pragma omp single
        {
            log_info("max value: %d", max_core_val);
            histogram = vector<int32_t>(max_core_val + 1, 0);
        }
#pragma omp for
        for (auto u = 0; u < n; u++) {
            auto core_val = f(core[u]);
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