#include <climits>
#include <cassert>

#include <chrono>
#include <sstream>
#include <fstream>

#include <omp.h>

#include "util/graph/graph.h"
#include "../util/util.h"
#include "util/log/log.h"
#include "util/serialization/pretty_print.h"
#include "../util/timer.h"
#include "../util/md5.h"
#include "opt_pkt/parallel_all_edge_cnc.h"
#include "../reordering_utils/reorder_utils.h"

using namespace std::chrono;

void read_env() {
    extern int NUM_THREADS;
    NUM_THREADS = omp_get_max_threads();
    log_info("NUM_PROCS:     %d", omp_get_num_procs());
    log_info("NUM_THREADS:   %d", NUM_THREADS);
}

void display_stats(int *EdgeSupport, long numEdges, string output_folder) {
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
    log_info("Total #Edges: %s", FormatWithCommas(numEdges).c_str());
    log_info("Min-truss: %d； #Edges in Min-truss: %s", minSup + 2, FormatWithCommas(numEdgesWithMinSup).c_str());
    log_info("Max-truss: %d; #Edges in Max-truss: %s", maxSup + 2, FormatWithCommas(numEdgesWithMaxSup).c_str());
}

void PKT_intersection(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge);

void PKT_marking(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge);

void Ros(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge);

void WCJames(graph_t *g, int *EdgeSupport, MapType &edgeToIdMap, Edge *edgeIdToEdge);

void PKT_serial_marking(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge);

void PKT_serial_intersection(graph_t *g, int *EdgeSupport, Edge *edgeIdToEdge);

int main(int argc, char *argv[]) {
    setlocale(LC_NUMERIC, "");
    if (argc < 2) {
        fprintf(stderr, "%s <Graph file>\n", argv[0]);
        exit(1);
    }

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

    //set log file descriptor
#ifdef USE_LOG
    FILE *log_f = nullptr;
    if (argc >= 4) {
        log_f = fopen(argv[3], "a+");
        log_set_fp(log_f);
    }
#endif

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
#if defined(PKT_SERIAL_INTER)
    PKT_serial_intersection(&g, EdgeSupport, edgeIdToEdge);
#elif defined(PKT_SERIAL_MARK)
    PKT_serial_marking(&g, EdgeSupport, edgeIdToEdge);
#elif defined(PKT_INTER)
    PKT_intersection(&g, EdgeSupport, edgeIdToEdge);
#elif defined(PKT_MARK)
    PKT_marking(&g, EdgeSupport, edgeIdToEdge);
#elif defined(ROS)
    Ros(&g, EdgeSupport, edgeIdToEdge);
#elif defined(WC)
    auto edgeToIdMap = Convert(&g, edgeIdToEdge, (g.m / 2));
    log_info("Hash Map Construction: %.9lfs", global_timer.elapsed());
    global_timer.reset();
    WCJames(&g, EdgeSupport, edgeToIdMap, edgeIdToEdge);
#endif
    log_info("Parallel K-Truss: %.9lfs", global_timer.elapsed());

    auto output_dir = string(argv[1]) + "/" + string("ktruss-") + algorithm_name + ".histogram";
    log_info("Output Dir: %s", output_dir.c_str());
    display_stats(EdgeSupport, g.m / 2, output_dir);
    if (g.m < 40) {
        stringstream ss;
        ss << pretty_print_array(EdgeSupport, g.m / 2);
        log_info("Edge Support Array: %s", ss.str().c_str());
    }

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
