#include <climits>
#include <cassert>

#include <chrono>
#include <sstream>
#include <fstream>

#include <omp.h>

#include "util/graph/graph.h"
#include "util/util.h"
#include "util/log/log.h"
#include "util/serialization/pretty_print.h"
#include "util/timer.h"
#include "util/md5.h"
#include "parallel_all_edge_cnc.h"
#include "reordering_utils/reorder_utils.h"

inline void read_env() {
    extern int NUM_THREADS;
    NUM_THREADS = omp_get_max_threads();
    log_info("NUM_PROCS:     %d", omp_get_num_procs());
    log_info("NUM_THREADS:   %d", NUM_THREADS);
}

inline void display_stats(int *EdgeSupport, long numEdges, string output_folder) {
    auto res = core_val_histogram(numEdges, EdgeSupport, false);
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
    log_info("Total #Edges: %s", FormatWithCommas(numEdges).c_str());
    log_info("Min-truss: %d； #Edges in Min-truss: %s", minSup + 2, FormatWithCommas(numEdgesWithMinSup).c_str());
    log_info("Max-truss: %d; #Edges in Max-truss: %s", maxSup + 2, FormatWithCommas(numEdgesWithMaxSup).c_str());
}

void PKT_intersection(graph_t *g, int *&EdgeSupport, Edge *&edgeIdToEdge);