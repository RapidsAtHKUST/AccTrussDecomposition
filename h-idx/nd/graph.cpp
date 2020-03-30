#include <util/log/log.h>
#include <util/graph/graph_bin_input_helper.h>
#include "main.h"

#define MAXLINE 1000000
#define WRITE_BINARY

static int really_read(std::istream &is, char *buf, size_t global_size) {
    char *temp2 = buf;
    while (global_size != 0) {
        is.read(temp2, global_size);
        size_t s = is.gcount();
        if (!is)
            return -1;

        global_size -= s;
        temp2 += s;
    }
    return 0;
}

template<typename VtxType, typename EdgeType>
void writeBinary(char *filename, VtxType nVtx, EdgeType nEdge, vector<vector<VtxType>> &graph) {

    string str(filename);
    string fl = str + ".bin";
    FILE *filep = fopen(fl.c_str(), "w");
    int vtxt = sizeof(VtxType);
    int edget = sizeof(EdgeType);
    fwrite(&vtxt, sizeof(int), 1, filep);
    fwrite(&edget, sizeof(int), 1, filep);

    fwrite(&nVtx, sizeof(VtxType), 1, filep);
    fwrite(&nEdge, sizeof(EdgeType), 1, filep);

    for (VtxType i = 0; i < nVtx; i++) {
        auto sz = graph[i].size();
        fwrite(&sz, sizeof(EdgeType), 1, filep);
    }

    for (VtxType i = 0; i < nVtx; i++)
        fwrite(&(graph[i][0]), sizeof(VtxType), graph[i].size(), filep);

    fclose(filep);
}

template<typename VtxType, typename EdgeType>
void readBinary(char *filename, vector<vector<VtxType>> &graph, EdgeType *nEdge) {

    ifstream in(filename);
    int vtxsize; //in bytes
    int edgesize; //in bytes

    //reading header
    in.read((char *) &vtxsize, sizeof(int));
    in.read((char *) &edgesize, sizeof(int));

    if (!in) {
        cerr << "IOError" << endl;
        return;
    }

    if (vtxsize != sizeof(VtxType)) {
        cerr << "Incompatible VertexSize." << endl;
        return;
    }

    if (edgesize != sizeof(EdgeType)) {
        cerr << "Incompatible EdgeSize." << endl;
        return;
    }

    vertex nVtx;
    in.read((char *) &nVtx, sizeof(VtxType));
    in.read((char *) nEdge, sizeof(EdgeType));

    graph.resize(nVtx);
    EdgeType *pxadj = (EdgeType *) malloc(sizeof(EdgeType) * nVtx);
    really_read(in, (char *) pxadj, sizeof(EdgeType) * nVtx);
    for (vertex i = 0; i < nVtx; i++) {
        graph[i].resize(pxadj[i]);
        really_read(in, (char *) &(graph[i][0]), sizeof(VtxType) * pxadj[i]);
    }
}

template<typename VtxType, typename EdgeType>
void readEdgeList(bool mm, char *filename, Graph &graph, EdgeType *nEdge) {
    char *line = (char *) malloc(sizeof(char) * MAXLINE);
    FILE *matfp = fopen(filename, "r");

    // skip comments
    do
        fgets(line, MAXLINE, matfp);
    while (line[0] == '%' || line[0] == '#');

    VtxType nVtx;
    vector<couple> coords;
    VtxType u, v, nv = 0;
    stringstream ss(line);
    if (mm) {
        ss >> nVtx >> *nEdge;
        printf("|V|: %d   |E|: %d\n", nVtx, *nEdge);
    } else {
        ss >> u >> v;
        nv = max(nv, (max(u, v)));
        if (u != v) {
            coords.push_back(make_tuple(u, v));
            coords.push_back(make_tuple(v, u));
        }
    }

    while (fgets(line, MAXLINE, matfp)) {
        stringstream ss(line);
        ss >> u >> v;
        nv = max(nv, (max(u, v)));
        if (u != v) {
            coords.push_back(make_tuple(u, v));
            coords.push_back(make_tuple(v, u));
        }
    }
    fclose(matfp);

    if (mm) {
        if (nVtx != nv + 1) {
            printf("nVtx in header (%d) is wrong, must be %d\n", nVtx, nv + 1);
            nVtx = nv + 1;
        }
    } else
        nVtx = nv + 1;

    sort(coords.begin(), coords.end());

    // begin constructing graph
    graph.resize(nVtx);
    EdgeType i = 0;
    graph[get<0>(coords[i])].push_back(get<1>(coords[i]));
    for (i = 1; i < coords.size(); i++)
        if (coords[i] != coords[i - 1])
            graph[get<0>(coords[i])].push_back(get<1>(coords[i]));

    // sort each neighbor list
    EdgeType ne = 0;
    for (auto v : graph) {
        sort(v.begin(), v.end());
        ne += v.size();
    }
    *nEdge = ne / 2;

    if (mm) {
        if (*nEdge != ne / 2) {
            printf("nEdge in header (%d) is wrong, must be %d\n", *nEdge, ne / 2);
            *nEdge = ne / 2;
        }
    } else
        *nEdge = ne / 2;
}

template<typename VtxType, typename EdgeType>
void readGraph(char *filename, vector<vector<VtxType>> &graph, EdgeType *nEdge) {
    string st(filename);
    string gname = st.substr(st.find_last_of('/') + 1);
    int idx = gname.find_last_of('.');
    if (idx == -1 || ((gname.size() >= (idx + 2)) && (gname[idx + 1] == '5'))) {
        log_info("Read Dir Edge List: %s", filename);
        int nVtx = 0;
        int *adj = nullptr;
        uint32_t *xadj = nullptr;
        uint32_t num_edges = 0;
        readDirectory(filename, nVtx, num_edges, adj, xadj);
        *nEdge = num_edges;

        // Copy to the graph.
        graph.resize(nVtx);
        assert(xadj[nVtx] == num_edges * 2);
#pragma omp parallel for schedule(dynamic, 1000)
        for (auto u = 0; u < nVtx; u++) {
            graph[u].resize(xadj[u + 1] - xadj[u]);
            memcpy(&graph[u].front(), adj + xadj[u], (xadj[u + 1] - xadj[u]) * sizeof(int));
        }
        free(adj);
        free(xadj);
    } else {
        string ext = gname.substr(idx);
        if (ext == ".bin")
            readBinary<VtxType, EdgeType>(filename, graph, nEdge);
        else if (ext == ".mtx")
            readEdgeList<VtxType, EdgeType>(true, filename, graph, nEdge);
        else
            readEdgeList<VtxType, EdgeType>(false, filename, graph, nEdge);
#ifdef WRITE_BINARY
        if (ext != ".bin") {
            vertex nVtx = graph.size();
            writeBinary<VtxType, EdgeType>(filename, nVtx, *nEdge, graph);
            printf("Binary graph is written\n");
        }
#endif
    }
}

template void readGraph(char *filename, vector<vector<vertex>> &graph, edge *nEdge);

