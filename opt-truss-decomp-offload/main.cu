#include <climits>
#include <cassert>

#include <chrono>
#include <sstream>
#include <fstream>

#include <omp.h>

#include "util/graph.h"
#include "util/log.h"
#include "util/pretty_print.h"
#include "util/timer.h"
#include "util/cuda/cuda_util.h"

#include "reordering_utils/reorder_utils.h"

#include "cuda_extern_functions.cuh"
#include "main_helper.h"

int main(int argc, char *argv[]) {
    setlocale(LC_NUMERIC, "");
    if (argc < 2) {
        fprintf(stderr, "%s <Graph file>\n", argv[0]);
        exit(1);
    }

    ZLCUDAMemStat mem_stat;
    ZLCUDATimer time_stat;

    string algorithm_name;
    string cmd(argv[0]);
    auto pos = cmd.find_last_of('/');
    if (pos != string::npos) {
        algorithm_name = cmd.substr(pos + 1, cmd.size());
    } else {
        algorithm_name = cmd;
    }
    //set log file descriptor
#ifdef USE_LOG
    FILE *log_f = nullptr;
    if (argc >= 4) {
        log_f = fopen(argv[3], "a+");
        log_set_fp(log_f);
    }
#endif
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
    auto edgeIdToEdge = (Edge *) malloc(sizeof(Edge) * (g.m / 2));
    auto EdgeSupport = (int *) malloc(sizeof(int) * (g.m / 2));
    log_info("Malloc Time: %.9lf s", get_eid_timer.elapsed());
    auto org_num_edges = g.m / 2;

    get_eid_timer.reset();
    //Populate the edge list array
    getEidAndEdgeList(&g, edgeIdToEdge);
    log_info("Init Eid Time: %.9lf s", get_eid_timer.elapsed());
    get_eid_timer.reset();

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
    int *EdgeSupportCUDA, *output, *final_result_output;
    ZLCudaMalloc(&output, sizeof(int) * org_num_edges, &mem_stat);
    ZLCudaMalloc(&final_result_output, sizeof(int) * org_num_edges, &mem_stat);
    ZLCudaMalloc(&EdgeSupportCUDA, sizeof(int) * (g.m / 2), &mem_stat);
    log_info("Malloc Time: %.9lfs", global_timer.elapsed());

#ifndef GPU_ONLY
    eid_t *level_start_pos, *edge_offsets_level, *edge_off_org;
    int *edge_sup;
    Edge *edge_lst;
    auto level = TrussDecompositionLevelsCPU(g, EdgeSupport, edgeIdToEdge,
                                             level_start_pos, edge_offsets_level, edge_off_org,
                                             edge_sup, edge_lst);
    Timer offload_timer;
    cudaMemcpy(output, edge_offsets_level, sizeof(int) * org_num_edges, cudaMemcpyHostToDevice);
    cudaMemcpy(EdgeSupportCUDA, edge_sup, sizeof(int) * g.m / 2, cudaMemcpyHostToDevice);

    assert(level_start_pos[level + 1] == 0);
    log_info("Current g.m: %'lld", g.m / 2);
    PKT_cuda(&g, edge_off_org, EdgeSupportCUDA, edge_lst,
             100, output, level_start_pos, &mem_stat, &time_stat, level);
    cudaDeviceSynchronize();
    log_info("Offloading Comp Time: %.9lfs", offload_timer.elapsed());
#else
    auto level_start_pos = (eid_t *) calloc(MAX_LEVEL, sizeof(eid_t));
    cudaMemcpy(EdgeSupportCUDA, EdgeSupport, sizeof(int) * g.m / 2, cudaMemcpyHostToDevice);

    Timer tc_timer;
    invoke_tc_bmp_gpu(&g, EdgeSupportCUDA);
    extern double tc_time;
    tc_time = tc_timer.elapsed();
    PKT_cuda(&g, nullptr, EdgeSupportCUDA, edgeIdToEdge,
             100, output, level_start_pos, &mem_stat, &time_stat, 0);
#endif
    log_info("Parallel K-Truss: %.9lfs", global_timer.elapsed());

    auto output_dir = string(argv[1]) + "/" + string("ktruss-") + algorithm_name + ".histogram";
    log_info("Output Dir: %s", output_dir.c_str());


    /*Recover the EdgeSupport for checking*/
    Timer recovery_timer;
    CheckLevelOff(level_start_pos);
#pragma omp parallel
    for (int l = 0;; l++) {

        auto start = level_start_pos[l];
        auto end = level_start_pos[l + 1];
        if (start == org_num_edges) break;
        if (start > end) {
            log_fatal("error in level stat pos: %d, [%d, %d)", l, start, end);
            exit(-1);
        }
#pragma omp for
        for (int i = start; i < end; i++) {
            final_result_output[output[i]] = l;
        }
    }
    log_info("Finish Constructing Final Results..., Recovery Time: %.9lfs", recovery_timer.elapsed());
    display_stats(final_result_output, org_num_edges, output_dir);
    log_info("Finish Checking, ET: %.9lfs", recovery_timer.elapsed_and_reset());

    //Free memory
    free_graph(&g);
    free(level_start_pos);
#ifndef GPU_ONLY
    free(edge_offsets_level);
    free(edge_off_org);
    free(edge_sup);
    free(edge_lst);
#endif

    free(edgeIdToEdge);
    free(EdgeSupport);
    ZLCudaFree(output, &mem_stat);
    ZLCudaFree(final_result_output, &mem_stat);

    log_info("Free Time: %.9lfs", recovery_timer.elapsed());
#ifdef USE_LOG
    if (log_f != nullptr) {
        log_info("Flush File and Close...");
        fflush(log_f);
        fclose(log_f);
    }
#endif
    return 0;
}
