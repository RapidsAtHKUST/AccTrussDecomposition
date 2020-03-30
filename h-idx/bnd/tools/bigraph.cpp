// Copyright 2006-2014 Yun Zhang
// Department of Computer Science
// University of Tennessee
//
// This file is part of MBEA.
//
// MBEA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/* API for Bit-Based Adjacency Matrix for bipartite graphs */
/* Implement functions defined in bigraph.h */
/* Graph Theory Team, Computer Science Department */
/* University of Tennessee, Knoxville */
/* Yun Zhang, yzhang@eecs.utk.edu, December 12, 2004 */
/* Last Updated: 12/18/2014 */

#include "bigraph.h"

#include <cassert>

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <chrono>
#include <cstring>
#include <queue>

#include "util/serialization/pretty_print.h"
#include "util/log/log.h"
#include "util/util.h"

using namespace std;
using namespace std::chrono;

BiGraph::BiGraph(string dir) {
    loadGraph(dir);
}

void BiGraph::printSum() {
    log_info("num_v1: %s; num_v2: %s; edge: %s", FormatWithCommas(num_v1).c_str(), FormatWithCommas(num_v2).c_str(),
             FormatWithCommas(num_edges).c_str());
}

void BiGraph::init(unsigned int num1, unsigned int num2) {
    num_v1 = num1;
    num_v2 = num2;
    num_edges = 0;

    neighbor_v1.resize(num_v1);
    neighbor_v2.resize(num_v2);

    degree_v1.resize(num_v1);
    degree_v2.resize(num_v2);

    fill_n(degree_v1.begin(), num_v1, 0);
    fill_n(degree_v2.begin(), num_v2, 0);
}

void BiGraph::loadGraph(string dir) {
    auto tmp_start = high_resolution_clock::now();
    log_info("load graph");

    unsigned int n1, n2;
    int u, v, r;
    string metaFile = dir + "graph.meta";
    string edgeFile = dir + "graph.e";

    FILE *metaGraph = fopen(metaFile.c_str(), "r");
    FILE *edgeGraph = fopen(edgeFile.c_str(), "r");

    if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2) {
        fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
        exit(1);
    }
    log_info("n1: %s, n2: %s", FormatWithCommas(n1).c_str(), FormatWithCommas(n2).c_str());

    init(n1, n2);
    while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF) {
        if (r != 2) {
            fprintf(stderr, "Bad file format: u v incorrect\n");
            exit(1);
        }

        addEdge(u, v);
        num_edges++;
    }
    log_info("edge num: %s", FormatWithCommas(num_edges).c_str());
    fclose(metaGraph);
    fclose(edgeGraph);

    auto load_end = high_resolution_clock::now();
    log_info("0) graph loading time: %.6f s",
             static_cast<float>(duration_cast<microseconds>(load_end - tmp_start).count()) / (pow(10, 6)));

#pragma omp parallel
    {
#pragma omp for schedule(dynamic, 500)
        for (int i = 0; i < num_v1; ++i) {
            neighbor_v1[i].shrink_to_fit();
            sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
        }
#pragma omp for schedule(dynamic, 500)
        for (int i = 0; i < num_v2; ++i) {
            neighbor_v2[i].shrink_to_fit();
            sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
        }
    }
    auto tmp_end = high_resolution_clock::now();
    log_info("0) graph sorting time: %.6f s",
             static_cast<float>(duration_cast<microseconds>(tmp_end - load_end).count()) / (pow(10, 6)));
}

void BiGraph::addEdge(vid_t u, vid_t v) {
    neighbor_v1[u].push_back(v);
    ++degree_v1[u];
    neighbor_v2[v].push_back(u);
    ++degree_v2[v];
}


bool BiGraph::isEdge(vid_t u, vid_t v) {
    return binary_search(neighbor_v1[u].begin(), neighbor_v1[u].begin() + degree_v1[u], v);
}

