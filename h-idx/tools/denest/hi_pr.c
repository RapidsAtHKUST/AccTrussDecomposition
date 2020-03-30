/* Maximum flow - highest lavel push-relabel algorithm */
/* COPYRIGHT C 1995, 2000 by IG Systems, Inc., igsys@eclipse.net */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "values.h"
#include "types.h"          /* type definitions */
#include "parser.c"         /* parser */
#include "timer.c"          /* timing routine */


/*
#define GLOB_UPDT_FREQ 0.5
*/
#define GLOB_UPDT_FREQ 0.5
#define ALPHA 6
#define BETA 12

#define WHITE 0
#define GREY 1
#define BLACK 2

/* global variables */

long   n;                    /* number of nodes */
long   m;                    /* number of arcs */
long   nm;                   /* n + ALPHA * m */
long   nMin;                 /* smallest node id */
node   *nodes;               /* array of nodes */
arc    *arcs;                /* array of arcs */
bucket *buckets;             /* array of buckets */
cType  *cap;                 /* array of capacities */
node   *source;              /* source node pointer */
node   *sink;                /* sink node pointer */
//node   **queue;              /* queue for BFS */
//node   **qHead, **qTail, **qLast;     /* queue pointers */
long   dMax;                 /* maximum label */
long   aMax;                 /* maximum actie node label */
long   aMin;                 /* minimum active node label */
double flow;                 /* flow value */
long pushCnt  = 0;           /* number of pushes */
long relabelCnt   = 0;       /* number of relabels */
long updateCnt    = 0;       /* number of updates */
long gapCnt   = 0;           /* number of gaps */
long gNodeCnt = 0;           /* number of nodes after gap */  
float t, t2;                 /* for saving times */
node   *sentinelNode;        /* end of the node list marker */
arc *stopA;                  /* used in forAllArcs */
long workSinceUpdate=0;      /* the number of arc scans since last update */
float globUpdtFreq;          /* global update frequency */

/* macros */

#define forAllNodes(i) for ( i = nodes; i != sentinelNode; i++ )
#define forAllArcs(i,a) for (a = i->first, stopA = (i+1)->first; a != stopA; a++)

#define nNode( i ) ( (i) - nodes + nMin )
#define nArc( a )  ( ( a == NULL )? -1 : (a) - arcs )

#define min( a, b ) ( ( (a) < (b) ) ? a : b )

/* FIFO queue for BFS macros */
/*
#define qInit() \
{\
  qHead = qTail = queue;\
}

#define qEmpty ( qHead == qTail )

#define qEnqueue(i) \
{\
  *qTail = i;\
  if ( qTail == qLast ) qTail = queue;\
  else qTail++;\
}

#define qDequeue(i) \
{\
  i = *qHead;\
  if ( qHead == qLast ) qHead = queue;\
  else qHead++;\
}
*/

/* 
   bucket macros:
   bucket's active node list is singly-linked
     operations aAdd, aRemove (from the front)
   bucket's inactive list is doubly-linked
     operations iAdd, iDelete (from arbitrary position)
*/

long i_dist;

#define aAdd(l,i)\
{\
  i->bNext = l->firstActive;\
  l->firstActive = i;\
  i_dist = i->d;\
  if (i_dist < aMin)\
    aMin = i_dist;\
  if (i_dist > aMax)\
    aMax = i_dist;\
  if (dMax < aMax)\
    dMax = aMax;\
}

/* i must be the first element */
#define aRemove(l,i)\
{\
  l->firstActive = i->bNext;\
}

node *i_next, *i_prev;
#define iAdd(l,i)\
{\
  i_next = l->firstInactive;\
  i->bNext = i_next;\
  i->bPrev = sentinelNode;\
  i_next->bPrev = i;\
  l->firstInactive = i;\
}

#define iDelete(l,i)\
{\
  i_next = i->bNext;\
  if (l->firstInactive == i) {\
    l->firstInactive = i_next;\
    i_next->bPrev = sentinelNode;\
  }\
  else {\
    i_prev = i->bPrev;\
    i_prev->bNext = i_next;\
    i_next->bPrev = i_prev;\
  }\
}

/* allocate datastructures, initialize related variables */

int allocDS( )

