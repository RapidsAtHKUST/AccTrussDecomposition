## Complexity

According to the **KCore** O(m * h-idx),
**KTruss** is O((Tri-cnt + TC) * h-idx).
In practice, much smaller. See Lijun's tutorial.

Whereas **Peel** is O(TC) + O(TC) + O(Tri-Cnt) + O(E).

## Execute

serial, async-update, async-update for only required (need change)

```
./pnd /mnt/storage1/yche/datasets/snap_livejournal 23
./pnd /mnt/storage1/yche/datasets/snap_livejournal 230
./pnd /mnt/storage1/yche/datasets/snap_livejournal 2300
```

## Binary Format

```
vtxsize (sizeof) | edgesize (sizeof) | nVtx | nEdge | deg_lst | adj
```

## Compile

- 'make' to compile, it produces Asynchronous Nucleus Decomposition(AND) algoritm.

- To get the Synchronous version (SND), compile as 'SYNC=yes make'.

- OMP_NUM_THREADS=X './pnd <graph> <algorithm>' to run;
		 <graph> is the input graph in matrix market (.mtx) [1] or edge list (SNAP) [2] format. It can be a binary file as well (See [3])
		 <algorithm> can be X, X0 or X00 for X is 12, 23 or 34. X runs sequential peeling algorithm, X0 runs parallel local algorithm without notification mechanism, and X00 is for the most efficient parallel algorithm that uses notification mechanism (See the paper for details)

- <algorithm> can also be 912 or 923 for partialAND computations of core and truss decompositions. However, files for degree/triangle-count and core/truss numbers should exist (requires an earlier run that has DUMP_K=yes and DUMP_Hs=yes, see below).

- Example: "OMP_NUM_THREADS=16 ./pnd adjnoun.mtx 2300" does most efficient parallel truss decomposition (with notification mechanism) with 16 threads.

- To get the K values of vertices/edges, compile as 'DUMP_K=yes make'.

- To get the all the intermediate kappa values of vertices/edges, compile as 'DUMP_Hs=yes make'.

- Please cite this paper if you use the code:
	
    "Local Algorithms for Hierarchical Dense Subgraph Discovery"
	A. E. Sariyuce, C. Seshadhri, A. Pinar
	PVLDB, 12(1), 2019

- Contact a.erdemsariyuce@gmail.com for any questions/comments
    

[1] Matrix market has ".txt" or ".mtx" suffix. Its format for a 4 clique:
% First line is |V|, |E|
4 6
0 1
0 2
0 3
1 2
1 3
2 3

[2] SNAP format has "out." prefix. Its format for a 4 clique:

0 1
0 2
0 3
1 2
1 3
2 3

[3] Activate WRITE_BINARY macro in graph.cpp to write binary graph files with ".bin" suffix -- recommended for large graphs


