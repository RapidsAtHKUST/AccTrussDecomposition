#pragma once

#include "util/graph/graph.h"
#include "util/timer.h"
#include "util/log/log.h"
#include "util/search/search_util.h"
#include "util/stat.h"

#include "pkt_support_update_utils.h"
#include "parallel_all_edge_cnc.h"
#include "iter_stat_helper.h"
#include "extern_variables.h"

#define V_BUFF_SIZE (4096)
#define MAX_LEVEL (20000)

class IterHelper {
public:
    vector<uint32_t> histogram_;
    int omp_num_threads_;
    graph_t *g;
    eid_t *compact_num_edges_;
    vid_t *compact_adj_;
    eid_t *compact_eid_;

    size_t num_edges_;  // num_edges_ is changed during the shrinking.
    int n_;

public:
#ifdef BMP_PROCESSED
    BoolArray<word_type> processed_;
#else
    bool *processed_;
#endif

    // Origin Edge Offset.
    eid_t *edge_off_org_;
    eid_t *level_start_pos_;
    eid_t *edge_offsets_level_;
    int level_size_;

    // Bucket Related.
    BoolArray<word_type> bucket_removed_indicator_;
    int bucket_level_end_ = 0;
    bool *in_bucket_window_;
    eid_t *bucket_buf_;
    size_t window_bucket_buf_size_ = 0;

    size_t total_size_ = 0;

    // Queue Related. (curr_/next_).
    long curr_tail_;
    long next_tail_;
    eid_t *curr_;

#ifdef BMP_QUEUE
    BoolArray<word_type> in_curr_;
#else
    bool *in_curr_;
#endif
    eid_t *next_;
#ifdef BMP_QUEUE
    BoolArray<word_type> in_next_;
#else
    bool *in_next_;
#endif
    // For Graph Shrink.
    bool *is_vertex_updated_;
    eid_t *off_end_;
    vid_t *global_v_buffer_;
public:
    // View (edge list and edge support)
    int **edge_sup_ptr_;
    Edge **edge_lst_ptr_;

    // Shrink Related Extra Memory.
    eid_t *edge_off_org_shrink_;
    int *edge_support_shrink_;
    Edge *edge_lst_shrink_;
    eid_t *bucket_buf_shrink_;

    uint32_t *edge_lst_relative_off_; // // prefix-sum inclusive
    uint32_t *bucket_relative_off_; // prefix-sum inclusive
public:
    // BSR.
    vector<vector<int>> partition_id_lst;
    vector<vector<bmp_word_type>> bitmap_in_partition_lst;

    void FreeBSR();

public:
    IterHelper(graph_t *g, int **edge_sup_ptr, Edge **edge_lst_ptr);

    void MemSetIterVariables(int max_omp_threads);

    void ComputeTriSupport(IterStatTLS &iter_stat_tls);

    void SCANGraph(int level);

    void ShrinkCSREID(volatile eid_t *global_buffer_size, vid_t *local_buffer);

    void CompactCSREID();

    void ShrinkEdgeList();

    void MarkProcessed();

    void SwapCurNextQueue();

    void ProcessSupportZeros();

    ~IterHelper();
};

void TriCntDetailSubLevel(graph_t *g, eid_t *curr,
#ifndef BMP_QUEUE
        bool *InCurr,
#else
                          BoolArray<word_type> &InCurr,
#endif
                          long currTail, int *EdgeSupport, int level, eid_t *next,
#ifndef BMP_QUEUE
        bool *InNext,
#else
                          BoolArray<word_type> &InNext,
#endif
                          long *nextTail,
#ifdef BMP_PROCESSED
                          BoolArray<word_type> &processed_,
#else
        bool *processed_,
#endif
                          Edge *edgeIdtoEdge, eid_t *off_end,
                          bool *is_vertex_updated, IterHelper &iter_helper, volatile eid_t &global_v_buff_size
);

/*
 * F requires a callable or a functor with signature `void (int)`
 */
