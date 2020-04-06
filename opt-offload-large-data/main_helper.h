#pragma once

#include <climits>
#include <cassert>

#include <chrono>
#include <sstream>
#include <fstream>

#include <omp.h>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/serialization/pretty_print.h"
#include "util/timer.h"
#include "util/md5.h"
#include "util/cuda/cuda_util.h"

#include "util/histogram.h"

#include "main_helper.h"

#define MAX_LEVEL  (20000)

inline void CheckLevelOff(eid_t *level_start_pos) {
    auto last = MAX_LEVEL - 1;
    while (level_start_pos[last] == 0)last--;
    vector<int32_t> histogram;
    for (auto i = 1; i < last + 1; i++) {
        histogram.emplace_back(level_start_pos[i] - level_start_pos[i - 1]);
    }
#ifdef YCHE_DEBUG
    log_info("Levels: %zu", histogram.size());
#endif

    stringstream ss;
    ss << histogram;
#ifdef YCHE_DEBUG
    log_info("Histogram: %s", ss.str().c_str());
#endif
    stringstream ss2;
    ss2 << ss.str() << "\n";
    log_info("Checking Level Off, Md5sum of histogram: %s", md5(ss2.str()).c_str());
}

inline void read_env() {
    extern int NUM_THREADS;
    NUM_THREADS = omp_get_max_threads();
    log_info("NUM_PROCS:     %d", omp_get_num_procs());
    log_info("NUM_THREADS:   %d", NUM_THREADS);
}

inline void display_stats(int *EdgeSupport, long numEdges, string output_folder) {
    auto res = core_val_histogram(numEdges, EdgeSupport, true);
    ofstream ofs(output_folder);
    ofs << res << endl;
    {
        stringstream ss;
        ss << res << "\n";
        log_info("Md5sum of histogram: %s", md5(ss.str()).c_str());
    }

    int minSup = INT_MAX;
    int maxSup = 0;

    for (long i = 0; i < numEdges; i++) {
        if (minSup > EdgeSupport[i]) {
            minSup = EdgeSupport[i];
        }

        if (maxSup < EdgeSupport[i]) {
            maxSup = EdgeSupport[i];
        }
    }

    long numEdgesWithMinSup = 0, numEdgesWithMaxSup = 0;

    for (long i = 0; i < numEdges; i++) {
        if (EdgeSupport[i] == minSup) {
            numEdgesWithMinSup++;
        }

        if (EdgeSupport[i] == maxSup) {
            numEdgesWithMaxSup++;
        }
    }
    log_info("Total #Edges: %'lld", numEdges);
    log_info("Min-truss: %d； #Edges in Min-truss: %'lld", minSup + 2, numEdgesWithMinSup);
    log_info("Max-truss: %d; #Edges in Max-truss: %'lld", maxSup + 2, numEdgesWithMaxSup);
}

void PKT_cuda(graph_t *g, eid_t *edge_off_origin_cpu, int *&EdgeSupport, Edge *edgeIdToEdge, int shrink_factor,
              int *output, eid_t *level_start_pos, ZLCUDAMemStat *mem_stat, ZLCUDATimer *time_stat, int level);