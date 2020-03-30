#pragma once

#include <algorithm>
#include <vector>

using namespace std;

using edge_lst_type = vector<pair<int32_t, int32_t>>;

void readDirEdgeList(char *filename, int &nVtx, uint32_t &nEdge, int *&adj, uint32_t *&xadj);

void readDirectory(char *filename, int &nVtx, uint32_t &nEdge, int *&adj_lst, uint32_t *&xadj);