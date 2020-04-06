//
// Created by yche on 7/14/19.
//

#include "iter_helper.h"
#include "util/primitives/local_buffer.h"
#include "util/primitives/primitives.h"

IterHelper::IterHelper(graph_t *g, int **edge_sup_ptr, Edge **edge_lst_ptr)
        : g(g), num_edges_(g->m / 2), n_(g->n),
#ifdef BMP_PROCESSED
          processed_(num_edges_),
#endif
          bucket_removed_indicator_(num_edges_),
          curr_tail_(0), next_tail_(0)
#ifdef BMP_QUEUE
        , in_curr_(num_edges_), in_next_(num_edges_)
#endif
        , edge_sup_ptr_(edge_sup_ptr), edge_lst_ptr_(edge_lst_ptr) {
    Timer malloc_timer;
#ifndef BMP_PROCESSED
    processed_ = (bool *) malloc(num_edges_ * sizeof(bool));
#endif
    curr_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));
    next_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));

#ifndef BMP_QUEUE
    in_curr_ = (bool *) malloc(num_edges_ * sizeof(bool));
    in_next_ = (bool *) malloc(num_edges_ * sizeof(bool));
#endif
    log_info("Malloc Time: %.6lfs", malloc_timer.elapsed());

    level_size_ = 0;
    edge_off_org_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));
    level_start_pos_ = (eid_t *) calloc(MAX_LEVEL, sizeof(eid_t));
    edge_offsets_level_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));
    log_info("Malloc Time (Edge Off/ Level CSR): %.6lfs", malloc_timer.elapsed());

    is_vertex_updated_ = (bool *) malloc(n_ * sizeof(bool));
    off_end_ = (eid_t *) malloc((n_ + 1) * sizeof(eid_t));
    global_v_buffer_ = (vid_t *) malloc(n_ * sizeof(vid_t));

    // Compact Graph Related
    compact_num_edges_ = (eid_t *) malloc((g->n + 1) * sizeof(eid_t));
    compact_num_edges_[0] = 0;
    compact_adj_ = (vid_t *) malloc(2 * num_edges_ * sizeof(vid_t));
    compact_eid_ = (eid_t *) malloc(2 * num_edges_ * sizeof(eid_t));

    // Shrinking Graph Related.
    edge_off_org_shrink_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));
    edge_support_shrink_ = (int *) malloc(num_edges_ * sizeof(int));
    edge_lst_shrink_ = (Edge *) malloc(num_edges_ * sizeof(Edge));
    bucket_buf_shrink_ = (eid_t *) malloc(num_edges_ * sizeof(eid_t));

    bucket_relative_off_ = (uint32_t *) malloc((num_edges_) * sizeof(uint32_t));
    edge_lst_relative_off_ = (uint32_t *) malloc((num_edges_) * sizeof(uint32_t));
    log_info("Malloc Time (For Shrinking Graph): %.6lfs", malloc_timer.elapsed());

    partition_id_lst = vector<vector<int >>(g->n);
    bitmap_in_partition_lst = vector<vector<bmp_word_type >>(g->n);
    log_info("Malloc Time (For BSR): %.6lfs", malloc_timer.elapsed());

    in_bucket_window_ = (bool *) malloc(sizeof(bool) * num_edges_);
    bucket_buf_ = (eid_t *) malloc(sizeof(eid_t) * num_edges_);
}

