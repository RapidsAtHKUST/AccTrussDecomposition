#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>
#include <set>

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <pthread.h>


#include "ulib.h"
#include "graph.h"
#include "timestamp.hpp"
#include "bucket.h"
#include "larray.h"

static util::timestamp hcd (0, 0);
static util::timestamp thatcall (0, 0);

//#define VERIFY
//#define VERIFY_K
//#define K_HISTOGRAM
//#define K_VALUES


// GAME MODES
#define LOAD		1
#define SAVE		2
#define JUST_RUN	3

// EDGE GENERATION OPTIONS
#define RANDOM_GENERATION           	0
#define FROM_FILE                   	1

// ALGORITHM OPTIONS
#define N_CORE		1
#define TRAVERSAL	2
#define N_TRAVERSAL	3


#define print_v(i) (i+1)

using namespace std;
typedef int vertex; //vertices are 32 bytes

struct edge {
	vertex u;
	vertex v;
};

struct cd_elt {
	vertex id;
	int core_degree;
};

struct incremental_debug {
	bool insert_ow_remove;
	vertex u;
	vertex v;
	vertex core_v_size;
	vertex core_e_size;
	int core_number;
	int old_K_u;
	int old_K_v;
	vertex numof_changed_K_vertices;
	char graph_change_str[20];
	char update_K_str[20];
	char maintenance_str[20];
	vertex visited_size;
	vertex evicted_size;
	vertex cd_size;
	vertex processed_size;
};

struct root_and_vsize_and_esize {
	vertex root;
	vertex vsize;
	vertex esize;
};

struct core_no_and_size {
	int core_no;
	vertex size;
};

struct id_and_core_no {
	//    vertex id1;
	//    vertex id2;
	vertex id;
	int core_no;
	int count;
};

struct roots_and_size {
	int root1;
	int root2;
	vertex size;
};

struct id_core_size {
	int root;
	int core;
	vertex size;
};

struct edge_for_batch {
	vertex u;
	vertex v;
	bool is_u_root;
	bool is_v_root;
	int core_number;
};

typedef vector<vector<vertex> > Graph;
typedef vector<vertex> v_container;
typedef vector<cd_elt> core_degrees;
typedef vector<vector<root_and_vsize_and_esize> > cc_sizes;


struct snapshot {
	vector<vertex> K;
	vector<vector<vertex> > hcd;
	vector<vector<vertex> > maxcores;
};

struct couple {
	double pr;
	int id;
};


void load_state (char* filename, v_container& K, int hop
#ifdef MAINTAIN_CD
		, vector<vector<vertex> >& hop_degrees
#endif
	);

void fast_base_kcore (char* filename, Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int hop);

void take_from_file (Graph* graph, int count, edge* edge_list, string cfile);

void randomly_generate_edges (Graph* graph, int count, edge* edge_list, string cfile);

int onebyone_kcore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
		vector<vector<vertex> >& hop_degrees,
#endif
		util::timestamp& totaltime, int* core_number,
		int count, edge* edges,
		incremental_debug* change_info, int hop, int algorithm);

void ncore_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop);

void traversal_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop);

void ntraversal_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop);

void ncore_removal (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info);

void traversal_removal (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop);

int base_kcore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
		vector<vector<vertex> >& hop_degrees,
#endif
		int hop, util::timestamp& totaltime, int *core_number);

int core_degree (Graph* graph, v_container* K, vertex v, int k);

void find_subcore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
#endif
		HashMap<int>* reverse_map, vertex root, Graph* subcore, core_degrees* cd);

vertex hop_core_degree (Graph& graph, v_container& K, vertex v, int k, int hop);

void propagate_eviction (Graph* graph, v_container* K, HashMap<vertex>* cd, HashMap<bool>* evicted,
		int core_of_root, vertex v);

vertex hop_core_degree_CD (vector<vector<vertex> >& hop_degrees, Graph& graph, v_container& K, vertex v, int k, int hop);

void pre_update_hCD_values (int hop, Graph& graph, v_container& K, vertex root,
		vertex r1, vertex r2, vector<vector<vertex> >& hop_degrees);

void post_update_hCD_values (int hop, Graph& graph, v_container& K,
		vector<vertex>& changeds, vector<vector<vertex> >& hop_degrees);
