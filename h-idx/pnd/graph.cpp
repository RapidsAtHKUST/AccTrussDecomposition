#include "main.h"
#include "util/graph/graph_bin_input_helper.h"
#include "util/log/log.h"

#define MAXLINE INT_MAX
#define WRITE_BINARY

static int really_read(istream &is, char *buf, size_t global_size) {
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
void writeBinary(char *filename, VtxType nVtx, EdgeType nEdge, VtxType *adj, EdgeType *xadj) {

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
        EdgeType sz = xadj[i + 1] - xadj[i];
        fwrite(&sz, sizeof(EdgeType), 1, filep);
    }

    fwrite(adj, sizeof(VtxType), xadj[nVtx], filep);

    fclose(filep);
}

template<typename VtxType, typename EdgeType>
void readBinary(char *filename, VtxType *nVtx, EdgeType *nEdge, VtxType **adj, EdgeType **xadj) {

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
        cerr << "Incompatible VertexSize" << endl;
        return;
    }

    if (edgesize != sizeof(EdgeType)) {
        cerr << "Incompatible EdgeSize" << endl;
        return;
    }

    in.read((char *) nVtx, sizeof(VtxType)); // we already write this as +1
    in.read((char *) nEdge, sizeof(EdgeType));

    (*xadj) = (EdgeType *) malloc(sizeof(EdgeType) * (*nVtx + 1));
    (*adj) = (VtxType *) malloc(sizeof(VtxType) * (*nEdge * 2));

    (*xadj)[0] = 0;
    for (VtxType i = 0; i < *nVtx; i++) {
        EdgeType nt = 0;
        really_read(in, (char *) &nt, sizeof(EdgeType));
        (*xadj)[i + 1] = (*xadj)[i] + nt;
    }
    really_read(in, (char *) (*adj), sizeof(VtxType) * (*xadj)[*nVtx]);
}

template<typename VtxType, typename EdgeType>
void VV2CRS(vector<vector<VtxType>> &graph, VtxType *nVtx, EdgeType *nEdge, VtxType **adj, EdgeType **xadj) {
    EdgeType ei = 0;
    *xadj = (EdgeType *) malloc(sizeof(EdgeType) * (*nVtx + 1));
    *adj = (VtxType *) malloc(sizeof(VtxType) * (*nEdge * 2));
    (*xadj)[0] = 0;
    for (VtxType i = 0; i < *nVtx; i++) {
        (*xadj)[i + 1] = graph[i].size() + (*xadj)[i];
        for (VtxType j = 0; j < graph[i].size(); j++)
            (*adj)[ei++] = graph[i][j];
        graph[i].clear();
    }
    graph.clear();
}

template<typename VtxType, typename EdgeType>
void readEdgeList(bool mm, char *filename, VtxType *nVtx, EdgeType *nEdge, VtxType **adj, EdgeType **xadj) {
    char *line = (char *) malloc(sizeof(char) * MAXLINE);
    FILE *matfp = fopen(filename, "r");

    // skip comments
    do
        fgets(line, MAXLINE, matfp);
    while (line[0] == '%' || line[0] == '#');

    vector<couple> coords;
    VtxType u, v, nv = 0;
    stringstream ss(line);
    if (mm) {
        ss >> *nVtx >> *nEdge;
        log_info("|V|: '%d   |E|: '%d", *nVtx, *nEdge);
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
        if (*nVtx != nv + 1) {
            printf("nVtx in header (%d) is wrong, must be %d\n", *nVtx, nv + 1);
            *nVtx = nv + 1;
        }
    } else
        *nVtx = nv + 1;

    sort(coords.begin(), coords.end());

    // begin constructing graph
    vector<vector<VtxType>> graph(*nVtx);
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

    VV2CRS(graph, nVtx, nEdge, adj, xadj);
}

template<typename VtxType, typename EdgeType>
void readGraph(char *filename, VtxType *nVtx, EdgeType *nEdge, VtxType **adj, EdgeType **xadj) {
    string st(filename);
    string gname = st.substr(st.find_last_of('/') + 1);
    int idx = gname.find_last_of('.');

    log_info("idx: %d", idx);
    if (idx == -1 || ((gname.size() >= (idx + 2)) && (gname[idx + 1] == '5'))) {
        log_info("Read Dir Edge List: %s", filename);
//        readDirEdgeList(filename, *nVtx, *nEdge, *adj, *xadj);
        readDirectory(filename, *nVtx, *nEdge, *adj, *xadj);
    } else {
        string ext = gname.substr(idx);
        if (ext == ".bin")
            readBinary<VtxType, EdgeType>(filename, nVtx, nEdge, adj, xadj);
        else if (ext == ".mtx")
            readEdgeList<VtxType, EdgeType>(true, filename, nVtx, nEdge, adj, xadj);
        else if (ext == ".txt" || ext == ".tsv")
            readEdgeList<VtxType, EdgeType>(false, filename, nVtx, nEdge, adj, xadj);

#ifdef WRITE_BINARY
        if (ext != ".bin") {
            writeBinary<VtxType, EdgeType>(filename, *nVtx, *nEdge, *adj, *xadj);
            printf("Binary graph is written\n");
        }
#endif

    }
}

template void readGraph(char *filename, vertex *nVtx, edge *nEdge, vertex **adj, edge **xadj);

