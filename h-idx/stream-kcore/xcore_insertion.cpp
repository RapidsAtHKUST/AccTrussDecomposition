#include "main-kcore.hpp"

vertex hop_core_degree (Graph& graph, v_container& K, vertex v, int k, int hop) {
	util::timestamp t1;
	if (hop == 1) {
		int val = 0;
		for (unsigned int i = 0; i < graph[v].size(); i++) {
			vertex w = graph[v][i];
			if (K[w] >= k)
				val++;
		}
		return val;
	}
	else {
		int val = 0;
		for (unsigned int i = 0; i < graph[v].size(); i++) {
			vertex w = graph[v][i];
			if ((K[w] > k) || ((K[w] == k) && (hop_core_degree(graph, K, w, k, hop - 1) > k)))
				val++;
		}
		return val;
	}
	util::timestamp t2;
	hcd += t2 - t1;
}

vertex hop_core_degree_CD (vector<vector<vertex> >& hop_degrees, Graph& graph, v_container& K, vertex v, int k, int hop) {
	if (hop == 1) {
		int val = 0;
		for (unsigned int i = 0; i < graph[v].size(); i++) {
			vertex w = graph[v][i];
			if (K[w] >= k)
				val++;
		}
		return val;
	}
	else {
		int val = 0;
		for (unsigned int i = 0; i < graph[v].size(); i++) {
			vertex w = graph[v][i];
			if ((K[w] > k) || ((K[w] == k) && (hop_degrees[hop - 2][w] > k)))
				val++;
		}
		return val;
	}
}

void find_ncore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		HashMap<int>* reverse_map, vertex root, Graph* ncore,
		core_degrees* cd, int hop) {

	// each edge list of vertex v, in subcore, starts with  v
	vertex nVtx= (*graph).size();

	HashMap<bool> visited(false, nVtx);
	queue<vertex> bfsorder;

	cd_elt cd_temp;
	visited[root] = true;
	int core_of_root = (*K)[root];
	bfsorder.push(root);
	while (!bfsorder.empty()) {

		vertex v = bfsorder.front();
		bfsorder.pop();
		v_container new_vertex;
		new_vertex.push_back(v);
		cd_temp.id = v;
		cd_temp.core_degree = 0;

#ifdef MAINTAIN_CD
		cd_temp.core_degree = hop_degrees[hop - 1][v];
#endif

		for (vertex i = 0; i < (*graph)[v].size(); i++) {
			vertex w = (*graph)[v][i];
#ifdef MAINTAIN_CD
			vertex tmp;
			if (hop > 1)
				tmp = hop_degrees[hop - 2][w];
			else
				tmp = INT_MAX;
			if (((*K)[w] == core_of_root) && (tmp > core_of_root)) {
				new_vertex.push_back(w);
				if (visited.hasDefaultValue(w)) {
					bfsorder.push(w);
					visited[w] = true;
				}
			}
#else
			int cd_of_w = INT_MAX;
			if (hop > 1)
				cd_of_w = hop_core_degree (*graph, *K, w, core_of_root, hop - 1);
			if (((*K)[w] > core_of_root) || (((*K)[w] == core_of_root) && (cd_of_w > core_of_root))) {
				cd_temp.core_degree++;
				if (((*K)[w] == core_of_root) && (cd_of_w > core_of_root))
				{
					new_vertex.push_back(w);
					if (visited.hasDefaultValue(w)) {
						bfsorder.push(w);
						visited[w] = true;
					}
				}
			}
#endif

		}

		(*cd).push_back (cd_temp);
		(*ncore).push_back(new_vertex);
		(*reverse_map)[v] = (*ncore).size() - 1;
		new_vertex.clear();
	}

	visited.reset(false);
	return;
}

void pre_update_hCD_values (int hop, Graph& graph, v_container& K, vertex root,
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
							hop_degrees[h][w]++;
							if (h < hop -1 && hop_degrees[h][w] == roots_core + 1)
								frontiers[h].insert(w);
						}
					}
				}
			}

			hop_degrees[h][u]++;
			if (h < hop - 1 && hop_degrees[h][u] == (roots_core + 1))
				frontiers[h].insert(u);
		}
	}
	else {
		vertex u1 = r1;
		vertex u2 = r2;
		for (int h = 0; h < hop; h++) {

			if (h == 0) {
				hop_degrees[h][u1]++;
				if (hop_degrees[h][u1] == roots_core + 1)
					frontiers[h].insert(u1);

				hop_degrees[h][u2]++;
				if (hop_degrees[h][u2] == roots_core + 1)
					frontiers[h].insert(u2);
			}
			else {
				if (hop_degrees[h-1][u2] > roots_core) {
					hop_degrees[h][u1]++;
					if (h < hop - 1 && hop_degrees[h][u1] == roots_core + 1)
						frontiers[h].insert(u1);
				}

				if (hop_degrees[h-1][u1] > roots_core) {
					hop_degrees[h][u2]++;
					if (h < hop - 1 && hop_degrees[h][u2] == roots_core + 1)
						frontiers[h].insert(u2);
				}

				for (it = frontiers[h-1].begin(); it != frontiers[h-1].end(); it++) {
					vertex v = *it;
					for (int i = 0; i < graph[v].size(); i++) {
						int w = graph[v][i];
						if (!(v == u1 && w == u2) && !(v == u2 && w == u1) && K[w] == roots_core) {
							hop_degrees[h][w]++;
							if (h < hop - 1 && hop_degrees[h][w] == roots_core + 1)
								frontiers[h].insert(w);
						}
					}
				}
			}
		}
	}
}

