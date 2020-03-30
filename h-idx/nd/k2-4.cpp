#include "main.h"

// per edge
lol count4cliques (Graph& graph, Graph& orderedGraph, vector<vertex>& xel, vector<vp>& el, vector<vertex>& FC) {

	lol fc = 0;
	for (vertex i = 0; i < orderedGraph.size(); i++)
		for (vertex j = 0; j < orderedGraph[i].size(); j++)
			for (vertex k = j + 1; k < orderedGraph[i].size(); k++)
				for (vertex l = k + 1; l < orderedGraph[i].size(); l++) {
					vertex a = orderedGraph[i][j];
					vertex b = orderedGraph[i][k];
					vertex c = orderedGraph[i][l];
					if (orderedConnected(graph, orderedGraph, a, b) &&
							orderedConnected(graph, orderedGraph, b, c) &&
							orderedConnected(graph, orderedGraph, a, c)) {
						FC[getEdgeId (i, a, xel, el, graph)]++;
						FC[getEdgeId (i, b, xel, el, graph)]++;
						FC[getEdgeId (i, c, xel, el, graph)]++;
						FC[getEdgeId (a, b, xel, el, graph)]++;
						FC[getEdgeId (a, c, xel, el, graph)]++;
						FC[getEdgeId (b, c, xel, el, graph)]++;
						fc++;
					}
				}
	return fc;
}

void base_k24 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* max24, string vfile, FILE* fp) {

	const auto f1 = chrono::steady_clock::now();
	vertex nVtx = graph.size();

	// Create directed graph from low degree vertices to higher degree vertices AND prepare a CSR-like structure to index the edges
	vector<vp> el;
	vector<vertex> xel;
	Graph orderedGraph;
	createOrderedIndexEdges (graph, el, xel, orderedGraph);

	// 4-clique counting for each edge
	vector<vertex> FC (nEdge, 0);
	lol fcc = count4cliques (graph, orderedGraph, xel, el, FC);

	fprintf (fp, "# 4-cliques: %lld\n", fcc);
	const auto f2 = chrono::steady_clock::now();
	print_time (fp, "4-clique counting: ", f2 - f1);

	// Peeling
	const auto p1 = chrono::steady_clock::now();
	K.resize (el.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize(nEdge, nEdge); // maximum 4-clique count of an edge is nEdge
	for (size_t i = 0; i < el.size(); i++)
		if (FC[i] > 0)
			nBucket.Insert (i, FC[i]);
		else
			K[i] = 0;

	vertex fc_e = 0;

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
		component.resize (el.size(), -1);
	}

	vertex monitor = 0;
	while (true) {
		edge e;
		edge val;
		if (nBucket.PopMin(&e, &val) == -1)
			break;

#ifdef MONITOR
		if (monitor % 10000 == 0)
			printf ("e: %d    val: %d    counter: %d  nEdge: %d\n", e, val, monitor, nEdge);
		monitor++;
#endif

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			skeleton.push_back (sc);
		}

		fc_e = K[e] = val;

		vertex u = el[e].first;
		vertex v = el[e].second;
		vector<vertex> commonNeighbors;
		intersection (graph[u], graph[v], commonNeighbors);
		for (size_t j = 0; j < commonNeighbors.size(); j++) {
			for (size_t k = j + 1; k < commonNeighbors.size(); k++) {
				vertex w = commonNeighbors[j];
				vertex x = commonNeighbors[k];
				if (orderedConnected (graph, orderedGraph, w, x)) {
					edge a = getEdgeId (u, w, xel, el, graph);
					edge b = getEdgeId (v, w, xel, el, graph);
					edge c = getEdgeId (u, x, xel, el, graph);
					edge d = getEdgeId (v, x, xel, el, graph);
					edge f = getEdgeId (w, x, xel, el, graph);

					if (K[a] == -1 && K[b] == -1 && K[c] == -1 && K[d] == -1 && K[f] == -1) { // 5 neighbor edges
						if (nBucket.CurrentValue(a) > fc_e)
							nBucket.DecVal(a);
						if (nBucket.CurrentValue(b) > fc_e)
							nBucket.DecVal(b);
						if (nBucket.CurrentValue(c) > fc_e)
							nBucket.DecVal(c);
						if (nBucket.CurrentValue(d) > fc_e)
							nBucket.DecVal(d);
						if (nBucket.CurrentValue(f) > fc_e)
							nBucket.DecVal(f);
					}
					else if (hierarchy)
						createSkeleton (e, {a, b, c, d, f}, &nSubcores, K, skeleton, component, unassigned, relations);
				}
			}
		}

		if (hierarchy)
			updateUnassigned (e, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*max24 = fc_e;

	const auto p2 = chrono::steady_clock::now();

	if (!hierarchy) {
		print_time (fp, "Only peeling time: ", p2 - p1);
		print_time (fp, "Total time: ", (p2 - p1) + (f2 - f1));
	}
	else {
		print_time (fp, "Only peeling + on-the-fly hierarchy construction time: ", p2 - p1);
		const auto b1 = chrono::steady_clock::now();
		buildHierarchy (*max24, relations, skeleton, &nSubcores, nEdge, nVtx);
		const auto b2 = chrono::steady_clock::now();

		print_time (fp, "Building hierarchy time: ", b2 - b1);
		print_time (fp, "Total 2,4 nucleus decomposition time (excluding density computation): ", (p2 - p1) + (f2 - f1) + (b2 - b1));

		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		const auto d1 = chrono::steady_clock::now();
		helpers hp (&el);
		presentNuclei (24, skeleton, component, graph, nEdge, hp, vfile, fp);
		const auto d2 = chrono::steady_clock::now();

		print_time (fp, "Total 2,4 nucleus decomposition time: ", (p2 - p1) + (f2 - f1) + (b2 - b1) + (d2 - d1));
	}
}
