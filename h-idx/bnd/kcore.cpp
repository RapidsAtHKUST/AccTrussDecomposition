#include "main.h"

void base_kcore (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, lol* maxCore, string vfile, FILE* fp) {
    Timer timer;
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

    log_info("K-core Peeling Elapsed Time: %.6lf s", timer.elapsed());

	if (hierarchy) {
		buildHierarchy (*maxCore, relations, skeleton, &nSubcores, nEdge, nVtx);

//		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());
		helpers dummy;
		Graph dum;
//		presentNuclei ("CORE", skeleton, component, nEdge, dummy, vfile, graph, dum, NULL, fp);
	}
}

void weighted_base_kcore (Wraph& wraph, bool hierarchy, edge nEdge, vector<vertex>& K, lol* maxCore, string vfile, FILE* fp) {

	const auto peelingStart = chrono::steady_clock::now();
	size_t nVtx = wraph.size();
	double max_degree = 0;
	for (size_t i = 0; i < nVtx; i++) {
		double wsum = 0;
		for (int j = 0; j < wraph[i].size(); j++)
			wsum += wraph[i][j].w;
		if (wsum > max_degree)
			max_degree = wsum;
	}
	max_degree *= 10;
	int maxdeg = (int) max_degree + 1;

	// Peeling
	K.resize (wraph.size(), -1);
	Naive_Bucket na_bs;
	na_bs.Initialize(maxdeg, wraph.size());

	for (size_t i = 0; i < wraph.size(); i++) {
		int wsum = 0;
		for (int j = 0; j < wraph[i].size(); j++)
			wsum += (int) (10 * wraph[i][j].w);
		na_bs.Insert (i, wsum);
	}

	vertex degree_of_u = 0;
	vertex cid;
	vector<subcore> skeleton;
	vector<vertex> component;
	vector<vp> relations;
	vector<vertex> unassigned;
	vertex nSubcores;

	if (hierarchy) {
		cid = 0;
		nSubcores = 0;
		component.resize (wraph.size(), -1);
	}

	while (1) {
		int u, value_of_u;
		int ret = na_bs.PopMin(&u, &value_of_u);
		if (ret == -1) // if the bucket is empty
			break;
		if (value_of_u == 0) {
			K[u] = 0;
			continue;
		}

		if (hierarchy) {
			unassigned.clear();
			subcore sc (value_of_u);
			skeleton.push_back (sc);
		}

		degree_of_u = K[u] = value_of_u;

		for (size_t j = 0; j < wraph[u].size(); j++) { /* decrease the degree of the neighbors with greater degree */
			vertex v = wraph[u][j].n;
			int weig = (int) (wraph[u][j].w * 10);
			int curval = na_bs.CurrentValue(v);
			if ((K[v] == -1) && (curval - weig >= degree_of_u)) {
				for (int k = 0; k < weig; k++)
					na_bs.DecVal(v);
			}
			else if ((K[v] == -1) && (curval - weig < degree_of_u))
				;
			else if (hierarchy)
				createSkeleton (u, {v}, &nSubcores, K, skeleton, component, unassigned, relations);
		}


		if (hierarchy)
			updateUnassigned (u, component, &cid, relations, unassigned);

	}

	na_bs.Free();
	*maxCore = degree_of_u; // degree_of_u is degree of the last popped vertex
	Graph graph (wraph.size());
	for (int i = 0; i < wraph.size(); i++) {
		for (int j = 0; j < wraph[i].size(); j++)
			graph[i].push_back (wraph[i][j].n);
	}

	const auto peelingEnd = chrono::steady_clock::now();
	print_time (fp, "Total time: ", peelingEnd - peelingStart);

	if (hierarchy) {
		buildHierarchy (*maxCore, relations, skeleton, &nSubcores, nEdge, graph.size());
		const auto nucleusEnd = chrono::steady_clock::now();

		print_time (fp, "Fractional k-core decomposition time with hierarchy construction: ", nucleusEnd - peelingStart);
		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		helpers dummy;
		Graph dum;
		presentNuclei ("CORE", skeleton, component, nEdge, dummy, vfile, graph, dum, NULL, fp);
		const auto totalEnd = chrono::steady_clock::now();

		print_time (fp, "Total time, including the density computations: ", totalEnd - peelingStart);
	}

	return;
}