void IterHelper::MemSetIterVariables(int max_omp_threads) {
#pragma omp single
    {
        histogram_ = vector<uint32_t>((max_omp_threads + 1) * CACHE_LINE_ENTRY, 0);
        omp_num_threads_ = max_omp_threads;
    }
#pragma omp for
    for (auto i = 0; i < max_omp_threads; i++) {
        auto avg = n_ / max_omp_threads;
        auto iter_beg = avg * i;
        auto iter_end = (i == max_omp_threads - 1) ? n_ : avg * (i + 1);
        memset(is_vertex_updated_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(bool));
    }
#pragma omp for
    for (auto i = 0; i < max_omp_threads; i++) {
        auto avg = (n_ + 1) / max_omp_threads;
        auto iter_beg = avg * i;
        auto iter_end = (i == max_omp_threads - 1) ? (n_ + 1) : avg * (i + 1);
        memcpy(off_end_ + iter_beg, g->num_edges + iter_beg, sizeof(eid_t) * (iter_end - iter_beg));
    }
#pragma omp for
    for (auto i = 0; i < max_omp_threads; i++) {
        auto avg = num_edges_ / max_omp_threads;
        auto iter_beg = avg * i;
        auto iter_end = (i == max_omp_threads - 1) ? num_edges_ : avg * (i + 1);
#ifndef BMP_PROCESSED
        memset(processed_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(bool));
#endif
#ifndef BMP_QUEUE
        memset(in_curr_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(bool));
        memset(in_next_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(bool));
#endif
        memset(in_bucket_window_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(bool));
        memset(bucket_buf_ + iter_beg, 0, (iter_end - iter_beg) * sizeof(eid_t));

#ifdef SHRINK_EDGE_LIST
        // Identity.
        for (auto j = iter_beg; j < iter_end; j++) {
            edge_off_org_[j] = j;
        }
#endif
    }
}

void IterHelper::ComputeTriSupport(IterStatTLS &iter_stat_tls) {
    int *EdgeSupport = *edge_sup_ptr_;
    extern size_t packed_num;
#pragma omp barrier
#pragma omp single
    log_info("Before TC... %lld, %lld", g->n, g->m);
    // Pre-Process: Indexing Words.
#pragma omp for schedule(dynamic, 100) reduction(+:packed_num)
    for (auto u = 0; u < g->n; u++) {
        PackVertex(g, partition_id_lst, bitmap_in_partition_lst, u, packed_num);
    }
#pragma omp single
    {
        log_info("Packed#: %'zu", packed_num);
        log_info("PreProcess-BitmapOP Cost: %.9lf s, %'lld KB", iter_stat_tls.local_timer.elapsed(), getValue());
#ifdef SUP_STAT
        SupportUpdater::sup_update_num_arr = vector<size_t>(omp_get_num_threads() * CACHE_LINE_ENTRY);
#endif
    }
    // Triangle-Counting With Packing Index.
    auto bool_arr = BoolArray<bmp_word_type>(g->n);
#pragma omp for schedule(dynamic, 6000) reduction(+:tc_cnt)
    for (auto i = 0u; i < g->m; i++)
        ComputeSupportWithPack(g, EdgeSupport, tc_cnt, i, bool_arr,
                               partition_id_lst, bitmap_in_partition_lst);
#pragma omp single
    log_trace("TC Cnt: %'zu", tc_cnt / 3);

//    FreeBSR();
    iter_stat_tls.triTime = iter_stat_tls.local_timer.elapsed_and_reset();
#pragma omp barrier
}

void IterHelper::SwapCurNextQueue() {
    swap(curr_, next_);
    swap(in_curr_, in_next_);

    curr_tail_ = next_tail_;
    next_tail_ = 0;
}

void IterHelper::ShrinkCSREID(volatile eid_t *global_buffer_size, vid_t *local_buffer) {
    LocalWriteBuffer<vid_t, eid_t> local_write_buffer(local_buffer, V_BUFF_SIZE, global_v_buffer_,
                                                      global_buffer_size);

#pragma omp for
    for (auto u = 0; u < g->n; u++) {
        if (is_vertex_updated_[u]) {
            is_vertex_updated_[u] = false;
            local_write_buffer.push(u);
        }
    }
    local_write_buffer.submit_if_possible();

#pragma omp barrier

    // Assume global_buffer_size is volatile, visible to other threads.
    auto active_vertex_size = *global_buffer_size;
#pragma omp for schedule(dynamic, 600)
    for (auto idx = 0u; idx < active_vertex_size; idx++) {
        auto u = global_v_buffer_[idx];
        auto write_idx = g->num_edges[u];
        for (auto i = g->num_edges[u]; i < off_end_[u + 1]; i++) {
            auto old_eid = g->eid[i];
            if (!processed_[old_eid]) {
                g->adj[write_idx] = g->adj[i];
                g->eid[write_idx++] = old_eid;
            }
        }
        off_end_[u + 1] = write_idx;
    }
#pragma omp single
    {
        *global_buffer_size = 0;
    }
}