void BiGraph::pruneCore(num_t v1_deg_min, num_t v2_deg_min) {
    auto tmp_start = high_resolution_clock::now();
    vector<int> prunedV1(num_v1, 0);
    vector<int> prunedV2(num_v2, 0);

    // iterative BFS expansion
    // prunedV1 and prunedV2 are used for uniqueness of enqueueing
    vector<int> tmpV1Degree = degree_v1;
    vector<int> tmpV2Degree = degree_v2;
    queue<int> Q1;
    queue<int> Q2;
    for (int i = 0; i < num_v1; i++) {
        if (tmpV1Degree[i] < v1_deg_min) {
            Q1.emplace(i);
            prunedV1[i] = -1;
        }
    }
    for (int i = 0; i < num_v2; i++) {
        if (tmpV2Degree[i] < v2_deg_min) {
            Q2.emplace(i);
            prunedV2[i] = -1;
        }
    }

    while (!Q1.empty() || !Q2.empty()) {
        while (!Q1.empty()) {
            int u = Q1.front();
            Q1.pop();
            for (auto nei_u: neighbor_v1[u]) {
                if (prunedV2[nei_u] != -1) {
                    tmpV2Degree[nei_u]--;
                    if (tmpV2Degree[nei_u] < v2_deg_min) {
                        prunedV2[nei_u] = -1;
                        Q2.emplace(nei_u);
                    }
                }
            }
        }
        while (!Q2.empty()) {
            int v = Q2.front();
            Q2.pop();
            for (auto nei_v: neighbor_v2[v]) {
                if (prunedV1[nei_v] != -1) {
                    tmpV1Degree[nei_v]--;
                    if (tmpV1Degree[nei_v] < v1_deg_min) {
                        prunedV1[nei_v] = -1;
                        Q1.emplace(nei_v);
                    }
                }
            }
        }
    }

    auto tmp_end = high_resolution_clock::now();
    log_info("1) core pruning time: %.6f s",
             static_cast<float>(duration_cast<microseconds>(tmp_end - tmp_start).count()) / (pow(10, 6)));
    compressGraph(prunedV1, prunedV2);
}

void BiGraph::compressGraph(vector<int> &prunedV1, vector<int> &prunedV2) {
    auto tmp_start = high_resolution_clock::now();
    num_t order = 0;
    num_t n_num_v1 = 0;
    num_t n_num_v2 = 0;
    num_t n_edges = 0;

    // prunedV1 and prunedV2 are used as dictionaries, from 'prev vid' to 'new vid'
    for (int i = 0; i < num_v1; ++i) {
        if (prunedV1[i] != -1) {
            prunedV1[i] = order++;
        }
    }
    n_num_v1 = order;
    order = 0;
    for (int i = 0; i < num_v2; ++i) {
        if (prunedV2[i] != -1) {
            prunedV2[i] = order++;
        }
    }
    n_num_v2 = order;
    vector<vector<vid_t>> n_neighbor_v1(n_num_v1);
    vector<vector<vid_t>> n_neighbor_v2(n_num_v2);
    vector<int> n_degree_v1(n_num_v1);
    vector<int> n_degree_v2(n_num_v2);

#pragma omp parallel
    {
#pragma omp for schedule(dynamic, 500) reduction(+: n_edges)
        for (int i = 0; i < num_v1; ++i) {
            if (prunedV1[i] != -1) {
                int u = prunedV1[i];
                for (int j = 0; j < degree_v1[i]; ++j) {
                    int v = neighbor_v1[i][j];
                    if (prunedV2[v] != -1) {
                        n_neighbor_v1[u].push_back(prunedV2[v]);
                        n_edges++;
                    }
                }
            }
        }

        for (int i = 0; i < n_num_v1; ++i) {
// assume neighbors unique
#pragma omp for
            for (int j = 0; j < n_neighbor_v1[i].size(); ++j) {
                n_neighbor_v2[n_neighbor_v1[i][j]].push_back(i);
            }
        }

#pragma omp for schedule(dynamic, 500)
        for (int i = 0; i < n_num_v1; ++i) {
            n_neighbor_v1[i].shrink_to_fit();
            sort(n_neighbor_v1[i].begin(), n_neighbor_v1[i].end());
            n_degree_v1[i] = n_neighbor_v1[i].size();
        }

#pragma omp for schedule(dynamic, 500)
        for (int i = 0; i < n_num_v2; ++i) {
            n_neighbor_v2[i].shrink_to_fit();
            sort(n_neighbor_v2[i].begin(), n_neighbor_v2[i].end());
            n_degree_v2[i] = n_neighbor_v2[i].size();
        }
    }

    log_info("edge pruned: %s", FormatWithCommas(num_edges - n_edges).c_str());

    // assign tmp to the materialized ones
    num_v1 = n_num_v1;
    num_v2 = n_num_v2;
    num_edges = n_edges;
    swap(neighbor_v1, n_neighbor_v1);
    swap(neighbor_v2, n_neighbor_v2);
    swap(degree_v1, n_degree_v1);
    swap(degree_v2, n_degree_v2);

    auto tmp_end = high_resolution_clock::now();
    log_info("......compress graph time: %.6f s",
             static_cast<float>(duration_cast<microseconds>(tmp_end - tmp_start).count()) / (pow(10, 6)));
}

