#include "main-kcore.hpp"

int purecore_degree (Graph* graph, v_container* K, vertex v, int k, int* counted_v_size, int* counted_e_size) {

	bool more_to_do = false;
	if ((counted_v_size != NULL) && (counted_e_size != NULL))
		more_to_do = true;
	int val = 0;
	for (unsigned int i = 0; i < (*graph)[v].size(); i++) {
		vertex w = (*graph)[v][i];
		if (((*K)[w] > k) || (((*K)[w] == k) && (core_degree(graph, K, w, k) > k))) {
			val++;
			if (more_to_do) {
				(*counted_v_size)++;
				(*counted_e_size) += (*graph)[w].size();
			}
		}
	}
	return val;
}

void propagate_eviction (Graph* graph, v_container* K, HashMap<vertex>* cd, HashMap<bool>* evicted,
		int core_of_root, vertex v) {

	int nVtx = (*graph).size();
	(*evicted)[v] = true;

	for (int i = 0; i < (*graph)[v].size(); i++) {
		vertex w = (*graph)[v][i];
		if (((*K)[w] == core_of_root)) {
			(*cd)[w]--;

#ifdef TRV_DEBUG
			printf("for propagated vertex %d: cd: %d, K:%d\n",print_v(w), (*cd)[w], (*K)[w]);
#endif

			if (((*cd)[w] == core_of_root) && ((*evicted).hasDefaultValue(w))) {
#ifdef TRV_DEBUG
				printf("propagation from vertex %d: cd: %d, K:%d\n",print_v(w), (*cd)[w], (*K)[w]);
#endif
				propagate_eviction (graph, K, cd, evicted,
#ifdef SWITCH_DEBUG
						cd_flag,
#endif
						core_of_root, w);

#ifdef TRV_DEBUG
				printf("propagation from vertex %d: cd: %d, K:%d finishes\n",print_v(w), (*cd)[w], (*K)[w]);
#endif
			}
		}
	}
	return;
}

void pre_update_hCD_values_removal (int hop, Graph& graph, v_container& K, vertex root,
		vertex r1, vertex r2, vector<vector<vertex> >& hop_degrees) {

	int roots_core = K[root];
	set<vertex>::iterator it;
	vector<set<vertex> > frontiers;
	frontiers.resize(hop);

	if (K[r1] != K[r2]) {
		vertex u = root;
		for (int h = 0; h < hop; h++) {
			if (h > 0) {
				for (it = frontiers[h-1].begin(); it != frontiers[h-1].end(); it++) {
					vertex v = *it;
					for (int i = 0; i < graph[v].size(); i++) {
						int w = graph[v][i];
						if (K[w] == roots_core) {
							hop_degrees[h][w]--;
							if (h < hop -1 && hop_degrees[h][w] == roots_core)
								frontiers[h].insert(w);
						}
					}
				}
			}

			hop_degrees[h][u]--;
			if (h < hop - 1 && hop_degrees[h][u] == roots_core)
				frontiers[h].insert(u);
		}
	}
	else {

		vertex u1 = r1;
		vertex u2 = r2;

		vector<vector<int> > old_hop_degrees;
		vector<int> old1;
		vector<int> old2;
		for (int h = 0; h < hop; h++) {
			old1.push_back(hop_degrees[h][u1]);
			old2.push_back(hop_degrees[h][u2]);
		}
		old_hop_degrees.push_back(old1);
		old_hop_degrees.push_back(old2);


		for (int h = 0; h < hop; h++) {

			if (h == 0) {
				hop_degrees[h][u1]--;
				if (hop_degrees[h][u1] == roots_core)
					frontiers[h].insert(u1);

				hop_degrees[h][u2]--;
				if (hop_degrees[h][u2] == roots_core)
					frontiers[h].insert(u2);
			}
			else {
				if (old_hop_degrees[1][h-1] > roots_core) {
					hop_degrees[h][u1]--;
					if (h < hop - 1 && hop_degrees[h][u1] == roots_core)
						frontiers[h].insert(u1);
				}

				if (old_hop_degrees[0][h-1] > roots_core) {
					hop_degrees[h][u2]--;
					if (h < hop - 1 && hop_degrees[h][u2] == roots_core)
						frontiers[h].insert(u2);
				}

				for (it = frontiers[h-1].begin(); it != frontiers[h-1].end(); it++) {
					vertex v = *it;
					for (int i = 0; i < graph[v].size(); i++) {
						int w = graph[v][i];
						if (!(v == u1 && w == u2) && !(v == u2 && w == u1) && K[w] == roots_core) {

							hop_degrees[h][w]--;
							if (h < hop - 1 && hop_degrees[h][w] == roots_core)
								frontiers[h].insert(w);
						}
					}
				}
			}
		}
	}
}

