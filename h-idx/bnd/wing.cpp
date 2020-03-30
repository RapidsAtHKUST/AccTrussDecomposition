#include "main.h"

#define EL(A, B) (xRight[A]+B)

inline void limitedIntersection (Graph& rightGraph, Graph& leftGraph, vertex b, vertex c, Graph& butterflyCounts, vertex a, lol* bCount) {

	vertex i = 0, j = 0;
	while (rightGraph[b][i] < a) // b - a index
		i++;
	vertex ba = i;
	i++;
	while (rightGraph[c][j] < a) // c - a index
		j++;
	vertex ca = j;
	j++;

	while (i < rightGraph[b].size() && j < rightGraph[c].size()) {
		if (rightGraph[b][i] < rightGraph[c][j])
			i++;
		else if (rightGraph[c][j] < rightGraph[b][i])
			j++;
		else {
			// d is rightGraph[c][j] = rightGraph[b][i] b - d and c - d indices
			vertex bd = i;
			vertex cd = j;
			butterflyCounts[b][ba]++;
			butterflyCounts[b][bd]++;
			butterflyCounts[c][ca]++;
			butterflyCounts[c][cd]++;
			vertex d = rightGraph[c][j];
			
			vertex lmin = min (a, d);
			vertex lmax = max (a, d);

			vertex rmin = min (b, c);
			vertex rmax = max (b, c);

//			printf ("butterfly: %d %d   %d %d , degrees: %d %d   %d %d\n", lmin, lmax, rmin, rmax, leftGraph[lmin].size(), leftGraph[lmax].size(), rightGraph[rmin].size(), rightGraph[rmax].size());

			(*bCount)++;
			i++;
			j++;
		}
	}
}

void countButterflies (Graph& rightGraph, Graph& leftGraph, Graph& butterflyCounts, lol* bCount) {

	lol* leftWedges = (lol *) calloc (leftGraph.size(), sizeof(lol));
	lol* rightWedges = (lol *) calloc (rightGraph.size(), sizeof(lol));  
	
	for (vertex i = 0; i < leftGraph.size(); i++) {
		vertex a = i;
		for (vertex j = 0; j < leftGraph[i].size(); j++) {
			vertex b = leftGraph[i][j];
			leftWedges[a] += rightGraph[b].size() - 1;
			for (vertex k = j + 1; k < leftGraph[i].size(); k++) {
				// intersection set with greater than a's
				vertex c = leftGraph[i][k];
				limitedIntersection (rightGraph, leftGraph, b, c, butterflyCounts, a, bCount);
			}
		}
	}

        for (vertex i = 0; i < rightGraph.size(); i++) {
                vertex a = i;
                for (vertex j = 0; j < rightGraph[i].size(); j++) {
                        vertex b = rightGraph[i][j];
                        rightWedges[a] += leftGraph[b].size() - 1;
		}
	}



        for (vertex i = 0; i < rightGraph.size(); i++) {
                vertex a = i;
                for (vertex j = 0; j < rightGraph[i].size(); j++) {
			vertex b = rightGraph[i][j];
			for (vertex k = j+1; k < rightGraph[i].size(); k++) {
				vertex c = rightGraph[i][k];
				// printf ("Left two in wedge: %d %d  ,  %ld %ld\n", b, c, leftWedges[b], leftWedges[c]); 
			}
		}
	}
		
		


        for (vertex i = 0; i < leftGraph.size(); i++) {
                vertex a = i;
                for (vertex j = 0; j < leftGraph[i].size(); j++) {
                        vertex b = leftGraph[i][j];
                        for (vertex k = j+1; k < leftGraph[i].size(); k++) {
                                vertex c = leftGraph[i][k];
                                // printf ("Right two in wedge: %d %d  ,  %ld %ld\n", b, c, rightWedges[b], rightWedges[c]);
                        }
                }
        }

}

inline vertex getEdgeIndex (vertex a, vertex b, vector<vp>& el, vector<vertex>& xRight) {

	for (vertex i = xRight[a]; i < xRight[a+1]; i++)
		if (el[i].second == b)
			return i - xRight[a];
}

