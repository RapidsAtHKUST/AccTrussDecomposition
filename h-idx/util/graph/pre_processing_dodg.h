#pragma once

#include <future>
#include "pre_processing.h"
#include "util/stat.h"
#include "util/util.h"

bool RankLT(int du, int dv, int u, int v) {
//    assert(u != v);
    return du < dv || ((du == dv) && (u < v));
}

template<typename T, typename OFF>
void ConvertEdgeListToDODGCSR(OFF num_edges, pair<T, T> *&edge_lst,
                              uint32_t num_vertices, uint32_t *&deg_lst, OFF *&off, int32_t *&adj_lst,
                              int max_omp_threads) {
    ConvertEdgeListToDODGCSR(num_edges, edge_lst,
                             num_vertices, deg_lst, off, adj_lst,
                             max_omp_threads, [](size_t it) {
                return true;
            });
}

template<typename T, typename OFF>
void ConvertEdgeListToDODGCSRDiskBuffer(OFF num_edges, pair<T, T> *&edge_lst,
                                        uint32_t num_vertices, uint32_t *&deg_lst, OFF *&off, int32_t *&adj_lst,
                                        int max_omp_threads) {
    ConvertEdgeListToDODGCSRDiskBuffer(num_edges, edge_lst,
                                       num_vertices, deg_lst, off, adj_lst,
                                       max_omp_threads, [](size_t it) {
                return true;
            });
}

