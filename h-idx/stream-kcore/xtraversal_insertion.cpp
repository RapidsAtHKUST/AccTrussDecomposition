#include "main-kcore.hpp"

void update_K (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop) {

	util::timestamp maintenance_time (0,0);

	// root is found
	vertex root;
	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

	// MCD and PCD values are prepared
	util::timestamp t_maintenance_1;
#ifdef MAINTAIN_CD
	pre_update_hCD_values (hop, *graph, *K, root, u, v, hop_degrees);
#endif
	util::timestamp t_maintenance_2;
	maintenance_time += t_maintenance_2 - t_maintenance_1;

	// traversal algorithm is run
	(*ch_info).core_number = (*K)[root];
	int numof_changed_vertices = 0;

	util::timestamp eviction_time (0,0);

	int traversal_v_space = 0;
	int traversal_e_space = 0;
	int counted_v_size = 0;
	int counted_e_size = 0;

	vertex nVtx= (*graph).size();
	stack<vertex> kova;
	HashMap<bool> visited(false, nVtx);
	HashMap<bool> evicted(false, nVtx);
	HashMap<vertex> cd(0, nVtx);

#ifdef MAINTAIN_CD
	v_container changeds;
#endif

	int core_of_root = (*K)[root];
	kova.push (root);

#ifdef MAINTAIN_CD
	int tmp = hop_degrees[hop - 1][root];
#else
	int tmp = hop_core_degree (*graph, *K, root, core_of_root, hop);
#endif

	visited[root] = true;
	cd[root] += tmp;

	traversal_v_space++;
	traversal_e_space += tmp;

	while (!kova.empty()) {

		vertex v = kova.top();
		kova.pop();

		if (cd[v] > core_of_root) {
			for (unsigned int i = 0; i < (*graph)[v].size(); i++) {
				vertex w = (*graph)[v][i];
#ifdef MAINTAIN_CD
				int coredegree_of_w = hop_degrees[hop - 2][w];
#else
				int coredegree_of_w = hop_core_degree (*graph, *K, w, core_of_root, hop - 1);
#endif
				counted_v_size++;
				counted_e_size += (*graph)[w].size();

				if (visited.hasDefaultValue(w) && ((*K)[w] == core_of_root)
						&& (coredegree_of_w > core_of_root)) {
					visited[w] = true;
					kova.push (w);

#ifdef MAINTAIN_CD
					int cdeg = hop_degrees[hop - 1][w];
#else
					int cdeg = hop_core_degree (*graph, *K, w, core_of_root, hop + 1);
#endif

					cd[w] += cdeg;
					traversal_v_space++;
					traversal_e_space += cdeg;
				}
			}
		}
		else {
			if (evicted.hasDefaultValue(v)) {
				if (v != root) {
					propagate_eviction (graph, K, &cd, &evicted, core_of_root, v);
				}
				else {
					evicted[v] = true;
				}
			}
		}
	}

	for(HashMap<bool>::iterator it=visited.begin(); it!=visited.end(); ++it) {
		int i = it->first;
		if (evicted.hasDefaultValue(i)) {
			(*K)[i]++;
			numof_changed_vertices++;
#ifdef MAINTAIN_CD
			changeds.push_back (i);
#endif
		}
	}


	util::timestamp t_maintenance_3;
#ifdef MAINTAIN_CD
	post_update_hCD_values (hop, *graph, *K, changeds, hop_degrees);

#endif

	util::timestamp t_maintenance_4;
	maintenance_time += t_maintenance_4 - t_maintenance_3;

	(*ch_info).core_v_size = 0;
	(*ch_info).core_e_size = 0;

	(*ch_info).core_v_size = traversal_v_space;
	(*ch_info).core_e_size = traversal_e_space/2;

	visited.reset(false);
	evicted.reset(false);
	cd.reset(-1);

	if ((*K)[root] > (*core_number))
		*core_number = (*K)[root];

	(*ch_info).numof_changed_K_vertices = numof_changed_vertices;

	char timestr3[20];
	maintenance_time.to_c_str(timestr3, 20);
	strcpy ((*ch_info).maintenance_str, timestr3);

	return;
}

void ntraversal_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop) {

	util::timestamp t_begin;
	vertex root;
	util::timestamp graph_change_time (0,0);
	util::timestamp t_update_K_1;
	util::timestamp update_K_time (0,0);

	(*ch_info).insert_ow_remove = true;
	(*ch_info).u = u;
	(*ch_info).v = v;

	// graph is changed here, edge insertion in sorted manner
	util::timestamp t_graph_change_1;
	if (u < (*graph).size()) {
		if (((*graph)[u].size() == 0) || (*graph)[u][0] > v)
			(*graph)[u].insert((*graph)[u].begin(), v);
		else if ((*graph)[u][(*graph)[u].size() - 1] < v)
			(*graph)[u].insert((*graph)[u].end(), v);
		else {
			for (int i = 0; i < (*graph)[u].size(); i++) {
				if ((*graph)[u][i] > v) {
					(*graph)[u].insert((*graph)[u].begin() + i, v);
					break;
				}
			}
		}
	}
	else {
		v_container new_vertex;
		new_vertex.push_back(v);
		(*graph).push_back(new_vertex);
		new_vertex.clear();
	}

	if (v < (*graph).size()) {
		if (((*graph)[v].size() == 0) || (*graph)[v][0] > u)
			(*graph)[v].insert((*graph)[v].begin(), u);
		else if ((*graph)[v][(*graph)[v].size() - 1] < u)
			(*graph)[v].insert((*graph)[v].end(), u);
		else {
			for (int i = 0; i < (*graph)[v].size(); i++) {
				if ((*graph)[v][i] > u) {
					(*graph)[v].insert((*graph)[v].begin() + i, u);
					break;
				}
			}
		}
	}
	else {
		v_container new_vertex;
		new_vertex.push_back(u);
		(*graph).push_back(new_vertex);
		new_vertex.clear();
	}

	// graph change time is calculated
	util::timestamp t_graph_change_2;
	graph_change_time += (t_graph_change_2 - t_graph_change_1);
	char timestr1[20];
	graph_change_time.to_c_str (timestr1, 20);
	strcpy ((*ch_info).graph_change_str, timestr1);

	util::timestamp t_begin2;

	update_K (graph, K,
#ifdef MAINTAIN_CD
			hop_degrees,
#endif
			core_number, u, v,
			ch_info, hop);

	char timestr2[20];

	util::timestamp t_update_K_2;
	update_K_time += ((t_update_K_2 - t_update_K_1) - (t_graph_change_2 - t_graph_change_1));

	update_K_time.to_c_str (timestr2, 20);
	strcpy ((*ch_info).update_K_str, timestr2);

	util::timestamp t_end;

	return;
}