{

  nm = ALPHA * n + m;
  /*
  queue = (node**) calloc ( n, sizeof (node*) );
  if ( queue == NULL ) return ( 1 );
  qLast = queue + n - 1;
  qInit();
  */
  buckets = (bucket*) calloc ( n+2, sizeof (bucket) );
  if ( buckets == NULL ) return ( 1 );

  sentinelNode = nodes + n;
  sentinelNode->first = arcs + 2*m;

  return ( 0 );

} /* end of allocate */


void init( )

{
  node  *i;        /* current node */
  int overflowDetected;
  bucket *l;
  arc *a;
#ifdef EXCESS_TYPE_LONG
  double testExcess;
#endif
#ifndef OLD_INIT
  unsigned long delta;
#endif

  // initialize excesses

  forAllNodes(i) {
    i->excess = 0;
    i->current = i->first;
    forAllArcs(i, a)
      a->resCap = cap[a-arcs];
  }

  for (l = buckets; l <= buckets + n-1; l++) {
    l -> firstActive   = sentinelNode;
    l -> firstInactive  = sentinelNode;
  }
    
  overflowDetected = 0;
#ifdef EXCESS_TYPE_LONG
  testExcess = 0;
  forAllArcs(source,a) {
    if (a->head != source) {
      testExcess += a->resCap;
    }
  }
  if (testExcess > MAXLONG) {
    printf("c WARNING: excess overflow. See README for details.\nc\n");
    overflowDetected = 1;
  }
#endif
#ifdef OLD_INIT
  source -> excess = MAXLONG;
#else
  if (overflowDetected) {
    source -> excess = MAXLONG;
  }
  else {
    source->excess = 0;
    forAllArcs(source,a) {
      if (a->head != source) {
	pushCnt ++;
	delta = a -> resCap;
	a -> resCap -= delta;
	(a -> rev) -> resCap += delta;
	a->head->excess += delta;
      }
    }
  }

  /*  setup labels and buckets */
  l = buckets + 1;
    
  aMax = 0;
  aMin = n;
    
  forAllNodes(i) {
    if (i == sink) {
      i->d = 0;
      iAdd(buckets,i);
      continue;
    }
    if ((i == source) && (!overflowDetected)) {
      i->d = n;
    }
    else
      i->d = 1;
    if (i->excess > 0) {
      /* put into active list */
      aAdd(l,i);
    }
    else { /* i -> excess == 0 */
      /* put into inactive list */
      if (i->d < n)
	iAdd(l,i);
    }
  }
  dMax = 1;
#endif

  //  dMax = n-1;
  //  flow = 0.0;

} /* end of init */

void checkMax()

{
  bucket *l;

  for (l = buckets + dMax + 1; l < buckets + n; l++) {
    assert(l->firstActive == sentinelNode);
    assert(l->firstInactive == sentinelNode);
  }
}

/* global update via backward breadth first search from the sink */

void globalUpdate ()

{

  node  *i, *j;       /* node pointers */
  arc   *a;           /* current arc pointers  */
  bucket *l, *jL;          /* bucket */
  long curDist, jD;
  long state;


  updateCnt ++;

  /* initialization */

  forAllNodes(i)
    i -> d = n;
  sink -> d = 0;

  for (l = buckets; l <= buckets + dMax; l++) {
    l -> firstActive   = sentinelNode;
    l -> firstInactive  = sentinelNode;
  }

  dMax = aMax = 0;
  aMin = n;

  /* breadth first search */

  // add sink to bucket zero

  iAdd(buckets, sink);
  for (curDist = 0; 1; curDist++) {

    state = 0;
    l = buckets + curDist;
    jD = curDist + 1;
    jL = l + 1;
    /*
    jL -> firstActive   = sentinelNode;
    jL -> firstInactive  = sentinelNode;
    */

    if ((l->firstActive == sentinelNode) && 
	(l->firstInactive == sentinelNode))
      break;

    while (1) {

      switch (state) {
      case 0: 
	i = l->firstInactive;
	state = 1;
	break;
      case 1:
	i = i->bNext;
	break;
      case 2:
	i = l->firstActive;
	state = 3;
	break;
      case 3:
	i = i->bNext;
	break;
      default: 
	assert(0);
	break;
      }
      
      if (i == sentinelNode) {
	if (state == 1) {
	  state = 2;
	  continue;
	}
	else {
	  assert(state == 3);
	  break;
	}
      }

      /* scanning arcs incident to node i */
      forAllArcs(i,a) {
	if (a->rev->resCap > 0 ) {
	  j = a->head;
	  if (j->d == n) {
	    j->d = jD;
	    j->current = j->first;
	    if (jD > dMax) dMax = jD;
	    
	    if (j->excess > 0) {
	      /* put into active list */
	      aAdd(jL,j);
	    }
	    else {
	      /* put into inactive list */
	      iAdd(jL,j);
	    }
	  }
	}
      } /* node i is scanned */ 
    }
  }

} /* end of global update */

