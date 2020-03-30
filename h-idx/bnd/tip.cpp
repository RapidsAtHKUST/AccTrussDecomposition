#include "main.h"

inline lol nChoosek(lol n, int k) {

	if (k > n)
		return 0;
	if (k * 2 > n)
		k = n - k;
	if (k == 0)
		return 1;

	lol result = n;
	for (lol i = 2; i <= k; ++i) {
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}

lol countButterflies (Graph& rightGraph, Graph& leftGraph, lol* butterflyCounts, lol* bCount) {

	lol maxBc = 0;
	unordered_map<vertex, lol> dup;
	vertex i = 0;
	for (i = 0; i < rightGraph.size(); i++) {
		dup.clear();
		for (auto v : rightGraph[i])
			for (auto w : leftGraph[v])
				if (i < w)
					dup[w]++;

		for (auto it = dup.begin(); it != dup.end(); it++) {
			int x = it->first;
			lol count = it->second;
			if (x != i && count > 1) {
				lol c = nChoosek (count, 2);
				butterflyCounts[i] += c;
				butterflyCounts[x] += c;
			}
		}
		if (butterflyCounts[i] > maxBc)
			maxBc = butterflyCounts[i];
		(*bCount) += butterflyCounts[i];
	}
	*bCount /= 2;
	return maxBc;
}

void tipDecomposition (Graph& leftGraph, Graph& rightGraph, edge nEdge, vector<vertex>& K, bool hierarchy,
		lol* maxbicore, string vfile, FILE* fp, lol* bCount) {

	const auto c1 = chrono::steady_clock::now();
	lol* butterflyCounts = (lol*) calloc (sizeof(lol), rightGraph.size());
	lol maxBc = countButterflies (rightGraph, leftGraph, butterflyCounts, bCount); // counts butterflies for each vertex on the right
	
	const auto c2 = chrono::steady_clock::now();
	fprintf (fp, "# bflys: %lld\t\t maxBc: %lld\n", *bCount, maxBc);
	print_time (fp, "Counting butterflies per vertex time: ", c2 - c1);

	// Peeling
	const auto p1 = chrono::steady_clock::now();
	K.resize (rightGraph.size(), -1);
	Naive_Bucket nBucket;
	nBucket.Initialize (maxBc+1, rightGraph.size());

	for (size_t i = 0; i < rightGraph.size(); i++) {
		if (butterflyCounts[i] > 0)
			nBucket.Insert (i, butterflyCounts[i]);
		else
			K[i] = 0;
	}

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
		component.resize (rightGraph.size(), -1);
	}

	vertex bf_u = 0;
	while (true) {
		vertex u, val;
		if (nBucket.PopMin(&u, &val) == -1) // if the bucket is empty
			break;

		if (hierarchy) {
			unassigned.clear();
			subcore sc (val);
			skeleton.push_back (sc);
		}

		bf_u = K[u] = val;

		unordered_map<vertex, lol> dup;
		for (auto v : rightGraph[u])
			for (auto w : leftGraph[v])
				dup[w]++;

		for (auto it = dup.begin(); it != dup.end(); it++) {
			int x = it->first;
			lol count = it->second;
			if (x != u && count > 1) {
				if (K[x] == -1) {
					lol decreaseAmount = nChoosek (count, 2);
					if (nBucket.CurrentValue(x) - decreaseAmount <= val)
						nBucket.DecTo (x, val);
					else
						nBucket.DecTo (x, nBucket.CurrentValue(x) - decreaseAmount);
				}
				else if (hierarchy)
					createSkeleton (u, {x}, &nSubcores, K, skeleton, component, unassigned, relations);
			}
		}
		if (hierarchy)
			updateUnassigned (u, component, &cid, relations, unassigned);
	}

	nBucket.Free();
	*maxbicore = bf_u;

	const auto p2 = chrono::steady_clock::now();
	if (!hierarchy) {
		print_time (fp, "Only peeling time: ", p2 - p1);
		print_time (fp, "Total time: ", (p2 - p1) + (c2 - c1));
	}
	else {
		print_time (fp, "Only peeling + on-the-fly hierarchy construction time: ", p2 - p1);
		const auto b1 = chrono::steady_clock::now();
		buildHierarchy (*maxbicore, relations, skeleton, &nSubcores, nEdge, rightGraph.size(), leftGraph.size());
		const auto b2 = chrono::steady_clock::now();

		print_time (fp, "Building hierarchy time: ", b2 - b1);
		print_time (fp, "Total TIP time (excluding density computation): ", (p2 - p1) + (c2 - c1) + (b2 - b1));

		const auto d1 = chrono::steady_clock::now();
		helpers dummy;
		presentNuclei ("TIP", skeleton, component, nEdge, dummy, vfile, leftGraph, rightGraph, NULL, fp);
		const auto d2 = chrono::steady_clock::now();

		print_time (fp, "Total TIP time: ", (p2 - p1) + (c2 - c1) + (b2 - b1) + (d2 - d1));
	}
}
