//
// Created by yche on 12/12/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <sstream>
#include <opt_pkt/main_helper.h>

#include "util/serialization/pretty_print.h"
#include "util/log/log.h"
#include "util/graph/graph.h"

//Make a small graph once 98% vertices have been processed
#define frac 0.98

using namespace std;

//Number of threads used
int PKC_NUM_THREADS = 1;

//typedef unsigned int vid_t;
typedef unsigned int eid_t;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s <Graph file>\n", argv[0]);
        exit(1);
    }

    read_env();

    graph_t g;
    Graph yche_graph(argv[1]);
    g.adj = yche_graph.edge_dst;
    g.num_edges = yche_graph.node_off;
    g.n = yche_graph.nodemax;
    g.m = yche_graph.edgemax;
    long n = g.n;

    //set log file descriptor
#ifdef USE_LOG
    FILE *log_f = nullptr;
    if (argc >= 3) {
        log_info("log path : %s", argv[2]);
        log_f = fopen(argv[2], "a+");
        log_set_fp(log_f);
    }

#endif

    /* Contains the core number for each vertex */
    int *core = (int *) malloc(n * sizeof(int));
    assert(core != NULL);

    log_info("Computing k-core decomposition ...");

    double start_time = 0;

    /* If the graph has at least 1000 vertices use PKC  */
    start_time = timer();
    PKC(&g, core, PKC_NUM_THREADS);
    auto histogram = core_val_histogram(g.n, core);
    stringstream ss;

    if (histogram.size() < 300) {
        ss << histogram;
        log_info("All: %s", ss.str().c_str());
    } else {
        ss << pretty_print_array(&histogram.front(), 300);
        log_info("Top 300: %s", ss.str().c_str());
    }
    {
        stringstream ss;
        ss << histogram << "\n";
        log_info("Md5sum of histogram: %s", md5(ss.str()).c_str());
    }

    string cmd = argv[0];
    string algorithm_name;
    auto pos = cmd.find_last_of('/');
    if (pos != string::npos) {
        algorithm_name = cmd.substr(pos + 1, cmd.size());
    } else {
        algorithm_name = cmd;
    }

    auto output_dir = string(argv[1]) + "/" + string("kcore-") + algorithm_name + ".histogram";
    log_info("Output Dir: %s", output_dir.c_str());
    ofstream ofs(output_dir);
    ofs << histogram << endl;
    log_info("PKC time: %9.3lf sec\n", timer() - start_time);
/*******************************************************************************************/
    free(core);
//    free_graph(&g);
    return 0;
}