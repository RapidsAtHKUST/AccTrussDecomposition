#pragma once

template<typename T>
int ComputeCNHashBitVec(graph_t *g, uint32_t offset_beg, uint32_t offset_end, T &neighbor_bits) {
    auto cn_count = 0;
    for (auto offset = offset_beg; offset < offset_end; offset++) {
        if (neighbor_bits[g->adj[offset]]) {
            cn_count++;
        }
    }
    return cn_count;
}