/* second stage -- preflow to flow */
void stageTwo ( )
/*
   do dsf in the reverse flow graph from nodes with excess
   cancel cycles if found
   return excess flow in topological order
*/

/*
   i->d is used for dfs labels 
   i->bNext is used for topological order list
   buckets[i-nodes]->firstActive is used for DSF tree
*/

{
  node *i, *j, *tos, *bos, *restart, *r;
  arc *a;
  cType delta;

  /* deal with self-loops */
  forAllNodes(i) {
    forAllArcs(i,a)
      if ( a -> head == i ) {
	a -> resCap = cap[a - arcs];
      }
  }

  /* initialize */
  tos = bos = NULL;
  forAllNodes(i) {
    i -> d = WHITE;
    //    buckets[i-nodes].firstActive = NULL;
    buckets[i-nodes].firstActive = sentinelNode;
    i -> current = i -> first;
  }

  /* eliminate flow cycles, topologicaly order vertices */
  forAllNodes(i)
    if (( i -> d == WHITE ) && ( i -> excess > 0 ) &&
	( i != source ) && ( i != sink )) {
      r = i;
      r -> d = GREY;
      do {
	for ( ; i->current != (i+1)->first; i->current++) {
	  a = i -> current;
	  if (( cap[a - arcs] == 0 ) && ( a -> resCap > 0 )) { 
	    j = a -> head;
	    if ( j -> d == WHITE ) {
	      /* start scanning j */
	      j -> d = GREY;
	      buckets[j-nodes].firstActive = i;
	      i = j;
	      break;
	    }
	    else
	      if ( j -> d == GREY ) {
		/* find minimum flow on the cycle */
		delta = a -> resCap;
		while ( 1 ) {
		  delta = min ( delta, j -> current -> resCap );
		  if ( j == i )
		    break;
		  else
		    j = j -> current -> head;
		}

		/* remove delta flow units */
		j = i;
		while ( 1 ) {
		  a = j -> current;
		  a -> resCap -= delta;
		  a -> rev -> resCap += delta;
		  j = a -> head;
		  if ( j == i )
		    break;
		}
	  
		/* backup DFS to the first saturated arc */
		restart = i;
		for ( j = i -> current -> head; j != i; j = a -> head ) {
		  a = j -> current;
		  if (( j -> d == WHITE ) || ( a -> resCap == 0 )) {
		    j -> current -> head -> d = WHITE;
		    if ( j -> d != WHITE )
		      restart = j;
		  }
		}
	  
		if ( restart != i ) {
		  i = restart;
		  i->current++;
		  break;
		}
	      }
	  }
	}

	if (i->current == (i+1)->first) {
	  /* scan of i complete */
	  i -> d = BLACK;
	  if ( i != source ) {
	    if ( bos == NULL ) {
	      bos = i;
	      tos = i;
	    }
	    else {
	      i -> bNext = tos;
	      tos = i;
	    }
	  }

	  if ( i != r ) {
	    i = buckets[i-nodes].firstActive;
	    i->current++;
	  }
	  else
	    break;
	}
      } while ( 1 );
    }


  /* return excesses */
  /* note that sink is not on the stack */
  if ( bos != NULL ) {
    for ( i = tos; i != bos; i = i -> bNext ) {
      a = i -> first;
      while ( i -> excess > 0 ) {
	if (( cap[a - arcs] == 0 ) && ( a -> resCap > 0 )) {
	  if (a->resCap < i->excess)
	    delta = a->resCap;
	  else
	    delta = i->excess;
	  a -> resCap -= delta;
	  a -> rev -> resCap += delta;
	  i -> excess -= delta;
	  a -> head -> excess += delta;
	}
	a++;
      }
    }
    /* now do the bottom */
    i = bos;
    a = i -> first;
    while ( i -> excess > 0 ) {
      if (( cap[a - arcs] == 0 ) && ( a -> resCap > 0 )) {
	if (a->resCap < i->excess)
	  delta = a->resCap;
	else
	  delta = i->excess;
	a -> resCap -= delta;
	a -> rev -> resCap += delta;
	i -> excess -= delta;
	a -> head -> excess += delta;
      }
      a++;
    }
  }
}


