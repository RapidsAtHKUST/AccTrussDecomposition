#include "main.h"

inline void increment (vertex u, vertex v, vertex w, vector<vertex>& xtris, vector<vp>& el, vector<vertex>& xel, Graph& orderedTris, Graph& graph, Graph& FC) {
	vertex i = -1;
	for (i = xel[u]; i < xel[u+1]; i++)
		if (el[i].second == v)
			break;
	bool fl = false;
	for (vertex j = 0; j < orderedTris[i].size(); j++)
		if (orderedTris[i][j] == w) {
			FC[i][j]++;
			fl = true;
			break;
		}
}

inline void shake (vertex m, vertex u, vertex v, vertex w, vertex* a, vertex* b, Graph& graph) {
	if (m == u) {
		*a = v;
		*b = w;
		if (less_than (w, v, graph))
			swap (*a, *b);
	}
}

inline vertex maxOrdered (vertex a, vertex b, vertex c, Graph& graph) {
	if (less_than (b, a, graph))
		return less_than (a, c, graph) ? c : a;
	else
		return less_than (b, c, graph) ? c : b;
}

inline void threeWay (vector<vertex>& x, vector<vertex>& y, vector<vertex>& z, vector<vertex>& commonNeighbors) {
	vertex i = 0, j = 0, k = 0;
	while (i < x.size() && j < y.size() && k < z.size()) {
		vertex a = x[i];
		vertex b = y[j];
		vertex c = z[k];
		if (a == b && a == c) {
			commonNeighbors.push_back(a);
			i++; j++; k++;
		}
		else {
			vertex m = max ({a, b, c});
			if (a != m)
				i++;
			if (b != m)
				j++;
			if (c != m)
				k++;
		}
	}
}

inline vertex getTriangleId (vertex u, vertex v, vertex w, vector<vertex>& xtris, vector<vp>& el, vector<vertex>& xel, Graph& orderedTris, Graph& graph) {

	// given the neighbor triangle u, v, w; get el-id by smallest and middle, then get tris id by largest's index in orderedTris[el-id] : xtris[el-id]+index
	vertex a, b, m = maxOrdered (u, v, w, graph);
	shake (m, u, v, w, &a, &b, graph);
	shake (m, v, u, w, &a, &b, graph);
	shake (m, w, u, v, &a, &b, graph);

	vertex i = -1;
	for (i = xel[a]; i < xel[a+1]; i++)
		if (el[i].second == b)
			break;

	if (i == -1) {
		printf ("BUG in el of getTriangleId\n");
		exit(1);
	}

	bool fl = false;
	for (vertex j = 0; j < orderedTris[i].size(); j++)
		if (orderedTris[i][j] == m)
			return xtris[i] + j;

	if (!fl) {
		printf ("BUG in tris of getTriangleId\n");
		exit(1);
	}
}

void create_triangleList (Graph& orderedGraph, vector<vp>& el, Graph& orderedTris, vector<vt>& tris, vector<vertex>& xtris, Graph& FC) {

	xtris.push_back(0);
	for (size_t i = 0; i < el.size(); i++) {
		vertex u = get<0>(el[i]);
		vertex v = get<1>(el[i]);
		vector<vertex> commonNeighbors;
		intersection (orderedGraph[u], orderedGraph[v], commonNeighbors);
		for (auto w : commonNeighbors) {
			orderedTris[i].push_back (w);
			FC[i].push_back (0);
			vt tr = make_tuple (u, v, w);
			tris.push_back (tr);
		}
		xtris.push_back(tris.size());
	}
}

// per triangle
lol count4cliques (Graph& graph, Graph& orderedGraph, vector<vp>& el, vector<vertex>& xel, Graph& orderedTris, vector<vt>& tris, vector<vertex>& xtris, Graph& FC) {

	lol fc = 0;
	for (auto t : tris) {
		vertex i = 0, j = 0, k = 0;
		vertex u = get<0>(t);
		vertex v = get<1>(t);
		vertex w = get<2>(t);

		while (i < orderedGraph[u].size() && j < orderedGraph[v].size() && k < orderedGraph[w].size()) {
			vertex a = orderedGraph[u][i];
			vertex b = orderedGraph[v][j];
			vertex c = orderedGraph[w][k];

			if (a == b && a == c) {
				vertex x = a;
				increment (u, v, w, xtris, el, xel, orderedTris, graph, FC);
				increment (u, v, x, xtris, el, xel, orderedTris, graph, FC);
				increment (u, w, x, xtris, el, xel, orderedTris, graph, FC);
				increment (v, w, x, xtris, el, xel, orderedTris, graph, FC);
				i++; j++; k++;
				fc++;
			}
			else {
				vertex m = max ({a, b, c});
				if (a != m)
					i++;
				if (b != m)
					j++;
				if (c != m)
					k++;
			}
		}
	}
	return fc;
}