void IterHelper::CompactCSREID() {
    // also change off_end_
    InclusivePrefixSumOMP(histogram_, compact_num_edges_ + 1, g->n, [this](uint32_t it) {
        return off_end_[it + 1] - g->num_edges[it];
    });
    // Copy adj and eid
#pragma omp for
    for (auto u = 0; u < g->n; u++) {
        auto du = compact_num_edges_[u + 1] - compact_num_edges_[u];
        memcpy(compact_adj_ + compact_num_edges_[u], g->adj + g->num_edges[u], sizeof(vid_t) * du);
        memcpy(compact_eid_ + compact_num_edges_[u], g->eid + g->num_edges[u], sizeof(eid_t) * du);
        off_end_[u + 1] = compact_num_edges_[u + 1];
    }

#pragma omp single
    {
        swap(g->num_edges, compact_num_edges_);
        swap(g->adj, compact_adj_);
        swap(g->eid, compact_eid_);
    }
}

void IterHelper::ShrinkEdgeList() {
    // 1st: Select Edge List.
    FlagPrefixSumOMP(histogram_, edge_lst_relative_off_, num_edges_, [this](uint32_t it) {
        return processed_.get(it);
    });
    // Scatter edge list properties.
#pragma omp for
    for (auto i = 0u; i < num_edges_; i++) {
        if (!processed_.get(i)) {
            auto off = i - edge_lst_relative_off_[i];
            edge_off_org_shrink_[off] = edge_off_org_[i];
            edge_lst_shrink_[off] = (*edge_lst_ptr_)[i];
            edge_support_shrink_[off] = (*edge_sup_ptr_)[i];
        }
    }
#pragma omp single
    {
        swap(edge_off_org_, edge_off_org_shrink_);
        swap(*edge_sup_ptr_, edge_support_shrink_);
        swap(*edge_lst_ptr_, edge_lst_shrink_);
    }

    // 2nd: Update eid (For all the edges, instead of only deleted ones !!!)
#pragma omp for schedule(dynamic, 600)
    for (auto u = 0u; u < g->n; u++) {
        for (auto i = g->num_edges[u]; i < off_end_[u + 1]; i++) {
            auto org_eid = g->eid[i];
            g->eid[i] = org_eid - edge_lst_relative_off_[org_eid];
        }
    }

    // 3rd: Update queue (in_curr_, curr_)
    in_curr_.clearWordsInParallelOMP(num_edges_);
#pragma omp for
    for (auto i = 0u; i < curr_tail_; i++) {
        auto org_eid = curr_[i];
        auto new_eid = org_eid - edge_lst_relative_off_[org_eid];

        curr_[i] = new_eid;
        in_curr_.set_atomic(new_eid);
    }

    // 4th: Select Bucket.
    FlagPrefixSumOMP(histogram_, bucket_relative_off_, window_bucket_buf_size_, [this](uint32_t it) {
        return bucket_removed_indicator_.get(it) || processed_.get(bucket_buf_[it]);
    });
#pragma omp for
    for (auto i = 0u; i < num_edges_; i++) {
        in_bucket_window_[i] = false;
    }
#pragma omp for
    for (auto i = 0u; i < window_bucket_buf_size_; i++) {
        if (!bucket_removed_indicator_.get(i) && !processed_.get(bucket_buf_[i])) {
            auto off = i - bucket_relative_off_[i];
            bucket_buf_shrink_[off] = bucket_buf_[i];
        }
    }
    auto shrink_bucket_size = window_bucket_buf_size_ - bucket_relative_off_[window_bucket_buf_size_ - 1];
#pragma omp for
    for (auto i = 0u; i < shrink_bucket_size; i++) {
        auto org_eid = bucket_buf_shrink_[i];
        auto new_eid = org_eid - edge_lst_relative_off_[org_eid];
        bucket_buf_shrink_[i] = new_eid;
        in_bucket_window_[new_eid] = true;
    }
    // Clear bucket_removed_indicator_.
    bucket_removed_indicator_.clearWordsInParallelOMP(window_bucket_buf_size_);
    // Clear processed.
    processed_.clearWordsInParallelOMP(num_edges_);

#pragma omp single
    {
        auto num_del_edges = edge_lst_relative_off_[num_edges_ - 1];
        num_edges_ -= num_del_edges;
        log_info("# edges, #del, # window-buf-size: %'zu, %'zu, %'zu", num_edges_, num_del_edges,
                 window_bucket_buf_size_);
        window_bucket_buf_size_ = shrink_bucket_size;
        swap(bucket_buf_, bucket_buf_shrink_);
    }
}

