#pragma once

#include <omp.h>

#include <numeric>

#include "util/serialization/pretty_print.h"
#include "util/containers/boolarray.h"
#define CACHE_LINE_ENTRY (16)

using word_type = uint32_t;

void PKT_scan(long numEdges, int *EdgeSupport, int level, eid_t *curr, long *currTail, bool *InCurr);

void PKT_processSubLevel_intersection_handling_skew(
        graph_t *g, eid_t *curr, bool *InCurr, long currTail, int *EdgeSupport,
        int level, eid_t *next, bool *InNext, long *nextTail, bool *processed,
        Edge *edgeIdtoEdge);

class SupportUpdaterLegacy {
    long *index_ptr;
    vid_t *buff;
    eid_t *next;
    int *EdgeSupport;
    bool *InNext;
    long *nextTail;
    int level;
    long BUFFER_SIZE;
public:
    SupportUpdaterLegacy(long *indexPtr, vid_t *buff, eid_t *next, int *edgeSupport, bool *inNext, long *nextTail,
                         int level, long bufferSize) : index_ptr(indexPtr), buff(buff),
                                                       next(next), EdgeSupport(edgeSupport),
                                                       InNext(inNext), nextTail(nextTail), level(level),
                                                       BUFFER_SIZE(bufferSize) {}

public:
    void operator                                                                                                                                                                                                                                                                                                                                                                                                                                                                       ()(eid_t updated_edge) {
        auto &index = *index_ptr;
        int supE2 = __sync_fetch_and_sub(&EdgeSupport[updated_edge], 1);
        if (supE2 == (level + 1)) {
            buff[index] = updated_edge;
            InNext[updated_edge] = true;
            index++;
        }

        if (supE2 <= level) {
            __sync_fetch_and_add(&EdgeSupport[updated_edge], 1);
        }

        if (index >= BUFFER_SIZE) {
            long tempIdx = __sync_fetch_and_add(nextTail, BUFFER_SIZE);
            memcpy(next + tempIdx, buff, sizeof(eid_t) * BUFFER_SIZE);
            index = 0;
        }
    }
};
