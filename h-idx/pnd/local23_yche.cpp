#include <util/timer.h>
#include "main.h"
#include "util/log/log.h"
#include "util.h"
#include "set-inter/lemire/intersection.h"

#ifdef GPERFTOOLS
#include <gperftools/profiler.h>
#endif

#define MAX_INTERSECTION_SIZE (2048*1024)

vertex BinarySearch(couple *array, int offset_beg, int offset_end, int val) {
    while (offset_end - offset_beg >= 1) {
        auto mid = offset_beg + (offset_end - offset_beg) / 2;
        auto mid_val = get<1>(array[mid]);
        if (mid_val == val) {
            return mid;
        } else if (mid_val < val) {
            offset_beg = mid + 1;
        } else {
            offset_end = mid;
        }
    }
    return offset_end;
}

vertex getEdgeId(vertex u, vertex v, edge *xel, couple *el, vertex deg_u, vertex deg_v) {
    vertex a = v, b = u;
    if (deg_u < deg_v || (deg_u == deg_v && u < v))
        swap(a, b);
#ifdef STUPID
    for (edge i = xel[a]; i < xel[a + 1]; i++)
        if (get<1>(el[i]) == b)
            return i;
    return -1;
#else
    auto off = BinarySearch(el, xel[a], xel[a + 1], b);
    if (off != xel[a + 1]) {
        return off;
    }
    return -1;
#endif
}

int FindSrc(const edge *ordered_xadj, int u, uint32_t edge_idx, vertex nVtx) {
    if (edge_idx >= ordered_xadj[u + 1]) {
        // update last_u, preferring galloping instead of binary search because not large range here
        u = GallopingSearch(ordered_xadj, static_cast<uint32_t>(u) + 1, nVtx + 1, edge_idx);
        // 1) first > , 2) has neighbor
        if (ordered_xadj[u] > edge_idx) {
            while (ordered_xadj[u] - ordered_xadj[u - 1] == 0) { u--; }
            u--;
        } else {
            // ordered_xadj[u] == i
            while (ordered_xadj[u + 1] - ordered_xadj[u] == 0) {
                u++;
            }
        }
    }
    return u;
}

size_t
SetIntersectGalloping(vector<edge> &my_ptr1, vector<edge> &my_ptr2, edge *xadj, vertex *adj, vertex u, vertex v) {
    size_t size = 0;
    auto off_nei_u = xadj[u], off_nei_v = xadj[v];
    auto off_u_end = xadj[u + 1], off_v_end = xadj[v + 1];

    if (off_nei_u < off_u_end && off_nei_v < off_v_end) {
        while (true) {
            off_nei_u = GallopingSearch(adj, off_nei_u, off_u_end, adj[off_nei_v]);
            if (off_nei_u >= off_u_end) {
                break;
            }
            off_nei_v = GallopingSearch(adj, off_nei_v, off_v_end, adj[off_nei_u]);
            if (off_nei_v >= off_v_end) {
                break;
            }
            if (adj[off_nei_u] == adj[off_nei_v]) {
                my_ptr1[size] = off_nei_u;
                my_ptr2[size] = off_nei_v;
                size++;
                ++off_nei_u;
                ++off_nei_v;
                if (off_nei_u >= off_u_end || off_nei_v >= off_v_end) {
                    break;
                }
            }
        }
    }
    return size;
}

/*
 * Assume all the pointers are properly allocated
 */
void createRevLink(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, edge *xel, couple *el, uint32_t *rev_link) {
    Timer timer;
    size_t undir_edge_num = nEdge * 2;
    log_info("undir edge#: %zu", undir_edge_num);
#pragma omp parallel for schedule(dynamic, 6000)
    for (size_t edge_idx = 0; edge_idx < undir_edge_num; edge_idx++) {
        static thread_local int u = 0;
        u = FindSrc(xadj, u, edge_idx, nVtx);
        auto v = adj[edge_idx];
        vertex deg_u = xadj[u + 1] - xadj[u];
        vertex deg_v = xadj[v + 1] - xadj[v];

        rev_link[edge_idx] = getEdgeId(u, v, xel, el, deg_u, deg_v);
    }
    log_info("Finish Create Rev Link, Cost: %.6lfs", timer.elapsed());

    // Verify Logic.
    timer.reset();
#pragma omp parallel for schedule(dynamic, 6000)
    for (size_t edge_idx = 0; edge_idx < undir_edge_num; edge_idx++) {
        static thread_local int u = 0;

        u = FindSrc(xadj, u, edge_idx, nVtx);
        auto v = adj[edge_idx];
        vertex deg_u = xadj[u + 1] - xadj[u];
        vertex deg_v = xadj[v + 1] - xadj[v];

        uint32_t res = getEdgeId(u, v, xel, el, deg_u, deg_v);
        if (res != rev_link[edge_idx]) {
            log_fatal("edge (%d, %d), id: %d, Err %d, %d", u, v, edge_idx, res, rev_link[edge_idx]);
            exit(-1);
        }
    }
    log_info("Verify Pass, Cost: %.6lf", timer.elapsed());
}