void base_k34 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* max34, string vfile, FILE* fp) {

	const auto t1 = chrono::steady_clock::now();
	vertex nVtx = graph.size();

	// Create directed graph from low degree vertices to higher degree vertices AND prepare a CSR-like structure to index the edges
	vector<vp> el;
	vector<vertex> xel;
	Graph orderedGraph;
	createOrderedIndexEdges (graph, el, xel, orderedGraph);

	// Creating triangle list
	vector<vector<vertex>> orderedTris (nEdge); // like orderedGraph: each vector<vertex> is the list of third vertices, w, in the triangles of i-th edge, u - v, in el s.t. u < v < w (deg ordering)
	vector<vt> tris; // like el: list of the triangles aligned to the order in orderedTriangles
	vector<vertex> xtris; // like xel: indices in tris that starts the triangle list for an edge
	vector<vector<vertex>> FC (nEdge); // 4-clique counts of each triangle in the orderedTris structure
	create_triangleList (orderedGraph, el, orderedTris, tris, xtris, FC);
	const auto t2 = chrono::steady_clock::now();

	print_time (fp, "Triangle enumeration: ", t2 - t1);

	const auto f1 = chrono::steady_clock::now();
	// 4-clique counting for each triangle
	lol fc = count4cliques (graph, orderedGraph, el, xel, orderedTris, tris, xtris, FC);
	fprintf (fp, "# 4-cliques: %lld\n", fc);
	const auto f2 = chrono::steady_clock::now();
	print_time (fp, "4-clique counting: ", f2 - f1);

	// Peeling
	const auto p1 = chrono::steady_clock::now();
	K.resize (tris.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize (nEdge, tris.size()); // maximum 4-clique count of a triangle is nVtx

	vertex id = 0;
	for (size_t i = 0; i < FC.size(); i++)
		for (size_t j = 0; j < FC[i].size(); j++) {
			if (FC[i][j] > 0)
				nBucket.Insert (xtris[i]+j, FC[i][j]);
			else
				K[xtris[i] + j] = 0;
			id++;
		}

	vertex fc_t = 0;

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
		component.resize (tris.size(), -1);
	}

	vertex monitor = 0;
	while (true) {
		edge t;
		edge val ;
		if (nBucket.PopMin(&t, &val)) // if the bucket is empty
			break;

#ifdef MONITOR
		if (monitor % 10000 == 0)
			printf ("t: %d    val: %d    counter: %d  nEdge: %d\n", t, val, monitor, nEdge);
		monitor++;
#endif

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			skeleton.push_back (sc);
		}

		fc_t = K[t] = val;

		vertex u = get<0> (tris[t]);
		vertex v = get<1> (tris[t]);
		vertex w = get<2> (tris[t]);
		vector<vertex> commonNeighbors;
		threeWay (graph[u], graph[v], graph[w], commonNeighbors);
		for (auto x : commonNeighbors) { // decrease the FC of the neighbor triangles with greater FC
			vertex p = getTriangleId (u, v, x, xtris, el, xel, orderedTris, graph);
			vertex r = getTriangleId (u, w, x, xtris, el, xel, orderedTris, graph);
			vertex s = getTriangleId (v, w, x, xtris, el, xel, orderedTris, graph);
			if (K[p] == -1 && K[r] == -1 && K[s] == -1) {
				if (nBucket.CurrentValue(p) > fc_t)
					nBucket.DecVal(p);
				if (nBucket.CurrentValue(r) > fc_t)
					nBucket.DecVal(r);
				if (nBucket.CurrentValue(s) > fc_t)
					nBucket.DecVal(s);
			}
			else if (hierarchy)
				createSkeleton (t, {p, r, s}, &nSubcores, K, skeleton, component, unassigned, relations);
		}

		if (hierarchy)
			updateUnassigned (t, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*max34 = fc_t; // fc_t is fc of the last popped triangle

	const auto p2 = chrono::steady_clock::now();

	if (!hierarchy) {
		print_time (fp, "Only peeling time: ", p2 - p1);
		print_time (fp, "Total time: ", (p2 - p1) + (f2 - f1) + (t2 - t1));
	}
	else {
		print_time (fp, "Only peeling + on-the-fly hierarchy construction time: ", p2 - p1);
		const auto b1 = chrono::steady_clock::now();
		buildHierarchy (*max34, relations, skeleton, &nSubcores, nEdge, nVtx);
		const auto b2 = chrono::steady_clock::now();

		print_time (fp, "Building hierarchy time: ", b2 - b1);
		print_time (fp, "Total 3,4 nucleus decomposition time (excluding density computation): ", (p2 - p1) + (f2 - f1) + (t2 - t1) + (b2 - b1));

		fprintf (fp, "# subcores: %d\t\t # subsubcores: %d\t\t |V|: %d\n", nSubcores, skeleton.size(), graph.size());

		const auto d1 = chrono::steady_clock::now();
		helpers hp (&tris);
		presentNuclei (34, skeleton, component, graph, nEdge, hp, vfile, fp);
		const auto d2 = chrono::steady_clock::now();

		print_time (fp, "Total 3,4 nucleus decomposition time: ", (p2 - p1) + (f2 - f1) + (t2 - t1) + (b2 - b1) + (d2 - d1));
	}
}
