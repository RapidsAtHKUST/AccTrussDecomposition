#ifndef KT_HMAP_H
#define KT_HMAP_H

#include "kt.h"
#include <stdbool.h>

typedef struct {
    int32_t hmsize;
    int32_t *map;
} kt_hmap_t;


static inline void hash_list(
        kt_hmap_t *const hmap,
        int32_t const *const elems,
        ssize_t const len) {
    int32_t const hmsize = hmap->hmsize;
    int32_t *const map = hmap->map;

    int32_t l;
    for (ssize_t e = 0; e < len; ++e) {
        int32_t const val = elems[e];
        if (val < 0) {
            continue;
        }

        for (l = (val & hmsize); map[l] != -1; l = ((l + 1) & hmsize));
        map[l] = val;
    }
}


static inline bool query_hmap(
        kt_hmap_t const *const hmap,
        int32_t const query) {
    int32_t const hmsize = hmap->hmsize;
    int32_t const *const map = hmap->map;

    int32_t l;
    for (l = (query & hmsize); map[l] != query && map[l] != -1; l = ((l + 1) & hmsize));

    return (map[l] == query);
}


static inline void clear_hmap(
        kt_hmap_t *const hmap,
        int32_t const *const elems,
        ssize_t const len) {
    int32_t const hmsize = hmap->hmsize;
    int32_t *const map = hmap->map;

    int32_t l;

    for (ssize_t e = 0; e < len; ++e) {
        int32_t const val = elems[e];
        if (val < 0) {
            continue;
        }
        for (l = (val & hmsize); map[l] != val; l = ((l + 1) & hmsize));
        map[l] = -1;
    }
}


kt_hmap_t *alloc_hmap(
        ssize_t max_elems);

void free_hmap(
        kt_hmap_t *hmap);


#endif