/* gap relabeling */

int gap (emptyB)
     bucket *emptyB;

{

  bucket *l;
  node  *i; 
  long  r;           /* index of the bucket before l  */
  int   cc;          /* cc = 1 if no nodes with positive excess before
		      the gap */

  gapCnt ++;
  r = ( emptyB - buckets ) - 1;

  /* set labels of nodes beyond the gap to "infinity" */
  for ( l = emptyB + 1; l <= buckets + dMax; l ++ ) {
    // this does nothing for high level selection 
    // but is needed for wave initialization
#ifdef WAVE_INIT
    for (i = l -> firstActive; i != sentinelNode; i = i -> bNext) {
      i -> d = n;
      gNodeCnt++;
    }
    l -> firstActive = sentinelNode;
#endif
    for ( i = l -> firstInactive; i != sentinelNode; i = i -> bNext ) {
      i -> d = n;
      gNodeCnt ++;
    }

    l -> firstInactive = sentinelNode;
  }

  cc = ( aMin > r ) ? 1 : 0;

  dMax = r;
  aMax = r;

  return ( cc );

}

/*--- relabelling node i */

long relabel (i)

node *i;   /* node to relabel */

{

  node  *j;
  long  minD;     /* minimum d of a node reachable from i */
  arc   *minA;    /* an arc which leads to the node with minimal d */
  arc   *a;

  assert(i->excess > 0);

  relabelCnt++;
  workSinceUpdate += BETA;

  i->d = minD = n;
  minA = NULL;

  /* find the minimum */
  forAllArcs(i,a) {
    workSinceUpdate++;
    if (a -> resCap > 0) {
      j = a -> head;
      if (j->d < minD) {
	minD = j->d;
	minA = a;
      }
    }
  }

  minD++;
      
  if (minD < n) {

    i->d = minD;
    i->current = minA;

    if (dMax < minD) dMax = minD;

  } /* end of minD < n */
      
  return ( minD );

} /* end of relabel */


/* discharge: push flow out of i until i becomes inactive */

void discharge (i)

node  *i;

{

  node  *j;                 /* sucsessor of i */
  long  jD;                 /* d of the next bucket */
  bucket *lj;               /* j's bucket */
  bucket *l;                /* i's bucket */
  arc   *a;                 /* current arc (i,j) */
  cType  delta;
  arc *stopA;

  assert(i->excess > 0);
  assert(i != sink);
  do {

    jD = i->d - 1;
    l = buckets + i->d;

    /* scanning arcs outgoing from  i  */
    for (a = i->current, stopA = (i+1)->first; a != stopA; a++) {
      if (a -> resCap > 0) {
	j = a -> head;

	if (j->d == jD) {
	  pushCnt ++;
	  if (a->resCap < i->excess)
	    delta = a->resCap;
	  else
	    delta = i->excess;
	  a->resCap -= delta;
	  a->rev->resCap += delta;

	  if (j != sink) {

	    lj = buckets + jD;

	    if (j->excess == 0) {
	      /* remove j from inactive list */
	      iDelete(lj,j);
	      /* add j to active list */
	      aAdd(lj,j);
	    }
	  }

	  j -> excess += delta;
	  i -> excess -= delta;
	  
	  if (i->excess == 0) break;

	} /* j belongs to the next bucket */
      } /* a  is not saturated */
    } /* end of scanning arcs from  i */

    if (a == stopA) {
      /* i must be relabeled */
      relabel (i);

      if (i->d == n) break;
      if ((l -> firstActive == sentinelNode) && 
	  (l -> firstInactive == sentinelNode)
	  )
	gap (l);

      if (i->d == n) break;
    }
    else {
      /* i no longer active */
      i->current = a;
      /* put i on inactive list */
      iAdd(l,i);
      break;
    }
  } while (1);
}


// go from higher to lower buckets, push flow
void wave() {

  node   *i;
  bucket  *l;

  for (l = buckets + aMax; l > buckets; l--) {
    for (i = l->firstActive; i != sentinelNode; i = l->firstActive) {
      aRemove(l,i);

      assert(i->excess > 0);
      discharge (i);

    }
  }
}


/* first stage  -- maximum preflow*/

