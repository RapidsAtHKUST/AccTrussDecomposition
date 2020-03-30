#include "main.h"

void base_kcore (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxCore, string vfile, FILE* fp) {

	const auto p1 = chrono::steady_clock::now();
	vertex nVtx = graph.size();
	vertex maxDeg = 0;
	for (auto g : graph)
		if (g.size() > maxDeg)
			maxDeg = g.size();

	// Peeling
	K.resize (graph.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize(maxDeg, nVtx);
	for (vertex i = 0; i < graph.size(); i++) {
		if (graph[i].size() > 0)
			nBucket.Insert (i, graph[i].size());
		else
			K[i] = 0;
	}

	vertex deg_u = 0;

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

		deg_u = K[u] = val;

		for (auto v : graph[u]) { // decrease the degree of the neighbors with greater degree
			vertex deg_v = nBucket.CurrentValue(v);
			if (deg_v > deg_u)
				nBucket.DecVal(v);
			else if (hierarchy) // hierarchy related
				createSkeleton (u, {v}, &nSubcores, K, skeleton, component, unassigned, relations);
		}
		if (hierarchy)
			updateUnassigned (u, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*maxCore = deg_u; // deg_u is degree of the last popped vertex

	const auto p2 = chrono::steady_clock::now();
	if (!hierarchy) {
		print_time (fp, "Peeling time: ", p2 - p1);
	}
	else  {
		print_time (fp, "Peeling + on-the-fly hiearchy construction time: ", p2 - p1);
		const auto b1 = chrono::steady_clock::now();
		buildHierarchy (*maxCore, relations, skeleton, &nSubcores, nEdge, nVtx);
		const auto b2 = chrono::steady_clock::now();

		print_time (fp, "Building hierarchy time: ", b2 - b1);
		print_time (fp, "Total 1,2 nucleus decomposition time (excluding density computation): ", (p2 - p1) + (b2 - b1));

		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		const auto d1 = chrono::steady_clock::now();
		helpers hp;
		presentNuclei (12, skeleton, component, graph, nEdge, hp, vfile, fp);
		const auto d2 = chrono::steady_clock::now();

		print_time (fp, "Total 1,2 nucleus decomposition time: ", (p2 - p1) + (b2 - b1) + (d2 - d1));
	}
}
