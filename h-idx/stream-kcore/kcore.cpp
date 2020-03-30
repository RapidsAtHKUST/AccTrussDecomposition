#include "main-kcore.hpp"

void update_on_insertion (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop, int algorithm) {
	if (algorithm == N_CORE) { // subcore and purecore algorithms for hop = 1 and hop = 2
		ncore_insertion (graph, K,
#ifdef MAINTAIN_CD
			hop_degrees,
#endif
			core_number, u, v, ch_info, hop);
	}
	else if (algorithm == TRAVERSAL) { // traversal algorithm (Alg 5 in VLDBJ paper)
		traversal_insertion (graph, K,
#ifdef MAINTAIN_CD
			&(hop_degrees[0]),
			&(hop_degrees[1]),
#endif
			core_number, u, v, ch_info, hop);
	}
	else if (algorithm == N_TRAVERSAL) { // multihop traversal algorithm (Sec 4.5 in VLDBJ paper)
		ntraversal_insertion (graph, K,
#ifdef MAINTAIN_CD
			hop_degrees,
#endif
			core_number, u, v, ch_info, hop);
	}
}

void update_on_removal (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int* core_number, vertex u, vertex v,
		incremental_debug* ch_info, int hop, int algorithm) {

	if (algorithm == N_CORE) { // subcore and purecore algorithms for hop = 1 and hop = 2
		ncore_removal (graph, K,
#ifdef MAINTAIN_CD
				&hop_degrees[0],
#endif
				core_number, u, v,	ch_info);
	}
	else if (algorithm == TRAVERSAL || algorithm == N_TRAVERSAL) { // traversal algorithm. RCD is an option.
		traversal_removal (graph, K,
#ifdef MAINTAIN_CD
				hop_degrees,
#endif
				core_number, u, v, ch_info, hop);
	}
}

int onebyone_kcore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
		vector<vector<vertex> >& hop_degrees,