void stageOne ( )

{

  node   *i;
  bucket  *l;             /* current bucket */


#if defined(INIT_UPDATE) || defined(OLD_INIT) || defined(WAVE_INIT)
  globalUpdate ();
#endif

  workSinceUpdate = 0;

#ifdef WAVE_INIT
  wave();
#endif  

  /* main loop */
  while ( aMax >= aMin ) {
    l = buckets + aMax;
    i = l->firstActive;

    if (i == sentinelNode)
      aMax--;
    else {
      aRemove(l,i);

      assert(i->excess > 0);
      discharge (i);

      if (aMax < aMin)
	break;

      /* is it time for global update? */
      if (workSinceUpdate * globUpdtFreq > nm) {
	globalUpdate ();
	workSinceUpdate = 0;
      }

    }
    
  } /* end of the main loop */
    
  flow = sink -> excess;

} 

void deallocDS() {
    free(buckets);
}

excessType min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin)

    long _n;
    long _m;
    node *_nodes;
    arc *_arcs;
    cType *_cap;
    node *_source;
    node *_sink;
    long _nMin;

{
    n = _n;
    m = _m;
    nodes = _nodes;
    arcs = _arcs;
    cap = _cap;
    source = _source;
    sink = _sink;
    nMin = _nMin;

#ifdef CHECK_SOLUTION
    node *i;
    arc *a;
    excessType sum;
    bucket *l;
#endif

    node *j;
    int  cc;
    
    cc = allocDS();
    if ( cc ) { fprintf ( stderr, "Allocation error\n"); exit ( 1 ); }

    t = timer();
    t2 = t;

    init();
    stageOne ( );

    t2 = timer() - t2;

    fprintf (stderr, "flow:       %12.01f\n", flow);

    fprintf (stderr, "cut tm:      %10.2f\n", t2);

#ifdef CHECK_SOLUTION

    /* check if you have a flow (pseudoflow) */
    /* check arc flows */
    forAllNodes(i) {
        forAllArcs(i,a) {
            if (cap[a - arcs] > 0) /* original arc */
                if ((a->resCap + a->rev->resCap != cap[a - arcs]) 
                        || (a->resCap < 0)
                        || (a->rev->resCap < 0)) {
                    printf("ERROR: bad arc flow\n");
                    exit(2);
                }
        }
    }

    /* check conservation */
    forAllNodes(i)
        if ((i != source) && (i != sink)) {
            if (i->excess < 0) {
                printf("ERROR: nonzero node excess\n");
                exit(2);
            }

            sum = 0;
            forAllArcs(i,a) {
                if (cap[a - arcs] > 0) /* original arc */
                    sum -= cap[a - arcs] - a->resCap;
                else
                    sum += a->resCap;
            }

            if (i->excess != sum) {
                printf("ERROR: conservation constraint violated\n");
                exit(2);
            }
        }

    /* check if mincut is saturated */
    aMax = dMax = 0;
    for (l = buckets; l < buckets + n; l++) {
        l->firstActive = sentinelNode;
        l->firstInactive = sentinelNode;
    }
    globalUpdate();
    if (source->d < n) {
        printf("ERROR: the solution is not optimal\n");
        exit(2);
    }

    printf("c\nc Solution checks (feasible and optimal)\nc\n");
#endif

#ifdef PRINT_STAT
    printf ("c pushes:      %10ld\n", pushCnt);
    printf ("c relabels:    %10ld\n", relabelCnt);
    printf ("c updates:     %10ld\n", updateCnt);
    printf ("c gaps:        %10ld\n", gapCnt);
    printf ("c gap nodes:   %10ld\n", gNodeCnt);
    printf ("c\n");
#endif

#ifdef PRINT_CUT
    globalUpdate();
    printf ("c nodes on the sink side\n");
    forAllNodes(j)
        if (j->d < n)
            printf("c %ld\n", nNode(j));

#endif

    return sink -> excess;
}

#ifndef NO_MAIN
int main() {
    long _n;
    long _m;
    node *_nodes;
    arc *_arcs;
    cType *_cap;
    node *_source;
    node *_sink;
    long _nMin;
    parse( &_n, &_m, &_nodes, &_arcs, &_cap, &_source, &_sink, &_nMin );
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    min_cut(_n, _m, _nodes, _arcs, _cap, _source, _sink, _nMin);
    return 0;
}
#endif
