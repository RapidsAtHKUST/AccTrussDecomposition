#pragma once

#include <atomic>
#include <iostream>

/**
     * source: https://github.com/wjakob/dset
 * Lock-free parallel disjoint set data structure (aka UNION-FIND)
 * with path compression and union by rank
 *
 * Supports concurrent FindRoot(), IsSameSet() and Union() calls as described
 * in the paper
 *
 * "Wait-free Parallel Algorithms for the Union-Find Problem"
 * by Richard J. Anderson and Heather Woll
 *
 * In addition, this class supports optimistic locking (try_lock/unlock)
 * of disjoint sets and a combined Union+unlock operation.
 *
 * \author Wenzel Jakob
 */
class DisjointSets {
public:
    explicit DisjointSets(uint32_t size) : data_size(size) {
        mData = new std::atomic<uint64_t>[size];
        for (uint32_t i = 0; i < size; ++i)
            mData[i] = (uint32_t) i;
    }

    ~DisjointSets() {
        free(mData);
    }

    uint32_t FindRoot(uint32_t id) const {
        while (id != parent(id)) {
            uint64_t value = mData[id];
            uint32_t new_parent = parent((uint32_t) value);
            uint64_t new_value =
                    (value & 0xFFFFFFFF00000000ULL) | new_parent;
            /* Try to update parent (may fail, that's ok) */
            if (value != new_value)
                mData[id].compare_exchange_weak(value, new_value);
            id = new_parent;
        }
        return id;
    }

    bool IsSameSet(uint32_t id1, uint32_t id2) const {
        for (;;) {
            id1 = FindRoot(id1);
            id2 = FindRoot(id2);
            if (id1 == id2)
                return true;
            if (parent(id1) == id1)
                return false;
        }
    }

    uint32_t Union(uint32_t id1, uint32_t id2) {
        for (;;) {
            id1 = FindRoot(id1);
            id2 = FindRoot(id2);

            if (id1 == id2)
                return id1;

            uint32_t r1 = rank(id1), r2 = rank(id2);

            if (r1 > r2 || (r1 == r2 && id1 < id2)) {
                std::swap(r1, r2);
                std::swap(id1, id2);
            }

            uint64_t oldEntry = ((uint64_t) r1 << 32) | id1;
            uint64_t newEntry = ((uint64_t) r1 << 32) | id2;

            if (!mData[id1].compare_exchange_strong(oldEntry, newEntry))
                continue;

            if (r1 == r2) {
                oldEntry = ((uint64_t) r2 << 32) | id2;
                newEntry = ((uint64_t) (r2 + 1) << 32) | id2;
                /* Try to update the rank (may fail, that's ok) */
                mData[id2].compare_exchange_weak(oldEntry, newEntry);
            }

            break;
        }
        return id2;
    }

    uint32_t size() const { return data_size; }

    uint32_t rank(uint32_t id) const {
        return ((uint32_t) (mData[id] >> 32)) & 0x7FFFFFFFu;
    }

    uint32_t parent(uint32_t id) const {
        return (uint32_t) mData[id];
    }

    friend std::ostream &operator<<(std::ostream &os, const DisjointSets &f) {
        for (size_t i = 0; i < f.size(); ++i)
            os << i << ": parent=" << f.parent(i) << ", rank=" << f.rank(i) << std::endl;
        return os;
    }

    uint32_t data_size;
    mutable std::atomic<uint64_t> *mData;
};
