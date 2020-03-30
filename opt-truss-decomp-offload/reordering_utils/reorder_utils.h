#pragma once

#include "../util/graph.h"

void PKC(graph_t *g, int *deg, int num_of_threads);

void ReorderKCoreDegeneracy(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict);

void ReorderRandom(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict);

void ReorderDegDescending(graph_t &g, vector<int32_t> &new_vid_dict, vector<int32_t> &old_vid_dict);

void ReorderWithFileDict(graph_t &g, string dir, string reorder_method, vector<int32_t> &new_vid_dict,
                         vector<int32_t> &old_vid_dict);

void ReorderWrapper(graph_t &g, string dir, string reorder_method, vector<int32_t> &new_vid_dict,
                         vector<int32_t> &old_vid_dict);