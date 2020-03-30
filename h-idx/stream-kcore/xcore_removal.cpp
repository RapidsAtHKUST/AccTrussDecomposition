#include "main-kcore.hpp"

void ncore_removal (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info) {

	util::timestamp graph_change_time (0,0);
	util::timestamp update_K_time (0,0);

	util::timestamp t_update_K_1;

	(*ch_info).insert_ow_remove = false;
	(*ch_info).u = u;
	(*ch_info).v = v;
	vertex root;
	Graph subcore; // each edge list of vertex v starts with v
	core_degrees cd; // pairs of vertex id and cd of vertex
	vertex nVtx= (*graph).size();

	HashMap<int> reverse_map(-1, nVtx);

	// subcore is found on old graph (including removed edge), then cd's are adjusted
	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

#ifdef MAINTAIN_CD
	// maxcore_degrees update
	int roots_core = (*K)[root];
	if ((*K)[u] != (*K)[v]) {
		(*maxcore_degrees)[root]--;
	}
	else {
		(*maxcore_degrees)[u]--;
		(*maxcore_degrees)[v]--;
	}
#endif

	(*ch_info).core_number = (*K)[root];

	util::timestamp t1_find_subcore;
	find_subcore (graph, K,
#ifdef MAINTAIN_CD
			maxcore_degrees,
#endif
			&reverse_map, root, &subcore, &cd); // each edge list of vertex v, in subcore, starts with v
	util::timestamp t2_find_subcore;

	// graph is changed here
	util::timestamp t_graph_change_1;
	// edge removal
	for (int i = 0; i < (*graph)[u].size(); i++) {
		if ((*graph)[u][i] == v) {
			(*graph)[u].erase((*graph)[u].begin() + i);
			break;
		}
	}

	for (int i = 0; i < (*graph)[v].size(); i++) {
		if ((*graph)[v][i] == u) {
			(*graph)[v].erase((*graph)[v].begin() + i);
			break;
		}
	}
	util::timestamp t_graph_change_2;

	bool both_ow_root;
	// subcore is changed here
	both_ow_root = false;
	if ((*K)[u] == (*K)[v])
		both_ow_root = true;

	if (both_ow_root) {
		vertex u_rev = reverse_map[u];
		for (vertex j = 1; j < subcore[u_rev].size(); j++) {
			vertex v_tmp = subcore[u_rev][j];
			if (v_tmp == v)
				subcore[u_rev].erase(subcore[u_rev].begin() + j);
		}

		vertex v_rev = reverse_map[v];
		for (vertex j = 1; j < subcore[v_rev].size(); j++) {
			vertex u_tmp = subcore[v_rev][j];
			if (u_tmp == u)
				subcore[v_rev].erase(subcore[v_rev].begin() + j);
		}
	}

	graph_change_time += (t_graph_change_2 - t_graph_change_1);

	int tot_size = 0;
	for (int i = 0; i < subcore.size(); i++)
		tot_size += subcore[i].size() - 1;

	(*ch_info).core_v_size = subcore.size();
	(*ch_info).core_e_size = tot_size / 2;

	// 'bucket'ization
	Bucket bs;
	nVtx = (*graph).size();

	vertex max_core_degree = 0;
	if (both_ow_root) {
		for (vertex i = 0; i < cd.size(); i++) {
#ifndef MAINTAIN_CD
			if (cd[i].id == u)
				cd[i].core_degree--;

			if (cd[i].id == v)
				cd[i].core_degree--;
#endif

			if (cd[i].core_degree > max_core_degree)
				max_core_degree = cd[i].core_degree;
		}
	}
	else {
		for (vertex i = 0; i < cd.size(); i++) {
#ifndef MAINTAIN_CD
			if (cd[i].id == root)
				cd[i].core_degree--;
#endif

			if (cd[i].core_degree > max_core_degree)
				max_core_degree = cd[i].core_degree;
		}
	}

	bs.Initialize(max_core_degree);
	vertex core_degree_of_root;
	for (vertex i = 0; i < cd.size(); i++) {
		bs.Insert (cd[i].id, cd[i].core_degree);
		if (subcore[i][0] == root)
			core_degree_of_root = cd[i].core_degree;
	}

	int core_of_root = (*K)[root];
	vertex core_degree_of_u = 0;

#ifdef MAINTAIN_CD
	v_container changeds;
#endif

	vertex numof_changed_vertices = 0;
	while (1) {
		vertex u;
		int value_of_u;
		int ret = bs.PopMin(&u, &value_of_u);

		if (ret == -1)
			break;
		int asdf = (*K)[u];
		if ((*K)[u] > value_of_u) {
			(*K)[u] = value_of_u;
			numof_changed_vertices++;
#ifdef MAINTAIN_CD
			changeds.push_back(u);
#endif
		}

		core_degree_of_u = value_of_u;

		if (core_degree_of_u < core_of_root) {
			vertex u_rev = reverse_map[u];
			assert (u == subcore[u_rev][0]);
			for (vertex j = 1; j < subcore[u_rev].size(); j++) { /* decrease the degree of the neighboors with greater degree*/
				vertex v = subcore[u_rev][j]; //v is real vertex id
				if (bs.CurrentValue(v) > core_degree_of_u) {
					bs.DecVal(v);
				}
			}
		}
		else {
			break;
		}
	}


#ifdef MAINTAIN_CD

	bool any_K_change = false;
	if (changeds.size() > 0)
		any_K_change = true;

	if (any_K_change) {
		int len = (*graph).size();
		vertex nVtx= (*graph).size();
		HashMap<int> processed (false, nVtx);

		for (int i = 0; i < changeds.size(); i++)
			processed[changeds[i]] = true;

		v_container neigs;

		for (int i = 0; i < changeds.size(); i++) {
			int u = changeds[i];
			(*maxcore_degrees)[u] = core_degree (graph, K, u, (*K)[u]);
			for (int j = 0; j < (*graph)[u].size(); j++) {
				vertex w = (*graph)[u][j];
				if (processed.hasDefaultValue(w) && (((*K)[w] == (*K)[u]) || ((*K)[w] == ((*K)[u] + 1)))) {
					neigs.push_back (w);
					processed[w] = true;
				}
			}
		}

		for (int i = 0; i < neigs.size(); i++) {
			vertex w = neigs[i];
			(*maxcore_degrees)[w] = core_degree (graph, K, w, (*K)[w]);
		}

		neigs.clear();
		processed.reset(false);
	}
	changeds.clear();
#endif

	subcore.clear();
	cd.clear();
	reverse_map.reset(-1);


	if ((*K)[root] > (*core_number))
		*core_number = (*K)[root];

	(*ch_info).numof_changed_K_vertices = numof_changed_vertices;
	char timestr1[20];
	char timestr2[20];
	graph_change_time.to_c_str (timestr1, 20);
	strcpy ((*ch_info).graph_change_str, timestr1);

	util::timestamp t_update_K_2;
	update_K_time += ((t_update_K_2 - t_update_K_1) - (t_graph_change_2 - t_graph_change_1));

	update_K_time.to_c_str (timestr2, 20);
	strcpy ((*ch_info).update_K_str, timestr2);

	return;
}


