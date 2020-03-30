#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <string>
#include <initializer_list>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <sys/stat.h>
#include "bucket.h"

using namespace std;

#define LOWERBOUND 0
#define UPPERBOUND 1000000 // compute densities of subgraphs with at most this size, set to INT_MAX to compute all -- takes a lot of time
#define THRESHOLD 0.0
#define PRIME 251231 // for hash function

typedef long long lol;
typedef int vertex; // vertices are 32 bytes
typedef int edge; // edges are 32 bytes
typedef unordered_multimap<int, int> mulmap;
typedef pair<vertex, vertex> vp;
typedef tuple<vertex, vertex, vertex> vt;
typedef vector<vector<vertex> > Graph;

typedef chrono::duration<double> tms;
typedef tuple<vertex, vertex> couple;
typedef tuple<vertex, vertex, vertex> triple;


struct subcore {
	bool visible;
	vertex rank;
	vertex K;
	vertex parent;
	vertex root;
	vector<vertex> children;
	vertex size;
	edge nEdge;
	double ed;

	subcore (vertex k) {
		K = k;
		rank = 0;
		parent = -1;
		root = -1;
		visible = true;
		size = 0;
		nEdge = 0;
		ed = -1;
	}
};

struct helpers {
	helpers (vector<vp>* ael) {
		el = ael;
	}
	helpers (vector<vt>* atris) {
		tris = atris;
	}
	helpers () {}

	vector<vp>* el;
	vector<vt>* tris;
};


template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
template<typename S, typename T> struct hash<pair<S, T>>
{
	inline size_t operator()(const pair<S, T> & v) const
	{
		size_t seed = 0;
		::hash_combine(seed, v.first);
		::hash_combine(seed, v.second);
		return seed;
	}
};
}

inline bool hashUniquify (vector<vertex>& vertices) {
	unordered_map<vertex, bool> hermap;
	for (size_t i = 0; i < vertices.size(); i++) {
		int t = vertices[i];
		if (hermap.find (t) == hermap.end())
			hermap[t] = true;
		else {
			vertices.erase (vertices.begin() + i);
			i--;
		}
		if (i > UPPERBOUND)
			return false;
	}
	sort (vertices.begin(), vertices.end());
	return true;
}

inline void print_time (FILE* fp, const string& str, tms t) {
	fprintf (fp, "%s %.6lf\n", str.c_str(), t.count());
	fflush(fp);
}

inline bool less_than (vertex u, vertex v, Graph& graph) {
	return (graph[u].size() < graph[v].size() || (graph[u].size() == graph[v].size() && u < v));
}

inline bool orderedConnected (Graph& graph, Graph& orderedGraph, vertex u, vertex v) {
	vertex a = u, b = v;
	if (less_than (v, u, graph))
		swap (a, b);
	for (auto c : orderedGraph[a])
		if (c == b)
			return true;
	return false;
}

inline void createOrderedIndexEdges (Graph& graph, vector<vp>& el, vector<vertex>& xel, Graph& orderedGraph) {
	xel.push_back(0);
	orderedGraph.resize(graph.size());
	for (size_t u = 0; u < graph.size(); u++) {
		for (size_t j = 0; j < graph[u].size(); j++) {
			vertex v = graph[u][j];
			if (less_than (u, v, graph)) {
				orderedGraph[u].push_back(v);
				vp c (u, v);
				el.push_back(c);
			}
		}
		xel.push_back(el.size());
	}
}

inline void createOrdered (Graph& orderedGraph, Graph& graph) {
	orderedGraph.resize (graph.size());
	for (vertex i = 0; i < graph.size(); ++i)
		for (auto u : graph[i])
			if (less_than (i, u, graph))
				orderedGraph[i].push_back(u);
}

inline vertex getEdgeId (vertex u, vertex v, vector<vertex>& xel, vector<vp>& el, Graph& graph) {

	vertex a = u, b = v;
	if (less_than (b, a, graph))
		swap (a, b);

	for (vertex i = xel[a]; i < xel[a+1]; i++)
		if (el[i].second == b)
			return i;

	printf ("getEdgeId returns -1\n");
	exit(1);
}

inline void intersection (vector<vertex>& a, vector<vertex>& b, vector<vertex>& c) {
	size_t i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if (a[i] < b[j])
			i++;
		else if (b[j] < a[i])
			j++;
		else {
			c.push_back(a[i]);
			i++;
			j++;
		}
	}
}

template <typename VtxType, typename EdgeType>
void readGraph (char *filename, vector<vector<VtxType>>& graph, EdgeType* nEdge);

void base_kcore (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxCore, string vfile, FILE* fp);
void base_k13 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxCore, string vfile, FILE* fp);
void base_k14 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxCore, string vfile, FILE* fp);
void base_ktruss (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxtruss, string vfile, FILE* fp);
void base_ktruss_storeTriangles (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* maxtruss, string vfile, FILE* fp);
void base_k24 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* max24, string vfile, FILE* fp);
void base_k34 (Graph& graph, bool hierarchy, edge nEdge, vector<vertex>& K, vertex* max34, string vfile, FILE* fp);

void createSkeleton (vertex u, initializer_list<vertex> neighbors, vertex* nSubcores, vector<vertex>& K, vector<subcore>& skeleton,	vector<vertex>& component, vector<vertex>& unassigned, vector<vp>& relations);
void updateUnassigned (vertex t, vector<vertex>& component, vertex* cid, vector<vp>& relations, vector<vertex>& unassigned);
void buildHierarchy (vertex cn, vector<vp>& relations, vector<subcore>& skeleton, vertex* nSubcores, edge nEdge, vertex nVtx);
void presentNuclei (int variant, vector<subcore>& skeleton, vector<vertex>& component, Graph& graph, edge nEdge, helpers& ax, string vfile, FILE* gp);
