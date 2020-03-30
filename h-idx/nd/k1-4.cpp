#include "main.h"

// per vertex
lol count4cliques (Graph& graph, Graph& orderedGraph, vector<vertex>& FC) {

	lol fc = 0;
	for (vertex i = 0; i < orderedGraph.size(); i++) {
		for (vertex j = 0; j < orderedGraph[i].size(); j++) {
			for (vertex k = j + 1; k < orderedGraph[i].size(); k++) {
				for (vertex l = k + 1; l < orderedGraph[i].size(); l++) {
					vertex a = orderedGraph[i][j];
					vertex b = orderedGraph[i][k];
					vertex c = orderedGraph[i][l];
					if (orderedConnected(graph, orderedGraph, a, b) &&
							orderedConnected(graph, orderedGraph, b, c) &&
							orderedConnected(graph, orderedGraph, a, c)) {
						FC[a]++;
						FC[b]++;
						FC[c]++;
						FC[i]++;
						fc++;
					}
				}
			}
		}
	}
	return fc;
}

void base_k14 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* max14, string vfile, FILE* fp) {

	const auto f1 = chrono::steady_clock::now();
	vertex nVtx = graph.size();

	// Create directed graph from low degree vertices to higher degree vertices
	Graph orderedGraph;
	createOrdered (orderedGraph, graph);

	// 4-clique counting for each vertex
	vector<vertex> FC (nVtx, 0);
	lol fc = count4cliques (graph, orderedGraph, FC);

	vertex maxFC = 0;
	for (vertex i = 0; i < graph.size(); i++)
		if (FC[i] > maxFC)
			maxFC = FC[i];

	fprintf (fp, "# 4-cliques: %lld\n", fc);
	const auto f2 = chrono::steady_clock::now();
	print_time (fp, "4-clique counting: ", f2 - f1);

	// Peeling
	const auto p1 = chrono::steady_clock::now();
	K.resize(nVtx, -1);
	Naive_Bucket nBucket;
	nBucket.Initialize(maxFC, nVtx);
	for (vertex i = 0; i < graph.size(); i++) {
		if (FC[i] > 0)
			nBucket.Insert (i, FC[i]);
		else
			K[i] = 0;
	}

	vertex fc_u = 0;

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
		component.resize (graph.size(), -1);
	}

	while (true) {
		vertex u, val;
		if (nBucket.PopMin(&u, &val) == -1) // if the bucket is empty
			break;

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			skeleton.push_back (sc);
		}

		fc_u = K[u] = val;

		for (vertex j = 0; j < graph[u].size(); j++) {
			vertex a = graph[u][j];
			for (vertex k = j + 1; k < graph[u].size(); k++) {
				vertex b = graph[u][k];
				if (orderedConnected(graph, orderedGraph, a, b)) {
					for (vertex l = k + 1; l < graph[u].size(); l++) {
						vertex c = graph[u][l];
						if (orderedConnected (graph, orderedGraph, a, c) && orderedConnected (graph, orderedGraph, b, c)) {
							if (K[a] == -1 && K[b] == -1 && K[c] == -1) {
								if (nBucket.CurrentValue(a) > fc_u)
									nBucket.DecVal(a);
								if (nBucket.CurrentValue(b) > fc_u)
									nBucket.DecVal(b);
								if (nBucket.CurrentValue(c) > fc_u)
									nBucket.DecVal(c);
							}
							else if (hierarchy)
								createSkeleton (u, {a, b, c}, &nSubcores, K, skeleton, component, unassigned, relations);
						}
					}
				}
			}
		}

		if (hierarchy)
			updateUnassigned (u, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*max14 = fc_u;

	const auto p2 = chrono::steady_clock::now();

	if (!hierarchy) {
		print_time (fp, "Only peeling time: ", p2 - p1);
		print_time (fp, "Total time: ", (p2 - p1) + (f2 - f1));
	}
	else {
		print_time (fp, "Only peeling + on-the-fly hierarchy construction time: ", p2 - p1);
		const auto b1 = chrono::steady_clock::now();
		buildHierarchy (*max14, relations, skeleton, &nSubcores, nEdge, nVtx);
		const auto b2 = chrono::steady_clock::now();

		print_time (fp, "Building hierarchy time: ", b2 - b1);
		print_time (fp, "Total 1,4 nucleus decomposition time (excluding density computation): ", (p2 - p1) + (f2 - f1) + (b2 - b1));

		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		const auto d1 = chrono::steady_clock::now();
		helpers hp;
		presentNuclei (14, skeleton, component, graph, nEdge, hp, vfile, fp);
		const auto d2 = chrono::steady_clock::now();

		print_time (fp, "Total 1,4 nucleus decomposition time: ", (p2 - p1) + (f2 - f1) + (b2 - b1) + (d2 - d1));
	}
}