void traversal_purecore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
#endif
		vertex u, vertex v, vertex* numof_changed_vertices,
		incremental_debug* ch_info) {

	util::timestamp eviction_time (0,0);

	// root is found
	vertex root;
	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

	int traversal_v_space = 0;
	int traversal_e_space = 0;
	int counted_v_size = 0;
	int counted_e_size = 0;

	vertex nVtx= (*graph).size();
	stack<vertex> kova;
	HashMap<bool> visited(false, nVtx);
	HashMap<bool> evicted(false, nVtx);
	HashMap<vertex> cd(0, nVtx);

#ifdef SWITCH_DEBUG
	vertex visited_size = 0;
	vertex evicted_size = 0;
	vertex cd_size = 0;
	vertex processed_size = 0;

	bool* cd_flag = (bool *) malloc (sizeof(bool) * nVtx);
	for (int i = 0; i < nVtx; i++)
		cd_flag[i] = false;
#endif

#ifdef MAINTAIN_CD
	v_container changeds;
#endif

	int core_of_root = (*K)[root];
	kova.push (root);

#ifdef MAINTAIN_CD
	int tmp = (*purecore_degrees)[root];
#else
	int tmp = purecore_degree (graph, K, root, core_of_root, &counted_v_size, &counted_e_size);
#endif

	visited[root] = true;
	cd[root] += tmp;
#ifdef SWITCH_DEBUG
	cd_flag[root] = true;
#endif

	traversal_v_space++;
	traversal_e_space += tmp;

#ifdef TRV_DEBUG
	printf("for root %d: cd: %d, K:%d\n",print_v(root), cd[root], (*K)[root]);
#endif

	while (!kova.empty()) {

		vertex v = kova.top();
		kova.pop();

#ifdef TRV_DEBUG
		printf("for topped vertex %d: cd: %d, K:%d\n",print_v(v), cd[v], (*K)[v]);
#endif

		if (cd[v] > core_of_root) {
			for (unsigned int i = 0; i < (*graph)[v].size(); i++) {
				vertex w = (*graph)[v][i];
#ifdef MAINTAIN_CD
				int coredegree_of_w = (*maxcore_degrees)[w];
#else
				int coredegree_of_w = core_degree (graph, K, w, core_of_root);
				//		int coredegree_of_w = hop_core_degree (*graph, *K, w, core_of_root, 1);
#endif
				counted_v_size++;
				counted_e_size += (*graph)[w].size();

				if (visited.hasDefaultValue(w) && ((*K)[w] == core_of_root)
						&& (coredegree_of_w > core_of_root)) {
					visited[w] = true;
					kova.push (w);
#ifdef TRV_DEBUG
					printf("for pushed vertex %d: cd: %d, K:%d\n",print_v(w), cd[w], (*K)[w]);
#endif

#ifdef MAINTAIN_CD
					int cdeg = (*purecore_degrees)[w];
#else
					int cdeg = purecore_degree (graph, K, w, core_of_root, &counted_v_size, &counted_e_size);
#endif
					cd[w] += cdeg;

#ifdef SWITCH_DEBUG
					cd_flag[w] = true;
#endif

					traversal_v_space++;
					traversal_e_space += cdeg;
				}
			}
		}
		else {
#ifdef TRV_DEBUG
			printf("propagation from vertex %d: cd: %d, K:%d\n",print_v(v), cd[v], (*K)[v]);
#endif

			if (evicted.hasDefaultValue(v)) {
				if (v != root) {
					propagate_eviction (graph, K, &cd, &evicted,
#ifdef SWITCH_DEBUG
							cd_flag,
#endif
							core_of_root, v);
				}
				else {
					evicted[v] = true;
				}
			}
#ifdef TRV_DEBUG
			printf("propagation from vertex %d: cd: %d, K:%d finishes\n",print_v(v), cd[v], (*K)[v]);
#endif
		}
	}

	for(HashMap<bool>::iterator it=visited.begin(); it!=visited.end(); ++it) {
		int i = it->first;
		if (evicted.hasDefaultValue(i)) {
			(*K)[i]++;
			(*numof_changed_vertices)++;
#ifdef MAINTAIN_CD
			changeds.push_back (i);
#endif
		}
	}

	util::timestamp t_maintenance_3;
#ifdef MAINTAIN_CD

	bool any_K_change = false;
	if (changeds.size() > 0)
		any_K_change = true;

	int len = (*graph).size();
	HashMap<bool> processed(false, nVtx);

	for (int i = 0; i < changeds.size(); i++) {
		processed[changeds[i]] = true;
	}

	v_container neigs;
	v_container neigs_of_neigs;

	for (int i = 0; i < changeds.size(); i++) {
		int u = changeds[i];
		if (any_K_change) {
			(*maxcore_degrees)[u] = core_degree (graph, K, u, (*K)[u]);
			(*purecore_degrees)[u] = purecore_degree (graph, K, u, (*K)[u], NULL, NULL);
		}
		for (int j = 0; j < (*graph)[u].size(); j++) {
			vertex w = (*graph)[u][j];

			if (processed.hasDefaultValue(w) && (((*K)[w] == (*K)[u]) ||
					((any_K_change) && ((*K)[w] == ((*K)[u] - 1))))) {
				neigs.push_back (w);
				processed[w] = true;
			}
		}
	}

	for (int i = 0; i < neigs.size(); i++) {
		vertex w = neigs[i];
		if (any_K_change)
			(*maxcore_degrees)[w] = core_degree (graph, K, w, (*K)[w]);
		(*purecore_degrees)[w] = purecore_degree (graph, K, w, (*K)[w], NULL, NULL);
		if (any_K_change) {
			for (int j = 0; j < (*graph)[w].size(); j++) {
				vertex x = (*graph)[w][j];

				if (processed.hasDefaultValue(x) && (((*K)[x] == (*K)[w]) || ((*K)[x] == ((*K)[w] - 1)))) {
					neigs_of_neigs.push_back (x);
					processed[x] = true;
				}
			}
		}
	}

	if (any_K_change) {
		for (int i = 0; i < neigs_of_neigs.size(); i++) {
			vertex y = neigs_of_neigs[i];
			(*purecore_degrees)[y] = purecore_degree (graph, K, y, (*K)[y], NULL, NULL);
		}
	}

	neigs.clear();
	neigs_of_neigs.clear();

	processed.reset(false);
	changeds.clear();
#endif
	util::timestamp t_maintenance_4;

	(*ch_info).core_v_size = 0;
	(*ch_info).core_e_size = 0;
#ifdef TOTAL_TOUCHED
	(*ch_info).core_v_size += counted_v_size;
	(*ch_info).core_e_size += counted_e_size;
#endif

	(*ch_info).core_v_size = traversal_v_space;
	(*ch_info).core_e_size = traversal_e_space/2;

	visited.reset(false);
	evicted.reset(false);
	cd.reset(-1);
	return;
}

