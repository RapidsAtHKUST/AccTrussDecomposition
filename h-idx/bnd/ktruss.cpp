#include "main.h"

inline int ifConnected (Graph& graph, Graph& orientedGraph, Graph& TC, vertex u, vertex v) {
	vertex a = u, b = v;
	if (less_than (b, a, graph))
		swap (a, b);
	for (size_t k = 0; k < orientedGraph[a].size(); k++)
		if (orientedGraph[a][k] == b) {
			TC[a][k]++;
			return b;
		}
	return -1;
}

// per edge
lol countTriangles (Graph& graph, Graph& orientedGraph, Graph& TC) {
	for (size_t i = 0; i < orientedGraph.size(); i++) {
		for (size_t j = 0; j < orientedGraph[i].size(); j++) {
			for (size_t k = j + 1; k < orientedGraph[i].size(); k++) {
				vertex a = orientedGraph[i][j];
				vertex b = orientedGraph[i][k];
				vertex c = ifConnected (graph, orientedGraph, TC, a, b);
				if (c != -1) {
					TC[i][j]++;
					TC[i][k]++;
				}
			}
		}
	}

	lol tc = 0;
	for (size_t i = 0; i < orientedGraph.size(); i++)
		for (size_t j = 0; j < orientedGraph[i].size(); j++)
			tc += TC[i][j];

	return tc;
}

void base_ktruss (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, lol* maxtruss, string vfile, FILE* fp) {

	const auto peelingStart = chrono::steady_clock::now();

	vertex nVtx = graph.size();

	// Prepare a CSR-like structure to index edges and create directed graph from low degree vertices to higher degree vertices
	vector<vp> el;
	vector<vertex> xel;
	Graph orientedGraph;
	indexEdges (graph, el, xel, orientedGraph);
	vector<vector<vertex> > TC (nVtx);
	for (vertex i = 0; i < nVtx; i++)
		TC[i].resize (orientedGraph[i].size(), 0);

	//	Triangle counting for each edge
	lol tric = countTriangles (graph, orientedGraph, TC);
	tric /= 3;
	const auto tcEnd = chrono::steady_clock::now();
	print_time (fp, "Triangle counting: ", tcEnd - peelingStart);

	// Peeling
	K.resize (nEdge, -1);
	Naive_Bucket nBucket;
	nBucket.Initialize (nVtx, nEdge); // maximum triangle count of an edge is nVtx
	vertex id = 0;
	for (size_t i = 0; i < orientedGraph.size(); i++)
		for (size_t j = 0; j < orientedGraph[i].size(); j++) {
			if (TC[i][j] > 0)
				nBucket.Insert (id++, TC[i][j]);
			else
				K[id++] = 0;
		}

	vertex tc_e = 0;

	// required for hierarchy
	vertex cid; // subcore id number
	vector<subcore> skeleton; // equal K valued cores
	vector<vertex> component; // subcore ids for each vertex
	vector<vp> relations;
	vector<vertex> unassigned;
	vertex nSubcores;

	if (hierarchy) {
		cid = 0;
		nSubcores = 0;
		component.resize (nEdge, -1);
	}

	fflush (fp);
	int counter = 0;
	while (true) {
		edge e;
		vertex val;
		if (nBucket.PopMin(&e, &val) == -1) // if the bucket is empty
			break;

		if (counter % 10000 == 0) {
			fprintf (fp, "e: %d    val: %d    counter: %d  nEdge: %d\n", e, val, counter, nEdge);
			fflush (fp);
		}

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			sc.children.clear();
			skeleton.push_back (sc);
		}

		tc_e = K[e] = val;

		vertex u = el[e].first;
		vertex v = el[e].second;
		vector<vertex> commonNeighbors;
		intersection (graph[u], graph[v], commonNeighbors);
		for (auto w : commonNeighbors) { // decrease the TC of the neighbor edges with greater TC
			edge f = getEdgeId (u, w, xel, el, graph);
			edge g = getEdgeId (v, w, xel, el, graph);
			if (K[f] == -1 && K[g] == -1) {
				if (nBucket.CurrentValue(f) > tc_e)
					nBucket.DecVal(f);
				if (nBucket.CurrentValue(g) > tc_e)
					nBucket.DecVal(g);
			}
			else if (hierarchy)
				createSkeleton (e, {f, g}, &nSubcores, K, skeleton, component, unassigned, relations);
		}

		if (hierarchy)
			updateUnassigned (e, component, &cid, relations, unassigned);
		counter++;
	}

	nBucket.Free();
	*maxtruss = tc_e; // tc_e is tc of the last popped edge

	const auto peelingEnd = chrono::steady_clock::now();
	print_time (fp, "Peeling time: ", peelingEnd - peelingStart);

	if (hierarchy) {
		buildHierarchy (*maxtruss, relations, skeleton, &nSubcores, nEdge, nVtx);
		const auto nucleusEnd = chrono::steady_clock::now();

		print_time (fp, "Truss decomposition time with hierarchy construction: ", nucleusEnd - peelingStart);
		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		helpers hp (&el);
		Graph dum;
		presentNuclei ("TRUSS", skeleton, component, nEdge, hp, vfile, graph, dum, NULL, fp);
		const auto totalEnd = chrono::steady_clock::now();

		print_time (fp, "Total time, including the density computations: ", totalEnd - peelingStart);
	}
}