void IterHelper::SCANGraph(int level) {
    const int *EdgeSupport = *edge_sup_ptr_;
    // Size of cache line
    const int BUFFER_SIZE_BYTES = 2048;
    const int BUFFER_SIZE = BUFFER_SIZE_BYTES / sizeof(vid_t);
    constexpr size_t bits_in_word = sizeof(word_type) * 8;

    eid_t buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, long> local_queue_buf(buff, BUFFER_SIZE, curr_, &curr_tail_);

    eid_t bkt_buff[BUFFER_SIZE];
    LocalWriteBuffer<eid_t, size_t> local_bucket_buf(bkt_buff, BUFFER_SIZE, bucket_buf_, &window_bucket_buf_size_);

    auto updater = [EdgeSupport, level, &local_queue_buf, this](eid_t i, eid_t buffer_id) {
        if (EdgeSupport[i] == level) {
            bucket_removed_indicator_.set_atomic(buffer_id);

            local_queue_buf.push(i);
#ifndef BMP_QUEUE
            in_curr_[i] = true;
#else
            in_curr_.set_atomic(i);
#endif
        }
    };
    auto updater_with_bkt = [EdgeSupport, level, &local_queue_buf, &local_bucket_buf, this](eid_t i) {
        if (EdgeSupport[i] == level) {
            local_queue_buf.push(i);

#ifndef BMP_QUEUE
            in_curr_[i] = true;
#else
            in_curr_.set_atomic(i);
#endif
        }
        if (EdgeSupport[i] > level && EdgeSupport[i] < bucket_level_end_) {
            bool get_token = __sync_bool_compare_and_swap(&in_bucket_window_[i], false, true);
            if (get_token) {
                local_bucket_buf.push(i);
            }
        }
    };

    if (level == bucket_level_end_) {
#pragma omp barrier
        // Clear the bucket_removed_indicator
        bucket_removed_indicator_.clearWordsInParallelOMP(window_bucket_buf_size_);
#pragma omp single
        {
            bucket_level_end_ += LEVEL_SKIP_SIZE;
            total_size_ += window_bucket_buf_size_;
            window_bucket_buf_size_ = 0;
            log_info("Level: %d, bucket_level_end_: %d", level, bucket_level_end_);
        }
#ifdef BMP_PROCESSED
#pragma omp for schedule(dynamic, 1000)
        for (size_t word_idx = 0; word_idx < processed_.sizeOfWordsRange(num_edges_); word_idx++) {
            if (processed_.getWord(word_idx) == UINT32_MAX) {
                continue;
            } else {
                for (auto i = word_idx * bits_in_word;
                     i < min<size_t>((word_idx + 1) * bits_in_word, num_edges_); i++) {
                    if (processed_.get(i) == 0)
                        updater_with_bkt(i);
                }
            }
        }
#else
#pragma omp for schedule(dynamic, 100)
        for (auto u = 0; u < g_->n; u++) {
            for (auto j = g_->num_edges[u]; j < off_end_[u + 1]; j++) {
                if (u < g_->adj[j])
                    updater_with_bkt(g_->eid[j]);
            }
        }
#endif
        local_bucket_buf.submit_if_possible();
    } else {
        // TODO: Histogram to shrink (< current level). Or Remove Filtering.
//        assert(window_bucket_buf_size_ < static_cast<size_t >(num_edges_));
#pragma omp single
        {
            log_info("Level: %d, Bucket Size: %'zu", level, window_bucket_buf_size_);
        }
#pragma omp for
        for (size_t word_idx = 0;
             word_idx < (window_bucket_buf_size_ + bits_in_word - 1) / bits_in_word; word_idx++) {
            if (bucket_removed_indicator_.getWord(word_idx) != UINT32_MAX) {
                for (auto buffer_id = word_idx * bits_in_word;
                     buffer_id < min<size_t>((word_idx + 1) * bits_in_word, window_bucket_buf_size_); buffer_id++) {
                    if (!bucket_removed_indicator_.get(buffer_id))
                        updater(bucket_buf_[buffer_id], buffer_id);
                }
            }
        }
    }

    local_bucket_buf.submit_if_possible();
    local_queue_buf.submit_if_possible();

#pragma omp barrier
#pragma omp single
    log_info("Level: %d, Queue Size: %'lld", level, curr_tail_);
}