template<typename T, typename F, typename OFF>
void ConvertEdgeListToDODGCSRDiskBuffer(OFF num_edges, pair<T, T> *&edge_lst,
                                        uint32_t num_vertices, uint32_t *&deg_lst, OFF *&off, int32_t *&adj_lst,
                                        int max_omp_threads, F f) {
    Timer convert_timer;
    deg_lst = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    auto *dodg_deg_lst = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    off = (OFF *) malloc(sizeof(OFF) * (num_vertices + 1));
    auto cur_write_off = (OFF *) malloc(sizeof(OFF) * (num_vertices + 1));
    vector<OFF> histogram;

    auto io_future = std::async(std::launch::async, [=]() {
        auto tmp_file_fd = open("tmp_el.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        size_t size = num_edges * sizeof(int32_t) * 2;
        ftruncate(tmp_file_fd, size);
        auto write_buf = (pair<T, T> *) mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, tmp_file_fd, 0);
        memcpy(write_buf, edge_lst, size);
        return write_buf;
    });
#pragma omp parallel num_threads(max_omp_threads)
    {
        MemSetOMP(deg_lst, 0, num_vertices + 1);
        MemSetOMP(off, 0, num_vertices + 1);
#pragma omp single
        log_info("[%s]: InitTime: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // Histogram.
        EdgeListHistogram(num_vertices, num_edges, edge_lst, deg_lst, f);
        MemSetOMP(dodg_deg_lst, 0, num_vertices + 1);
#pragma omp for
        for (size_t i = 0u; i < num_edges; i++) {
            if (f(i)) {
                auto src = edge_lst[i].first;
                auto dst = edge_lst[i].second;
                if (RankLT(deg_lst[src], deg_lst[dst], src, dst))
                    __sync_fetch_and_add(&dodg_deg_lst[src], 1);
                else
                    __sync_fetch_and_add(&dodg_deg_lst[dst], 1);
            }
        }
#pragma omp single
        log_info("[%s]: Histogram Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // PrefixSum.
        InclusivePrefixSumOMP(histogram, off + 1, num_vertices, [&dodg_deg_lst](uint32_t it) {
            return dodg_deg_lst[it];
        });
#pragma omp single
        {
            log_debug("%zu", off[num_vertices]);
            assert(off[num_vertices] <= num_edges);
        }
        MemCpyOMP(cur_write_off, off, num_vertices + 1);

        // Write Edge List to File, Using Page Cache.
#pragma omp single
        {
            log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
            auto tmp = edge_lst;
            edge_lst = io_future.get();
            log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());

            size_t size = num_edges * sizeof(int32_t) * 2;
            free(tmp);
            madvise(edge_lst, size, MADV_SEQUENTIAL);

            if (adj_lst == nullptr) {
                log_info("Allocate Inside (adj_lst)...");
                adj_lst = (int32_t *) malloc(sizeof(int32_t) * off[num_vertices]);
            }
            log_info("[%s]: PrefixSum Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
        }

        // Scatter.
#pragma omp for schedule(dynamic, 32*4096/8)
        for (size_t i = 0; i < num_edges; i++) {
            if (f(i)) {
                auto src = edge_lst[i].first;
                auto dst = edge_lst[i].second;
                if (!RankLT(deg_lst[src], deg_lst[dst], src, dst)) {
                    swap(src, dst);
                }
                auto old_offset = __sync_fetch_and_add(&(cur_write_off[src]), 1);
                adj_lst[old_offset] = dst;
            }
        }
    }
    free(dodg_deg_lst);
    free(cur_write_off);
    log_info("[%s]: Total Conversion Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
}

void RevereseDODG(graph_t *org_g, graph_t *rev_g) {
    Timer convert_timer;
    auto max_omp_threads = omp_get_max_threads();

    rev_g->n = org_g->n;
    rev_g->m = org_g->m;
    auto num_vertices = org_g->n;
    rev_g->num_edges = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));

    auto *dodg_deg_lst = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    auto cur_write_off = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    vector<uint32_t> histogram;

#pragma omp parallel num_threads(max_omp_threads)
    {
        MemSetOMP(rev_g->num_edges, 0, num_vertices + 1);
        MemSetOMP(dodg_deg_lst, 0, num_vertices + 1);
        MemSetOMP(cur_write_off, 0, num_vertices + 1);
#pragma omp single
        log_info("[%s]: InitTime: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // Histogram.
#pragma omp for schedule(dynamic, 1000)
        for (size_t u = 0u; u < org_g->n; u++) {
            for (auto j = org_g->num_edges[u]; j < org_g->num_edges[u + 1]; j++) {
                auto v = org_g->adj[j];
                __sync_fetch_and_add(&dodg_deg_lst[v], 1);
            }
        }
#pragma omp single
        log_info("[%s]: Histogram Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // PrefixSum.
        InclusivePrefixSumOMP(histogram, rev_g->num_edges + 1, num_vertices, [&dodg_deg_lst](uint32_t it) {
            return dodg_deg_lst[it];
        });
        MemCpyOMP(cur_write_off, rev_g->num_edges, num_vertices + 1);
#pragma omp single
        {
            log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
            if (rev_g->adj == nullptr) {
                log_info("Allocate Inside (adj_lst)...");
                rev_g->adj = (int32_t *) malloc(sizeof(int32_t) * rev_g->num_edges[num_vertices]);
            }
            log_info("[%s]: PrefixSum Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
        }
        // Scatter.
#pragma omp for schedule(dynamic, 32*4096/8)
        for (size_t u = 0u; u < org_g->n; u++) {
            for (auto j = org_g->num_edges[u]; j < org_g->num_edges[u + 1]; j++) {
                auto src = org_g->adj[j];
                auto dst = u;
                auto old_offset = __sync_fetch_and_add(&(cur_write_off[src]), 1);
                rev_g->adj[old_offset] = dst;
            }
        }
        // Parallel Transform
#pragma omp for schedule(dynamic, 100)
        for (auto i = 0; i < rev_g->n; i++) {
            sort(rev_g->adj + rev_g->num_edges[i], rev_g->adj + rev_g->num_edges[i + 1]);
        }
    }
    free(dodg_deg_lst);
    free(cur_write_off);
    log_info("[%s]: Total Conversion Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
}

template<typename T, typename F, typename OFF>
void ConvertEdgeListToDODGCSR(OFF num_edges, pair<T, T> *&edge_lst,
                              uint32_t num_vertices, uint32_t *&deg_lst, OFF *&off, int32_t *&adj_lst,
                              int max_omp_threads, F f) {
    Timer convert_timer;
    deg_lst = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    auto *dodg_deg_lst = (uint32_t *) malloc(sizeof(uint32_t) * (num_vertices + 1));
    off = (OFF *) malloc(sizeof(OFF) * (num_vertices + 1));
    auto cur_write_off = (OFF *) malloc(sizeof(OFF) * (num_vertices + 1));
    vector<OFF> histogram;

#pragma omp parallel num_threads(max_omp_threads)
    {
        MemSetOMP(deg_lst, 0, num_vertices + 1);
        MemSetOMP(off, 0, num_vertices + 1);
#pragma omp single
        log_info("[%s]: InitTime: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // Histogram.
        EdgeListHistogram(num_vertices, num_edges, edge_lst, deg_lst, f);
        MemSetOMP(dodg_deg_lst, 0, num_vertices + 1);
#pragma omp for
        for (size_t i = 0u; i < num_edges; i++) {
            if (f(i)) {
                auto src = edge_lst[i].first;
                auto dst = edge_lst[i].second;
                if (RankLT(deg_lst[src], deg_lst[dst], src, dst))
                    __sync_fetch_and_add(&dodg_deg_lst[src], 1);
                else
                    __sync_fetch_and_add(&dodg_deg_lst[dst], 1);
            }
        }
#pragma omp single
        log_info("[%s]: Histogram Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());

        // PrefixSum.
        InclusivePrefixSumOMP(histogram, off + 1, num_vertices, [&dodg_deg_lst](uint32_t it) {
            return dodg_deg_lst[it];
        });
#pragma omp single
        {
            log_debug("%zu", off[num_vertices]);
            assert(off[num_vertices] <= num_edges);
        }
        MemCpyOMP(cur_write_off, off, num_vertices + 1);

        // Write Edge List to File, Using Page Cache.
#pragma omp single
        {
            log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());
            if (adj_lst == nullptr) {
                log_info("Allocate Inside (adj_lst)...");
                adj_lst = (int32_t *) malloc(sizeof(int32_t) * off[num_vertices]);
            }
            log_info("[%s]: PrefixSum Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
        }

        // Scatter.
#pragma omp for schedule(dynamic, 32*4096/8)
        for (size_t i = 0; i < num_edges; i++) {
            if (f(i)) {
                auto src = edge_lst[i].first;
                auto dst = edge_lst[i].second;
                if (!RankLT(deg_lst[src], deg_lst[dst], src, dst)) {
                    swap(src, dst);
                }
                auto old_offset = __sync_fetch_and_add(&(cur_write_off[src]), 1);
                adj_lst[old_offset] = dst;
            }
        }
    }
    free(dodg_deg_lst);
    free(cur_write_off);
    log_info("[%s]: Total Conversion Time: %.9lf s", __FUNCTION__, convert_timer.elapsed());
}

inline void ReorderDegDescendingDODG(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict,
                                     int32_t *&new_adj, uint32_t *&deg_lst) {
    Timer timer;

    auto max_omp_threads = omp_get_max_threads();
    auto max_deg = 0;
    auto *old_vid_dict_buffer = (int32_t *) malloc(sizeof(int32_t) * g.n);
    uint32_t *write_off = nullptr;
    uint32_t *bucket_ptrs = nullptr;
    auto histogram = vector<uint32_t>((max_omp_threads + 1) * CACHE_LINE_ENTRY, 0);

#pragma omp parallel num_threads(max_omp_threads)
    {
#pragma omp for reduction(max: max_deg)
        for (auto i = 0; i < g.n; i++) {
            max_deg = max<int>(max_deg, deg_lst[i]);
        }
#pragma omp single nowait
        {
            old_vid_dict = vector<int32_t>(g.n);
        }
#pragma omp for
        for (auto i = 0u; i < g.n; i++) {
            old_vid_dict_buffer[i] = i;
        }
        auto ptr = &old_vid_dict[0];
        BucketSortSmallBuckets(histogram, old_vid_dict_buffer, ptr, write_off, bucket_ptrs,
                               g.n, max_deg + 1, [deg_lst, old_vid_dict_buffer, max_deg](int i) {
                    auto u = old_vid_dict_buffer[i];
                    return max_deg - (deg_lst[u]);
                });
    }
    free(write_off);
    free(bucket_ptrs);
    free(old_vid_dict_buffer);

    log_info("Deg-descending time:  %.9lf s", timer.elapsed());

    Reorder(g, new_vid_dict, old_vid_dict, new_adj);
}
