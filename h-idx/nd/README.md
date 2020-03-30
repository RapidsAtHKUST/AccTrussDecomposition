- 'make' to compile

- './nucleus <graph> <algorithm> <hierarchy?>' to run;
		 <graph> is the input graph in matrix market (.mtx) [1] or edge list (SNAP) [2] format. It can be a binary file as well (See [3])
		 <algorithm> can be 12, 13, 14, 23, or 34. First digit is the r value and second digit is the s value for (r,s)-nucleus decomposition. 12 is k-core, 23 is k-truss with triangle connectivity
		 <hierarchy> is YES or NO. YES computes the hierarchy, subgraphs, and densities. NO computes only K values.

- When <hierarchy> is YES, there are 2 output files
		- <graph>_<algorithm>_Hierarchy: Runtimes, statistics, and significantly dense subgraphs, i.e., subgraph is a leaf, its size is larger or equal to LOWERBOUND (set to 0 in main.h), and its density is at least THRESHOLD value (set to 0.0 in main.h)
		- <graph>_<algorithm>_NUCLEI: Each line is a nucleus, first 6 numbers are subgraph id, K value, |V|, |E|, edge density, and 1 (0) if the nucleus is (not) a leaf in the hierarchy


- In the *-Hierarchy file, consider the following line;
"id: 17  K: 2  |V|: 7  |E|: 18  ed: 0.86  LEAF?: 1  parent id: 1	3 18 22 35 51 52 55 -1"
It means the subgraph with id 17 has K value of 2, and it has 7 vertices, 18 edges with 0.86 edge density (18/(7 choose 2)). The subgraph is a leaf in the hierarchy and its parent is the subgraph with the id of 1. Following seven numbers are the vertices in the subgraph.

- Example: "./nucleus adjnoun.mtx 34 YES" does (3,4)-decomposition and hierarchy construction

- To get the K values of vertices/edges, compile with 'K_VALUES=yes make'

- Please cite those papers if you use the code:

    "Finding the Hierarchy of Dense Subgraphs using Nucleus Decompositions"
	A. E. Sariyuce, C. Seshadhri, A. Pinar, U. V. Catalyurek
	International World Wide Web Conference (WWW), 2015.

    "Fast Hierarhcy Construction for Dense Subgraphs"
	A. E. Sariyuce, A. Pinar
	Very Large Data Bases Conference (VLDB), 2017	

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

    