void IterHelper::MarkProcessed() {
#pragma omp barrier

#pragma omp for schedule(static)
    for (long i = 0; i < curr_tail_; i++) {
        eid_t e = curr_[i];

#ifndef BMP_PROCESSED
        processed_[e] = true;
#else
        processed_.set_atomic(e);
#endif

#ifndef BMP_QUEUE
        in_curr_[e] = false;
#else
        in_curr_.unset_atomic(e);
#endif
    }

#pragma omp barrier
}

void IterHelper::FreeBSR() {
    Timer free_timer;

    auto mem_size = getValue();
#pragma omp for
    for (auto i = 0u; i < bitmap_in_partition_lst.size(); i++) {
        auto tmp = vector<bmp_word_type>();
        bitmap_in_partition_lst[i].swap(tmp);
    }
#pragma omp for
    for (auto i = 0u; i < partition_id_lst.size(); i++) {
        auto tmp = vector<int>();
        partition_id_lst[i].swap(tmp);
    }
#pragma omp single
    log_info("Free Cost (With BSRs): %.9lfs", free_timer.elapsed());

#pragma omp single
    {
#pragma omp task
        {
            log_info("tid: %d, free bitmap_in_partition_lst", omp_get_thread_num());
            vector<vector<bmp_word_type >> tmp;
            bitmap_in_partition_lst.swap(tmp);
        }
#pragma omp task
        {
            log_info("tid: %d, free partition_id_lst", omp_get_thread_num());
            vector<vector<int>> tmp;
            partition_id_lst.swap(tmp);
        }
    }

    auto mem_size_end = getValue();

#pragma omp single
    log_info("Free Cost (With 2D-BSR): %.9lfs, BSRs size: %'d KB", free_timer.elapsed(), mem_size - mem_size_end);
}

IterHelper::~IterHelper() {
    log_info("Bucket Arr Size: %'zu", window_bucket_buf_size_);
    log_info("Acc Bucket Arr Size: %'zu", total_size_);
    Timer free_timer;
    free(next_);
    free(curr_);

#ifndef BMP_QUEUE
    free(in_next_);
    free(in_curr_);
#endif
#ifndef BMP_PROCESSED
    free(processed_);
#endif

    free(edge_offsets_level_);
    free(level_start_pos_);
    free(edge_off_org_);

    // Compact
    free(compact_num_edges_);
    free(compact_eid_);
    free(compact_adj_);

    // Shrinking Edge List Related.
    free(bucket_buf_shrink_);
    free(edge_lst_shrink_);
    free(edge_off_org_shrink_);
    free(edge_support_shrink_);

    free(bucket_relative_off_);
    free(edge_lst_relative_off_);

    free(global_v_buffer_);
    free(is_vertex_updated_);
    free(off_end_);

    free(in_bucket_window_);
    free(bucket_buf_);
    log_info("Free Cost Prev: %.9lfs", free_timer.elapsed());

    if (!bitmap_in_partition_lst.empty() || !partition_id_lst.empty()) {
#pragma omp parallel
        FreeBSR();
    }
}