// single loop, three locks
lol count_triangles(vertex *T, vertex nVtx, const vertex *ordered_adj, const edge *ordered_xadj) {
    lol count = 0;
#pragma omp parallel
    {
        auto u = 0;
        vector<vertex> tmp;

#pragma omp for reduction(+:count) schedule(dynamic, 6000)
        for (auto j = 0; j < ordered_xadj[nVtx]; j++) {
            u = FindSrc(ordered_xadj, u, j, nVtx);
            // Intersection.
            auto v = ordered_adj[j];
            tmp.clear();
            set_intersection(ordered_adj + ordered_xadj[u], ordered_adj + ordered_xadj[u + 1],
                             ordered_adj + ordered_xadj[v], ordered_adj + ordered_xadj[v + 1],
                             back_inserter(tmp));
#pragma omp atomic
            T[j] += tmp.size();
            count += tmp.size();
            // u < v < w
            auto prev_it_u = ordered_xadj[u];
            for (auto iter_res = 0; iter_res < tmp.size(); iter_res++) {
                prev_it_u = LinearSearch(ordered_adj, prev_it_u, ordered_xadj[u + 1], tmp[iter_res]);
#pragma omp atomic
                T[prev_it_u] += 1;
            }

            auto prev_it_v = ordered_xadj[v];
            for (auto iter_res = 0; iter_res < tmp.size(); iter_res++) {
                prev_it_v = LinearSearch(ordered_adj, prev_it_v, ordered_xadj[v + 1], tmp[iter_res]);
#pragma omp atomic
                T[prev_it_v] += 1;
            }
        }
    }
    return count;
}

