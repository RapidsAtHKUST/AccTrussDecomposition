#ifndef _HIPR_H_
#define _HIPR_H_

#include "types.h"

excessType min_cut(long _n, long _m, node *_nodes, arc *_arcs, cType *_cap, node *_source, node *_sink, long _nMin);

void globalUpdate ();

#define forAllNodes(i) for ( i = nodes; i != sentinelNode; i++ )
#define nNode( i ) ( (i) - nodes + nMin )

extern node   *sentinelNode;        /* end of the node list marker */
extern long   nMin;                 /* smallest node id */
extern node   *nodes;               /* array of nodes */

#endif
