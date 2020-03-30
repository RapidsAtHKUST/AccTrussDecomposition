#pragma once

#include <new>
#include <malloc.h>
#include "omp.h"
#include <util/search_util.h>

inline uint32_t get_log_size(int x) {
    int cnt = 0;
    for (; x > 0; cnt++) {
        x >>= 1;
    }
    return cnt;
}

inline uint32_t get_part_size(int i) {
    return i == 0 ? 0 : 1 << (get_log_size(i) - 1);
}

class RadixFilter {
    BoolArray<uint64_t> psum_occupied_bool_;
    graph_t *g_;
    int radix_val_;
public:
    explicit RadixFilter(graph_t *g) : g_(g), radix_val_(-1) {}

    void Construct(int u) {
        auto deg = g_->num_edges[u + 1] - g_->num_edges[u];
//        if (deg > 0) {        // assume deg > 0
        // 1: Histogram.
        constexpr int heuristic_factor = 16;
        auto partition_size = get_part_size(deg) * heuristic_factor;
        radix_val_ = partition_size - 1;
        psum_occupied_bool_ = BoolArray<uint64_t>(partition_size);
        auto radix_val = partition_size - 1;
        for (auto j = g_->num_edges[u]; j < g_->num_edges[u + 1]; j++) {
            auto v = g_->adj[j];
            auto bucket_id = v & radix_val;
            psum_occupied_bool_.set(bucket_id);
        }
//        }
    }

    bool PossibleExist(int v) {
        auto bucket_id = v & radix_val_;
        return psum_occupied_bool_.get(bucket_id);
    }
};

class RadixSet {
    vector<int> psum_arr_;
    BoolArray<uint64_t> psum_occupied_bool_;
    vector<int> tmp_;
    vector<int> hash_table_;
    graph_t *g_;

public:
    explicit RadixSet(graph_t *g) : g_(g) {
        psum_arr_.reserve(1024 * 1204 * 2);
        hash_table_.reserve(1024 * 1204 * 2);
    }

    void Construct(int u) {
        auto deg = g_->num_edges[u + 1] - g_->num_edges[u];
        if (deg > 0) {
            // 1: Histogram.
            constexpr int heuristic_factor = 16;
            auto partition_size = get_part_size(deg) * heuristic_factor;
            psum_arr_.resize(partition_size + 1);
            memset(&psum_arr_.front(), 0, psum_arr_.size() * sizeof(int));
            hash_table_.resize(deg);
            psum_occupied_bool_ = BoolArray<uint64_t>(psum_arr_.size());
            auto radix_val = partition_size - 1;
            for (auto j = g_->num_edges[u]; j < g_->num_edges[u + 1]; j++) {
                auto v = g_->adj[j];
                auto bucket_id = v & radix_val;
                psum_arr_[bucket_id + 1]++;
                psum_occupied_bool_.set(bucket_id);
            }
            // 2: PrefixSum.
            for (auto i = 0u; i < partition_size; i++) {
                psum_arr_[i + 1] += psum_arr_[i];
            }
            // 3: Scatter.
            tmp_.resize(psum_arr_.size());
            memcpy(&tmp_.front(), &psum_arr_.front(), sizeof(int) * psum_arr_.size());
            for (auto j = g_->num_edges[u]; j < g_->num_edges[u + 1]; j++) {
                auto v = g_->adj[j];
                auto bucket_id = v & radix_val;
                hash_table_[tmp_[bucket_id]++] = v;
            }
        } else {
            psum_arr_.clear();
        }
    }

    bool Exist(int v) {
//        if (psum_arr_.empty())return false;   // Assume not zero deg.

        auto partition_size = psum_arr_.size() - 1;

        auto radix_val = partition_size - 1;
        auto bucket_id = v & radix_val;

        if (psum_occupied_bool_.get(bucket_id)) {
            for (auto j = psum_arr_[bucket_id]; j < psum_arr_[bucket_id + 1]; j++) {
                if (hash_table_[j] == v) {
                    return true;
                }
            }
        }
        return false;
    }
};

class RadixHashMap {
public:
    using hash_entry_t = pair<int, eid_t>;

private:
    graph_t *g_;
    int size_;

    vector<vector<int>> psum_arr_arr_;

