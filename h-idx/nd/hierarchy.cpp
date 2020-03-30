#include "main.h"

inline void assignToRoot (vertex* ch, vector<subcore>& skeleton) {
	vector<vertex> acc;
	vertex s = *ch;
	while (skeleton[s].root != -1) {
		acc.push_back (s);
		s = skeleton[s].root;
	}
	for (vertex i : acc)
		skeleton[i].root = s;
	*ch = s;
}

inline void assignToRepresentative (vertex* ch, vector<subcore>& skeleton) { // 2-pass path compression
	vertex u = *ch;
	vector<int> vs;
	while (skeleton[u].parent != -1) {
		vertex n = skeleton[u].parent;
		if (skeleton[n].K == skeleton[u].K) {
			vs.push_back (u);
			u = n;
		}
		else
			break;
	}
	*ch = u;
	for (vertex i : vs) {
		if (i != u)
			skeleton[i].parent = u;
	}
}

inline void store (vertex uComp, vertex vComp, vector<vertex>& unassigned, vector<vp>& relations) {
	vp c (vComp, uComp);
	if (uComp == -1) // it is possible that u didn't get an id yet
		unassigned.push_back (relations.size()); // keep those indices to process after the loop, below
	relations.push_back (c);
}

inline void merge (vertex u, vertex v, vector<vertex>& component, vector<subcore>& skeleton, int* nSubcores) {

	if (component[u] == -1) {
		component[u] = component[v];
		skeleton.erase (skeleton.end() - 1);
	}
	else { // merge component[u] and component[v] nodes
		vertex child = component[u];
		vertex parent = component[v];
		assignToRepresentative (&child, skeleton);
		assignToRepresentative (&parent, skeleton);
		if (child != parent) {
			if (skeleton[child].rank > skeleton[parent].rank)
				swap (child, parent);
			skeleton[child].parent = parent;
			skeleton[child].visible = false;
			if (skeleton[parent].rank == skeleton[child].rank)
				skeleton[parent].rank++;
			*nSubcores--;
		}
	}
}

void createSkeleton (vertex u, initializer_list<vertex> neighbors, vertex* nSubcores, vector<vertex>& K, vector<subcore>& skeleton,
		vector<vertex>& component, vector<vertex>& unassigned, vector<vp>& relations) {
	vertex smallest = -1, minK = INT_MAX;
	for (auto i : neighbors)
		if (K[i] != -1 && K[i] < minK) {
			smallest = i;
			minK = K[i];
		}
	if (smallest == -1)
		return;

	if (K[smallest] == K[u])
		merge (u, smallest, component, skeleton, nSubcores);
	else
		store (component[u], component[smallest], unassigned, relations);
}

void updateUnassigned (vertex t, vector<vertex>& component, vertex* cid, vector<vp>& relations, vector<vertex>& unassigned) {
	if (component[t] == -1) { // if e didn't get a component, give her a new one
		component[t] = *cid;
		++(*cid);
	}

	// update the unassigned components that are in the relations
	for (vertex i : unassigned)
		relations[i] = make_pair (relations[i].first, component[t]);
}

void buildHierarchy (vertex cn, vector<vp>& relations, vector<subcore>& skeleton, vertex* nSubcores, edge nEdge, vertex nVtx) {

	// bin the relations w.r.t. first's K
	vector<vector<vp>> binnedRelations (cn + 1);

	for (auto r : relations) {
		vertex a = r.first;
		vertex b = r.second;
		assignToRepresentative (&a, skeleton);
		assignToRepresentative (&b, skeleton);
		if (a == b)
			continue;
		vp c (a, b);
		binnedRelations[skeleton[a].K].push_back (c);
	}

	// process binnedRelations in reverse order
	for (vertex i = binnedRelations.size() - 1; i >= 0; i--) {
		vector<vp> mergeList;
		for (vertex j = 0; j < binnedRelations[i].size(); j++) { // each binnedRelations[i] has K of skeleton[b].K
			vertex a = binnedRelations[i][j].first;
			vertex root = binnedRelations[i][j].second;
			assignToRoot (&root, skeleton);
			if (a != root) {
				if (skeleton[a].K < skeleton[root].K) {
					skeleton[root].parent = a;
					skeleton[root].root = a;
				}
				else { // skeleton[root].K == skeleton[a].K
					vp c = (root < a) ? make_pair (root, a) : make_pair (a, root);
					mergeList.push_back (c);
				}
			}
		}

		// handle merges
		for (auto sc : mergeList) {
			vertex child = sc.first;
			vertex parent = sc.second;
			assignToRepresentative (&child, skeleton);
			assignToRepresentative (&parent, skeleton);
			if (child != parent) {
				if (skeleton[child].rank > skeleton[parent].rank)
					swap (child, parent);
				skeleton[child].parent = parent;
				skeleton[child].root = parent;
				skeleton[child].visible = false;
				if (skeleton[parent].rank == skeleton[child].rank)
					skeleton[parent].rank++;
			}
		}
	}

	*nSubcores += skeleton.size();

	// root core
	vertex nid = skeleton.size();
	subcore sc (0);
	for (size_t i = 0; i < skeleton.size(); i++)
		if (skeleton[i].parent == -1)
			skeleton[i].parent = nid;

	sc.size = nVtx;
	sc.nEdge = nEdge;
	sc.ed = nEdge / double (nVtx * (nVtx - 1) / 2);
	skeleton.push_back (sc);
}