void post_update_hCD_values (int hop, Graph& graph, v_container& K,
		vector<vertex>& changeds, vector<vector<vertex> >& hop_degrees) {

	util::timestamp tcall (0, 0);
	vector<vertex> nextch;
	HashMap<bool> processed(false, graph.size());

	for (vertex i = 0; i < changeds.size(); i++)
		processed[changeds[i]] = true;

	for (int i = 0; i < hop; i++) {
		nextch.clear();
		for (vertex j = 0; j < changeds.size(); j++) {
			vertex u = changeds[j];
			for (vertex k = 0; k < graph[u].size(); k++) {
				vertex w = graph[u][k];
				if (processed.hasDefaultValue(w) && (K[w] == K[u] || K[w] == (K[u] - 1))) {
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
			hop_degrees[i][u] = hop_core_degree_CD (hop_degrees, graph, K, u, K[u], i+1);
		}
	}
}

void ncore_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop) {

	util::timestamp graph_change_time (0,0);
	util::timestamp update_K_time (0,0);
	util::timestamp maintenance_time (0,0);

	util::timestamp t_update_K_1;

	(*ch_info).insert_ow_remove = true;
	(*ch_info).u = u;
	(*ch_info).v = v;
	vertex root;
	Graph ncore; // each edge list of vertex v starts with v
	core_degrees cd; // pairs of vertex id and cd of vertex

	vertex nVtx= (*graph).size();
	HashMap<int> reverse_map(-1, nVtx);

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

	util::timestamp t_graph_change_2;
	graph_change_time += (t_graph_change_2 - t_graph_change_1);

	// ncore is found
	if ((*K)[u] < (*K)[v])
		root = u;
	else
		root = v;

	util::timestamp t_maintenance_1;
#ifdef MAINTAIN_CD
	pre_update_hCD_values (hop, *graph, *K, root, u, v, hop_degrees);
#endif
	util::timestamp t_maintenance_2;
	maintenance_time += t_maintenance_2 - t_maintenance_1;

	(*ch_info).core_number = (*K)[root];
	util::timestamp t1_find_ncore;

	find_ncore (graph, K,
#ifdef MAINTAIN_CD
			hop_degrees,
#endif
			&reverse_map, root, &ncore, &cd,  hop); // each edge list of vertex v, in ncore, starts with v

	util::timestamp t2_find_ncore;

	int tot_size = 0;
	for (int i = 0; i < ncore.size(); i++)
		tot_size += ncore[i].size() - 1;

	(*ch_info).core_v_size = ncore.size();
	(*ch_info).core_e_size = tot_size / 2;

	// 'bucket'ization
	Bucket bs;
	nVtx = (*graph).size();

	vertex max_core_degree = 0;
	for (vertex i = 0; i < cd.size(); i++) {
		if (cd[i].core_degree > max_core_degree)
			max_core_degree = cd[i].core_degree;
	}

	bs.Initialize(max_core_degree);
	vertex core_degree_of_root;
	for (vertex i = 0; i < cd.size(); i++) {
		bs.Insert (cd[i].id, cd[i].core_degree);
		if (ncore[i][0] == root)
			core_degree_of_root = cd[i].core_degree;
	}

	int core_of_root = (*K)[root];
	vertex core_degree_of_u = 0;

#ifdef MAINTAIN_CD
	v_container changeds;
#endif

	util::timestamp ttt (0, 0);
	util::timestamp t1_loop;

	vertex numof_changed_vertices = 0;
	int count = 0;

	while (1) {
		count++;
		vertex u;
		int value_of_u;
		int ret = bs.PopMin(&u, &value_of_u);

		if (ret == -1)
			break;

		if (value_of_u == 0)
			continue;

		core_degree_of_u = value_of_u;

		if ((*K)[u] < value_of_u) {
			(*K)[u] = value_of_u;
			numof_changed_vertices++;
#ifdef MAINTAIN_CD
			changeds.push_back(u);
#endif

			vertex u;
			int value_of_u;
			int new_K_value = core_degree_of_u;
			while (bs.PopMin(&u, &value_of_u) != -1) {
				(*K)[u] = new_K_value;
				numof_changed_vertices++;
#ifdef MAINTAIN_CD
				changeds.push_back(u);
#endif


			}
			break;
		}
		else {
			util::timestamp t1;
			vertex u_rev = reverse_map[u];
			for (vertex j = 1; j < ncore[u_rev].size(); j++) { /* decrease the degree of the neighboors with greater degree*/
				vertex v = ncore[u_rev][j]; //v is real vertex id
				if (bs.CurrentValue(v) > core_degree_of_u)
					bs.DecVal(v);
			}
			util::timestamp t2;
			ttt += t2 - t1;

		}
	}

	util::timestamp t_maintenance_3;
#ifdef MAINTAIN_CD
	post_update_hCD_values (hop, *graph, *K, changeds, hop_degrees);
#endif
	util::timestamp t_maintenance_4;
	maintenance_time += t_maintenance_4 - t_maintenance_3;

	util::timestamp t2_loop;

	ncore.clear();
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

	char timestr3[20];
	maintenance_time.to_c_str(timestr3, 20);
	strcpy ((*ch_info).maintenance_str, timestr3);

	return;
}