void traversal_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop) {

	util::timestamp t_begin;

	vertex root;

	util::timestamp graph_change_time (0,0);
	util::timestamp update_K_time (0,0);
	util::timestamp t_update_K_1;

	(*ch_info).insert_ow_remove = true;
	(*ch_info).u = u;
	(*ch_info).v = v;
	//    vertex root;

	// graph is changed here
	util::timestamp t_graph_change_1;
	// edge insertion in sorted manner
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

	util::timestamp t_begin2;

	// root is found
	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

	// MCD and PCD values are prepared
	util::timestamp t_maintenance_1;
#ifdef MAINTAIN_CD
	int roots_core = (*K)[root];
	if ((*K)[u] != (*K)[v]) {
		(*maxcore_degrees)[root]++;
		(*purecore_degrees)[root]++;

		if ((*maxcore_degrees)[root] == (roots_core + 1)) {
			for (int i = 0; i < (*graph)[root].size(); i++) {
				int w = (*graph)[root][i];
				if (((*K)[w] == roots_core)) {
					(*purecore_degrees)[w]++;
				}
			}
		}
	}
	else {
		(*maxcore_degrees)[u]++;
		(*maxcore_degrees)[v]++;
		(*purecore_degrees)[u]++;
		(*purecore_degrees)[v]++;

		if ((*maxcore_degrees)[u] == (roots_core + 1)) {
			for (int i = 0; i < (*graph)[u].size(); i++) {
				int w = (*graph)[u][i];
				if ((w != v) && ((*K)[w] == roots_core)) {
					(*purecore_degrees)[w]++;
				}
			}
		}

		if ((*maxcore_degrees)[v] == (roots_core + 1)) {
			for (int i = 0; i < (*graph)[v].size(); i++) {
				int w = (*graph)[v][i];
				if ((w != u) && ((*K)[w] == roots_core)) {
					(*purecore_degrees)[w]++;
				}
			}
		}
	}
#endif
	util::timestamp t_maintenance_2;

	// traversal algorithm is run
	(*ch_info).core_number = (*K)[root];
	int numof_changed_vertices = 0;
	traversal_purecore (graph, K,
#ifdef MAINTAIN_CD
			maxcore_degrees,
			purecore_degrees,
#endif
			u, v, &numof_changed_vertices,
			ch_info);

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

	util::timestamp t_end;
	return;
}

