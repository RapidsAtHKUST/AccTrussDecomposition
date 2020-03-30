#include "main-kcore.hpp"

//<filename>_IS has hop+1 ints at each line and nVtx lines in total. First line
//is K value, and rest is MCD, PCD, 3CD ... values.
void load_state (char* filename, v_container& K, int hop
#ifdef MAINTAIN_CD
		, vector<vector<vertex> >& hop_degrees
#endif
	) {

#ifdef MAINTAIN_CD
	string tmp (filename);
	int idx = tmp.find_last_of("/");
	string initial_state = tmp.substr(idx+1) + "_IS";

	FILE* fp = fopen (initial_state.c_str(), "r");

	int k;
	char c;
	int i;
	for (i = 0; 1; i++) {
		if (fscanf (fp, "%d", &k) == EOF)
			break;
		K[i] = k;
		for (int j = 0; j < hop; j++) {
			fscanf (fp, "%d", &(hop_degrees[j][i]));
		}
		do {
			fscanf (fp, "%c", &c);
		}
		while (c != '\n');

	}
	fclose (fp);
#endif

}

void fast_base_kcore (char* filename, Graph* graph, v_container* K,
#ifdef MAINTAIN_CD
		vector<vector<vertex> >& hop_degrees,
#endif
		int hop) {

#ifdef MAINTAIN_CD
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

	for (int h = 0; h < hop; h++)
		for (vertex u = 0; u < (*graph).size(); u++)
			hop_degrees[h][u] = hop_core_degree_CD (hop_degrees, *graph, *K, u, (*K)[u], h+1);

	string tmp (filename);
	int idx = tmp.find_last_of("/");
	string initial_state = tmp.substr(idx+1) + "_IS";

	FILE* fp = fopen (initial_state.c_str(), "w");

	for (int i = 0; i < nVtx; i++) {
		fprintf (fp, "%d ", (*K)[i]);
		for (int j = 0; j < hop; j++)
			fprintf (fp, "%d ", hop_degrees[j][i]);
		fprintf (fp, "\n");
	}
	fclose (fp);

#endif
}