template<typename F>
void AbstractPKT(graph_t *g, int *&EdgeSupport, Edge *&edgeIdToEdge, IterHelper &iter_helper, F f) {
    Timer malloc_timer;
    long numEdges = g->m / 2;
    auto max_omp_threads = omp_get_max_threads();
    log_info("Max Threads: %d", max_omp_threads);
    tls_psm_stat.resize(max_omp_threads, 0);
    tls_vm_stat.resize(max_omp_threads, 0);
    tls_psm_cmp_stat.resize(max_omp_threads, 0);
    tls_vm_cmp_stat.resize(max_omp_threads, 0);
#pragma omp parallel num_threads(max_omp_threads)
    {
        iter_helper.MemSetIterVariables(max_omp_threads);
    }
    log_info("Malloc & MemSet Time: %.6lfs", malloc_timer.elapsed());
    vector<double> shrink_time_lst;
    Timer iter_timer;
    Timer comp_timer;
    size_t iter_num = 0;
    size_t local_iter_num = 0;
    volatile eid_t global_v_buff_size = 0;
    size_t num_of_shrinks = 0;
    vector<int> tc_level;
    vector<double> tc_level_time;
    double init_tc_time = 0;
    double penalty_tc_time = 0;
#ifdef PAPER_FIGURE
    {
        stringstream ss;
        ss << pretty_print_array(g->num_edges, g->n + 1);
        log_info("CSR-off: %s", ss.str().c_str());

        reset(ss);
        ss << pretty_print_array(g->adj, g->m);
        log_info("CSR-adj: %s", ss.str().c_str());

        reset(ss);
        ss << pretty_print_array(g->eid, g->m);
        log_info("Map-eid: %s", ss.str().c_str());

        vector<int> src;
        vector<int> dst;
        for (int i = 0; i < g->m / 2; i++) {
            src.emplace_back(edgeIdToEdge[i].u);
            dst.emplace_back(edgeIdToEdge[i].v);
        }
        reset(ss);
        ss << src;
        log_info("Edge-src: %s", ss.str().c_str());

        reset(ss);
        ss << dst;
        log_info("Edge-dst: %s", ss.str().c_str());
    }

#endif
#pragma omp parallel
    {
        size_t acc_process_num = 0;
        double acc_time = 0;

        // TC.
        IterStatTLS iter_stat_tls;
        iter_helper.ComputeTriSupport(iter_stat_tls);
#pragma omp single
        {
#ifdef PAPER_FIGURE
            if (g->m < 40) {
                stringstream ss;
                ss << pretty_print_array(EdgeSupport, g->m / 2);
                vector<pair<pair<int, int>, int>> edge_list;
                for (auto i = 0; i < g->m / 2; i++) {
                    edge_list.emplace_back(make_pair(edgeIdToEdge[i].u, edgeIdToEdge[i].v), EdgeSupport[i]);
                }
                ss << edge_list << endl;
                log_info("Edge Support Array: %s", ss.str().c_str());
            }
#endif
            init_tc_time = iter_stat_tls.triTime;
            iter_timer.reset();
            log_info("TC time: %.9lfs", init_tc_time);
        }
        // Compute Truss.
        auto *local_buffer = (vid_t *) malloc(sizeof(vid_t) * V_BUFF_SIZE);
        int level = 0;
        long acc_deleted = 0;
        long todo = numEdges;
        while (todo > 0) {
            // 1st: Synchronization.
#pragma omp single
            {
                iter_stat_tls.PrintIterStat(iter_timer, todo, numEdges, level, iter_num, local_iter_num);
            }
            iter_stat_tls.ResetLocalTime();
            iter_stat_tls.RecordSyncTime();

            // 2nd: Scanning the graph to fetch the level.
            iter_helper.SCANGraph(level);
            iter_stat_tls.RecordSCANTime();

#ifdef SHRINK_EDGE_LIST
#pragma omp single
            {
                iter_helper.level_start_pos_[level + 1] = iter_helper.level_start_pos_[level];
            }
#endif
            // 3rd: Processing the graph (shrinking and updating supports).
            while (iter_helper.curr_tail_ > 0) {
                // Map the curr_ to result array.
#ifdef PAPER_FIGURE
#pragma omp single
                {
                    stringstream ss;
                    vector<pair<int, int>> edge_lst;
                    for (auto i = 0; i < iter_helper.curr_tail_; i++) {
                        auto edge = (*iter_helper.edge_lst_ptr_)[iter_helper.curr_[i]];
                        edge_lst.emplace_back(edge.u, edge.v);
                    }
                    sort(edge_lst.begin(), edge_lst.end());
                    ss << edge_lst;
                    log_info("Curr Queue: %s", ss.str().c_str());
                }
#endif
#ifdef SHRINK_EDGE_LIST
#pragma omp for
                for (auto i = 0; i < max_omp_threads; i++) {
                    auto avg = iter_helper.curr_tail_ / max_omp_threads;
                    auto iter_beg = avg * i;
                    auto iter_end = (i == max_omp_threads - 1) ? iter_helper.curr_tail_ : avg * (i + 1);
                    auto pos_off = iter_helper.level_start_pos_[level + 1];
                    for (auto iter = iter_beg; iter < iter_end; iter++) {
                        // map operation.
                        iter_helper.edge_offsets_level_[pos_off + iter] =
                                iter_helper.edge_off_org_[iter_helper.curr_[iter]];
                    }
                }
#pragma omp single
                {
                    iter_helper.level_start_pos_[level + 1] += iter_helper.curr_tail_;
                }
#endif

                todo = todo - iter_helper.curr_tail_;
                iter_stat_tls.RecordQueueSize(iter_helper.curr_tail_);
#ifndef WITHOUT_FIRST_LAST_LEVEL_OPT
                // All of them being the last level.
                if (todo == 0) {
                    // No need to process but need to copy the results back.
                    level = level + 1;
                    break;
                }
#endif

#ifndef NO_SHRINK_GRAPH
                // 3.1: Optional shrinking graph. (Move to here to maximally shrink the graph).
                if (acc_deleted > numEdges / graph_compaction_threshold) {
#pragma omp barrier
                    Timer shrink_timer;
                    iter_helper.ShrinkCSREID(&global_v_buff_size, local_buffer);
#ifdef COMPACT_CSR
                    iter_helper.CompactCSREID();
#endif
#ifdef SHRINK_EDGE_LIST
                    iter_helper.ShrinkEdgeList();
#endif
                    acc_deleted = 0;
#pragma omp single
                    {
                        iter_stat_tls.RecordShrinkNum(num_of_shrinks);
                        shrink_time_lst.emplace_back(shrink_timer.elapsed());
                    }
                }
#endif
                iter_stat_tls.RecordShrinkTime();

                // 3.2: Real Processing (updating supports).
#ifndef WITHOUT_FIRST_LAST_LEVEL_OPT
                if (level == 0) {
                    iter_helper.ProcessSupportZeros();
                } else {
#endif

#ifdef NO_TC_OPT
                    {
                        auto to_delete = iter_helper.curr_tail_;
                        f(level);
                        acc_deleted += to_delete;
                    }
#else
                    size_t task_size = iter_helper.curr_tail_ * (size_t) (level + 1);
                    size_t left_edge_size = todo;
                    double estimated_tc_time = left_edge_size / (g->m / 2.0) * init_tc_time + penalty_tc_time;
                    double estimated_peel_time = task_size / estimated_process_throughput;

                    if (estimated_tc_time > estimated_peel_time) {
                        auto to_delete = iter_helper.curr_tail_;
                        f(level);
                        acc_process_num += task_size;
                        acc_deleted += to_delete;
                    } else {
#pragma omp single
                        {
                            log_info("Estimated TC Time: %.9lfs, Peel Time: %.9lfs", estimated_tc_time,
                                     estimated_peel_time);
                            tc_level.emplace_back(level);
                            log_info("!!!TriCnt!!!, Task-Size: %'zu, TC-Cnt/50: %'zu", task_size, tc_cnt / 50);
                        }
                        Timer tc_timer;
                        TriCntDetailSubLevel(g, iter_helper.curr_, iter_helper.in_curr_,
                                             iter_helper.curr_tail_,
                                             *iter_helper.edge_sup_ptr_, level, iter_helper.next_,
                                             iter_helper.in_next_, &iter_helper.next_tail_,
                                             iter_helper.processed_, *iter_helper.edge_lst_ptr_,
                                             iter_helper.off_end_,
                                             iter_helper.is_vertex_updated_, iter_helper, global_v_buff_size);
                        acc_deleted = 0;
#pragma omp single
                        {
                            auto cost = tc_timer.elapsed();
                            if (estimated_tc_time * 1.2 < cost) {
                                penalty_tc_time += cost - estimated_tc_time;
                                log_info("Penalty TC-Time: %.9lfs", penalty_tc_time);
                            }
                            tc_level_time.emplace_back(cost);
                        }
                    }
#endif
#ifndef WITHOUT_FIRST_LAST_LEVEL_OPT
                }
#endif

                // 3.3: Swap Queues.
#pragma omp single
                {
                    iter_helper.SwapCurNextQueue();
                    iter_stat_tls.RecordIterNum(iter_num, local_iter_num);
#ifdef PAPER_FIGURE
                    if (g->m < 40) {
                        stringstream ss;
                        ss << pretty_print_array(EdgeSupport, g->m / 2);
                        vector<pair<pair<int, int>, int>> edge_list;
                        for (auto i = 0; i < g->m / 2; i++) {
                            edge_list.emplace_back(make_pair(edgeIdToEdge[i].u, edgeIdToEdge[i].v), EdgeSupport[i]);
                        }
                        ss << edge_list << endl;
                        log_info("Edge Support Array: %s", ss.str().c_str());
                    }
#endif
                }
#pragma omp barrier
                iter_stat_tls.RecordProcessTime();
            }
            level = level + 1;
#pragma omp barrier
            // End of Iterative Peeling for this Level.
        }

        // The end.
#pragma omp single
        {
            iter_helper.level_size_ = level;
#ifdef SHRINK_EDGE_LIST
            assert(iter_helper.level_start_pos_[iter_helper.level_size_ - 1] == numEdges);
#endif
            log_info("Total Levels: %d", iter_helper.level_size_);
            log_trace("Last Level Finished: %d, Elapsed Time: %.9lfs, Left/Total: %'lld/%'lld, "
                      "Local/Global-Iter#: %zu/%zu", level - 1,
                      iter_timer.elapsed_and_reset(), todo, numEdges, local_iter_num, iter_num);
            iter_stat_tls.PrintFinalStat(level, num_of_shrinks);
            stringstream ss;
            ss << tc_level << ", Time: " << tc_level_time;
            log_trace("TC-levels: %s", ss.str().c_str());

            stringstream ss2;
            ss2 << shrink_time_lst;
            log_trace("Shrink Time List: %s", ss2.str().c_str());
        }
        free(local_buffer);
    }  //End of parallel region
    log_info("Total computation cost: %.9lfs", comp_timer.elapsed_and_reset());

    log_info("#VM / #PSM :%s; %s", FormatWithCommas(accumulate(begin(tls_vm_stat), end(tls_vm_stat), (size_t)0)).c_str(),
             FormatWithCommas(accumulate(begin(tls_psm_stat), end(tls_psm_stat), (size_t)0)).c_str());
    log_info("#VM-cmp / #PSM-cmpt :%s; %s",
             FormatWithCommas(accumulate(begin(tls_vm_cmp_stat), end(tls_vm_cmp_stat), (size_t)0)).c_str(),
             FormatWithCommas(accumulate(begin(tls_psm_cmp_stat), end(tls_psm_cmp_stat), (size_t)0)).c_str());

    // Copy Back to Edge Support.
#ifdef SHRINK_EDGE_LIST
    for (auto i = 0; i < iter_helper.level_size_ - 1; i++) {
#pragma omp for nowait
        for (auto j = iter_helper.level_start_pos_[i]; j < iter_helper.level_start_pos_[i + 1]; j++) {
            EdgeSupport[iter_helper.edge_offsets_level_[j]] = i;
        }
    }
    log_info("Result Copy Time: %.9lfs ", comp_timer.elapsed());
#endif
}