void propagate_decrement (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
#endif
		HashMap<vertex>* cd,
		HashMap<bool>* decreased,
		HashMap<bool>* visited, int core_of_root,
		vertex v, v_container* changeds) {
	(*decreased)[v] = true;
	(*K)[v]--;
	(*changeds).push_back (v);
	for (int i = 0; i < (*graph)[v].size(); i++) {
		vertex w = (*graph)[v][i];
		if (((*K)[w] == core_of_root)) {
#ifdef MAINTAIN_CD
			if ((*visited).hasDefaultValue(w)) {
				(*cd)[w] += (*maxcore_degrees)[w];
				(*visited)[w] = true;
			}
			(*cd)[w]--;
#else
			(*cd)[w] = core_degree (graph, K, w, core_of_root);
#endif

			if ((!(*decreased)[w]) && ((*cd)[w] < core_of_root)) {
				//	    if (((*decreased).hasDefaultValue(w)) && ((*cd)[w] < core_of_root)) {
				propagate_decrement (graph, K,
#ifdef MAINTAIN_CD
						maxcore_degrees,
#endif
						cd, decreased,
						visited,
						core_of_root, w, changeds);
			}
		}
	}
	return;
}

void traversal_removal (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop) {

	util::timestamp t1;
	util::timestamp graph_change_time (0,0);
	util::timestamp update_K_time (0,0);

	util::timestamp t_update_K_1;

	(*ch_info).insert_ow_remove = false;
	(*ch_info).u = u;
	(*ch_info).v = v;
	int roots_core;
	vertex root;

	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

	(*ch_info).core_number = (*K)[root];
	vertex numof_changed_vertices = 0;

	v_container changeds;

	util::timestamp t2;
#ifdef MAINTAIN_CD
	pre_update_hCD_values_removal (hop, *graph, *K, root, u, v, hop_degrees);
#endif

	util::timestamp t3;

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

	vertex nVtx= (*graph).size();
	HashMap<bool> visited(false, nVtx);
	HashMap<bool> decreased(false, nVtx);
	HashMap<vertex> cd_array(0, nVtx);
	int core_of_root = (*K)[root];

	if ((*K)[u] != (*K)[v]) {
#ifdef MAINTAIN_CD
		int tmp = hop_degrees[0][root];
#else
		int tmp = core_degree (graph, K, root, core_of_root);
#endif
		if (visited.hasDefaultValue(root)) {
			cd_array[root] += tmp;
			visited[root] = true;
		}

		if ((decreased.hasDefaultValue(root)) && (cd_array[root] < core_of_root)) {
			propagate_decrement (graph, K,
#ifdef MAINTAIN_CD
					&hop_degrees[0],
#endif
					&cd_array, &decreased,
					&visited,
					core_of_root, root, &changeds);
		}
	}
	else {
#ifdef MAINTAIN_CD
		int tmp = hop_degrees[0][u];
#else
		int tmp = core_degree (graph, K, u, core_of_root);
#endif
		if (visited.hasDefaultValue(u)) {
			cd_array[u] += tmp;
			visited[u] = true;
		}

		if ((decreased.hasDefaultValue(u)) &&
				(cd_array[u] < core_of_root)) {
			propagate_decrement (graph, K,
#ifdef MAINTAIN_CD
					&hop_degrees[0],
#endif
					&cd_array, &decreased,
					&visited,
					core_of_root, u, &changeds);
		}

#ifdef MAINTAIN_CD
		tmp = hop_degrees[0][v];
#else
		tmp = core_degree (graph, K, v, core_of_root);
#endif
		if (visited.hasDefaultValue(v)) {
			cd_array[v] += tmp;
			visited[v] = true;
		}

		if ((decreased.hasDefaultValue(v)) &&
				(cd_array[v] < core_of_root)) {
			propagate_decrement (graph, K,
#ifdef MAINTAIN_CD
					&hop_degrees[0],
#endif
					&cd_array, &decreased,
					&visited,
					core_of_root, v, &changeds);
		}
	}


	numof_changed_vertices = changeds.size();
	(*ch_info).core_v_size = changeds.size();
	int tmp = 0;
	for (int i = 0; i < changeds.size(); i++)
		tmp += (*graph)[changeds[i]].size();
	(*ch_info).core_e_size = tmp / 2;

	visited.reset(false);
	decreased.reset(false);
	cd_array.reset(0);

	util::timestamp t4;

#ifdef MAINTAIN_CD
	util::timestamp tcall (0, 0);
	vector<vertex> nextch;
	HashMap<bool> processed(false, (*graph).size());

	for (vertex i = 0; i < changeds.size(); i++)
		processed[changeds[i]] = true;

	for (int i = 0; i < hop; i++) {
		nextch.clear();
		for (vertex j = 0; j < changeds.size(); j++) {
			vertex u = changeds[j];
			for (vertex k = 0; k < (*graph)[u].size(); k++) {
				vertex w = (*graph)[u][k];
				if (processed.hasDefaultValue(w) && ((*K)[w] == (*K)[u] || (*K)[w] == ((*K)[u] + 1))) {
					nextch.push_back(w);
					processed[w] = true;
				}
			}
		}
		util::timestamp t1;
		changeds.insert (changeds.end(), nextch.begin(), nextch.end());
		util::timestamp t2;
		tcall += t2 - t1;
		for (vertex j = 0; j < changeds.size(); j++) {
			vertex u = changeds[j];
			hop_degrees[i][u] = hop_core_degree_CD (hop_degrees, *graph, *K, u, (*K)[u], i+1);
		}
	}

#endif

	util::timestamp t5;

	changeds.clear();
	if ((*K)[root] > (*core_number))
		*core_number = (*K)[root];

	(*ch_info).numof_changed_K_vertices = numof_changed_vertices;
	char timestr1[20];
	char timestr2[20];
	graph_change_time += (t_graph_change_2 - t_graph_change_1);
	graph_change_time.to_c_str (timestr1, 20);
	strcpy ((*ch_info).graph_change_str, timestr1);

	util::timestamp t_update_K_2;
	update_K_time += ((t_update_K_2 - t_update_K_1) - (t_graph_change_2 - t_graph_change_1));

	update_K_time.to_c_str (timestr2, 20);
	strcpy ((*ch_info).update_K_str, timestr2);
	util::timestamp t6;

	return;
}

