#pragma once

#include <unordered_map>

inline void atomic_add(int *ptr, int add_val) {
    int64_t old_val;
    int64_t new_val;
    do {
        old_val = *ptr;
        new_val = old_val + add_val;
    } while (!__sync_bool_compare_and_swap(ptr, old_val, new_val));
}

struct UnionFind {
    int *parent;

    explicit UnionFind(int size) {
        parent = new int[size];


#pragma omp parallel for
        for (int i = 0; i < size; i++)parent[i] = i;
    }

    ~UnionFind() {
        delete[] parent;
    }

    int FindRoot(int x) {
        return (parent[x] < 0 || parent[x] == x) ? x : parent[x] = FindRoot(parent[x]);
    }

    void UnionThreadSafe(int u, int v) {
        int rx, ry;
        do {
            rx = FindRoot(u);
            ry = FindRoot(v);
            int index;
            if (rx < ry) {
                index = rx;
                rx = ry;
                ry = index;
            }
            if (rx == ry)break;
        } while (!__sync_bool_compare_and_swap(&(parent[rx]), rx, ry));
    }
};