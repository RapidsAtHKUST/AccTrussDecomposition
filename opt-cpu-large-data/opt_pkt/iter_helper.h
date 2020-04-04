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
    graph_t *g;
    int omp_num_threads_;
    size_t num_edges_;  // num_edges_ is changed during the shrinking.
    int n_;

public:
    BoolArray<word_type> processed_;

    // Origin Edge Offset.
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

    BoolArray<word_type> in_curr_;

    eid_t *next_;
    BoolArray<word_type> in_next_;

    // For Graph Shrink.
    bool *is_vertex_updated_;
    eid_t *off_end_;
    vid_t *global_v_buffer_;
public:
    // View (edge list and edge support)
    int **edge_sup_ptr_;
    Edge **edge_lst_ptr_;

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

    void MarkProcessed();

    void SwapCurNextQueue();

    void ProcessSupportZeros();

    ~IterHelper();
};

void TriCntDetailSubLevel(graph_t *g, eid_t *curr,
                          BoolArray<word_type> &InCurr,
                          long currTail, int *EdgeSupport, int level, eid_t *next,
                          BoolArray<word_type> &InNext,
                          long *nextTail,
                          BoolArray<word_type> &processed_,
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

#pragma omp parallel
    {
        size_t acc_process_num = 0;
        double acc_time = 0;

        // TC.
        IterStatTLS iter_stat_tls;
        iter_helper.ComputeTriSupport(iter_stat_tls);
#pragma omp single
        {
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

            // 3rd: Processing the graph (shrinking and updating supports).
            while (iter_helper.curr_tail_ > 0) {
                // Map the curr_ to result array.
                todo = todo - iter_helper.curr_tail_;
                iter_stat_tls.RecordQueueSize(iter_helper.curr_tail_);
                // All of them being the last level.
                if (todo == 0) {
                    // No need to process but need to copy the results back.
                    level = level + 1;
                    break;
                }

                // 3.1: Optional shrinking graph. (Move to here to maximally shrink the graph).
                if (acc_deleted > numEdges / graph_compaction_threshold) {
#pragma omp barrier
                    Timer shrink_timer;
                    iter_helper.ShrinkCSREID(&global_v_buff_size, local_buffer);
                    acc_deleted = 0;
#pragma omp single
                    {
                        iter_stat_tls.RecordShrinkNum(num_of_shrinks);
                        shrink_time_lst.emplace_back(shrink_timer.elapsed());
                    }
                }
                iter_stat_tls.RecordShrinkTime();

                // 3.2: Real Processing (updating supports).
                if (level == 0) {
                    iter_helper.ProcessSupportZeros();
                } else {

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
                }

                // 3.3: Swap Queues.
#pragma omp single
                {
                    iter_helper.SwapCurNextQueue();
                    iter_stat_tls.RecordIterNum(iter_num, local_iter_num);
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
}