int main(int argc, char *argv[]) {

	vertex nVtx, nEdge, *xadj, *adj;
	char *filename = argv[1];

	if (argc < 2) {// todo
		fprintf(stderr, "usage: %s \n <filename> \n <mode= 1 : one-by-one, 2 : batch, 3 : pull-based> \n <algorithm (for one-by-one only)= 11 : ncore, 22 : ntraversal, 33 : real traversal> \n <hop> \n <insert count> \n <remove count> \n "
				"<edge generator= 0 : random(creates files), 1 : subcore decomposition, 2 : purecore decomposition, 3 : from file \n", argv[0]);
		exit(1);
	}
	srand (time(NULL));
	ReadGraph<int,int, int>(argv[1], &nVtx, &xadj, &adj, NULL, NULL);

	string tmp (argv[1]);
	int idx = tmp.find_last_of("/");
	string asdf = tmp.substr(idx+1);
	string cfile = asdf + "_edges";
	Graph graph, messi, graph_st;
	graph.resize(nVtx);
	graph_st.resize(nVtx);
	messi.resize(nVtx);
	for (vertex i = 0; i < nVtx; ++i) {
		for (vertex j = xadj[i]; j < xadj[i+1]; j++) {
			graph[i].push_back(adj[j]);
			messi[i].push_back(adj[j]);
			graph_st[i].push_back(adj[j]);
		}
	}

#ifdef GRAPH_CHECK // checks if graph is correct
	if (1) {
		int zero_vs = 0;
		for (int i = 0; i < graph.size(); i++) {
			if (graph[i].size() == 0)
				zero_vs++;

			// loop check
			for (int j = 0; j < graph[i].size(); j++) {
				if (graph[i][j] == i) {
					printf("self loop at %d!!\n",print_v(i));
				}
			}

			// duplicate check
			for (int j = 0; j < graph[i].size(); j++) {
				for (int k = j + 1; k < graph[i].size(); k++) {
					if (graph[i][j] == graph[i][k]) {
						printf("duplicate edges at %d!!\n", print_v(i));
					}
				}
			}

			//correspondence check
			for (int j = 0; j < graph[i].size(); j++) {
				int v = graph[i][j];
				bool flag = false;
				for (int k = 0; k < graph[v].size(); k++) {
					if (graph[v][k] == i) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					printf("no correspondence for %d and %d\n", print_v(i), print_v(v));
				}
			}
		}

		printf("%d number of 0-deg vertices\n", zero_vs);
		printf("no problem sir no problem :( \n");
		exit(1);
	}
#endif

	nEdge = xadj[nVtx];
	int core_number; // 'core number' of whole graph
	v_container K(nVtx, 0);

	if (strrchr(argv[1], '/'))
		filename = strrchr(argv[1], '/') + 1;

	util::timestamp totaltime(0,0);
	util::timestamp bfsordertime(0,0);

	std::string algo_out;

	util::timestamp totaltime_static(0,0);
	char timestr_static[20];

	util::timestamp totaltime_stream(0,0);
	char timestr_stream[20];

	int game_mode = atoi(argv[2]); // LOAD_FOR_MHOP, SAVE_FOR_MHOP, SINGLE_HOP
	int algorithm = atoi(argv[3]); // 11 for ncore, 22 for ntraversal
	int hop = atoi(argv[4]); // starts from 2 (PCD) for ntraversal OR starts from 1 (MCD) from ncore.
	int count = atoi(argv[5]);
	int generation_type = atoi(argv[6]);


#ifdef MAINTAIN_CD
	v_container maxcore_degrees(nVtx, -1);
	v_container purecore_degrees(nVtx, -1);
	vector<vector<vertex> > hop_degrees;
	hop_degrees.resize(hop);
	for (int i = 0; i < hop; i++) {
		hop_degrees[i].resize(nVtx, -1);
	}
#endif

	int desired_K_value;

	edge* edge_list = (edge *) malloc (sizeof(edge) * count * 2);


	incremental_debug* change_info = (incremental_debug*) malloc(sizeof(incremental_debug) * (2 + 2 * count));
	incremental_debug* change_info_ins = (incremental_debug*) malloc(sizeof(incremental_debug) * (2 + 2 * count));
	incremental_debug* change_info_rem = (incremental_debug*) malloc(sizeof(incremental_debug) * (2 + 2 * count));

	switch (generation_type) {
	case FROM_FILE:
		take_from_file (&messi, count, edge_list, cfile);
		break;
	case RANDOM_GENERATION :
		randomly_generate_edges (&messi, count, edge_list, cfile);
		break;
	default:
		cout<<"unidentified input object..."<<endl;
		break;
	}


	if (game_mode == LOAD) {
		// load the state of K and hop_degrees from file
		load_state (argv[1], K, hop
#ifdef MAINTAIN_CD
				, hop_degrees
#endif
				);
	}
	else if (game_mode == SAVE) {
		// compute K and hop_degrees and dump to a file
		fast_base_kcore (argv[1], &graph_st, &K,
#ifdef MAINTAIN_CD
				hop_degrees,
#endif
				hop);
	}
	else if (game_mode == JUST_RUN) {
		/* streaming algorithm */
		base_kcore (&graph_st, &K,
#ifdef MAINTAIN_CD
				&maxcore_degrees,
				&purecore_degrees,
				hop_degrees,
#endif
				hop, totaltime, &core_number);
	}

	if (game_mode == LOAD || game_mode == JUST_RUN) {
		onebyone_kcore (&graph_st, &K,
#ifdef MAINTAIN_CD
				&maxcore_degrees,
				&purecore_degrees,
				hop_degrees,
#endif
				totaltime_stream, &core_number, count, edge_list, change_info, hop, algorithm);

		FILE* fp1 = fopen ("out_stream.txt","w");
		for (unsigned int i = 0; i < graph_st.size(); ++i) {
			fprintf(fp1, "K[%d]:\t%d\n", print_v(i), K[i]);
		}
		fclose (fp1);
		K.clear();
	}


#ifdef MAINTAIN_CD
	maxcore_degrees.clear();
	purecore_degrees.clear();
	hop_degrees.clear();
#endif
	/* ------------------------------------------------------------ */

#ifdef VERIFY_K // apply changes, runs traditional kcore, dumps to out_base.txt. Can be compared to out_stream.txt to verify K values
	if (game_mode == JUST_RUN || game_mode == LOAD) {
		/* graph is firstly prepared for benchmarking base algorithm, by applying insertions and removals */
		K.resize(nVtx);
#ifdef MAINTAIN_CD
		maxcore_degrees.resize(nVtx, -1);
		purecore_degrees.resize(nVtx, -1);

		hop_degrees.resize(hop);
		for (int i = 0; i < hop; i++) {
			hop_degrees[i].resize(nVtx, -1);
			}

#endif

		for (int i = 0; i < count; i++) { // edge insertion in sorted manner
			unsigned int u = edge_list[i].u;
			unsigned int v = edge_list[i].v;

			if (u < graph.size()) {
				if ((graph[u].size() == 0) ||  graph[u][0] > v)
					graph[u].insert(graph[u].begin(), v);
				else if (graph[u][graph[u].size() - 1] < v)
					graph[u].insert(graph[u].end(), v);
				else {
					for (unsigned int i = 0; i < graph[u].size(); i++) {
						if (graph[u][i] > v) {
							graph[u].insert(graph[u].begin() + i, v);
							break;
						}
					}
				}
			}
			else {
				v_container new_vertex;
				new_vertex.push_back(v);
				graph.push_back(new_vertex);
				new_vertex.clear();
			}

			if (v < graph.size()) {
				if ((graph[v].size() == 0) || graph[v][0] > u)
					graph[v].insert(graph[v].begin(), u);
				else if (graph[v][graph[v].size() - 1] < u)
					graph[v].insert(graph[v].end(), u);
				else {
					for (unsigned int i = 0; i < graph[v].size(); i++) {
						if (graph[v][i] > u) {
							graph[v].insert(graph[v].begin() + i, u);
							break;
						}
					}
				}
			}
			else {
				v_container new_vertex;
				new_vertex.push_back(u);
				graph.push_back(new_vertex);
				new_vertex.clear();
			}
		}

		for (int i = 0; i < count; i++) { // edge removal
			int u = edge_list_to_remove[i].u;
			int v = edge_list_to_remove[i].v;

			for (unsigned int i = 0; i < graph[u].size(); i++) {
				if (graph[u][i] == v) {
					graph[u].erase(graph[u].begin() + i);
					break;
				}
			}

			for (unsigned int i = 0; i < graph[v].size(); i++) {
				if (graph[v][i] == u) {
					graph[v].erase(graph[v].begin() + i);
					break;
				}
			}
		}

		/* base algorithm */

		base_kcore (&graph, &K,
#ifdef MAINTAIN_CD
				&maxcore_degrees,
				&purecore_degrees,
				hop_degrees,
#endif
				hop, totaltime_static, &core_number); // basic mindegree removal

		FILE* fp2 = fopen("out_base.txt","w");
		for (unsigned int i = 0; i < graph.size(); ++i) {
			fprintf(fp2, "K[%d]:\t%d\n", print_v(i), K[i]);
		}
		fclose(fp2);

		/* ---------------------------------------------------------- */
	}
#endif

	totaltime_static.to_c_str(timestr_static, 20);
	totaltime_stream.to_c_str(timestr_stream, 20);
	std::cout.precision(15);
	std::cout<<"filename:"<<filename
			<<" nVtx:"<<nVtx
			<<" nEdge:"<<nEdge/2
			<<" Core number:"<<core_number<<endl;

	free (edge_list);
	free (change_info);
	free (change_info_ins);
	free (change_info_rem);

#ifdef K_HISTOGRAM
	double* K_histogram = (double*) calloc (sizeof(double), (core_number + 1));
	int numv = 0;
	for (vertex i = 0; i < nVtx; ++i) {
		if (K[i] > 0) {
			K_histogram[K[i]]++;
			numv++;
		}
	}

	for (int i = 1; i < (core_number + 1); ++i) {
		cout<<"K_of["<<i<<"]:\t\t"<<K_histogram[i]<<endl;
	}
	free (K_histogram);
#endif

#ifdef K_VALUES
	for (vertex i = 0; i < nVtx; ++i) {
		cout<<"K["<<print_v(i)<<"]:\t"<<K[i]<<endl;
	}
#endif


	graph.clear();
	messi.clear();
	graph_st.clear();
	K.clear();
#ifdef MAINTAIN_CD
	maxcore_degrees.clear();
	purecore_degrees.clear();
	for (int i = 0; i < hop; i++) {
		hop_degrees[i].clear();
	}
	hop_degrees.clear();


#endif
	free(adj);
	free(xadj);
	tmp.clear();
	asdf.clear();

	return 0;
}