// no hierarchy construction
void wingDecomposition (Graph& leftGraph, Graph& rightGraph, edge nEdge, vector<vertex>& K, bool hierarchy,
		lol* maxbicore, FILE* fp, lol* bCount) {

//	FILE* lp = fopen ("left-deg", "w");
//	FILE* rp = fopen ("right-deg", "w");
//
//	for (int v = 0; v < leftGraph.size(); v++)
//		fprintf (lp, "%d  %d\n", v, leftGraph[v].size());
//
//	for (int v = 0; v < rightGraph.size(); v++)
//                fprintf (rp, "%d  %d\n", v, rightGraph[v].size());
//
//	fclose (lp);
//	fclose (rp);

	const auto pr1 = chrono::steady_clock::now();
	vector<vp> left_el;
	vector<vertex> xLeft;
	prefixSum (xLeft, leftGraph, left_el);
	vector<vp> right_el;
	vector<vertex> xRight;
	prefixSum (xRight, rightGraph, right_el);
	const auto pr2 = chrono::steady_clock::now();
	print_time (fp, "Prefix computation time (both sides): ", pr2 - pr1);

	const auto c1 = chrono::steady_clock::now();
	Graph butterflyCounts (rightGraph.size());
	for (vertex i = 0; i < rightGraph.size(); i++)
		butterflyCounts[i].resize (rightGraph[i].size(), 0);
	countButterflies (rightGraph, leftGraph, butterflyCounts, bCount); // counts butterflies for each edge
	
//	exit (1);
	
	lol ccc = 0;
	vertex maxBc = 0;
	for (auto g : butterflyCounts) {
		for (auto c : g) {
			if (c > maxBc)
				maxBc = c;
			ccc += c;
		}
	}
	cout << "BFLY: " << ccc / 4 << endl;
	const auto c2 = chrono::steady_clock::now();
	printf ("# BFLY: %ld\n", ccc / 4);
	printf ("maxBC: %ld\n", maxBc);
	fprintf (fp, "# bflys: %lld\t\t maxBc: %lld\n", *bCount, maxBc);
	print_time (fp, "Counting butterflies per edge time: ", c2 - c1);


	// peeling
	const auto p1 = chrono::steady_clock::now();
	K.resize (right_el.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize (maxBc, nEdge);
	vertex bid = 0;

	for (vertex i = 0; i < butterflyCounts.size(); i++)
		for (vertex j = 0; j < butterflyCounts[i].size(); j++) {
			vertex c = butterflyCounts[i][j];
			if (c > 0)
				nBucket.Insert (bid++, c);
			else
				K[bid++] = 0;
		}

	vertex bf_e = 0;
	while (true) {
		edge e;
		vertex val;
		if (nBucket.PopMin(&e, &val) == -1)
			break;

		bf_e = K[e] = val;

		vertex u = right_el[e].first;
		vertex v = right_el[e].second;
		vertex uvInd = getEdgeIndex (u, v, right_el, xRight);
#ifdef DEBUG
		printf ("%d %d\tBFLY: %d     W : %d\n", v, u, butterflyCounts[u][uvInd], val);
#endif
		vertex vuInd = getEdgeIndex (v, u, left_el, xLeft);

		// v is left vertex, u is right vertex, t is a right vertex and v's neighbor, w is a left vertex and neighbor to u and t
		// xyInd is the number i s.t. blaGraph[x][i] = y
		for (vertex vtInd = 0; vtInd < leftGraph[v].size(); vtInd++) {
			vertex t = leftGraph[v][vtInd];
			if (t == u || t == -1)
				continue;
			vertex tvInd = getEdgeIndex (t, v, right_el, xRight);
			vertex g = EL(t, tvInd);
			size_t i = 0, j = 0;
			while (i < rightGraph[u].size() && j < rightGraph[t].size()) {
				bool fl = false;
				if (rightGraph[t][j] == -1) {
					j++;
					fl = true;
				}
				if (rightGraph[u][i] == -1) {
					i++;
					fl = true;
				}
				if (fl)
					continue;

				if (rightGraph[u][i] < rightGraph[t][j])
					i++;
				else if (rightGraph[t][j] < rightGraph[u][i])
					j++;
				else if (rightGraph[u][i] != v) {
					vertex uwInd = i;
					vertex twInd = j;
					vertex f = EL(u, uwInd);
					vertex h = EL(t, twInd);
					if (nBucket.CurrentValue (f) > val)
						nBucket.DecVal (f);
					if (nBucket.CurrentValue (g) > val)
						nBucket.DecVal (g);
					if (nBucket.CurrentValue (h) > val)
						nBucket.DecVal (h);
					i++;
					j++;
				}
				else {
					i++;
					j++;
				}
			}
		}
		rightGraph[u][uvInd] = leftGraph[v][vuInd] = -1;
	}

	nBucket.Free();
	*maxbicore = bf_e;

	const auto p2 = chrono::steady_clock::now();
	print_time (fp, "Only peeling time: ", p2 - p1);
	print_time (fp, "Total WING time: ", (p2 - p1) + (c2 - c1) + (pr2 - pr1));
}

inline void indicesIntersectionHrc (vector<vertex>& a, vector<vertex>& b, vector<vertex>& res, vertex g) {

	size_t i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if (a[i] < b[j])
			i++;
		else if (b[j] < a[i])
			j++;
		else {
			if (a[i] != g) {
				res.push_back(i);
				res.push_back(j);
			}
			i++;
			j++;
		}
	}
}

