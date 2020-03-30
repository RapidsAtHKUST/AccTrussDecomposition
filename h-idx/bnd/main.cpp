#include "main.h"
#include "util/timer.h"
#include "util/log/log.h"

int main(int argc, char *argv[]) {

	const auto t1 = chrono::steady_clock::now();
#ifdef EXPS
	if (argc < 4) {
		if (argc == 3) {
			string s (argv[2]);
			if (s == "BUILD_LEFT" || s == "BUILD_RIGHT")
				printf ("Building projection\n");
		}
		else {
			fprintf (stderr, "usage: %s "
					"\n <filename>"
					"\n <nucleus type: RUN_CORE, RUN_WEIGHTED_CORE, RUN_TRUSS>"
					"\n <hierarchy?: YES or NO>\n", argv[0]);
			exit(1);
		}
	}
#else
	if (argc < 4) {

		fprintf (stderr, "usage: %s "
				"\n <filename>"
				"\n <nucleus type: LEFT_TIP, RIGHT_TIP, WING>"
				"\n <hierarchy?: YES or NO>\n", argv[0]);
		exit(1);
	}
#endif

	char *filename = argv[1];
	string tmp (argv[1]);
	string gname = tmp.substr (tmp.find_last_of("/") + 1);

	string nd (argv[2]);  // RIGHT_TIP, LEFT_TIP, WING 910 for rightVertex based, 911 for leftVertex based, 92 for edge
	if (!(nd == "RIGHT_TIP" || nd == "LEFT_TIP" || nd == "WING" || nd == "BUILD_LEFT" || nd == "BUILD_RIGHT" ||
			nd == "RUN_CORE" || nd == "RUN_WEIGHTED_CORE" || nd == "RUN_TRUSS" || nd == "MEASURE_LEFT" || nd == "MEASURE_RIGHT" )) {
		printf ("Invalid algorithm, options are RIGHT_TIP, LEFT_TIP and WING for bipartite graphs\n");
		printf ("Or, RUN_WEIGHTED_CORE and RUN_(CORE|TRUSS) for the projections\n");
		exit(1);
	}

	// read the graph, give sorted edges in left and rightGraph
	edge nEdge = 0;
	Graph leftGraph, rightGraph;
	string hrc;
#ifdef EXPS
	Graph gr;
	Wraph wg;
	if (nd == "RUN_CORE" || nd == "RUN_TRUSS" || nd == "RUN_WEIGHTED_CORE") {
		hrc = argv[3];
		readWeightedBinary (filename, wg, &nEdge);
		printf ("Projection:  nVtx: %d   nEdge: %d\n", wg.size(), nEdge);
		if (nd == "RUN_CORE" || nd == "RUN_TRUSS") {
			gr.resize (wg.size());
			for (int i = 0; i < wg.size(); i++) {
				gr[i].resize (wg[i].size());
				for (int j = 0; j < wg[i].size(); j++) {
					gr[i][j] = wg[i][j].n;
				}
			}
		}
	}
#endif
	if (nd == "RIGHT_TIP" || nd == "LEFT_TIP" || nd == "WING" || nd.find("BUILD") != string::npos ||  nd.find("MEASURE") != string::npos) {
		if (nd == "RIGHT_TIP" || nd == "LEFT_TIP" || nd == "WING")
			hrc = argv[3];
		readBipartite<vertex, vertex> (filename, &nEdge, leftGraph, rightGraph);
	}


	string vfile = gname + "_" + nd;
	string out_file;

	bool hierarchy = (hrc == "YES" ? true : false);
	if (hierarchy)
		out_file = vfile + "_Hierarchy";
	else
		out_file = vfile + "_K";

	FILE* fp;
	if (nd.find ("BUILD") == string::npos)
		fp = fopen (out_file.c_str(), "w");

	lol bCount = 0; // number of butterflies
	lol maxK; // maximum K value in the graph
	vector<vertex> K; // K values of vertices (or edges)

	Timer timer;
	if (nd == "RIGHT_TIP")
		tipDecomposition (leftGraph, rightGraph, nEdge, K, hierarchy, &maxK, vfile, fp, &bCount); // Right vertices are primary
	else if (nd == "LEFT_TIP")
		tipDecomposition (rightGraph, leftGraph, nEdge, K, hierarchy, &maxK, vfile, fp, &bCount); // Left vertices are primary
	else if (nd == "WING") {
		if (leftGraph.size() < rightGraph.size()) { // select the smaller set for faster computation
			fprintf (fp, "LEFT is chosen as the PRIMARY set\n");
			printf ("RIGHT pair, LEFT pair\n");
			if (hierarchy)
				wingDecompositionHrc (rightGraph, leftGraph, nEdge, K, hierarchy, &maxK, vfile, fp, &bCount);
			else
				wingDecomposition (rightGraph, leftGraph, nEdge, K, hierarchy, &maxK, fp, &bCount);
		}
		else {
			fprintf (fp, "RIGHT is chosen as the PRIMARY set\n");
			printf ("LEFT pair, RIGHT pair\n");
			if (hierarchy)
				wingDecompositionHrc (leftGraph, rightGraph, nEdge, K, hierarchy, &maxK, vfile, fp, &bCount);
			else
				wingDecomposition (leftGraph, rightGraph, nEdge, K, hierarchy, &maxK, fp, &bCount);
		}
	}
	log_info("Elapsed Time: %.6lf s", timer.elapsed());


#ifdef EXPS
	else if (nd == "BUILD_LEFT") {
		weighted_projection (leftGraph, rightGraph, vfile); // construct weighted projected graph from LEFT
		return 0;
	}
	else if (nd == "BUILD_RIGHT") {
		weighted_projection (rightGraph, leftGraph, vfile); // construct weighted projected graph from RIGHT
		return 0;
	}
	else if (nd == "RUN_CORE")
		base_kcore (gr, hierarchy, nEdge, K, &maxK, vfile, fp); // run k-core on the given projection graph
	else if (nd == "RUN_TRUSS")
		base_ktruss (gr, hierarchy, nEdge, K, &maxK, vfile, fp); // run k-truss on the given projection graph
	else if (nd == "RUN_WEIGHTED_CORE")
		weighted_base_kcore (wg, hierarchy, nEdge, K, &maxK, vfile, fp); // run fractional core on the given weighted projection graph
	else if (nd == "MEASURE_RIGHT") {
		string density_file (argv[3]);
		ff_vertex_ind_density (density_file, rightGraph); // database_conf
	}
	else if (nd == "MEASURE_LEFT") {
		string density_file (argv[3]);
		ff_vertex_ind_density (density_file, leftGraph); // condmat
	}
#endif

#ifdef DUMP_K
	string kfile = vfile + "_K_values";
	FILE* kf = fopen (kfile.c_str(), "w");
	for (vertex i = 0; i < K.size(); i++)
		fprintf (kf, "K[%d]: %lld\n", i, K[i]);
	fclose (kf);
#endif

	const auto t2 = chrono::steady_clock::now();
	if (nd == "LEFT_TIP" || nd == "RIGHT_TIP" || nd == "WING")
		printf ("%s\t|L|: %d\t|R|: %d\t|E|: %d\tmaxK: %d nButterflies: %ld\n", gname.c_str(), leftGraph.size(), rightGraph.size(), nEdge, maxK, bCount);

	print_time (fp, "End-to-end Time: ", t2 - t1);
	fclose (fp);


	return 0;
}

