//
// Created by yche on 5/20/19.
//

extern "C"
{
#include <GKlib.h>
#include "../struct.h"
#include "../defs.h"
}

//#define LOCKS // Problematic, do not know why yet.
#ifdef LOCKS

#include <omp.h>

#endif

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

#include "yche_serialization.h"
#include "log.h"
#include "timer.h"


using namespace std;
using namespace std::chrono;

using edge_lst_type = vector<pair<int32_t, int32_t>>;

edge_lst_type ReadEdgeList(string dir) {
    log_info("Path: %s", dir.c_str());
    edge_lst_type edges;
    string graphpath = dir + "/" + "undir_edge_list.bin";
    FILE *pFile = fopen(graphpath.c_str(), "r");
    YcheSerializer serializer;
    serializer.read_array(pFile, edges);
    fclose(pFile);
    log_info("edge#: %zu", edges.size());
    return edges;
}

#ifdef __cplusplus
extern "C" {
#endif


gk_graph_t *gk_graph_Read_bin_edge_lst(char *filename) {
    Timer timer;

    auto edge_lst = ReadEdgeList(filename);
    log_info("load edge list bin time: %.3lf s", timer.elapsed());

    int32_t max_node_id = -1;


    vector<int32_t> deg_lst;
    vector<ssize_t> off;
    vector<ssize_t> cur_write_off;
    int32_t *adj_lst;

    timer.reset();
#if defined(LOCKS)
    omp_lock_t *locks;
#endif

#pragma omp parallel
    {
        // 1st: get the cardinality of degree array
#pragma omp for reduction(max: max_node_id)
        for (uint32_t i = 0; i < edge_lst.size(); i++) {
            max_node_id = max(max_node_id, max(edge_lst[i].first, edge_lst[i].second));
        }
#pragma omp single nowait
        {
            deg_lst = vector<int32_t>(static_cast<uint32_t>(max_node_id + 1));

        }
#pragma omp single nowait
        {
            off = vector<ssize_t>(max_node_id + 2);
            off[0] = 0;
        }
#pragma omp for
        for (auto i = 0; i < deg_lst.size(); i++) {
            deg_lst[i] = 0;
        }

        // 2nd: to count grouped neighbors, store in `deg_lst`
#pragma omp for
        for (uint32_t i = 0; i < edge_lst.size(); i++) {
            // atomic add for edge.first
            auto src = edge_lst[i].first;
            auto dst = edge_lst[i].second;
            int inc_deg_val, cur_deg_src;
            do {
                cur_deg_src = deg_lst[src];
                inc_deg_val = cur_deg_src + 1;
            } while (!__sync_bool_compare_and_swap(&(deg_lst[src]), cur_deg_src, inc_deg_val));
            do {
                cur_deg_src = deg_lst[dst];
                inc_deg_val = cur_deg_src + 1;
            } while (!__sync_bool_compare_and_swap(&(deg_lst[dst]), cur_deg_src, inc_deg_val));
        }

        // 3rd: compute prefix_sum and then scatter
#pragma omp single
        {
            for (int i = 0; i < deg_lst.size(); i++) {
                off[i + 1] = off[i] + deg_lst[i];
            }
        }

#pragma omp single nowait
        {
            log_info("adj list size: %'lld", off[off.size() - 1]);
            adj_lst = gk_i32malloc(off.back(), "adjncy");
        }

#pragma omp single nowait
        {
            cur_write_off = off;
        }

#pragma omp single nowait
        {
#if defined(LOCKS)
            locks = new omp_lock_t[deg_lst.size()];
#endif
        }

#if defined(LOCKS)
#pragma omp for
        for (int i = 0; i < deg_lst.size(); i++) {
            omp_init_lock(&locks[i]);
        }
#endif

        // 4th: barrier before we do the computation, and then construct destination vertices in CSR
#pragma omp single
        {
            auto middle = high_resolution_clock::now();
            log_info("before csr transform time: %.3lf s", timer.elapsed());
        }

#pragma omp for
        for (size_t i = 0; i < edge_lst.size(); i++) {
            auto src = edge_lst[i].first;
            auto dst = edge_lst[i].second;

            ssize_t new_offset, old_offset;

#if defined(LOCKS)
            omp_set_lock(&locks[src]);
            old_offset = cur_write_off[src];
            new_offset = old_offset + 1;
            cur_write_off[src] = new_offset;
            omp_unset_lock(&locks[src]);

            adj_lst[old_offset] = dst;

            omp_set_lock(&locks[dst]);
            old_offset = cur_write_off[dst];
            new_offset = old_offset + 1;
            cur_write_off[dst] = new_offset;
            omp_unset_lock(&locks[dst]);

            adj_lst[old_offset] = src;
#else
            do {
                old_offset = cur_write_off[src];
                new_offset = old_offset + 1;
            } while (!__sync_bool_compare_and_swap(&(cur_write_off[src]), old_offset, new_offset));
            adj_lst[old_offset] = dst;

            do {
                old_offset = cur_write_off[dst];
                new_offset = old_offset + 1;
            } while (!__sync_bool_compare_and_swap(&(cur_write_off[dst]), old_offset, new_offset));
            adj_lst[old_offset] = src;
#endif
        }
#pragma omp single
        {
            auto middle2 = high_resolution_clock::now();
            log_info("before sort time: %.3lf s", timer.elapsed());
        }
        // 5th: sort each local ranges
#pragma omp for schedule(dynamic)
        for (auto u = 0; u < deg_lst.size(); u++) {
            if (cur_write_off[u] != off[u + 1]) {
                log_fatal("error %lld %lld", cur_write_off[u], off[u + 1]);
            }
            assert(cur_write_off[u] == off[u + 1]);
            sort(adj_lst + off[u], adj_lst + off[u + 1]);
        }
    }
    auto end = high_resolution_clock::now();
    log_info("edge list to csr time: %.3lf s", timer.elapsed());

    gk_graph_t *graph = gk_graph_Create();
    graph->nvtxs = max_node_id + 1;
    graph->xadj = gk_zsmalloc(off.size(), 0, "xadj");
    memcpy(graph->xadj, &off.front(), sizeof(ssize_t) * off.size());
    graph->adjncy = adj_lst;
    return graph;
}

#ifdef __cplusplus
}
#endif
