#include <cassert>

#include <chrono>

#include <omp.h>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/timer.h"
#include "opt_pkt/parallel_all_edge_cnc.h"
#include "reordering_utils/reorder_utils.h"
#include "opt_pkt/main_helper.h"
#include "util/program_options/popl.h"

#include "opt_pkt/extern_variables.h"

int main(int argc, char *argv[]) {
    setlocale(LC_NUMERIC, "");
    if (argc < 2) {
        fprintf(stderr, "%s <Graph file>\n", argv[0]);
        exit(1);
    }

#ifdef USE_LOG
    FILE *log_f = nullptr;
    if (argc >= 4) {
        log_f = fopen(argv[3], "a+");
        log_set_fp(log_f);
    }
#endif
    string algorithm_name;
    string cmd(argv[0]);
    auto pos = cmd.find_last_of('/');
    if (pos != string::npos) {
        algorithm_name = cmd.substr(pos + 1, cmd.size());
    } else {
        algorithm_name = cmd;
    }
    log_info("Algorithm name: %s", algorithm_name.c_str());
    read_env();

    graph_t g;

    //load the graph from file
    Graph yche_graph(argv[1]);
    g.adj = yche_graph.edge_dst;
    g.num_edges = yche_graph.node_off;
    g.n = yche_graph.nodemax;
    g.m = yche_graph.edgemax;

    string reorder_method(argv[2]);

    vector<int32_t> new_vid_dict;
    vector<int32_t> old_vid_dict;
    ReorderWrapper(g, argv[1], reorder_method, new_vid_dict, old_vid_dict);

    if (argc >= 5) {
        // see https://github.com/badaix/popl
        using namespace popl;
        OptionParser op("Allowed options");
        op.add<Value<int>>("g", "gt", "graph compaction threshold",
                           graph_compaction_threshold, &graph_compaction_threshold);
        op.add<Value<double>>("e", "ept", "estimate process throughput", estimated_process_throughput,
                              &estimated_process_throughput);
        op.add<Value<int>>("r", "rs", "range size", range_size, &range_size);
        op.parse(argc, argv);
        log_info("gt: %d, ept: %.3lf, rs: %d", graph_compaction_threshold, estimated_process_throughput, range_size);
    }

    /************   Compute k - truss *****************************************/
    //edge list array
    Timer get_eid_timer;

    Edge *edgeIdToEdge = (Edge *) malloc((g.m / 2) * sizeof(Edge));
    assert(edgeIdToEdge != nullptr);
    log_info("Malloc Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();

    //Populate the edge list array
    getEidAndEdgeList(&g, edgeIdToEdge);
    log_info("Init Eid Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();
#ifdef EID_TEST
    exit(-1);
#ifdef USE_LOG
    if (log_f != nullptr) {
        log_info("Flush File and Close...");
        fflush(log_f);
        fclose(log_f);
    }
#endif
#endif
    int *EdgeSupport = (int *) malloc(g.m / 2 * sizeof(int));
    assert(EdgeSupport != nullptr);

    auto max_omp_threads = omp_get_max_threads();
    log_info("Max Threads: %d", max_omp_threads);
#pragma omp parallel for
    for (auto i = 0; i < max_omp_threads; i++) {
        auto avg = g.m / 2 / max_omp_threads;
        auto iter_beg = avg * i;
        auto iter_end = (i == max_omp_threads - 1) ? g.m / 2 : avg * (i + 1);
        memset(EdgeSupport + iter_beg, 0, (iter_end - iter_beg) * sizeof(int));
    }
    log_info("Init EdgeSupport Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();

    Timer global_timer;
#if defined(PKT_INTER)
    PKT_intersection(&g, EdgeSupport, edgeIdToEdge);
#elif defined(PKT_MARK)
    PKT_marking(&g, EdgeSupport, edgeIdToEdge);
#else
    log_fatal("No algorithm");
    exit(-1);
#endif
    log_info("Parallel K-Truss: %.9lfs", global_timer.elapsed());

    auto output_dir = string(argv[1]) + "/" + string("ktruss-") + algorithm_name + ".histogram";
    log_info("Output Dir: %s", output_dir.c_str());
    display_stats(EdgeSupport, g.m / 2, output_dir);
#ifdef PAPER_FIGURE
    if (g.m < 40) {
        stringstream ss;
        ss << pretty_print_array(EdgeSupport, g.m / 2);
        vector<pair<pair<int, int>, int>> edge_list;
        for (auto i = 0; i < g.m / 2; i++) {
            edge_list.emplace_back(make_pair(edgeIdToEdge[i].u, edgeIdToEdge[i].v), EdgeSupport[i]);
        }
        ss << edge_list;
        log_info("Edge Support Array: %s", ss.str().c_str());
    }
#endif

    //Free memory
    free_graph(&g);
    free(edgeIdToEdge);
    free(EdgeSupport);

#ifdef USE_LOG
    if (log_f != nullptr) {
        log_info("Flush File and Close...");
        fflush(log_f);
        fclose(log_f);
    }
#endif
    return 0;
}
