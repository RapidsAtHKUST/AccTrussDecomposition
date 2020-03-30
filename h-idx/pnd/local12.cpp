#include "main.h"

// this is faster than sort-based computation
inline int mapInitialHI(vertex ind, vertex *adj, edge *xadj, vertex *P
#ifdef SYNC
        , vertex* Q
#endif
) {

    unordered_map<vertex, vertex> gmap;
    vertex greaters = 0;
    vertex equals = 0;
    vertex H = 0;

    for (vertex j = xadj[ind]; j < xadj[ind + 1]; j++) {
        vertex w = adj[j];
        vertex sm = P[w];
        if (sm == H + 1) {
            if (equals > 0) {
                equals--;
                greaters++;
                gmap[sm]++;
            } else { // equals = 0
                H++;
                vertex gH = 0;
                auto it = gmap.find(H);
                if (it != gmap.end()) {
                    gH = it->second;
                    gmap.erase(H);
                }
                equals = gH + 1;
                greaters -= gH;
            }
        } else if (sm > H + 1) {
            if (equals > 0) {
                equals--;
                greaters++;
                gmap[sm]++;
            } else { // equals = 0
                greaters++;
                H++;
                vertex gH = 0;
                auto it = gmap.find(H);
                if (it != gmap.end()) {
                    gH = it->second;
                    gmap.erase(H);
                }
                equals = gH;
                greaters -= gH;
                gmap[sm]++;
            }
        }
    }

    vertex oP = P[ind];
#ifdef SYNC
    Q[ind] = H;
#else
    P[ind] = H;
#endif

    if (H < oP)
        return 1;
    else
        return 0;
}

