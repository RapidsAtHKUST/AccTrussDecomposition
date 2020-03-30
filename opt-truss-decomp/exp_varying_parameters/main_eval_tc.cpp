#include <cassert>

#include <chrono>

#include <omp.h>

#include "util/graph/graph.h"
#include "util/log/log.h"
#include "util/stat.h"
#include "util/timer.h"

#include "opt_pkt/parallel_all_edge_cnc.h"
#include "reordering_utils/reorder_utils.h"
#include "opt_pkt/main_helper.h"

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

    /************   Compute k - truss *****************************************/
    //edge list array
    Timer get_eid_timer;
    Edge *edgeIdToEdge = (Edge *) malloc((g.m / 2) * sizeof(Edge));
    assert(edgeIdToEdge != nullptr);
    log_info("Malloc Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();

    //Populate the edge list array
    int old_env = omp_get_max_threads();
    log_info("n_t: %d", old_env);
    omp_set_num_threads(40);
    getEidAndEdgeList(&g, edgeIdToEdge);
    log_info("Init Eid Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();

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
    omp_set_num_threads(old_env);
    log_info("n_t: %d", omp_get_max_threads());

    // Baseline TC.
    Timer tc_timer;
    extern size_t tc_cnt;
#ifdef DTC
#pragma omp parallel
    {
        // Triangle-Counting With Packing Index.
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
        for (auto i = 0u; i < g.m; i++)
            ComputeSupport(&g, EdgeSupport, tc_cnt, i);
    }
#elif defined(WP)
    auto partition_id_lst = vector<vector<int >>(g.n);
    auto bitmap_in_partition_lst = vector<vector<bmp_word_type >>(g.n);
#pragma omp parallel
    {
        extern size_t packed_num;
        Timer timer;
        auto beg_mem = getValue();
#pragma omp single
        {
            log_info("Before TC... %lld, %lld", g.n, g.m);
            log_info("Before TC Memory: %'lld KB", g.n, g.m, getValue());
        }
        // Pre-Process: Indexing Words.
#pragma omp for schedule(dynamic, 100) reduction(+:packed_num)
        for (auto u = 0; u < g.n; u++) {
            PackVertex(&g, partition_id_lst, bitmap_in_partition_lst, u, packed_num);
        }
#pragma omp single
        {
            log_info("Packed#: %'zu", packed_num);
            log_info("PreProcess-BitmapOP Cost: %.9lf s, Memory Cost: %'lld KB", timer.elapsed(), getValue());
            log_info("Memory Overheads: %'lld KB", timer.elapsed(), getValue() - beg_mem);
        }
        // Triangle-Counting With Packing Index.
        auto bool_arr = BoolArray<bmp_word_type>(g.n);
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
        for (auto i = 0u; i < g.m; i++)
            ComputeSupportWithPack(&g, EdgeSupport, tc_cnt, i, bool_arr,
                                   partition_id_lst, bitmap_in_partition_lst);
    }

#else

#pragma omp parallel
    {
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
        for (auto i = 0u; i < g.m; i++) {
            ComputeSupportBaseLine(&g, EdgeSupport, tc_cnt, i);
        }
    }
#endif
    log_trace("TC Cnt: %'zu", tc_cnt / 3);
    log_trace("TC Time: %.9lfs", tc_timer.elapsed());

#ifdef USE_LOG
    if (log_f != nullptr) {
        log_info("Flush File and Close...");
        fflush(log_f);
        fclose(log_f);
    }
#endif
    return 0;
}