    // key (v) and eid for (u,v)
    vector<vector<pair<int, eid_t>>> hash_table_arr_;

public:

    explicit RadixHashMap(graph_t *g) : g_(g), size_(g_->n),
                                        psum_arr_arr_(size_), hash_table_arr_(size_) {
        // Construct in Parallel
#pragma omp parallel
        {
            ParallelPopulate();

#pragma omp for
            for (auto u = 0; u < size_; u++) {
                Construct(u);
            }
        }
    }

    void Construct(int u) {
        // 1: Histogram.
        auto &psum_arr = psum_arr_arr_[u];
        if (psum_arr.empty())return;

        auto &hash_table = hash_table_arr_[u];

        auto partition_size = psum_arr.size() - 1;

        auto radix_val = partition_size - 1;
        for (auto j = g_->num_edges[u]; j < g_->num_edges[u + 1]; j++) {
            auto v = g_->adj[j];
            auto bucket_id = v & radix_val;
//            assert(bucket_id < psum_arr.size());
            psum_arr[bucket_id + 1]++;
        }
        // 2: PrefixSum.
        for (auto i = 0u; i < partition_size; i++) {
            psum_arr[i + 1] += psum_arr[i];
        }
        // 3: Scatter.
        auto tmp = psum_arr;
        for (auto j = g_->num_edges[u]; j < g_->num_edges[u + 1]; j++) {
            auto v = g_->adj[j];
            auto bucket_id = v & radix_val;
            hash_table[tmp[bucket_id]++] = make_pair(v, g_->eid[j]);
        }
    }

    void find_u_psum_table_size(int u, vector<int> *&psum_arr_ptr, vector<hash_entry_t> *&hash_table_ptr,
                                uint32_t &radix_val) {
        psum_arr_ptr = &psum_arr_arr_[u];
        hash_table_ptr = &hash_table_arr_[u];

        auto partition_size = psum_arr_ptr->size() - 1;
        radix_val = partition_size - 1;
    }

    // Assume `psum_arr` is not empty.
    eid_t *get(vector<int> *psum_arr_ptr, vector<hash_entry_t> *hash_table_ptr,
               uint32_t radix_val, int v) {
        auto &psum_arr = *psum_arr_ptr;

        auto &hash_table = *hash_table_ptr;
        auto bucket_id = v & radix_val;
        for (auto j = psum_arr[bucket_id]; j < psum_arr[bucket_id + 1]; j++) {
            if (hash_table[j].first == v) {
                return &hash_table[j].second;
            }
        }
        return nullptr;
    }

    eid_t *get(int u, int v) {
        auto &psum_arr = psum_arr_arr_[u];
        if (psum_arr.empty())return nullptr;

        auto &hash_table = hash_table_arr_[u];

        auto partition_size = psum_arr.size() - 1;

        auto radix_val = partition_size - 1;
        auto bucket_id = v & radix_val;
        for (auto j = psum_arr[bucket_id]; j < psum_arr[bucket_id + 1]; j++) {
            if (hash_table[j].first == v) {
                return &hash_table[j].second;
            }
        }
        return nullptr;
    }

    void ParallelPopulate() {
#pragma omp for
        for (auto u = 0; u < size_; u++) {
            auto deg = g_->num_edges[u + 1] - g_->num_edges[u];
            if (deg > 0) {
                auto partition_size = get_part_size(deg);
                psum_arr_arr_[u] = vector<int>(partition_size + 1, 0);
            }
        }
#pragma omp for
        for (auto i = 0; i < size_; i++) {
            hash_table_arr_[i] = vector<hash_entry_t>(g_->num_edges[i + 1] - g_->num_edges[i]);
        }
    }

    void ManuallyFree() {
        Timer free_timer;
#pragma omp parallel
        {
#pragma omp for
            for (auto i = 0; i < size_; i++) {
                vector<int> tmp;
                psum_arr_arr_[i].swap(tmp);
            }
#pragma omp for
            for (auto i = 0; i < size_; i++) {
                vector<hash_entry_t> tmp;
                hash_table_arr_[i].swap(tmp);
            }
        }
        log_info("Free radix hash map cost: %.6lfs", free_timer.elapsed());
    }

    ~RadixHashMap() {
        ManuallyFree();
    }
};