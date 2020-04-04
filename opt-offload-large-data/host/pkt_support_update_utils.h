#pragma once

#include <omp.h>

#include <numeric>

#include <util/pretty_print.h>
#include <util/lemire/EWAHBoolArray/headers/boolarray.h>
#include "local_buffer.h"

#define CACHE_LINE_ENTRY (16)
#define BUCKET_OPT

using word_type = uint32_t;

void PKT_scan(long numEdges, int *EdgeSupport, int level, eid_t *curr, long *currTail, bool *InCurr);

void PKT_processSubLevel_intersection_handling_skew(
        graph_t *g, eid_t *curr, bool *InCurr, long currTail, int *EdgeSupport,
        int level, eid_t *next, bool *InNext, long *nextTail, bool *processed,
        Edge *edgeIdtoEdge);

class SupportUpdater {
    int *EdgeSupport;

#ifndef BMP_QUEUE
    bool *InNext;
#else
    BoolArray<word_type> *InNext;
#endif
    int level;
    LocalWriteBuffer<eid_t, long> local_queue_buffer_;
    LocalWriteBuffer<eid_t, size_t> local_bucket_buffer_;
    int bucket_level_end_;
    bool *in_bucket_window_;
public:
#ifdef SUP_STAT
    static vector<size_t> sup_update_num_arr;
#endif

    SupportUpdater(int *edgeSupport,
#ifndef BMP_QUEUE
            bool *inNext,
#else
                   BoolArray<word_type> &inNext,
#endif
                   int level,
                   LocalWriteBuffer<eid_t, long> local_write_buffer,
                   LocalWriteBuffer<eid_t, size_t> local_bucket_buffer, int bucket_level_end, bool *in_bucket_window) :
            EdgeSupport(edgeSupport),
#ifndef BMP_QUEUE
            InNext(inNext),
#else
            InNext(&inNext),
#endif
            level(level), local_queue_buffer_(local_write_buffer),
            local_bucket_buffer_(local_bucket_buffer), bucket_level_end_(bucket_level_end),
            in_bucket_window_(in_bucket_window) {}

private:
#ifdef BUCKET_OPT

    void AddEdgeToBucketIfPossible(int sup, eid_t eid) {
        if (sup - 1 > level && sup - 1 < bucket_level_end_) {
            bool get_token = __sync_bool_compare_and_swap(&in_bucket_window_[eid], false, true);
            if (get_token) {
                local_bucket_buffer_.push(eid);
            }
        }
    }

#endif

    // TODO: rename it.
    void operator()(eid_t updated_edge) {
#ifdef SUP_STAT
        static thread_local auto &sup_update_num = SupportUpdater::sup_update_num_arr[omp_get_thread_num() * CACHE_LINE_ENTRY];
        sup_update_num++;
#endif
        auto addr = &EdgeSupport[updated_edge];
        if (*addr <= level) return;     // Avoid unnecessary atomic operations.
        int supE2 = __sync_fetch_and_sub(addr, 1);
        if (supE2 == (level + 1)) {
            local_queue_buffer_.push(updated_edge);
#ifndef BMP_QUEUE
            InNext[updated_edge] = true;
#else
            InNext->set_atomic(updated_edge);
#endif
        }
        if (supE2 <= level) {
            __sync_fetch_and_add(addr, 1);
        }
#ifdef BUCKET_OPT
        AddEdgeToBucketIfPossible(supE2, updated_edge);
#endif
    }

public:
    void SubmitLocalBufferNext() {
        local_queue_buffer_.submit_if_possible();
        local_bucket_buffer_.submit_if_possible();
    }

    //If e1, e2, e3 forms a triangle
    void PeelTriangle(eid_t e1, eid_t e2, eid_t e3,
#ifdef BMP_PROCESSED
                      BoolArray<word_type> &processed,
#else
            const bool *processed,
#endif
#ifndef BMP_QUEUE
            const bool *InCurr
#else
                      BoolArray<word_type> &InCurr
#endif
    ) {
#ifndef BMP_QUEUE
        bool is_peel_e2 = !InCurr[e2];
        bool is_peel_e3 = !InCurr[e3];
#else
        bool is_peel_e2 = !InCurr.get(e2);
        bool is_peel_e3 = !InCurr.get(e3);
#endif

        if (is_peel_e2 || is_peel_e3) {     // Important for the WE dataset. (peel many edges in a sub-level).
#ifndef BMP_PROCESSED
            if ((!processed[e2]) && (!processed[e3])) {
#else
            if ((!processed.get(e2)) && (!processed.get(e3))) {
#endif
                //Decrease support of both e2 and e3
                if (is_peel_e2 && is_peel_e3) {
                    this->operator()(e2);
                    this->operator()(e3);
                } else if (is_peel_e2) {
                    if (e1 < e3) {
                        this->operator()(e2);
                    }
                } else {
                    if (e1 < e2) {
                        this->operator()(e3);
                    }
                }
            }
        }
    }
};

#ifdef SUP_STAT

inline void PrintSupStat(int level){
    stringstream ss;
    auto num_threads = omp_get_num_threads();
    auto sup_update_num_arr = SupportUpdater::sup_update_num_arr;
    for (auto i = 0; i < num_threads; i++) {
        sup_update_num_arr[i] = sup_update_num_arr[i * CACHE_LINE_ENTRY];
    }
    ss << pretty_print_array(&sup_update_num_arr.front(), num_threads);

    log_info("Current Level: %d, SupUpdates: %s, Total: %'zu", level, ss.str().c_str(),
             accumulate(begin(sup_update_num_arr), begin(sup_update_num_arr) + num_threads,
                        (size_t) 0));
}
#endif