int mapInitialHIRevLink(edge ind, edge *xadj, vertex *adj, couple *el, vertex *P, const uint32_t *rev_link) {
    unordered_map<vertex, vertex> gmap;
    static thread_local vector<edge> my_ptr1(MAX_INTERSECTION_SIZE);
    static thread_local vector<edge> my_ptr2(MAX_INTERSECTION_SIZE);
    vertex greaters = 0;
    vertex equals = 0;
    vertex H = 0;
    vertex u = get<0>(el[ind]);
    vertex v = get<1>(el[ind]);

    auto size = SetIntersectGalloping(my_ptr1, my_ptr2, xadj, adj, u, v);

    for (auto ri = 0u; ri < size; ri++) {
        auto id1 = rev_link[my_ptr1[ri]];
        auto id2 = rev_link[my_ptr2[ri]];
        vertex sm = min(P[id1], P[id2]);

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
    P[ind] = H;
    if (H < oP) {
        return 1;
    } else
        return 0;
}

void updateAndNotify(edge ind, vertex *P, int newP, vector<edge> &neigs, bool *changed) {
    P[ind] = newP;
    changed[ind] = true;
    for (int k = 0; k < neigs.size(); k++) {
        if (P[neigs[k]] >= P[ind]) {
            changed[neigs[k]] = true;
        }
    }
}

int efficientUpdateHIRevLink(edge ind, edge *xadj, vertex *adj, couple *el, vertex *T, bool *changed,
                             const uint32_t *rev_link) {
    vector<edge> neigs;
    vertex previous_T = T[ind];
    vertex greaterequals = 0;
    vector<vertex> smallers(previous_T, 0);
    bool yep_set = false;
    static thread_local vector<edge> my_ptr1(MAX_INTERSECTION_SIZE);
    static thread_local vector<edge> my_ptr2(MAX_INTERSECTION_SIZE);

    vertex u = get<0>(el[ind]);
    vertex v = get<1>(el[ind]);

    auto size = SetIntersectGalloping(my_ptr1, my_ptr2, xadj, adj, u, v);

    for (auto ri = 0u; ri < size; ri++) {
        auto id1 = rev_link[my_ptr1[ri]];
        auto id2 = rev_link[my_ptr2[ri]];
        neigs.push_back(id1);
        neigs.push_back(id2);
        auto cur_T = (T[id1] <= T[id2]) ? T[id1] : T[id2];

        if (cur_T >= previous_T)
            greaterequals++;
        else {
            smallers[cur_T]++;
        }

        if (greaterequals == previous_T) {
            yep_set = true;
            break;
        }
    }

    if (!yep_set && size != 0) {
        vertex j;
        for (j = previous_T - 1; j > 0; j--) {
            greaterequals += smallers[j];
            if (greaterequals >= j) {
                break;
            }
        }

        updateAndNotify(ind, T, j, neigs, changed);
        return 1;
    }
    return 0;
}

// AND algorithm with the notification mechanism
void nmLocal23(vertex nVtx, edge nEdge, vertex *adj, edge *xadj, vertex *T) {
    const auto t_begin = chrono::steady_clock::now();
    log_info("# of Edges: %s", FormatWithCommas(nEdge).c_str());
    // Ordered (directed) graph creation
    auto *el = (couple *) malloc(sizeof(couple) * nEdge);
    edge *xel = (edge *) malloc(sizeof(edge) * (nVtx + 1));
    auto *ordered_adj = (vertex *) malloc(sizeof(vertex) * nEdge);
    edge *ordered_xadj = (edge *) malloc(sizeof(edge) * (nVtx + 1));;

    createOrdered(nVtx, nEdge, adj, xadj, el, xel, ordered_adj, ordered_xadj);

    const auto t_cog = chrono::steady_clock::now();
    tms t1 = t_cog - t_begin;
    log_trace ("Creating ordered graph: %.6lf secs", t1.count());

    // Triangle counting for each edge
    T = (vertex *) calloc(nEdge, sizeof(vertex));

    lol tricount = count_triangles(T, nVtx, ordered_adj, ordered_xadj); // single loop with three locks

    free(ordered_adj);
    free(ordered_xadj);
    const auto t_tc = chrono::steady_clock::now();
    tms t2 = t_tc - t_cog;
    log_trace ("Triangle counting time: %.6lf secs", t2.count());

#ifndef FAST
    log_info("# triangles: %'lld", tricount);
#endif

    auto *rev_link = (uint32_t *) malloc(sizeof(uint32_t) * 2 * nEdge);
    createRevLink(nVtx, nEdge, adj, xadj, xel, el, rev_link);

    int oc = 0;
    bool flag = true;

#ifdef GPERFTOOLS
    ProfilerStart("pnd.log");
#endif
    int nt;
#pragma omp parallel
    {
        nt = omp_get_num_threads();
    }
    int64_t prev_total = 0;

    int64_t counters[nt];
    for (int i = 0; i < nt; i++)
        counters[i] = 0;

#pragma omp parallel for schedule(dynamic, 1000)
    for (edge ind = 0; ind < nEdge; ind++) {
        counters[omp_get_thread_num()]++;
//        mapInitialHI(ind, xadj, adj, xel, el, T);
        mapInitialHIRevLink(ind, xadj, adj, el, T, rev_link);
    }
//    bool changed[nEdge];      // fix bug
    bool *changed = new bool[nEdge];
    memset(changed, 255, sizeof(bool) * nEdge); // set all true

    const auto t_init = chrono::steady_clock::now();;
    tms t3 = t_init - t_tc;
    auto cnt_sum = accumulate(counters, counters + nt, 0L);
    log_trace("local/global #changes: %s/%s, Iter: %d, Time: %.6lf secs",
              FormatWithCommas(cnt_sum - prev_total).c_str(),
              FormatWithCommas(cnt_sum).c_str(), oc, t3.count());
    prev_total = cnt_sum;
//    log_trace ("H %d time: %.6lf secs", oc, t3.count());
//    {
//        stringstream ss;
//        auto cnt_sum = accumulate(counters, counters + nt, 0L);
//        ss << pretty_print_array(counters, nt);
//        log_info("H %d Changes: %s, Sum: %'lld", oc, ss.str().c_str(), cnt_sum);
//    }
    tms td = chrono::duration<double>::zero();

    oc++;

    while (flag) {
        const auto td1 = chrono::steady_clock::now();
        flag = false;

#pragma omp parallel for schedule (dynamic, 1000)
        for (edge ind = 0; ind < nEdge; ind++) {
            if (!changed[ind])
                continue;
            counters[omp_get_thread_num()]++;
            changed[ind] = false;
//            int a = efficientUpdateHI(ind, xadj, adj, xel, el, T, changed);
            int a = efficientUpdateHIRevLink(ind, xadj, adj, el, T, changed, rev_link);
            if (a == 1)
                flag = true;
        }

        const auto td2 = chrono::steady_clock::now();

        tms step = td2 - td1;
//        log_trace ("H %d time: %.6lf secs", oc, step.count());
//        auto cnt_sum = accumulate(counters, counters + nt, 0L);
//
//        stringstream ss;
//        ss << pretty_print_array(counters, nt);
//        log_info("H %d Changes: %s, Sum: %'lld", oc, ss.str().c_str(), cnt_sum);
        cnt_sum = accumulate(counters, counters + nt, 0L);
        log_trace("local/global #changes: %s/%s, Iter: %d, Time: %.6lf secs",
                  FormatWithCommas(cnt_sum - prev_total).c_str(),
                  FormatWithCommas(cnt_sum).c_str(), oc, step.count());
        prev_total = cnt_sum;

        oc++;
    }
#ifdef GPERFTOOLS
    log_info("GperfToolsEnd");
    ProfilerStop();
#endif
    core_val_histogram(nEdge, T, true);

    free(T);
    free(el);
    delete[]changed;
    log_trace ("Converges at %d", oc);
    const auto t_end = chrono::steady_clock::now();
    tms total = t_end - t_begin - td;
    log_trace ("Total time: %.6lf secs", total.count());
}
