#include "main.h"

inline int getTriangleId (vertex u, vertex v, vertex w, edge* xtl, triangle_id* tlist, vertex* ordered_adj, edge* ordered_xadj) {
	edge ind = findInd (u, v, ordered_adj, ordered_xadj);
	for (vertex i = xtl[ind]; i < xtl[ind + 1]; i++)
		if (get<2>(tlist[i].triple) == w)
			return i;
	return -1;
}

void enumTriangles (edge nEdge, vertex* ordered_adj, edge* ordered_xadj, couple* el, vector<triangle_id>& tl, edge* xtl) {
	vertex ind = 0;
	xtl[ind++] = 0;
	for (size_t i = 0; i < nEdge; i++) {
		vector<vertex> is;
		intersection2 (ordered_adj, ordered_xadj, get<0>(el[i]), get<1>(el[i]), is);
		for (size_t j = 0; j < is.size(); j++) {
			triangle_id t;
			t.triple = make_tuple(get<0>(el[i]), get<1>(el[i]), is[j]);
			t.id = 0;
			tl.push_back(t);
		}
		xtl[ind++] = tl.size();
	}
	return;
}

inline vertex getComplexTriangleId (vertex a, vertex b, vertex c, edge* xtl, triangle_id* tlist, edge* xadj, vertex* adj, edge* ordered_xadj, vertex* ordered_adj) {
	vertex u, v, w;
	if (isSmaller (xadj, c, a)) {
		u = c;
		v = a;
		w = b;
	}
	else if (isSmaller (xadj, c, b)) {
		u = a;
		v = c;
		w = b;
	}
	else {
		u = a;
		v = b;
		w = c;
	}
	return getTriangleId (u, v, w, xtl, tlist, ordered_adj, ordered_xadj);
}

lol intersection3for4cliques (edge nEdge, edge* xadj, vertex* ordered_adj, edge* ordered_xadj, couple* el, edge* xtl, triangle_id* tlist) {
	lol count = 0;
#pragma omp parallel for
	for (size_t i = 0; i < nEdge; i++) { // u < v
		vertex u = get<0>(el[i]);
		vertex v = get<1>(el[i]);
		vector<vertex> is;
		intersection2 (ordered_adj, ordered_xadj, u, v, is);
		for (size_t j = 0; j < is.size(); j++) { // u < v < w
			vertex wcand = is[j];
			for (size_t k = j+1; k < is.size(); k++) { // u < v < x
				vertex xcand = is[k];
				vertex w = wcand, x = xcand;
				if (isSmaller (xadj, x, w))
					swap (w, x);
				if (findInd (w, x, ordered_adj, ordered_xadj) != -1) {
					vertex in1 = getTriangleId (u, v, w, xtl, tlist, ordered_adj, ordered_xadj);
					vertex in2 = getTriangleId (u, v, x, xtl, tlist, ordered_adj, ordered_xadj);
					vertex in3 = getTriangleId (u, w, x, xtl, tlist, ordered_adj, ordered_xadj);
					vertex in4 = getTriangleId (v, w, x, xtl, tlist, ordered_adj, ordered_xadj);
#pragma omp atomic
					(tlist[in1].id)++;

#pragma omp atomic
					(tlist[in2].id)++;

#pragma omp atomic
					(tlist[in3].id)++;

#pragma omp atomic
					(tlist[in4].id)++;

#ifndef FAST
#pragma omp atomic
					count++;
#endif
				}
			}
		}
	}
	return count;
}

