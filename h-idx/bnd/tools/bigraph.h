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

/* API for Bit-Based Adjacency Matrix for undirected bipartite graphs */
/* Graph Theory Team, Computer Science Department */
/* University of Tennessee, Knoxville */
/* Yun Zhang, yzhang@cs.utk.edu, September 2006 */
/* Updated: 12/17/2013 */

#ifndef __BIGRAPH_H
#define __BIGRAPH_H

#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <unordered_set>

#include "bnd/main.h"

#include "util/containers/ThreadSafeDisjointSet.h"

using namespace std;
typedef vertex vid_t;
typedef int num_t;

class BiGraph {
private:
    num_t num_v1;
    num_t num_v2;
    num_t num_edges;

    std::vector<std::vector<vid_t>> neighbor_v1;
    std::vector<std::vector<vid_t>> neighbor_v2;

    std::vector<int> degree_v1;
    std::vector<int> degree_v2;
private:
    // clustering on the conceptual graph to get similar u
    bool *is_in_cc;
private:
    void init(unsigned int num_v1, unsigned int num_v2);

    void loadGraph(std::string dir);

    void compressGraph(std::vector<int> &prunedV1, std::vector<int> &prunedV2);

public:
    explicit BiGraph(std::string dir);

    ~BiGraph() = default;

    void addEdge(vid_t u, vid_t v);

    bool isEdge(vid_t u, vid_t v);

    num_t getV1Num() { return num_v1; }

    num_t getV2Num() { return num_v2; }

    num_t getV1Degree(vid_t u) { return degree_v1[u]; }

    num_t getV2Degree(vid_t u) { return degree_v2[u]; }

    std::vector<vid_t> &getV2Neighbors(vid_t u) { return neighbor_v2[u]; }

    std::vector<vid_t> &getV1Neighbors(vid_t u) { return neighbor_v1[u]; }

    void printSum();

public:
    void pruneCore(num_t v1_deg_min, num_t v2_deg_min);

    void clusterV1ViaExpansion(num_t v2_min);
};

#endif  /* __BIGRAPH_H */