void BiGraph::clusterV1ViaExpansion(num_t v2_min) {
    is_in_cc = new bool[neighbor_v1.size()];
    memset(is_in_cc, false, neighbor_v1.size());
    log_info("|V1|:%d", neighbor_v1.size());
    DisjointSets disjoint_sets = DisjointSets(neighbor_v1.size());
    vector<int> cluster_id(neighbor_v1.size());

    long union_cnt = 0;
    long iter_cnt = 0;

    // 1st: prune V1, using expansion which yields poor locality, but more efficient
    auto tmp_start = high_resolution_clock::now();
#pragma omp parallel
    {
        // represents (vertex id, count)
        vector<pair<int, int>> counting_arr(neighbor_v1.size(), pair<int, int>(-1, 0));
#pragma omp for schedule(dynamic, 100) reduction(+:iter_cnt) reduction(+:union_cnt)
        for (auto u = 0u; u < neighbor_v1.size(); u++) {
            for (auto v: neighbor_v1[u]) {
                auto it_start = upper_bound(begin(neighbor_v2[v]), end(neighbor_v2[v]), u);
                for (auto it = it_start; it != end(neighbor_v2[v]); ++it) {
                    iter_cnt++;
                    int uu = *it;
                    auto &val_ref = counting_arr[uu].second;
                    // lazy clear
                    if (counting_arr[uu].first != u) {
                        counting_arr[uu].first = u;
                        val_ref = 0;
                    }
                    if (val_ref < v2_min) {
                        val_ref++;

                        if (val_ref >= v2_min) {
                            disjoint_sets.Union(u, uu);
                            union_cnt++;
                            is_in_cc[u] = true;
                            is_in_cc[uu] = true;
                        }
                    }
                }
            }
        }
    }
    auto all_end = high_resolution_clock::now();
    log_info("2) clustering time: %.6f s",
             static_cast<float>(duration_cast<microseconds>(all_end - tmp_start).count()) / (pow(10, 6)));

    long non_negative = 0;
    set<int> cluster_id_set;
    map<int, vector<int>> clusters;
    for (auto i = 0; i < neighbor_v1.size(); i++) {
        cluster_id[i] = is_in_cc[i] ? disjoint_sets.FindRoot(i) : -1;
        if (cluster_id[i] != -1) {
            cluster_id_set.emplace(cluster_id[i]);
            clusters[cluster_id[i]].emplace_back(i);
            non_negative++;
        }
    }

    int trivial_cnt = 0;
    for (auto id: cluster_id_set) {
        if (clusters[id].size() > 9)
            log_info("cluster %d, size: %s", id, FormatWithCommas(clusters[id].size()).c_str());
        else
            trivial_cnt++;
    }
    log_info("trivial cnt: %d", trivial_cnt);

    // 2nd: construct and compress
    vector<int> is_prune_v1(neighbor_v1.size(), -1);
    vector<int> is_prune_v2(neighbor_v2.size(), -1);
#pragma omp parallel for
    for (auto i = 0; i < neighbor_v1.size(); i++) {
        if (is_in_cc[i]) {
            is_prune_v1[i] = 0;
            for (auto v: neighbor_v1[i]) {
                is_prune_v2[v] = 0;
            }
        }
    }
    compressGraph(is_prune_v1, is_prune_v2);
    printSum();

    // 3rd: prune degree one vertices in V2
    long deg_one_v = 0;
    // should not use resize before clear, resize only construct new elements
    is_prune_v1.clear();
    is_prune_v1.resize(neighbor_v1.size(), 0);

    is_prune_v2.clear();
    is_prune_v2.resize(neighbor_v2.size(), 0);

#pragma omp parallel for reduction(+:deg_one_v)
    for (auto i = 0; i < neighbor_v2.size(); i++) {
        if (degree_v2[i] == 1) {
            is_prune_v2[i] = -1;
            deg_one_v++;
        }
    }
    log_info("deg one |V2|: %s", FormatWithCommas(deg_one_v).c_str());
    compressGraph(is_prune_v1, is_prune_v2);
    printSum();

    log_info("num of clusters: %d, candidates |V1|: %s", cluster_id_set.size(),
             FormatWithCommas(non_negative).c_str());
    log_info("iter: %s, union_cnt: %s", FormatWithCommas(iter_cnt).c_str(),
             FormatWithCommas(union_cnt).c_str());

    delete[]is_in_cc;
}