inline int mapInitialHI (edge ind, vertex* adj, edge* xadj, triangle_id* tlist, edge* xtl, vertex* ordered_adj, edge* ordered_xadj, vertex* P
#ifdef SYNC
		, vertex* Q
#endif
) {

	unordered_map<vertex, vertex> gmap;
	vertex greaters = 0;
	vertex equals = 0;
	vertex H = 0;
	vertex u = get<0> (tlist[ind].triple);
	vertex v = get<1> (tlist[ind].triple);
	vertex w = get<2> (tlist[ind].triple);

	vertex ii = xadj[u];
	vertex jj = xadj[v];
	vertex kk = xadj[w];
	vertex u_size = xadj[u+1];
	vertex v_size = xadj[v+1];
	vertex w_size = xadj[w+1];

	while (ii < u_size && jj < v_size && kk < w_size) {
		vertex a = adj[ii];
		vertex b = adj[jj];
		vertex c = adj[kk];
		if (a == b && a == c) {
			vertex x = a;
			vertex id1 = getComplexTriangleId (u, v, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id2 = getComplexTriangleId (u, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id3 = getComplexTriangleId (v, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);

			vertex sm = min (min (P[id1], P[id2]), P[id3]);

			if (sm == H + 1) {
				if (equals > 0) {
					equals--;
					greaters++;
					gmap[sm]++;
				}
				else { // equals = 0
					H++;
					int gH = 0;
					auto it = gmap.find(H);
					if (it != gmap.end()) {
						gH = it->second;
						gmap.erase (H);
					}
					equals = gH + 1;
					greaters -= gH;
				}
			}
			else if (sm > H + 1) {
				if  (equals > 0) {
					equals--;
					greaters++;
					gmap[sm]++;
				}
				else { // equals = 0
					greaters++;
					H++;
					int gH = 0;
					auto it = gmap.find(H);
					if (it != gmap.end()) {
						gH = it->second;
						gmap.erase (H);
					}
					equals = gH;
					greaters -= gH;
					gmap[sm]++;
				}
			}
			ii++;
			jj++;
			kk++;
		}
		else {
			vertex m = max (max (a, b), c);
			if (a != m)
				ii++;
			if (b != m)
				jj++;
			if (c != m)
				kk++;
		}
	}

	vertex oP = P[ind];
#ifdef SYNC
	Q[ind] = H;
#else
	P[ind] = H;
#endif

	if (H < oP) {
		return 1;
	}
	else
		return 0;
}

inline int regularUpdateHI (edge ind, vertex* adj, edge* xadj, triangle_id* tlist, edge* xtl, vertex* ordered_adj, edge* ordered_xadj, vertex* P
#ifdef SYNC
			, vertex* Q
#endif
	) {

	vertex previous_P = P[ind];
	vertex greaterequals = 0;
	vector<vertex> smallers (previous_P, 0);
	bool yep_set = false;

	vertex u = get<0> (tlist[ind].triple);
	vertex v = get<1> (tlist[ind].triple);
	vertex w = get<2> (tlist[ind].triple);

	vertex ii = xadj[u];
	vertex jj = xadj[v];
	vertex kk = xadj[w];

	vertex u_size = xadj[u+1];
	vertex v_size = xadj[v+1];
	vertex w_size = xadj[w+1];

	bool has4Clique = false;
	while (ii < u_size && jj < v_size && kk < w_size) {
		vertex a = adj[ii];
		vertex b = adj[jj];
		vertex c = adj[kk];
		if (a == b && a == c) {
			has4Clique = true;
			vertex x = a;
			vertex id1 = getComplexTriangleId (u, v, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id2 = getComplexTriangleId (u, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id3 = getComplexTriangleId (v, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex cur_F = min (min (P[id1], P[id2]), P[id3]);

			if (cur_F >= previous_P)
				greaterequals++;
			else
				smallers[cur_F]++;
			if (greaterequals == previous_P) {
				yep_set = true;
				break;
			}
			ii++; jj++; kk++;
		}
		else {
			vertex m = max (max (a, b), c);
			if (a != m)
				ii++;
			if (b != m)
				jj++;
			if (c != m)
				kk++;
		}
	}

	if (!yep_set && has4Clique) {
		vertex j;
		for (j = previous_P - 1; j > 0; j--) {
			greaterequals += smallers[j];
			if (greaterequals >= j)
				break;
		}
#ifdef SYNC
		if (Q[ind] != j) {
			Q[ind] = j;
			return 1;
		}
#else
		if (P[ind] != j) {
			P[ind] = j;
			return 1;
		}
#endif
	}
	return 0;
}

inline void updateAndNotify (int ind, vertex* P, int newP, vector<vertex>& neigs, bool* changed) {
	P[ind] = newP;
	changed[ind] = true;
	for (auto w : neigs)
		if (P[w] >= P[ind])
			changed[w] = true;
}

inline int efficientUpdateHI (edge ind, vertex* adj, edge* xadj, triangle_id* tlist, edge* xtl, vertex* ordered_adj, edge* ordered_xadj, vertex* P, bool* changed) {

	vector<vertex> neigs;
	vertex previous_P = P[ind];
	vertex greaterequals = 0;
	vector<vertex> smallers (previous_P, 0);
	bool yep_set = false;

	vertex u = get<0> (tlist[ind].triple);
	vertex v = get<1> (tlist[ind].triple);
	vertex w = get<2> (tlist[ind].triple);

	vertex ii = xadj[u];
	vertex jj = xadj[v];
	vertex kk = xadj[w];

	vertex u_size = xadj[u+1];
	vertex v_size = xadj[v+1];
	vertex w_size = xadj[w+1];

	bool has4Clique = false;
	while (ii < u_size && jj < v_size && kk < w_size) {
		vertex a = adj[ii];
		vertex b = adj[jj];
		vertex c = adj[kk];
		if (a == b && a == c) {
			has4Clique = true;
			vertex x = a;
			vertex id1 = getComplexTriangleId (u, v, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id2 = getComplexTriangleId (u, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id3 = getComplexTriangleId (v, w, x, xtl, tlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex cur_F = min (min (P[id1], P[id2]), P[id3]);

			if (P[id1] <= previous_P)
				neigs.push_back (id1);
			if (P[id2] <= previous_P)
				neigs.push_back (id2);
			if (P[id3] <= previous_P)
				neigs.push_back (id3);

			if (cur_F >= previous_P)
				greaterequals++;
			else
				smallers[cur_F]++;
			if (greaterequals == previous_P) {
				yep_set = true;
				break;
			}
			ii++; jj++; kk++;
		}
		else {
			vertex m = max (max (a, b), c);
			if (a != m)
				ii++;
			if (b != m)
				jj++;
			if (c != m)
				kk++;
		}
	}


	if (!yep_set && has4Clique) {
		vertex j;
		for (j = previous_P - 1; j > 0; j--) {
			greaterequals += smallers[j];
			if (greaterequals >= j) {
				break;
			}
		}
		updateAndNotify (ind, P, j, neigs, changed);
		return 1;
	}
	return 0;
}



// base AND and SND algorithms, no notification mechanism. compile with SYNC=yes to get the synchronous mode (SND)
void baseLocal34 (vertex nVtx, edge nEdge, vertex* adj, edge* xadj, vertex* P, const char* vfile) {

	const auto t_begin = chrono::steady_clock::now();

	// Ordered (directed) graph creation
	couple* el = (couple *) malloc (sizeof(couple) * nEdge);
	edge* xel = (edge *) malloc (sizeof(edge) * (nVtx+1));
	vertex* ordered_adj = (vertex *) malloc (sizeof(vertex) * nEdge );
	edge* ordered_xadj = (edge *) malloc (sizeof(edge) * (nVtx+1));;

	createOrdered (nVtx, nEdge, adj, xadj, el, xel, ordered_adj, ordered_xadj);

	const auto t_cog = chrono::steady_clock::now();
	tms t1 = t_cog - t_begin;
	printf ("Creating ordered graph: %.6lf secs\n", t1.count());

	// Enumerating triangles
	edge* xtl = (edge *) malloc (sizeof(edge) * (nEdge + 1));
	vector<triangle_id> tlist;
	enumTriangles (nEdge, ordered_adj, ordered_xadj, el, tlist, xtl);

	const auto t_tri = chrono::steady_clock::now();
	tms t2 = t_tri - t_cog;
	printf ("Enumerating triangles time: %.6lf secs\n", t2.count());
	cout << "# triangles: " << tlist.size() << endl;

	// 4-clique counting
	P = (vertex *) malloc (sizeof(vertex) * tlist.size());

#ifdef SYNC
	printf ("It is SYNC\n");
	vertex* Q = (vertex *) malloc (sizeof(vertex) * tlist.size());
#else
	printf ("It is ASYNC\n");
#endif

	triangle_id* Ntlist = (triangle_id *) malloc (sizeof (triangle_id) * tlist.size());
	for (edge i = 0; i < tlist.size(); i++) {
		Ntlist[i].id = tlist[i].id;
		Ntlist[i].triple = tlist[i].triple;
	}

	lol fccount = intersection3for4cliques (nEdge, xadj, ordered_adj, ordered_xadj, el, xtl, Ntlist);
#ifndef FAST
	cout << "# 4-cliques: " << fccount << endl;
#endif
	exit (1);
#pragma omp parallel for
	for (edge i = 0; i < tlist.size(); i++)
		P[i] = Ntlist[i].id;

	const auto t_fc = chrono::steady_clock::now();
	tms t3 = t_fc - t_tri;
	printf ("4-clique counting: %.6lf secs\n", t3.count());

	int oc = 0;
	bool flag = true;
	edge sz = tlist.size();

#pragma omp parallel for schedule (dynamic, 1000)
	for (edge ind = 0; ind < sz; ind++) {
		mapInitialHI (ind, adj, xadj, Ntlist, xtl, ordered_adj, ordered_xadj, P
#ifdef SYNC
				, Q
#endif
		);
	}

#ifdef SYNC
	memcpy (P, Q, sizeof(vertex) * sz);
#endif

	const auto t_init = chrono::steady_clock::now();
	tms t4 = t_init - t_fc;
	printf ("H %d time: %.6lf secs\n", oc, t4.count());
	tms td  = chrono::duration<double>::zero();
#ifdef DUMP_Hs
	const auto ts1 = chrono::steady_clock::now();
	print_Ks (sz, P, vfile, oc);
	const auto ts2 = chrono::steady_clock::now();
	td += ts2 - ts1;
#endif
	oc++;

	while (flag) {
		const auto td1 = chrono::steady_clock::now();
		flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
		for (edge ind = 0; ind < sz; ind++) {
			int fl = regularUpdateHI (ind, adj, xadj, Ntlist, xtl, ordered_adj, ordered_xadj, P
#ifdef SYNC
				, Q
#endif
			);
			if (fl == 1)
				flag = true;
		}
		const auto td2 = chrono::steady_clock::now();

#ifdef SYNC
		memcpy (P, Q, sizeof(vertex) * sz);
#endif

#ifdef DUMP_Hs
		const auto ts1 = chrono::steady_clock::now();
		print_Ks (sz, P, vfile, oc);
		const auto ts2 = chrono::steady_clock::now();
		td += ts2 - ts1;
#endif

		tms step = td2 - td1;
		printf ("H %d time: %.6lf secs\n", oc, step.count());
		oc++;
	}

#ifdef DUMP_K
	const auto ts3 = chrono::steady_clock::now();
	print_Ks (sz, P, vfile);
	const auto ts4 = chrono::steady_clock::now();
	td += ts4 - ts3;
#endif

	free (P);
	free (xel);
	free (el);
	free (Ntlist);
	free (xtl);
	free (ordered_adj);
	free (ordered_xadj);
#ifdef SYNC
	free (Q);
#endif

	printf ("Converges at %d\n", oc);
	const auto t_end = chrono::steady_clock::now();
	tms total = t_end - t_begin - td;
	printf ("Total time: %.6lf secs\n", total.count());
	return;
}

// AND algorithm with the notification mechanism
void nmLocal34 (vertex nVtx, edge nEdge, vertex* adj, edge* xadj, vertex* P, const char* vfile) {
#ifdef SYNC
	printf ("No SYNC for notification-mechanism\n");
	exit(1);
#else
	const auto t_begin = chrono::steady_clock::now();

	// Ordered (directed) graph creation
	couple* el = (couple *) malloc (sizeof(couple) * nEdge);
	edge* xel = (edge *) malloc (sizeof(edge) * (nVtx+1));
	vertex* ordered_adj = (vertex *) malloc (sizeof(vertex) * nEdge );
	edge* ordered_xadj = (edge *) malloc (sizeof(edge) * (nVtx+1));;

	createOrdered (nVtx, nEdge, adj, xadj, el, xel, ordered_adj, ordered_xadj);

	const auto t_cog = chrono::steady_clock::now();
	tms t1 = t_cog - t_begin;
	printf ("Creating ordered graph: %.6lf secs\n", t1.count());

	// Enumerating triangles
	edge* xtl = (edge *) malloc (sizeof(edge) * (nEdge + 1));
	vector<triangle_id> tlist;
	enumTriangles (nEdge, ordered_adj, ordered_xadj, el, tlist, xtl);

	const auto t_tri = chrono::steady_clock::now();
	tms t2 = t_tri - t_cog;
	printf ("Enumerating triangles time: %.6lf secs\n", t2.count());
	cout << "# triangles: " << tlist.size() << endl;

	// 4-clique counting
	P = (vertex *) malloc (sizeof(vertex) * tlist.size());

	triangle_id* Ntlist = (triangle_id *) malloc (sizeof (triangle_id) * tlist.size());
	for (edge i = 0; i < tlist.size(); i++) {
		Ntlist[i].id = tlist[i].id;
		Ntlist[i].triple = tlist[i].triple;
	}

	lol fccount = intersection3for4cliques (nEdge, xadj, ordered_adj, ordered_xadj, el, xtl, Ntlist);
#pragma omp parallel for
	for (edge i = 0; i < tlist.size(); i++)
		P[i] = Ntlist[i].id;

	const auto t_fc = chrono::steady_clock::now();
	tms t3 = t_fc - t_tri;
	printf ("4-clique counting: %.6lf secs\n", t3.count());
#ifndef FAST
	cout << "# 4-cliques: " << fccount << endl;
#endif

	int oc = 0;
	bool flag = true;
	edge sz = tlist.size();

#pragma omp parallel for schedule (dynamic, 1000)
	for (edge ind = 0; ind < sz; ind++) {
		mapInitialHI (ind, adj, xadj, Ntlist, xtl, ordered_adj, ordered_xadj, P);
	}

	bool changed[sz];
	memset (changed, 255, sizeof(bool) * sz); // set all true

	const auto t_init = chrono::steady_clock::now();
	tms t4 = t_init - t_fc;
	printf ("H %d time: %.6lf secs\n", oc, t4.count());
	tms td  = chrono::duration<double>::zero();
#ifdef DUMP_Hs
	const auto ts1 = chrono::steady_clock::now();
	print_Ks (sz, P, vfile, oc);
	const auto ts2 = chrono::steady_clock::now();
	td += ts2 - ts1;
#endif
	oc++;

	while (flag) {
		const auto td1 = chrono::steady_clock::now();
		flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
		for (edge ind = 0; ind < sz; ind++) {
			if (!changed[ind])
				continue;
			changed[ind] = false;
			int a = efficientUpdateHI (ind, adj, xadj, Ntlist, xtl, ordered_adj, ordered_xadj, P, changed);
			if (a == 1)
				flag = true;
		}
		const auto td2 = chrono::steady_clock::now();

#ifdef DUMP_Hs
		const auto ts1 = chrono::steady_clock::now();
		print_Ks (sz, P, vfile, oc);
		const auto ts2 = chrono::steady_clock::now();
		td += ts2 - ts1;
#endif

		tms step = td2 - td1;
		printf ("H %d time: %.6lf secs\n", oc, step.count());
		oc++;
	}

#ifdef DUMP_K
	const auto ts3 = chrono::steady_clock::now();
	print_Ks (sz, P, vfile);
	const auto ts4 = chrono::steady_clock::now();
	td += ts4 - ts3;
#endif


	free (P);
	free (xel);
	free (el);
	free (Ntlist);
	free (xtl);
	free (ordered_adj);
	free (ordered_xadj);

	printf ("Converges at %d\n", oc);
	const auto t_end = chrono::steady_clock::now();
	tms total = t_end - t_begin - td;
	printf ("Total time: %.6lf secs\n", total.count());
	return;
#endif
}

// Partly parallel 3,4 computation (only 4clique counting is parallel)
void k34 (vertex nVtx, edge nEdge, vertex* adj, edge* xadj, vertex* F, const char* vfile) {

	const auto t_begin = chrono::steady_clock::now();

	// Ordered (directed) graph creation
	couple* el = (couple *) malloc (sizeof(couple) * nEdge);
	edge* xel = (edge *) malloc (sizeof(edge) * (nVtx+1));
	vertex* ordered_adj = (vertex *) malloc (sizeof(vertex) * nEdge );
	edge* ordered_xadj = (edge *) malloc (sizeof(edge) * (nVtx+1));;

	createOrdered (nVtx, nEdge, adj, xadj, el, xel, ordered_adj, ordered_xadj);

	const auto t_cog = chrono::steady_clock::now();
	tms t1 = t_cog - t_begin;
	printf ("Creating ordered graph: %.6lf secs\n", t1.count());

	// Enumerating triangles
	edge* xtl = (edge *) malloc (sizeof(edge) * (nEdge + 1));
	vector<triangle_id> tlist;
	enumTriangles (nEdge, ordered_adj, ordered_xadj, el, tlist, xtl);

	const auto t_tri = chrono::steady_clock::now();
	tms t2 = t_tri - t_cog;
	printf ("Enumerating triangles time: %.6lf secs\n", t2.count());

	// 4-clique counting
	F = (vertex *) malloc (sizeof(vertex) * tlist.size());
	memset (F, -1, sizeof(vertex) * tlist.size());

	cout << "# triangles: " << tlist.size() << endl;
	triangle_id* Ntlist = (triangle_id *) malloc (sizeof (triangle_id) * tlist.size());
	for (edge i = 0; i < tlist.size(); i++) {
		Ntlist[i].id = tlist[i].id;
		Ntlist[i].triple = tlist[i].triple;
	}

	lol fccount = intersection3for4cliques (nEdge, xadj, ordered_adj, ordered_xadj, el, xtl, Ntlist);

	const auto t_fc = chrono::steady_clock::now();
	tms t3 = t_fc - t_tri;
	printf ("4-clique counting: %.6lf secs\n", t3.count());
#ifndef FAST
	cout << "# 4-cliques: " << fccount << endl;
#endif

	// Peeling
	Naive_Bucket na_bs;
	edge cid = 0;
	na_bs.Initialize (tlist.size(), tlist.size());
	for (size_t i = 0; i < tlist.size(); i++) {
		if (Ntlist[i].id > 0) // this is 4c count
			na_bs.Insert (cid, Ntlist[i].id);
		cid++;
	}
	vertex fc_of_uvw = 0;
	int order = 0;

	while (1) {
		edge uvw, value_of_uvw ;
		edge ret = na_bs.PopMin(&uvw, &value_of_uvw);
		if (ret == -1)
			break;

		if (value_of_uvw == 0)
			continue;

		fc_of_uvw = F[uvw] = value_of_uvw;
		vertex u = get<0> (tlist[uvw].triple);
		vertex v = get<1> (tlist[uvw].triple);
		vertex w = get<2> (tlist[uvw].triple);

		vector<vertex> intersection;
		intersection3 (adj, xadj, u, v, w, intersection);
		for (auto x: intersection) {
			vertex id1 = getComplexTriangleId (u, v, x, xtl, Ntlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id2 = getComplexTriangleId (u, w, x, xtl, Ntlist, xadj, adj, ordered_xadj, ordered_adj);
			vertex id3 = getComplexTriangleId (v, w, x, xtl, Ntlist, xadj, adj, ordered_xadj, ordered_adj);

			if (F[id1] == -1 && F[id2] == -1 && F[id3] == -1) {
				int cur_id1 = na_bs.CurrentValue(id1);
				int cur_id2 = na_bs.CurrentValue(id2);
				int cur_id3 = na_bs.CurrentValue(id3);

				if (na_bs.CurrentValue(id1) > fc_of_uvw)
					na_bs.DecVal(id1);
				if (na_bs.CurrentValue(id2) > fc_of_uvw)
					na_bs.DecVal(id2);
				if (na_bs.CurrentValue(id3) > fc_of_uvw)
					na_bs.DecVal(id3);
			}
		}
	}

	na_bs.Free();
	for (size_t i = 0; i < tlist.size(); i++)
		if (F[i] == -1)
			F[i] = 0;

	tms td  = chrono::duration<double>::zero();
#ifdef DUMP_K
	const auto ts3 = chrono::steady_clock::now();
	print_Ks (tlist.size(), F, vfile);
	const auto ts4 = chrono::steady_clock::now();
	td += ts4 - ts3;
#endif

	free (F);
	free (xel);
	free (el);
	free (Ntlist);
	free (xtl);
	free (ordered_adj);
	free (ordered_xadj);

	cout << "Max 34 number: " << fc_of_uvw << endl;
	const auto t_end = chrono::steady_clock::now();
	tms total = t_end - t_begin;
	printf ("Total time: %.6lf secs\n", total.count());
	return;
}