inline int regularUpdateHI(vertex ind, vertex *adj, edge *xadj, vertex *P
#ifdef SYNC
        , vertex* Q
#endif
) {
    vertex previous_P = P[ind];
    vertex greaterequals = 0;
    vector<vertex> smallers(previous_P, 0);
    bool yep_set = false;
    vertex ne = xadj[ind + 1] - xadj[ind];
    for (edge j = xadj[ind]; j < xadj[ind + 1]; j++) {
        vertex w = adj[j];
        vertex pw = P[w];
        if (pw >= previous_P)
            greaterequals++;
        else
            smallers[pw]++;
        if (greaterequals == previous_P) {
            yep_set = true;
            break;
        }
    }

    if (!yep_set && ne > 0) { // watch for degree zeros
        vertex j = 0;
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

inline void updateAndNotify(vertex ind, vertex *P, vertex newP, vector<vertex> &neigs, bool *changed) {
    P[ind] = newP;
    changed[ind] = true;
    for (vertex k = 0; k < neigs.size(); k++)
        if (P[neigs[k]] >= P[ind])
            changed[neigs[k]] = true;
}

inline int efficientUpdateHI(vertex ind, vertex *adj, edge *xadj, vertex *P, bool *changed) {
    vector<vertex> neigs;
    vertex previous_P = P[ind];
    vertex greaterequals = 0;
    vector<vertex> smallers(previous_P, 0);
    bool yep_set = false;
    vertex ne = xadj[ind + 1] - xadj[ind];
    for (edge j = xadj[ind]; j < xadj[ind + 1]; j++) {
        vertex w = adj[j];
        vertex pw = P[w];
        if (pw <= previous_P)
            neigs.push_back(w);
        if (pw >= previous_P)
            greaterequals++;
        else
            smallers[pw]++;
        if (greaterequals == previous_P) {
            yep_set = true;
            break;
        }
    }

    if (!yep_set && ne > 0) { // watch for degree zeros
        vertex j;
        for (j = previous_P - 1; j > 0; j--) {
            greaterequals += smallers[j];
            if (greaterequals >= j)
                break;
        }
        updateAndNotify(ind, P, j, neigs, changed);
        return 1;
    }
    return 0;
}


// base AND and SND algorithms, no notification mechanism. compile with SYNC=yes to get the synchronous mode (SND)
void baseLocal12(vertex nVtx, vertex *adj, edge *xadj, vertex *P, const char *vfile) {

    const auto t_begin = chrono::steady_clock::now();
    P = (vertex *) calloc(nVtx, sizeof(vertex));

#pragma omp parallel for default (shared)
    for (vertex i = 0; i < nVtx; i++)
        P[i] = xadj[i + 1] - xadj[i];

#ifdef SYNC
    printf ("It is SYNC\n");
    vertex* Q = (vertex *) malloc (sizeof(vertex) * nVtx);
#else
    printf("It is ASYNC\n");
#endif

    const auto t_deg = chrono::steady_clock::now();
    tms t1 = t_deg - t_begin;
    printf("Degree finding time: %.6lf secs\n", t1.count());

    int oc = 0;
    bool flag = true;

#pragma omp parallel for schedule (dynamic, 1000)
    for (vertex ind = 0; ind < nVtx; ind++) {
        mapInitialHI(ind, adj, xadj, P
#ifdef SYNC
                , Q
#endif
        );
    }

#ifdef SYNC
    memcpy (P, Q, sizeof(vertex) * nVtx);
#endif

    const auto t_init = chrono::steady_clock::now();;
    tms t2 = t_init - t_deg;
    printf("H %d time: %.6lf secs\n", oc, t2.count());
    tms td = chrono::duration<double>::zero();
#ifdef DUMP_Hs
    const auto ts1 = chrono::steady_clock::now();
    print_Ks (nVtx, P, vfile, oc);
    const auto ts2 = chrono::steady_clock::now();
    td += ts2 - ts1;
#endif
    oc++;

    while (flag) {
        const auto td1 = chrono::steady_clock::now();
        flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
        for (vertex ind = 0; ind < nVtx; ind++) {
            int fl = regularUpdateHI(ind, adj, xadj, P
#ifdef SYNC
                    , Q
#endif
            );

            if (fl == 1)
                flag = true;
        }


#ifdef SYNC
        memcpy (P, Q, sizeof(vertex) * nVtx);
#endif

        const auto td2 = chrono::steady_clock::now();
#ifdef DUMP_Hs
        const auto ts1 = chrono::steady_clock::now();
        print_Ks (nVtx, P, vfile, oc);
        const auto ts2 = chrono::steady_clock::now();
        td += ts2 - ts1;
#endif

        tms step = td2 - td1;
        printf("H %d time: %.6lf secs\n", oc, step.count());
        oc++;
    }

#ifdef DUMP_K
    const auto ts3 = chrono::steady_clock::now();
    print_Ks (nVtx, P, vfile);
    const auto ts4 = chrono::steady_clock::now();
    td += ts4 - ts3;
#endif
    core_val_histogram(nVtx, P, true);

    free(P);
#ifdef SYNC
    free (Q);
#endif
    printf("Converges at %d\n", oc);
    const auto t_end = chrono::steady_clock::now();
    tms total = t_end - t_begin - td;
    printf("Total time: %.6lf secs\n", total.count());
    return;
}

// AND algorithm with the notification mechanism
void nmLocal12(vertex nVtx, vertex *adj, edge *xadj, vertex *P, const char *vfile) {
#ifdef SYNC
    printf ("No SYNC for notification-mechanism\n");
    exit(1);
#else
    const auto t_begin = chrono::steady_clock::now();
    P = (vertex *) calloc(nVtx, sizeof(vertex));

#pragma omp parallel for default (shared)
    for (vertex i = 0; i < nVtx; i++)
        P[i] = xadj[i + 1] - xadj[i];

    const auto t_deg = chrono::steady_clock::now();
    tms t1 = t_deg - t_begin;
    printf("Degree finding time: %.6lf secs\n", t1.count());

    int oc = 0;
    bool flag = true;

    tms td = chrono::duration<double>::zero();
#ifdef DUMP_Hs
    const auto ts1 = chrono::steady_clock::now();
    print_Ks (nVtx, P, vfile, oc);
    oc++;
    const auto ts2 = chrono::steady_clock::now();
    td += ts2 - ts1;
#endif

    int nt;
#pragma omp parallel
    {
        nt = omp_get_num_threads();
    }

    int counters[nt];

    for (int i = 0; i < nt; i++)
        counters[i] = 0;

//	bool changed[nVtx];
    bool *changed = new bool[nVtx];

    memset(changed, 255, sizeof(bool) * nVtx); // set all true
    int64_t prev_total = 0;
#pragma omp parallel for schedule (dynamic, 1000)
    for (vertex ind = 0; ind < nVtx; ind++) {
        counters[omp_get_thread_num()]++;
        mapInitialHI(ind, adj, xadj, P);
    }

    const auto t_init = chrono::steady_clock::now();;
    tms t2 = t_init - t_deg;

    auto cnt_sum = accumulate(counters, counters + nt, 0L);
    log_trace("local/global #changes: %s/%s, Iter: %d, Time: %.6lf secs",
              FormatWithCommas(cnt_sum - prev_total).c_str(),
              FormatWithCommas(cnt_sum).c_str(), oc, t2.count());
    prev_total = cnt_sum;
#ifdef DUMP_Hs
    const auto ts1 = chrono::steady_clock::now();
    print_Ks (nVtx, P, vfile, oc);
    const auto ts2 = chrono::steady_clock::now();
    td += ts2 - ts1;
#endif
    oc++;

    while (flag) {
        const auto td1 = chrono::steady_clock::now();
        flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
        for (vertex i = 0; i < nVtx; i++) {
            vertex ind = i;
            if (!changed[ind])
                continue;
            counters[omp_get_thread_num()]++;
            changed[ind] = false;
            int a = efficientUpdateHI(ind, adj, xadj, P, changed);
            if (a == 1)
                flag = true;
        }
        const auto td2 = chrono::steady_clock::now();

#ifdef DUMP_Hs
        const auto ts1 = chrono::steady_clock::now();
        print_Ks (nVtx, P, vfile, oc);
        const auto ts2 = chrono::steady_clock::now();
        td += ts2 - ts1;
#endif

        tms step = td2 - td1;

        {
            cnt_sum = accumulate(counters, counters + nt, 0L);
//            stringstream ss;
//            ss << pretty_print_array(counters, nt);
//            log_info("H %d Changes: %s, Sum: %'lld， time: %.6lf secs", oc, ss.str().c_str(), cnt_sum, step.count());
            log_trace("local/global #changes: %s/%s, Iter: %d, Time: %.6lf secs",
                      FormatWithCommas(cnt_sum - prev_total).c_str(),
                      FormatWithCommas(cnt_sum).c_str(), oc, step.count());
            prev_total = cnt_sum;
        }
//        log_info("H %d time: %.6lf secs\n", oc, step.count());
        oc++;
    }

#ifdef DUMP_K
    const auto ts3 = chrono::steady_clock::now();
    print_Ks (nVtx, P, vfile);
    const auto ts4 = chrono::steady_clock::now();
    td += ts4 - ts3;
#endif
    core_val_histogram(nVtx, P, true);

    free(P);
    printf("Converges at %d\n", oc);
    const auto t_end = chrono::steady_clock::now();
    tms total = t_end - t_begin - td;
    printf("Total time: %.6lf secs\n", total.count());
    delete[]changed;
    return;
#endif
}

// Sequential k-core computation
void kcore(vertex nVtx, vertex *adj, edge *xadj, vertex *K, const char *vfile) {

    const auto t_begin = chrono::steady_clock::now();
    size_t max_degree = 0;
    for (size_t i = 0; i < nVtx; i++) {
        auto deg = xadj[i + 1] - xadj[i];
        if (deg > max_degree)
            max_degree = deg;
    }
    K = (vertex *) malloc(nVtx * sizeof(vertex));

    // Peeling
    Naive_Bucket<vertex> na_bs;
    na_bs.Initialize(max_degree, nVtx);
    for (size_t i = 0; i < nVtx; i++) {
        auto deg = xadj[i + 1] - xadj[i];
        if (deg > 0)
            na_bs.Insert(i, deg);
        else
            K[i] = 0;
    }

    vertex degree_of_u = 0;
    while (1) {
        vertex u, val;
        if (na_bs.PopMin(&u, &val) == -1) // if the bucket is empty
            break;

        if (val == 0)
            continue;

        degree_of_u = K[u] = val;

        for (auto i = xadj[u]; i < xadj[u + 1]; i++) { /* decrease the degree of the neighbors with greater degree */
            vertex v = adj[i];
            if (na_bs.CurrentValue(v) > val)
                na_bs.DecVal(v);
        }
    }

    na_bs.Free();
    tms td = chrono::duration<double>::zero();
#ifdef DUMP_K
    const auto ts3 = chrono::steady_clock::now();
    print_Ks (nVtx, K, vfile);
    const auto ts4 = chrono::steady_clock::now();
    td += ts4 - ts3;
#endif
    core_val_histogram(nVtx, K, true);

    free(K);
    cout << "Max core number: " << degree_of_u << endl;
    const auto t_end = chrono::steady_clock::now();
    tms total = t_end - t_begin - td;
    printf("Total time: %.6lf secs\n", total.count());
    return;
}


// For partialnmLocal12 function
inline void AnotherupdateAndNotify(vertex ind, vertex *P, vertex newP, vector<vertex> &neigs, int *changed) {
    P[ind] = newP;
    if (changed[ind] == 0)
        changed[ind] = 1;
    for (vertex k = 0; k < neigs.size(); k++)
        if (P[neigs[k]] >= P[ind]) {
            if (changed[neigs[k]] == 0) // THIS is important!!!
                changed[neigs[k]] = 1;
        }
}

inline int AnotherefficientUpdateHI(vertex ind, vertex *adj, edge *xadj, vertex *P, int *changed) {
    vector<vertex> neigs;
    vertex previous_P = P[ind];
    vertex greaterequals = 0;
    vector<vertex> smallers(previous_P, 0);
    bool yep_set = false;
    vertex ne = xadj[ind + 1] - xadj[ind];
    for (edge j = xadj[ind]; j < xadj[ind + 1]; j++) {
        vertex w = adj[j];
        vertex pw = P[w];
        if (pw <= previous_P)
            neigs.push_back(w);
        if (pw >= previous_P)
            greaterequals++;
        else
            smallers[pw]++;
        if (greaterequals == previous_P) {
            yep_set = true;
            break;
        }
    }

    if (!yep_set && ne > 0) { // watch for degree zeros
        vertex j;
        for (j = previous_P - 1; j > 0; j--) {
            greaterequals += smallers[j];
            if (greaterequals >= j)
                break;
        }
        AnotherupdateAndNotify(ind, P, j, neigs, changed);
        return 1;
    }
    return 0;
}


// Function in Sec. 5.3
void partialnmLocal12(int *changed, vertex nVtx, vertex *adj, edge *xadj, vertex *P) {

#pragma omp parallel for default (shared)
    for (vertex i = 0; i < nVtx; i++)
        P[i] = xadj[i + 1] - xadj[i];

#pragma omp parallel for schedule (dynamic, 1000)
    for (vertex ind = 0; ind < nVtx; ind++)
        if (changed[ind] == 1)
            mapInitialHI(ind, adj, xadj, P);

    bool flag = true;
    while (flag) {
        flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
        for (vertex i = 0; i < nVtx; i++) {
            vertex ind = i;
            if (changed[ind] != 1)
                continue;
            changed[ind] = 0;
            int a = AnotherefficientUpdateHI(ind, adj, xadj, P, changed);
            if (a == 1)
                flag = true;
        }
    }
    return;
}


// For Fig. 14a. Applies partialAND on the ego network of a given sample vertex. 4 * TEST_SIZE is the number of samples.
// Reads degrees and core-numbers from files
void converge12onEgo(vertex nVtx, vertex *adj, edge *xadj, vertex *K, string kfile) {

    string fk = kfile + "_1200_CORE_H_0"; // Degrees are read
    FILE *fp = fopen(fk.c_str(), "r");
    K = (vertex *) malloc(nVtx * sizeof(vertex));
    vertex *D = (vertex *) malloc(nVtx * sizeof(vertex));

    vector<tuple<int, int>> dv;
    int i = 0;
    while (fscanf(fp, "%d", &(D[i])) != EOF) {
        dv.push_back(make_tuple(i, D[i]));
        i++;
    }
    sort(dv.begin(), dv.end(), kksort);

    fk = kfile + "_1200_CORE_FINAL_K"; // Core numbers are read
    fp = fopen(fk.c_str(), "r");
    vector<tuple<int, int>> cv;
    i = 0;
    while (fscanf(fp, "%d", &(K[i])) != EOF) {
        cv.push_back(make_tuple(i, K[i]));
        i++;
    }
    sort(cv.begin(), cv.end(), kksort);
    fclose(fp);

    vector<vertex> sample_vertices;

    srand(time(NULL));

    // samples vertices from degree-sorted array and core-number-sorted-array
    for (int i = 1; i <= TEST_SIZE; i++) {
        int u = rand() % (i * nVtx / TEST_SIZE);
        sample_vertices.push_back(get<0>(dv[u]));
        sample_vertices.push_back(get<0>(cv[u]));
        sample_vertices.push_back(get<0>(dv[i - 1]));
        sample_vertices.push_back(get<0>(cv[i - 1]));
    }

    vertex *P = (vertex *) calloc(nVtx, sizeof(vertex));
    int changed[nVtx];
    for (int i = 0; i < nVtx; i++)
        changed[i] = -1;

    for (auto v : sample_vertices) {
        memset(P, 0, nVtx);
        const auto t_begin = chrono::steady_clock::now();

        changed[v] = 1;
        for (int i = xadj[v]; i < xadj[v + 1]; i++)
            changed[adj[i]] = 1;
        partialnmLocal12(changed, nVtx, adj, xadj, P);

        const auto t_end = chrono::steady_clock::now();
        tms t1 = t_end - t_begin;
        printf("Local convergence time: %.6lf secs\n", t1.count());

        int pv = P[v], kv = K[v];
        vector<vertex> gt, rs;
        for (int i = xadj[v]; i < xadj[v + 1]; i++) {
            vertex w = adj[i];
            if (K[w] >= kv)
                gt.push_back(w);

            if (P[w] >= pv)
                rs.push_back(w);
        }

        printf("12_EGO -- P: %d  vs  K: %d\t", P[v], K[v]);
        sort(rs.begin(), rs.end());
        sort(gt.begin(), gt.end());

        int is = commons(rs, gt);
        double prec = (double) is / rs.size(), recall = (double) is / gt.size();
        double f1 = 2 * prec * recall / (prec + recall), jaccard = (double) is / (gt.size() + rs.size() - is);

        // Comparison of partialAND results (P) and the ground-truth core numbers (K)
        printf("base: %d\tjac: %lf\tprec: %lf\trec: %lf\tf1: %lf\t\t", gt.size(), jaccard, prec, recall, f1);

        {
            for (vertex i = 0; i < nVtx; i++)
                P[i] = D[i];

            int pv = P[v], kv = K[v];
            vector<vertex> gt, rs;
            for (int i = xadj[v]; i < xadj[v + 1]; i++) {
                vertex w = adj[i];

                if (K[w] >= kv)
                    gt.push_back(w);

                if (P[w] >= pv)
                    rs.push_back(w);
            }

            printf("deg_EGO -- deg	: %d  vs  K: %d\t", P[v], K[v]);
            sort(rs.begin(), rs.end());
            sort(gt.begin(), gt.end());

            int is = commons(rs, gt);
            double prec = (double) is / rs.size(), recall = (double) is / gt.size();
            double f1 = 2 * prec * recall / (prec + recall), jaccard = (double) is / (gt.size() + rs.size() - is);

            // Comparison of degrees (D) and the ground-truth core numbers (K)
            printf("base: %d\tjac: %lf\tprec: %lf\trec: %lf\tf1: %lf\n", gt.size(), jaccard, prec, recall, f1);
        }
    }
}