void IterHelper::ProcessSupportZeros() {
    auto edgeIdtoEdge = *edge_lst_ptr_;
#pragma omp for schedule(static)
    for (long i = 0; i < curr_tail_; i++) {
        eid_t e1 = curr_[i];

        Edge edge = edgeIdtoEdge[e1];
        vid_t u = edge.u;
        vid_t v = edge.v;
        eid_t uStart = g->num_edges[u], uEnd = off_end_[u + 1];
        eid_t vStart = g->num_edges[v], vEnd = off_end_[v + 1];

        is_vertex_updated_[u] = true;
        is_vertex_updated_[v] = true;
    }
    MarkProcessed();
}

void PKT_processSubLevel_intersection_handling_skew(graph_t *g, eid_t *curr,
                                                    BoolArray<word_type> &InCurr,
                                                    long currTail, int *EdgeSupport, int level, eid_t *next,
                                                    BoolArray<word_type> &InNext,
                                                    long *nextTail,
                                                    BoolArray<word_type> &processed,
                                                    Edge *edgeIdtoEdge, eid_t *off_end,
                                                    bool *is_vertex_updated, IterHelper &iter_helper
);

int IterHelper::TrussDecompositionMergeBased() {
    IterHelper &iter_helper = *this;
    auto process_functor = [&iter_helper](int level) {
        PKT_processSubLevel_intersection_handling_skew(iter_helper.g, iter_helper.curr_, iter_helper.in_curr_,
                                                       iter_helper.curr_tail_,
                                                       *iter_helper.edge_sup_ptr_, level, iter_helper.next_,
                                                       iter_helper.in_next_, &iter_helper.next_tail_,
                                                       iter_helper.processed_, *iter_helper.edge_lst_ptr_,
                                                       iter_helper.off_end_,
                                                       iter_helper.is_vertex_updated_, iter_helper);
    };
    auto &EdgeSupport = *iter_helper.edge_sup_ptr_;
    auto &edgeIdToEdge = *iter_helper.edge_lst_ptr_;
    auto level = AbstractPKT(g, EdgeSupport, edgeIdToEdge, iter_helper, process_functor);
    return level;
}

void IterHelper::TransferResult(eid_t *&level_start_pos, eid_t *&edge_offsets_level, eid_t *&edge_off_org,
                                int *&edge_sup, Edge *&edge_lst) {
    level_start_pos = level_start_pos_;
    level_start_pos_ = nullptr;
    edge_offsets_level = edge_offsets_level_;
    edge_offsets_level_ = nullptr;
    edge_sup = *edge_sup_ptr_;
    *edge_sup_ptr_ = nullptr;
    edge_lst = *edge_lst_ptr_;
    *edge_lst_ptr_ = nullptr;
    edge_off_org = edge_off_org_;
    edge_off_org_ = nullptr;
}

int TrussDecompositionLevelsCPU(graph_t &g, int *&EdgeSupport, Edge *&edgeIdToEdge,
                                eid_t *&level_start_pos, eid_t *&edge_offsets_level, eid_t *&edge_off_org,
                                int *&edge_sup, Edge *&edge_lst) {
    IterHelper iter_helper(&g, &EdgeSupport, &edgeIdToEdge);
    int level = iter_helper.TrussDecompositionMergeBased();
    iter_helper.TransferResult(level_start_pos, edge_offsets_level, edge_off_org, edge_sup, edge_lst);
    return level;
}