void wingDecompositionHrc (Graph& leftGraph, Graph& rightGraph, edge nEdge, vector<vertex>& K, bool hierarchy,
		lol* maxbicore, string vfile, FILE* fp, lol* bCount) {

	const auto pr1 = chrono::steady_clock::now();
	vector<vp> right_el;
	vector<vertex> xRight;
	prefixSum (xRight, rightGraph, right_el);
	const auto pr2 = chrono::steady_clock::now();
	print_time (fp, "Prefix computation time (single side): ", pr2 - pr1);

	const auto c1 = chrono::steady_clock::now();
	Graph butterflyCounts (rightGraph.size());
	for (vertex i = 0; i < rightGraph.size(); i++)
		butterflyCounts[i].resize (rightGraph[i].size(), 0);
	countButterflies (rightGraph, leftGraph, butterflyCounts, bCount); // counts butterflies for each vertex on the right
	vertex maxBc = 0;
	for (auto g : butterflyCounts)
		for (auto c : g)
			if (c > maxBc)
				maxBc = c;
	const auto c2 = chrono::steady_clock::now();
	fprintf (fp, "# bflys: %lld\t\t maxBc: %lld\n", *bCount, maxBc);
	print_time (fp, "Counting butterflies per edge time: ", c2 - c1);


	// peeling and hierarchy construction
	const auto p1 = chrono::steady_clock::now();
	K.resize (right_el.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize (maxBc, nEdge);
	vertex bid = 0;

	for (vertex i = 0; i < butterflyCounts.size(); i++) {
		for (vertex j = 0; j < butterflyCounts[i].size(); j++) {
			vertex c = butterflyCounts[i][j];
			if (c > 0)
				nBucket.Insert (bid++, c);
			else
				K[bid++] = 0;
		}
	}

	vertex bf_e = 0;

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
		component.resize (right_el.size(), -1);
	}

	while (true) {
		edge e;
		vertex val;
		if (nBucket.PopMin(&e, &val) == -1)
			break;

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			skeleton.push_back (sc);
		}

		bf_e = K[e] = val;

		vertex u = right_el[e].first;
		vertex v = right_el[e].second;
		vertex uvInd = getEdgeIndex (u, v, right_el, xRight);

		// v is left vertex, u is right vertex, t is a right vertex and v's neighbor, w is a left vertex and neighbor to u and t
		// xyInd is the number i s.t. blaGraph[x][i] = y
		for (vertex vtInd = 0; vtInd < leftGraph[v].size(); vtInd++) {
			vertex t = leftGraph[v][vtInd];
			if (t == u)
				continue;
			vertex tvInd = getEdgeIndex (t, v, right_el, xRight);
			vector<vertex> ds;
			indicesIntersectionHrc (rightGraph[u], rightGraph[t], ds, v); // each intersection is vertex w, on the left
			for (vertex j = 0; j < ds.size(); j += 2) {
				vertex uwInd = ds[j];
				vertex twInd = ds[j+1];
				// we have u, t on right; v, w on left; indices from u, t to v, w
				vertex f = EL(u, uwInd);
				vertex g = EL(t, tvInd);
				vertex h = EL(t, twInd);
				if (K[f] == -1 && K[g] == -1 && K[h] == -1) {
					if (nBucket.CurrentValue (f) > val)
						nBucket.DecVal (f);
					if (nBucket.CurrentValue (g) > val)
						nBucket.DecVal (g);
					if (nBucket.CurrentValue (h) > val)
						nBucket.DecVal (h);
				}
				else if (hierarchy)
					createSkeleton (e, {f, g, h}, &nSubcores, K, skeleton, component, unassigned, relations);
			}
		}
		if (hierarchy)
			updateUnassigned (e, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*maxbicore = bf_e;

	const auto p2 = chrono::steady_clock::now();
	print_time (fp, "Only peeling + on-the-fly hierarchy construction time: ", p2 - p1);
	const auto b1 = chrono::steady_clock::now();
	buildHierarchy (*maxbicore, relations, skeleton, &nSubcores, nEdge, rightGraph.size(), leftGraph.size());
	const auto b2 = chrono::steady_clock::now();

	print_time (fp, "Building hierarchy time: ", b2 - b1);
	print_time (fp, "Total WING time (excluding density computation): ", (pr2 - pr1) + (c2 - c1) + (p2 - p1) + (b2 - b1));

	const auto d1 = chrono::steady_clock::now();
	helpers hp (&right_el);
	presentNuclei ("WING", skeleton, component, nEdge, hp, vfile, leftGraph, rightGraph, &xRight, fp);
	const auto d2 = chrono::steady_clock::now();

	print_time (fp, "Total WING time: ", (pr2 - pr1) + (c2 - c1) + (p2 - p1) + (b2 - b1) + (d2 - d1));
}
