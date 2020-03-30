/*
	Author: Seyed-Vahid Sanei-Mehri
	Contact: vahid.sanei@gmail.com or vas@iastate.edu

	Here is the source code for ** BUTTERFLY COUNTING IN BIPARTITE NETWORKS **
	On Arxiv: Sanei-Mehri, Seyed-Vahid, Erdem Saryuce, and Srikanta Tirthapura. "Butterfly Counting in Bipartite Networks." arXiv preprint arXiv:1801.00338 (2017).

	Abstract:
		We consider the problem of counting motifs in bipartite affiliation networks, such as author-paper, user-product, and actor-movie relations. 
		We focus on counting the number of occurrences of a "butterfly", a complete 2�2 biclique, the simplest cohesive higher-order structure in a bipartite graph. 
		Our main contribution is a suite of randomized algorithms that can quickly approximate the number of butterflies in a graph with a provable guarantee on accuracy. 
		An experimental evaluation on large real-world networks shows that our algorithms return accurate estimates within a few seconds, even for networks with trillions of 
		butterflies and hundreds of millions of edges.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_set>
#include <map>
#include <sstream>
#include <random>
//#include <boost/random/mersenne_twister.hpp>
//#include <boost/random/uniform_int_distribution.hpp>
//#include <boost/random/uniform_real_distribution.hpp>
//#include <boost/random/random_device.hpp>

using namespace std;
//using namespace boost::random;

#define SZ(x) ((int)x.size())
#define ll long long
#define ull unsigned long long
#define ld long double
#define eps 1e-11
#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))

const int ITER_VER = 2200;
const ll shift = 1000 * 1000 * 1000LL;
const double TIME_LIMIT = 20;
const int N_WEDGE_ITERATIONS = 2 * 1000 * 1000 * 10;
const int ITERATIONS_SAMPLING = 5;
const int N_SPARSIFICATION_ITERATIONS = 5;
const int TIME_LIMIT_SPARSIFICATION = 10000; // !half an hour
const int N_FAST_EDGE_BFC_ITERATIONS = 2100; // used for fast edge sampling
const int N_FAST_WEDGE_ITERATIONS = 50; // used for fast wedge sampling

char input_address[2000], output_address[2000];

set<pair<int, int> > edges;
vector<pair<int, int> > list_of_edges;
map<int, int> vertices[2];
vector<int> index_map;
vector<int> vertices_in_left;
vector<int> vertices_in_right;
vector<vector<int> > adj;
vector<vector<int> > sampled_adj_list;
vector<bool> visited;
vector<int> list_of_vertices;
vector<int> vertex_counter;

ll n_vertices;
ll n_edges;
ld exact_n_bf;
ll n_wedge_in_partition[2];
ll largest_index_in_partition[2];

vector<int> clr;
vector<int> hashmap_C;
vector<ll> sum_wedges;
vector<ll> sum_deg_neighbors;
vector<int> aux_array_two_neighboorhood;

void clear_everything() {
    largest_index_in_partition[0] = largest_index_in_partition[1] = 0;
    n_vertices = 0;
    n_edges = 0;
    edges.clear();
    vertices[0].clear();
    vertices[1].clear();
    index_map.clear();
    vertices_in_left.clear();
    vertices_in_right.clear();
    adj.clear();
    sampled_adj_list.clear();
    visited.clear();
    list_of_edges.clear();
    vertex_counter.clear();
    clr.clear();
    hashmap_C.clear();
    sum_wedges.clear();
    sum_deg_neighbors.clear();
    aux_array_two_neighboorhood.clear();
}

void resize_all() {
    clr.resize(n_vertices);
    hashmap_C.resize(n_vertices);
    aux_array_two_neighboorhood.resize(n_vertices);
    sum_wedges.resize(n_vertices);
    visited.resize(n_vertices);
    index_map.resize(n_vertices);
    sum_deg_neighbors.resize(n_vertices);
}

// ------------- Read the graph ---------------------
void add_vertex(int A, int side) {
    if (vertices[side].find(A) == vertices[side].end()) {
        if (side == 0) vertices_in_left.push_back(A);
        else vertices_in_right.push_back(A);
        vertices[side][A] = 1;
    }
}

void get_index(int &A, int side) {
    if (vertices[side].find(A) == vertices[side].end()) {
        vertices[side][A] = largest_index_in_partition[side]++;
    }
    A = vertices[side][A];
}

void add_edge(int &A, int &B) {
    add_vertex(A, 0);
    add_vertex(B, 1);
    if (edges.find(make_pair(A, B)) == edges.end()) {
        edges.insert(make_pair(A, B));
        n_edges++;
    }
}

bool all_num(string &s) {
    for (int i = 0; i < SZ(s); i++) if ((s[i] >= '0' && s[i] <= '9') == false) return false;
    return true;
}

void get_graph() {
    freopen(input_address, "r", stdin);
    string s;
    cin.clear();
    while (getline(cin, s)) {
        stringstream ss;
        ss << s;
        vector<string> vec_str;
        for (string z; ss >> z; vec_str.push_back(z));
        if (SZ(vec_str) >= 2) {
            bool is_all_num = true;
            for (int i = 0; i < min (2, SZ(vec_str)); i++) is_all_num &= all_num(vec_str[i]);
            if (is_all_num) {
                int A, B;
                ss.clear();
                ss << vec_str[0];
                ss >> A;
                ss.clear();
                ss << vec_str[1];
                ss >> B;
                add_edge(A, B);
            }
        }
    }
    vertices[0].clear();
    vertices[1].clear();
    largest_index_in_partition[0] = 0;
    largest_index_in_partition[1] = SZ(vertices_in_left);
    n_vertices = SZ(vertices_in_left) + SZ(vertices_in_right);
    adj.resize(n_vertices, vector<int>());
    for (auto edge : edges) {
        int A = edge.first;
        int B = edge.second;
        get_index(A, 0);
        get_index(B, 1);
        adj[A].push_back(B);
        adj[B].push_back(A);
        list_of_edges.push_back(make_pair(A, B));
    }
    resize_all();

    n_wedge_in_partition[0] = 0;
    for (int i = 0; i < largest_index_in_partition[0]; i++) {
        n_wedge_in_partition[0] += (((ll) SZ(adj[i])) * (SZ(adj[i]) - 1)) >> 1;
    }
    n_wedge_in_partition[1] = 0;
    for (int i = largest_index_in_partition[0]; i < largest_index_in_partition[1]; i++) {
        n_wedge_in_partition[1] += ((ll) SZ(adj[i]) * (SZ(adj[i]) - 1)) >> 1;
    }
    for (int i = 0; i < n_vertices; i++) {
        sort(adj[i].begin(), adj[i].end());
        sum_deg_neighbors[i] = 0;
        for (auto neighbor : adj[i]) {
            sum_deg_neighbors[i] += SZ(adj[neighbor]);
        }
    }
    cerr << " for test # edges :: " << SZ(list_of_edges) << " left :: " << SZ(vertices_in_left) << " right :: "
         << SZ(vertices_in_right) << endl;
    sort(list_of_edges.begin(), list_of_edges.end());
    fclose(stdin);
}
// ------------- Read the graph ---------------------

int exact_neighbor_intersections(int a, int b) {
    int common = 0;
    if (SZ(adj[a]) > SZ(adj[b])) swap(a, b);
    unordered_set<int> set;
    for (int i = 0; i < SZ(adj[a]); i++) set.insert(adj[a][i]);
    for (int j = 0; j < SZ(adj[b]); j++) {
        if (set.find(adj[b][j]) != set.end())
            common++;
    }
    return common;
}

double fast_neighbor_intersections(int a, int b) {
    if (SZ(adj[a]) > SZ(adj[b])) swap(a, b);
    random_device rdw;
    mt19937 genedg(rdw());
    uniform_int_distribution<int> dis(0, SZ(adj[a]) - 1);
    ld sum_wedges = 0;
    int n_iterations = N_WEDGE_ITERATIONS;
    for (int i = 0; i < n_iterations; i++) {
        int c = adj[a][dis(genedg)];
        if (binary_search(adj[b].begin(), adj[b].end(), c)) {
            sum_wedges += SZ(adj[a]);
        }
    }
    sum_wedges /= n_iterations;
    return sum_wedges;
}

ll exact_butterfly_counting(vector<vector<int> > &graph) {
    int side = n_wedge_in_partition[0] < n_wedge_in_partition[1];
    ld res = 0;
    for (int vertex = side == 0 ? 0 : SZ(vertices_in_left); vertex < largest_index_in_partition[side]; vertex++) {
        int idx = 0;
        for (int j = 0; j < SZ(graph[vertex]); j++) {
            int neighbor = graph[vertex][j];
            for (int k = 0; k < SZ(graph[neighbor]); k++) {
                int two_hop_neighborhood = graph[neighbor][k];
                if (vertex > two_hop_neighborhood) {
                    res += hashmap_C[two_hop_neighborhood];
                    hashmap_C[two_hop_neighborhood]++;
                    if (hashmap_C[two_hop_neighborhood] == 1)
                        aux_array_two_neighboorhood[idx++] = two_hop_neighborhood;
                } else break;
            }
        }
        for (int j = 0; j < idx; j++) {
            hashmap_C[aux_array_two_neighboorhood[j]] = 0;
        }
    }
    return res;
}

ll compute_n_wedges() {
    ll wedges = 0;
    for (int i = 0; i < n_vertices; i++) {
        wedges += ((ll) (SZ(adj[i])) * ((ll) SZ(adj[i]) - 1)) >> 1;
        sum_wedges[i] = wedges;
    }
    return wedges;
}


ld error_percent(ld &res) {
    if (exact_n_bf == 0) return 0;
    ld error = (res - exact_n_bf) / exact_n_bf * 100.0;
    if (error < 0) error *= -1.0;
    return error;
}

ld wedge_sampling(uniform_int_distribution<ll> &dis, mt19937_64 &eng, int &iter, int &alpha, ll &n_wedges) {
    ld res_wedge_samp = 0;
    for (; iter < alpha; iter++) {
        int l1, l2;
        ll ran = dis(eng);
        int lo = 0, hi = n_vertices - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (sum_wedges[mid] < ran) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        random_device rdev_wedge_low;
        mt19937 eng_wedge(rdev_wedge_low());
        uniform_int_distribution<int> dis1(0, SZ(adj[lo]) - 1);
        l1 = dis1(eng_wedge);
        uniform_int_distribution<int> dis2(0, SZ(adj[lo]) - 2);
        l2 = dis2(eng_wedge);
        if (l2 >= l1) l2++;
        l1 = adj[lo][l1];
        l2 = adj[lo][l2];
        res_wedge_samp += exact_neighbor_intersections(l1, l2) - 1;
    }
    return res_wedge_samp;
}

ld fast_wedge_sampling(uniform_int_distribution<ll> &dis, mt19937_64 &gen, int &iter, int &alpha, ll &n_wedges) {
    ld res_fast_wedge_samp = 0;
    for (; iter < alpha; iter++) {
        int l1, l2;
        ll ran = dis(gen);
        int lo = 0, hi = n_vertices - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (sum_wedges[mid] < ran) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        random_device rdev_wedge_low;
        mt19937 eng_fast_wedge(rdev_wedge_low());
        uniform_int_distribution<int> dis1(0, SZ(adj[lo]) - 1);
        l1 = dis1(eng_fast_wedge);
        uniform_int_distribution<int> dis2(0, SZ(adj[lo]) - 2);
        l2 = dis2(eng_fast_wedge);
        if (l2 >= l1) l2++;
        l1 = adj[lo][l1];
        l2 = adj[lo][l2];
        res_fast_wedge_samp += fast_neighbor_intersections(l1, l2);
    }
    return res_fast_wedge_samp;
}

ld colorful_sparsification(int num_clr) {
    random_device rdev_colorful;
    mt19937 eng_colorful(rdev_colorful());
    uniform_int_distribution<int> dis(0, num_clr - 1);

    for (int i = 0; i < n_vertices; i++) {
        clr[i] = dis(eng_colorful);
    }
    sampled_adj_list.resize(n_vertices, (vector<int>()));

    n_wedge_in_partition[0] = n_wedge_in_partition[1] = 0;
    for (auto edge : edges) {
        int A = edge.first;
        int B = edge.second;
        if (A > B && clr[A] == clr[B]) {
            sampled_adj_list[A].push_back(B);
            sampled_adj_list[B].push_back(A);
            n_wedge_in_partition[0] += 2 * SZ(sampled_adj_list[A]) - 1;
            n_wedge_in_partition[1] += 2 * SZ(sampled_adj_list[B]) - 1;
        }
    }
    ld beta = exact_butterfly_counting(sampled_adj_list);
    return beta * num_clr * num_clr * num_clr;
}

ld edge_saprsification(double prob) {
    prob = prob > 1.0 ? 1.0 : prob;
    random_device rdev_edge_sprs;
    mt19937 eng_edg_sprs(rdev_edge_sprs());
    uniform_real_distribution<double> dis(0.0, 1.0);

    sampled_adj_list.clear();
    sampled_adj_list.resize(n_vertices, (vector<int>()));

    n_wedge_in_partition[0] = n_wedge_in_partition[1] = 0;
    for (auto edge : edges) {
        int A = edge.first;
        int B = edge.second;
        double coin = dis(eng_edg_sprs);
        if (coin <= prob || abs(coin - prob) <= eps) {
            sampled_adj_list[A].push_back(B);
            sampled_adj_list[B].push_back(A);
            n_wedge_in_partition[0] += 2 * SZ(sampled_adj_list[A]) - 1;
            n_wedge_in_partition[1] += 2 * SZ(sampled_adj_list[B]) - 1;
        }
    }
    ld beta = exact_butterfly_counting(sampled_adj_list);
    return (ld) beta / (prob * prob * prob * prob);
}

ld exact_BFC_per_edge(int a, int b) {
    ld bfc_per_edge = 0;
    for (int k = 0; k < SZ(adj[a]); k++) {
        int c = adj[a][k];
        if (c != b) {
            bfc_per_edge += exact_neighbor_intersections(c, b) - 1;
        }
    }
    return bfc_per_edge;
}

ld fast_exact_BFC_per_edge(int a, int b) {
    for (int i = 0; i < SZ(adj[a]); i++) {
        int neighbor = adj[a][i];
        if (neighbor != b) {
            for (int j = 0; j < SZ(adj[neighbor]); j++) {
                int two_hop_neighborhood = adj[neighbor][j];
                if (two_hop_neighborhood != a) {
                    index_map[two_hop_neighborhood]++;
                }
            }
        }
    }
    ld bfc_per_edge = 0;
    for (int i = 0; i < SZ(adj[b]); i++) {
        int neighbor = adj[b][i];
        bfc_per_edge += index_map[neighbor];
    }
    for (int i = 0; i < SZ(adj[a]); i++) {
        int neighbor = adj[a][i];
        for (int j = 0; j < SZ(adj[neighbor]); j++) {
            index_map[adj[neighbor][j]] = 0;
        }
    }
    return bfc_per_edge;
}

random_device rd_edge;
mt19937_64 eng_ran_bfc_per_edge(rd_edge());

ld randomized_BFC_per_edge(int a, int b) {
    if (SZ(adj[a]) <= 1 || SZ(adj[b]) <= 1) {
        return 0;
    }
    uniform_int_distribution<int> dis_a(0, SZ(adj[a]) - 1);
    uniform_int_distribution<int> dis_b(0, SZ(adj[b]) - 1);
    ld res_ran_bfc_per_edge = 0;
    for (int i = 0; i < N_FAST_EDGE_BFC_ITERATIONS; i++) {
        int x = adj[a][dis_a(eng_ran_bfc_per_edge)];
        int y = adj[b][dis_b(eng_ran_bfc_per_edge)];
        if (x != b && y != a && binary_search(adj[x].begin(), adj[x].end(), y)) {
            res_ran_bfc_per_edge += ((ld) SZ(adj[a])) * ((ld) SZ(adj[b]));
        }
    }
    res_ran_bfc_per_edge /= N_FAST_EDGE_BFC_ITERATIONS;
    return res_ran_bfc_per_edge;
}

ld exact_bfc_per_vertex(int vertex) {
    ld res = 0;
    for (int i = 0; i < SZ(adj[vertex]); i++) {
        int neighbor = adj[vertex][i];
        for (int j = 0; j < SZ(adj[neighbor]); j++) {
            int two_hop_neighborhood = adj[neighbor][j];
            if (two_hop_neighborhood != vertex) {
                res += index_map[two_hop_neighborhood];
                index_map[two_hop_neighborhood]++;
            }
        }
    }
    for (int i = 0; i < SZ(adj[vertex]); i++) {
        int neighbor = adj[vertex][i];
        for (int j = 0; j < SZ(adj[neighbor]); j++) {
            index_map[adj[neighbor][j]] = 0;
        }
    }
    return res;
}

ld edge_sampling(mt19937 &eng, uniform_int_distribution<int> &dis, int &iter, int &alpha) {
    ld ans = 0;
    for (; iter < alpha; iter++) {
        int random_edge = dis(eng);
        int a = list_of_edges[random_edge].first;
        int b = list_of_edges[random_edge].second;
        ans += fast_exact_BFC_per_edge(a, b);
    }
    return ans;
}

ld fast_edge_sampling(mt19937 &eng, uniform_int_distribution<int> &dis, int &iter, int &alpha) {
    ld res = 0;
    for (; iter < alpha; iter++) {
        int random_edge = dis(eng);
        int a = list_of_edges[random_edge].first;
        int b = list_of_edges[random_edge].second;
        if (sum_deg_neighbors[a] > sum_deg_neighbors[b]) {
            swap(a, b);
        }
        if (SZ(adj[b]) + sum_deg_neighbors[a] * 2 > N_FAST_EDGE_BFC_ITERATIONS)
            res += randomized_BFC_per_edge(a, b);
        else
            res += fast_exact_BFC_per_edge(a, b);
    }
    return res;
}

ld vertex_sampling(uniform_int_distribution<ll> &dis, mt19937_64 &eng, int &mx, int &iter, int &alpha) {
    ld res = 0;
    for (; iter < alpha; iter++) {
        int random_vertex = dis(eng);
        res += exact_bfc_per_vertex(random_vertex);
    }
    return res;
}

void edge_sparsfication_time_tracker() {
    for (double prob = 0.012; prob < 1.0; prob *= 2) {
        vector<pair<ld, pair<ld, ld> > > aux_res;
        for (int i = 0; i < N_SPARSIFICATION_ITERATIONS; i++) {
            double beg_clock = clock();
            ld res = edge_saprsification(prob);
            double end_clock = clock();
            ld error = error_percent(res);
            double elpased_time = double(end_clock - beg_clock) / CLOCKS_PER_SEC;
            aux_res.push_back(make_pair(error, make_pair(elpased_time, res)));
        }

        sort(aux_res.begin(), aux_res.end());
        double elpased_time = aux_res[N_SPARSIFICATION_ITERATIONS / 2].second.first;
        ld Er = aux_res[N_SPARSIFICATION_ITERATIONS / 2].first;

        if (prob >= 1) {
            cout << elpased_time << " " << 1 << " " << 0 << endl;
            if (elpased_time < TIME_LIMIT_SPARSIFICATION) {
                cout << TIME_LIMIT << " " << 1 << " " << 0 << endl;
            } else {
                cout << elpased_time << " " << 1 << " " << 0 << endl;
            }
            break;
        } else {
            cout << elpased_time << " " << prob << " " << Er << " " << endl;
        }
        if (elpased_time >= TIME_LIMIT_SPARSIFICATION)
            break;
    }
}

void coloful_sparsification_time_tracker() {
    for (int num_clr = 10000;; num_clr /= 2.0) {
        double prob = 1. / num_clr;
        vector<pair<ld, pair<ld, ld> > > aux_ans;
        for (int i = 0; i < N_SPARSIFICATION_ITERATIONS; i++) {
            double beg = clock();
            ld res = colorful_sparsification(num_clr);
            double prob = 1. / num_clr;
            double end = clock();
            ld error = error_percent(res);
            double elapsed_time = double(end - beg) / CLOCKS_PER_SEC;
            aux_ans.push_back(make_pair(error, make_pair(elapsed_time, res)));
        }
        sort(aux_ans.begin(), aux_ans.end());
        double elapsed_time = aux_ans[N_SPARSIFICATION_ITERATIONS / 2].second.first;
        ld error = aux_ans[N_SPARSIFICATION_ITERATIONS / 2].first;
        if (prob >= 1) {
            cout << elapsed_time << " " << 1 << " " << 0 << endl;
            if (elapsed_time < TIME_LIMIT_SPARSIFICATION)
                cout << TIME_LIMIT << " " << 1 << " " << 0 << endl;
            else
                cout << elapsed_time << " " << 1 << " " << 0 << endl;

            break;
        } else
            cout << elapsed_time << " " << prob << " " << error << endl;
        if (elapsed_time >= TIME_LIMIT_SPARSIFICATION)
            break;
    }
}

void edge_sampling_time_tracker() {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> dis(0, n_edges - 1);
    double elapsed_time = 0;
    ld res = 0;
    vector<ld> total_res;
    for (int alpha = 10, iter = 0;; alpha += 10) {
        double cur_elapsed_time = 0;
        vector<pair<ld, pair<ld, ld> > > aux_res;
        double res_from_previous_iterations = 0;
        for (int i = 0; i < SZ(total_res); i++) {
            res_from_previous_iterations += (total_res[i] / 4.0) / alpha;
        }
        int previous_iteration = iter;
        for (int k = 0; k < ITERATIONS_SAMPLING; k++) { // run the algorithm ITERATION times
            iter = previous_iteration;
            double cur_beg_clock = clock();
            res = edge_sampling(eng, dis, iter, alpha);
            double cur_end_clock = clock();
            cur_elapsed_time = double(cur_end_clock - cur_beg_clock) / CLOCKS_PER_SEC;
            ld ans = (res / 4.0) / alpha;
            ans += res_from_previous_iterations;
            ans *= n_edges;
            ld error = error_percent(ans);
            aux_res.push_back(make_pair(error, make_pair(cur_elapsed_time, res)));
        }
        sort(aux_res.begin(), aux_res.end()); // take the median
        cur_elapsed_time = aux_res[ITERATIONS_SAMPLING / 2].second.first;
        ld error = aux_res[ITERATIONS_SAMPLING / 2].first;
        elapsed_time += cur_elapsed_time;

        total_res.push_back(aux_res[ITERATIONS_SAMPLING / 2].second.second);
        cout << elapsed_time << " " << iter << " " << error << endl;
        if (elapsed_time >= TIME_LIMIT) {
            cout << alpha << endl;
            break;
        }
    }
}

void fast_edge_sampling_time_tracker() {
    random_device rd;
    mt19937 genedg(rd());
    uniform_int_distribution<int> dis(0, n_edges - 1);
    double elapsed_time = 0;
    ld res = 0;
    vector<ld> total_res;
    for (int alpha = 1000, iter = 0;; alpha += 1000) {
        double cur_elapsed_time = 0;
        vector<pair<ld, pair<ld, ld> > > aux_res;
        double res_from_previous_iterations = 0;
        for (int i = 0; i < SZ(total_res); i++) {
            res_from_previous_iterations += (total_res[i] / 4.0) / alpha;
        }
        int previous_iterations = iter;
        for (int k = 0; k < ITERATIONS_SAMPLING; k++) { // run the algorithm ITERATION times
            iter = previous_iterations;
            double cur_beg_clock = clock();
            res = fast_edge_sampling(genedg, dis, iter, alpha);
            double cur_end_clock = clock();
            double cur_elapsed_time = double(cur_end_clock - cur_beg_clock) / CLOCKS_PER_SEC;
            ld ans = (res / 4.0) / (alpha);
            ans += res_from_previous_iterations;
            ans *= n_edges;
            ld error = error_percent(ans);
            aux_res.push_back(make_pair(error, make_pair(cur_elapsed_time, res)));
        }
        sort(aux_res.begin(), aux_res.end()); // take the median
        cur_elapsed_time = aux_res[ITERATIONS_SAMPLING / 2].second.first;
        ld error = aux_res[ITERATIONS_SAMPLING / 2].first;
        elapsed_time += cur_elapsed_time;
        total_res.push_back(aux_res[ITERATIONS_SAMPLING / 2].second.second);

        cout << elapsed_time << " " << iter << " " << error << endl;
        if (elapsed_time >= TIME_LIMIT) {
            cout << alpha << endl;
            break;
        }
    }
}

void vertex_sampling_time_tracker() {
    vector<int> cnt_vertex(n_vertices);
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<ll> dis(0, n_vertices - 1);
    double elapsed_time = 0;
    ld res = 0;
    vector<ld> total_res;
    int mx = 0;
    for (int alpha = 10, iter = 0;; alpha += 10) {
        double cur_elaped_time = 0;
        vector<pair<ld, pair<ld, ld> > > aux_res;
        double res_from_previous_iterations = 0;
        for (int I = 0; I < SZ(total_res); I++) {
            res_from_previous_iterations += (total_res[I] / 4.0) / alpha;
        }
        int previous_iterations = iter;
        for (int k = 0; k < ITERATIONS_SAMPLING; k++) { // run the algorithm ITERATION times
            iter = previous_iterations;
            double cur_beg_clock = clock();
            res = vertex_sampling(dis, eng, mx, iter, alpha);
            double cur_end_clock = clock();
            double cur_elapsed_time = double(cur_end_clock - cur_beg_clock) / CLOCKS_PER_SEC;
            ld ans = (res / 4.0) / alpha;
            ans += res_from_previous_iterations;
            ans *= n_vertices;
            ld error = error_percent(ans);
            aux_res.push_back(make_pair(error, make_pair(cur_elaped_time, res)));
        }
        sort(aux_res.begin(), aux_res.end()); // take the median
        cur_elaped_time = aux_res[ITERATIONS_SAMPLING / 2].second.first;
        ld error = aux_res[ITERATIONS_SAMPLING / 2].first;
        elapsed_time += cur_elaped_time;
        total_res.push_back(aux_res[ITERATIONS_SAMPLING / 2].second.second);

        cout << elapsed_time << " " << iter << " " << aux_res[ITERATIONS_SAMPLING / 2].first << endl;
        if (elapsed_time >= TIME_LIMIT) {
            cout << alpha << endl;
            break;
        }
    }
}

void wedge_sampling_time_tracker() {
    clock_t beg_clock_n_wedge = clock();
    ll n_wedges = compute_n_wedges();
    clock_t end_clock_n_wedge = clock();
    double time_n_wedges = double(end_clock_n_wedge - beg_clock_n_wedge) / CLOCKS_PER_SEC;
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<ll> dis(1, n_wedges);
    double total_elapsed_time = 0;
    ld res = 0;
    ld total = 0;
    vector<ld> total_res;
    for (int alpha = 1000, iter = 0;; alpha += 5000) {
        vector<pair<ld, pair<ld, ld> > > aux_res;
        ld res_sum_from_previous_results = 0;
        for (int i = 0; i < SZ(total_res); i++) {
            res_sum_from_previous_results += (total_res[i] / 4.0) / alpha;
        }
        ld cur_res = 0;
        int pre_iteration = iter;
        for (int k = 0; k < ITERATIONS_SAMPLING; k++) { // run the algorithm ITERATION times
            iter = pre_iteration;
            double beg = clock();
            res = wedge_sampling(dis, eng, iter, alpha, n_wedges);
            double end = clock();
            double cur_elapsed_time = double(end - beg) / CLOCKS_PER_SEC;
            cur_res = (res / 4.0) / alpha;
            cur_res += res_sum_from_previous_results;
            cur_res *= (ld) n_wedges;
            ld error = error_percent(cur_res);
            aux_res.push_back(make_pair(error, make_pair(cur_elapsed_time, res)));
        }
        sort(aux_res.begin(), aux_res.end()); // take the median
        double cur_elapsed_time = aux_res[ITERATIONS_SAMPLING / 2].second.first;
        ld error = aux_res[ITERATIONS_SAMPLING / 2].first;
        total_elapsed_time += cur_elapsed_time;
        total_res.push_back(aux_res[ITERATIONS_SAMPLING / 2].second.second);

        cout << cur_elapsed_time + time_n_wedges << " " << iter << " " << error << endl;
        if (total_elapsed_time + time_n_wedges >= TIME_LIMIT) {
            cout << "iterations: " << alpha << endl;
            break;
        }
    }
    return;
}

void fast_wedge_sampling_time_tracker() {
    clock_t beg_clock_n_wedge = clock();
    ll n_wedges = compute_n_wedges();
    clock_t end_clock_n_wedge = clock();
    double time_n_wedges = double(end_clock_n_wedge - beg_clock_n_wedge) / CLOCKS_PER_SEC;
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<ll> dis(1, n_wedges);
    double total_elapsed_time = 0;
    ld res = 0;
    ld total = 0;
    vector<ld> total_res;
    for (int alpha = 1000, iter = 0;; alpha += 5000) {
        double cur_elapsed_time = 0;
        vector<pair<ld, pair<ld, ld> > > aux_res;
        ld res = 0;
        int pre_iteration = iter;
        for (int k = 0; k < ITERATIONS_SAMPLING; k++) { // run the algorithm ITERATION times
            iter = pre_iteration;
            double beg = clock();
            res = fast_wedge_sampling(dis, eng, iter, alpha, n_wedges);
            double end = clock();
            double aux_elapsed_time = double(end - beg) / CLOCKS_PER_SEC;
            res += total;
            res /= 4.0;
            res /= alpha;
            res *= (ld) n_wedges;
            ld error = error_percent(res);
            aux_res.push_back(make_pair(error, make_pair(aux_elapsed_time, res)));
        }
        sort(aux_res.begin(), aux_res.end()); // take the median
        double aux_elapsed_time = aux_res[ITERATIONS_SAMPLING / 2].second.first;
        ld error = aux_res[ITERATIONS_SAMPLING / 2].first;
        total_elapsed_time += aux_elapsed_time;
        total += aux_res[ITERATIONS_SAMPLING / 2].second.second;

        cout << total_elapsed_time + time_n_wedges << " " << iter << " " << error << endl;
        if (total_elapsed_time + time_n_wedges >= TIME_LIMIT) {
            cout << "iterations: " << alpha << endl;
            break;
        }
    }
    return;
}

void exact_algorithm_time_tracker() {
    double beg_clock = clock();
    exact_n_bf = exact_butterfly_counting(adj);
    double end_clock = clock();
    double elapsed_time = (end_clock - beg_clock) / CLOCKS_PER_SEC;
    cout << " Exact algorithm is done in " << elapsed_time << " secs. There are " << exact_n_bf << " butterflies."
         << endl;
}

string algorithm_names[8] = {"Exact", "Edge Sampling", "Fast Edge Sampling", "Vertex Sampling", "Wedge Sampling",
                             "Edge Sparsification", "Colorful Sparsification"};

void read_the_graph() {
    clear_everything();
    cerr << " Insert the input (bipartite network) file location" << endl;
    cerr << " >>> ";
    cin >> input_address;
    cerr << " Insert the output file" << endl;
    cerr << " >>> ";
    cin >> output_address;
    freopen(output_address, "w", stdout);
    cerr
            << " ---------------------------------------------------------------------------------------------------------------------- \n";
    cerr << "| * Note that edges should be separated line by line.\n\
| In each line, the first integer number is considered as a vertex in the left partition of bipartite network, \n\
| and the second integer number is a vertex in the right partition. \n\
| In addition, multiple edges are removed from the given bipartite network.\n\
| Also, note that in this version of the source code, we did NOT remove vertices with degree zero.\n";
    cerr
            << " ---------------------------------------------------------------------------------------------------------------------- \n";

    cerr << " Processing the graph ... (please wait) \n";

    get_graph();

    cerr << " -------------------------------------------------------------------------- \n";
    cerr << " The graph is processed - there are " << n_vertices << " vertices and " << n_edges << " edges  \n";
    cerr << " -------------------------------------------------------------------------- \n";
}

void choose_algorithm() {
    string s;
    while (true) {
        cerr << " Insert one of the following numbers (1-7): \n\
	 [1]: Exact Algorithm \n\
	 [2]: Edge Sampling Algorithm \n\
	 [3]: Fast Edge Sampling Algorithm \n\
	 [4]: Vertex Sampling Algorithm \n\
	 [5]: Wedge Sampling Algorithm \n\
	 [6]: Edge Sparsification Algorithm \n\
	 [7]: Colorful Sparsification Algorithm \n";
        cerr << " >>> ";
        cin >> s;
        if (SZ(s) == 1 && s[0] >= '0' && s[0] <= '7') break;
    }
    int chosen = s[0] - '0';
    if (chosen > 1) {
        cerr << " " << algorithm_names[chosen - 1]
             << " Algorithm is a randomized algorithm. To report the accuracy, we need exact number of butterflies"
             << endl;
        cerr
                << " Insert the number of butterflies. In the case, you do not know the number of butterflies, insert \"N\".\n We will run the exact algorithm for you."
                << endl;
        string comm;
        cerr << " >>> ";
        cin >> comm;
        read_the_graph();
        if (all_num(comm)) {
            stringstream ss;
            ss << comm;
            ss >> exact_n_bf;
        } else {
            cerr
                    << " As you do not know the exact number of butterflies, we are going to run the exact algorithm ... \n";
            exact_algorithm_time_tracker();
        }
    } else {
        read_the_graph();
    }

    cerr << " " << algorithm_names[chosen - 1] << " Algorithm is running ... (please wait) " << endl;
    if (chosen == 1) {
        exact_algorithm_time_tracker();
    } else {
        if (chosen <= 5)
            cout << "Time(sec) #Iterations Error(%)" << endl;
        else
            cout << "Time(sec) Probability Error(%)" << endl;
        if (chosen == 2) {
            edge_sampling_time_tracker();
        } else if (chosen == 3) {
            fast_edge_sampling_time_tracker();
        } else if (chosen == 4) {
            vertex_sampling_time_tracker();
        } else if (chosen == 5) {
            wedge_sampling_time_tracker();
        } else if (chosen == 6) {
            edge_sparsfication_time_tracker();
        } else if (chosen == 7) {
            coloful_sparsification_time_tracker();
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    choose_algorithm();
    cerr << " Take a look at the output file ..." << endl;
    return 0;
}