#include "main-kcore.hpp"

//#define WHICH_EDGES_WILL_CHANGE // prints the generated edges

void randomly_generate_edges (Graph* graph, int count, edge* edge_list, string cfile) {

	char inp[50];
	strcpy (inp, cfile.c_str());
	FILE* fp = fopen(inp, "w");

	int num_of_edges = count;
	int nVtx = (*graph).size();

	while (num_of_edges > 0) {

		bool correct_edge = false;

		while (1) {
			correct_edge = true;
			vertex u = (nVtx) * (rand() / (double)RAND_MAX);
			vertex v;
			if ((*graph)[u].size() > 0) {
				v = (*graph)[u][0];
				vertex u_t, v_t;
				u_t = u;
				v_t = v;
				if (u > v) {
					u_t = v;
					v_t = u;
				}
				for (int i = 0; i < (count - num_of_edges); i++) {
					if ((edge_list[i].u == u_t) && (edge_list[i].v == v_t)) {
						correct_edge = false;
						break;
					}
				}
			}
			else
				correct_edge = false;

			if (correct_edge) {
				edge e;
				e.u = u;
				e.v = v;
				if (u > v) {
					e.u = v;
					e.v = u;
				}
#ifdef EDGE_INFO
				cout << "EDGE TO BE REMOVED / INSERTED IS: " << e.u << "-" << e.v << endl;
#endif
				edge_list[count-num_of_edges] = e;
				num_of_edges--;
				break;
			}
		}
	}

	for (int i = 0; i < count; i++)
		fprintf(fp, "%d\t%d\n", edge_list[i].u, edge_list[i].v);

	fclose(fp);
	return;
}

void take_from_file (Graph* graph, int count, edge* edge_list, string cfile) {

	int num_of_edges = count;
	int nVtx = (*graph).size();
	vertex u, v;
	char inp[50];
	strcpy (inp, cfile.c_str());
	FILE* fp = fopen(inp, "r");

	while (1) {
		if (fscanf (fp, "%d %d", &u, &v) == EOF)
			break;
		edge e;
		e.u = u;
		e.v = v;
		if (u > v) {
			e.u = v;
			e.v = u;
		}
		edge_list[count - num_of_edges] = e;
		num_of_edges--;
	}

	fclose (fp);
	return;
}