#endif
		util::timestamp& totaltime, int* core_number,
		int count, edge* edges,
		incremental_debug* change_info, int hop, int algorithm) {

	char *p = (char*) &totaltime;
	util::timestamp *pout = (util::timestamp*) p;
	util::timestamp t1;
	int num_of_edges = count;
	int nVtx = (*graph).size();

	srand (time(NULL));

	int edge_counter = 0;
	int counter = 0;
	while (num_of_edges > 0) {
		vertex u,v;

		// edge removal
		u = edges[edge_counter].u;
		v = edges[edge_counter].v;
		change_info[counter].old_K_u = (*K)[u];
		change_info[counter].old_K_v = (*K)[v];
		update_on_removal (graph, K,
#ifdef MAINTAIN_CD
					hop_degrees,
#endif
					core_number, u, v, change_info+counter, hop, algorithm
			);
		counter++;

#ifdef VERIFY // verify each removal
		v_container verify_K ((*graph).size(), 0);
		v_container verify_maxcore_degrees ((*graph).size(), -1);
		v_container verify_purecore_degrees ((*graph).size(), -1);
#ifdef MAINTAIN_CD
		vector<vector<vertex> > verify_hop_degrees;
		verify_hop_degrees.resize(hop);
		for (vertex i = 0; i < hop; i++)
			verify_hop_degrees[i].resize((*graph).size());
#endif

		int dummy = 0;
		vector<vector<vertex> > x;
		base_kcore (graph, &verify_K,
#ifdef MAINTAIN_CD
				&verify_maxcore_degrees,
				&verify_purecore_degrees,
				verify_hop_degrees,
#endif
				hop, totaltime, &dummy); // basic min-degree removal

		int cnt = 0;
		char str[10];
		for (unsigned int i = 0; i < (*K).size(); i++) {
			if ((*K)[i] != verify_K[i]) {
				strcpy (str, "removal");
				printf("on %d-th %s (%d-%d), base_K[%d]: %d\tstream_K[%d]: %d\n", counter, str, print_v(u),
						print_v(v), print_v(i), verify_K[i], print_v(i), (*K)[i]);
				cnt++;
			}
#ifdef MAINTAIN_CD
			for (int j = 0; j < hop; j++) {
				if (hop_degrees[j][i] != verify_hop_degrees[j][i]) {
					strcpy (str, "removal");
					printf("on %d-th %s (%d-%d), base_%dCD[%d]: %d\tstream_%dCD[%d]: %d\n", counter, str, print_v(u),
							print_v(v), j, print_v(i), verify_hop_degrees[j][i], j, print_v(i), hop_degrees[j][i]);
				}
			}
#endif
		}
		verify_K.clear();
		verify_maxcore_degrees.clear();
		verify_purecore_degrees.clear();
#endif

		int idx = counter - 1;
		printf("%-15s%6d-%6d %-15s%7s %-15s%10d,%10d %-10s%6d %-5s%3d\t%3d\n",
				"removal: ", print_v(change_info[idx].u), print_v(change_info[idx].v),
				"updateKTm: ", change_info[idx].update_K_str,
				"size (v,e): ", change_info[idx].core_v_size, change_info[idx].core_e_size,
				"nChKv: ", change_info[idx].numof_changed_K_vertices,
				"Ks: ", change_info[idx].old_K_u, change_info[idx].old_K_v
		);

		// edge insertion
		change_info[counter].old_K_u = (*K)[u];
		change_info[counter].old_K_v = (*K)[v];
		update_on_insertion (graph, K,
#ifdef MAINTAIN_CD
					maxcore_degrees,
					purecore_degrees,
					hop_degrees,
#endif
		core_number, u, v, change_info+counter, hop, algorithm);
		num_of_edges--;
		edge_counter++;
		counter++;

#ifdef VERIFY
		v_container verify_K ((*graph).size(), 0);
		v_container verify_maxcore_degrees ((*graph).size(), -1);
		v_container verify_purecore_degrees ((*graph).size(), -1);
#ifdef MAINTAIN_CD
		vector<vector<vertex> > verify_hop_degrees;
		verify_hop_degrees.resize(hop);
		for (vertex i = 0; i < hop; i++)
			verify_hop_degrees[i].resize((*graph).size());
#endif
		int dummy = 0;
		base_kcore (graph, &verify_K,
#ifdef MAINTAIN_CD
				&verify_maxcore_degrees,
				&verify_purecore_degrees,
				verify_hop_degrees,
#endif
				hop, totaltime, &dummy); // basic min-degree removal

		int cnt = 0;
		char str[10];
		for (unsigned int i = 0; i < (*K).size(); i++) {
			if ((*K)[i] != verify_K[i]) {
				strcpy (str, "insertion");
				printf("on %d-th %s (%d-%d), base_K[%d]: %d\tstream_K[%d]: %d\n", counter, str, print_v(u),
						print_v(v), print_v(i), verify_K[i], print_v(i), (*K)[i]);
				cnt++;
			}
#ifdef MAINTAIN_CD
			for (int j = 0; j < hop; j++) {
				if (hop_degrees[j][i] != verify_hop_degrees[j][i]) {
					strcpy (str, "insertion");
					printf("on %d-th %s (%d-%d), base_%dCD[%d]: %d\tstream_%dCD[%d]: %d\n", counter, str, print_v(u),
						print_v(v), j, print_v(i), verify_hop_degrees[j][i], j, print_v(i), hop_degrees[j][i]);
				}
			}
#endif
		}
		verify_K.clear();
		verify_maxcore_degrees.clear();
		verify_purecore_degrees.clear();
#endif


		idx = counter - 1;
		printf("%-15s%6d-%6d %-15s%7s %-15s%10d,%10d %-10s%6d %-5s%3d\t%3d\n",
				"insertion: ", print_v(change_info[idx].u), print_v(change_info[idx].v),
				"updateKTm: ", change_info[idx].update_K_str,
				"size (v,e): ", change_info[idx].core_v_size, change_info[idx].core_e_size,
				"nChKv: ", change_info[idx].numof_changed_K_vertices,
				"Ks: ", change_info[idx].old_K_u, change_info[idx].old_K_v
		);
	}

	util::timestamp t2;
	*pout += (t2-t1);
	return 0;
}

