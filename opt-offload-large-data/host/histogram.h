#pragma once

#include <sstream>

#include "util/pretty_print.h"

template<typename T>
vector<int32_t> core_val_histogram(int n, T &core, bool is_print = false) {
    Timer histogram_timer;
    // core-value histogram
    int max_core_val = 0;
    vector<int32_t> histogram;
#pragma omp parallel
    {
#pragma omp for reduction(max:max_core_val)
        for (auto u = 0; u < n; u++) {
            max_core_val = max(max_core_val, core[u]);
        }
#pragma omp single
        {
            log_info("max value: %d", max_core_val);
            histogram = vector<int32_t>(max_core_val + 1, 0);
        }
        vector<int32_t> local_histogram(histogram.size());

#pragma omp for
        for (auto u = 0; u < n; u++) {
            auto core_val = core[u];
            local_histogram[core_val]++;
        }

        // local_histogram[i] is immutable here.
        for (auto i = 0; i < local_histogram.size(); i++) {
#pragma omp atomic
            histogram[i] += local_histogram[i];
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
    log_info("Histogram Time: %.9lf s", histogram_timer.elapsed());

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
                log_info("bin[%d - %d]: %'lld", last, i, acc);
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
                log_info("bin[%d - %d]: %'lld", i, last, acc);
                last = i + 1;
                acc = 0;
            }
        }
    }
    log_info("total bin counts: %d", bin_cnt);
    return histogram;
}