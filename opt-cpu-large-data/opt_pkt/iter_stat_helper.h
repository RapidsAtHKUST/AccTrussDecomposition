#pragma once


template<typename T>
string stl_to_string(T &stl) {
    stringstream ss;
    ss << stl;
    return ss.str();
}

class IterStatTLS {
public:
    Timer local_timer;
    double triTime = 0;
    double sync_time = 0;
    double shrinkTime = 0;
    double scanTime = 0;
    double procTime = 0;

#ifdef LOCAL_STAT
    vector<double> local_sync_time_arr_;
    vector<double> local_shrink_time_arr_;
    vector<double> local_scan_time_arr_;
    vector<double> local_process_time_arr_;
    vector<size_t> local_queue_size_arr_;
#endif
    size_t local_shrink_times = 0;

    void RecordQueueSize(size_t queue_size) {
#ifdef LOCAL_STAT
        local_queue_size_arr_.emplace_back(queue_size);
#endif
    }

    void RecordSyncTime() {
        auto local_sync_time = local_timer.elapsed_and_reset();
        sync_time += local_sync_time;
#ifdef LOCAL_STAT
        local_sync_time_arr_.emplace_back(local_sync_time);
#endif
    }

    void RecordShrinkTime() {
        auto local_shrink_time = local_timer.elapsed_and_reset();
        shrinkTime += local_shrink_time;
#ifdef LOCAL_STAT
        local_shrink_time_arr_.emplace_back(local_shrink_time);
#endif
    }

    void RecordSCANTime() {
        auto local_scan_time = local_timer.elapsed_and_reset();
        scanTime += local_scan_time;
#ifdef LOCAL_STAT
        local_scan_time_arr_.emplace_back(local_scan_time);
#endif
    }

    void RecordProcessTime() {
        auto local_process_time = local_timer.elapsed_and_reset();
        procTime += local_process_time;
#ifdef LOCAL_STAT
        local_process_time_arr_.emplace_back(local_process_time);
#endif
    }

    void RecordShrinkNum(size_t &num_of_shrinks) {
        num_of_shrinks++;
        local_shrink_times++;
    }

    void RecordIterNum(size_t &iter_num, size_t &local_iter_num) {
        iter_num++;
        local_iter_num++;
    }

    void ResetLocalTime() {
#ifdef LOCAL_STAT
        local_queue_size_arr_.clear();
        local_sync_time_arr_.clear();
        local_shrink_time_arr_.clear();
        local_scan_time_arr_.clear();
        local_process_time_arr_.clear();
#endif
    }

    void PrintIterStat(Timer &iter_timer, int todo, long numEdges,
                       int level, size_t &iter_num, size_t &local_iter_num) {
        log_trace("Current Level: %d, Elapsed Time: %.9lfs, Left/Total: %'lld/%'lld, "
                  "Local/Global-Iter#: %zu/%zu", level,
                  iter_timer.elapsed_and_reset(), todo, numEdges, local_iter_num, iter_num);
#ifdef LOCAL_STAT
        log_info("Current Level: %d, Local Sync Time: %s, Local Shrink Time: %s (Shrink#: %zu), "
                 "Local SCAN Time: %s, Local Process Time: %s, Queue Size: %s", level,
                 stl_to_string(local_sync_time_arr_).c_str(),
                 stl_to_string(local_shrink_time_arr_).c_str(),
                 local_shrink_times, stl_to_string(local_scan_time_arr_).c_str(),
                 stl_to_string(local_process_time_arr_).c_str(),
                 stl_to_string(local_queue_size_arr_).c_str());
#endif
        local_shrink_times = 0;
        local_iter_num = 0;
#ifdef SUP_STAT
        PrintSupStat(level);
#endif
    }

    void PrintFinalStat(int level, int num_of_shrinks) {
#ifdef SUP_STAT
        PrintSupStat(level);
#endif
        log_info("The end: #of Shrinks: %zu", num_of_shrinks);
#ifdef LOCAL_STAT
        log_info("Current Level: %d, Local Sync Time: %s, Local Shrink Time: %s (Shrink#: %zu), "
                 "Local SCAN Time: %s, Local Process Time: %s,  Queue Size: %s", level,
                 stl_to_string(local_sync_time_arr_).c_str(),
                 stl_to_string(local_shrink_time_arr_).c_str(), local_shrink_times,
                 stl_to_string(local_scan_time_arr_).c_str(), stl_to_string(local_process_time_arr_).c_str(),
                 stl_to_string(local_queue_size_arr_).c_str());
#endif
        log_info("Tri time: %.3lfs, Sync Time: %.3lfs, Shrink Time: %.3lfs, "
                 "Scan Time: %.3lfs, Proc Time: %.3lfs", triTime, sync_time, shrinkTime, scanTime, procTime);
        log_info("PKT-intersection-Time (Sum up Above Five): %9.3lfs",
                 triTime + sync_time + shrinkTime + scanTime + procTime);
    }

};