int core_degree (Graph* graph, v_container* K, vertex v, int k) {
	int val = 0;
	for (unsigned int i = 0; i < (*graph)[v].size(); i++) {
		vertex w = (*graph)[v][i];
		if ((*K)[w] >= k)
			val++;
	}
	return val;
}

#ifdef MAINTAIN_CD
int purecore_degree_fast (Graph* graph, v_container* K,
		v_container* maxcore_degrees,
		vertex v, int k, int* counted_v_size, int* counted_e_size) {

	bool more_to_do = false;
	if ((counted_v_size != NULL) && (counted_e_size != NULL))
		more_to_do = true;
	int val = 0;
	for (unsigned int i = 0; i < (*graph)[v].size(); i++) {
		vertex w = (*graph)[v][i];
		if ((*K)[w] > k) {
			val++;
			if (more_to_do) {
				(*counted_v_size)++;
				(*counted_e_size) += (*graph)[w].size();
			}
		}
		else if ((*K)[w] == k) {
			if ((*maxcore_degrees)[w] > k) {
				val++;
				if (more_to_do) {
					(*counted_v_size)++;
					(*counted_e_size) += (*graph)[w].size();
				}
			}
		}
	}
	return val;
}
#endif


// traditional kcore algorithm
int base_kcore (Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		v_container* maxcore_degrees,
		v_container* purecore_degrees,
		vector<vector<vertex> >& hop_degrees,
#endif
		int hop, util::timestamp& totaltime, int *core_number) {

	char *p = (char*) &totaltime;
	util::timestamp *pout = (util::timestamp*) p;
	util::timestamp t1;
	Naive_Bucket na_bs;
	int nVtx = (*graph).size();

	unsigned int max_degree = 0;
	for (vertex i = 0; i < nVtx; i++) {
		if ((*graph)[i].size() > max_degree)
			max_degree = (*graph)[i].size();
	}

	na_bs.Initialize(max_degree, ((*graph).size()));
	for (vertex i = 0; i < nVtx; i++) {
		vertex degree_of_i = (*graph)[i].size();
		na_bs.Insert (i, degree_of_i);
	}

	vertex degree_of_u = 0;
	util::timestamp t1_loop;
	while (1) {
		vertex u = -5;
		int value_of_u = -1;
		int ret = na_bs.PopMin(&u, &value_of_u);

		if (ret == -1)
			break;

		if (value_of_u == 0)
			continue;

		degree_of_u = (*K)[u] = value_of_u;
		for (unsigned int j = 0; j < (*graph)[u].size(); j++) { /* decrease the degree of the neighbors with greater degree*/
			vertex v = (*graph)[u][j];
			if (na_bs.CurrentValue(v) > degree_of_u) {
				na_bs.DecVal(v);
			}
		}
	}
	util::timestamp t2_loop;
	*core_number = degree_of_u; // degree_of_u is degree of last popped vertex

#ifdef MAINTAIN_CD
	if ((maxcore_degrees != NULL)
			&& (purecore_degrees != NULL)) {
		for (vertex u = 0; u < (*graph).size(); u++)
			(*maxcore_degrees)[u] = core_degree (graph, K, u, (*K)[u]);
		for (vertex u = 0; u < (*graph).size(); u++)
			(*purecore_degrees)[u] = purecore_degree_fast (graph, K, maxcore_degrees, u, (*K)[u], NULL, NULL);
	}

	for (int h = 0; h < hop; h++)
		for (vertex u = 0; u < (*graph).size(); u++)
			hop_degrees[h][u] =
					hop_core_degree (*graph, *K, u, (*K)[u], h+1);
#endif

	util::timestamp t2;
	*pout += (t2-t1);

	FILE* fp1 = fopen ("out_base.txt","w");
	for (unsigned int i = 0; i < (*graph).size(); ++i) {
		fprintf(fp1, "K[%d]:\t%d\n", print_v(i), (*K)[i]);
	}
	fclose (fp1);


	return 0;
}

