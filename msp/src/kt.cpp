/*!
\file
\brief The various k-truss decomposition routines
\date Started 6/3/2017
\author George
\version\verbatim $Id: cmdline.c 20946 2017-05-10 23:12:48Z karypis $ \endverbatim
*/
extern "C"
{
#include "kt.h"
}

#include "yche/log.h"
#include "yche/core_histogram.h"

#define hfun1(vi, vj, i, range) \
           (((ssize_t)(((((ssize_t)vi)+5)^((ssize_t)vj)*(((ssize_t)vi>>32)+1)^((ssize_t)vj<<7)) + (i)*((1+((ssize_t)vi>>3)+1)^((ssize_t)vj<<5))))%range)


#ifndef DYNAMIC_CHUNK
#define DYNAMIC_CHUNK 16
#endif

/*************************************************************************/
/*! Determine the iperm for the key order using counting sort.
*/
/*************************************************************************/
int32_t *gk_i32kvipermi(int32_t n, gk_i32kv_t *cand) {
    int i, j, k, range;
    int32_t *counts, *iperm;

    for (range = 0, i = 0; i < n; i++) {
        if (cand[i].key > range)
            range = cand[i].key;
    }
    range++;

    counts = gk_i32smalloc(range + 1, 0, "counts");
    for (i = 0; i < n; i++)
        counts[cand[i].key]++;
    MAKECSR(i, range, counts);

    iperm = gk_i32smalloc(n, 0, "iperm");
    for (i = 0; i < n; i++)
        iperm[counts[cand[i].key]++] = i;

    gk_free((void **) &counts, LTERM);

    return iperm;
}


/*************************************************************************/
/*! Reorder the vertices in the graph in inc degree and return the upper
    triangular part of the reordered graph in which the adjancency lists
    are sorted in increasing order.
*/
/*************************************************************************/
gk_graph_t *kt_PreprocessAndExtractUpper(params_t *params, vault_t *vault) {
    int32_t vi, vj, vk, nvtxs;
    ssize_t ei, eiend, ej, ejend, nedges;
    ssize_t *xadj, *uxadj;
    int32_t *adjncy, *uadjncy, *perm = NULL, *iperm = NULL;
    gk_i32kv_t *cand = NULL;
    gk_graph_t *graph;

    nvtxs = vault->graph->nvtxs;
    xadj = vault->graph->xadj;
    adjncy = vault->graph->adjncy;

    cand = gk_i32kvmalloc(nvtxs, "cand");
    for (vi = 0; vi < nvtxs; vi++) {
        cand[vi].key = (int32_t) (xadj[vi + 1] - xadj[vi]);
        cand[vi].val = vi;
    }

    perm = vault->perm = gk_i32smalloc(nvtxs, -1, "perm");   /* perm[old-vtx-num]  => new-vtx-num */
    iperm = vault->iperm = gk_i32kvipermi(nvtxs, cand);        /* iperm[new-vtx-num] => old-vtx-num */
    for (vi = 0; vi < nvtxs; vi++)
        perm[iperm[vi]] = vi;


    /* create the reordered/sorted upper triangular portion of the graph */
    graph = gk_graph_Create();
    graph->nvtxs = nvtxs;
    graph->xadj = uxadj = gk_zmalloc(nvtxs + 1, "uxadj");
    graph->adjncy = uadjncy = gk_i32malloc(10 + (xadj[nvtxs] >> 1), "uadjncy");

    uxadj[0] = nedges = 0;
    for (vi = 0; vi < nvtxs; vi++) {
        vj = iperm[vi];
        for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
            //assert(adjncy[ej] < nvtxs);
            if ((vk = perm[adjncy[ej]]) > vi) /* keep only the upper part */
                uadjncy[nedges++] = vk;
        }
        uxadj[vi + 1] = nedges;

        if (nedges - uxadj[vi] > 1)
            gk_i32sorti(nedges - uxadj[vi], uadjncy + uxadj[vi]);  /* sort adjncy list */
    }
    log_debug("Upper nedges: %zu out of %zu", uxadj[nvtxs], xadj[nvtxs]);

    gk_free((void **) &cand, LTERM);

    return graph;
}


/*************************************************************************/
/*! Creates the transpose of the upper-triangular graph with location
    offsets at +1 locations.
    This is used for the JIK algorithm.
*/
/*************************************************************************/
gk_graph_t *kt_TransposeUforJIK(params_t *params, gk_graph_t *graph) {
    int32_t vi, vj, nvtxs;
    ssize_t ei, eiend, nedges;
    ssize_t *xadj, *txadj;
    int32_t *adjncy, *tadjncy;
    gk_graph_t *tgraph;

    nvtxs = graph->nvtxs;
    xadj = graph->xadj;
    adjncy = graph->adjncy;

    tgraph = gk_graph_Create();
    tgraph->nvtxs = nvtxs;
    tgraph->xadj = txadj = gk_zsmalloc(nvtxs + 1, 0, "txadj");
    tgraph->adjncy = tadjncy = gk_i32malloc(2 * (xadj[nvtxs] + 1), "tadjncy");

    for (vi = 0; vi < nvtxs; vi++) {
        if (xadj[vi + 1] - xadj[vi] < 2)
            continue;
        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend - 1; ei++)
            txadj[adjncy[ei]] += 2;
    }
    MAKECSR(vi, nvtxs, txadj);

    for (vi = 0; vi < nvtxs; vi++) {
        if (xadj[vi + 1] - xadj[vi] < 2)
            continue;

        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend - 1; ei++) {
            vj = adjncy[ei];
            tadjncy[txadj[vj]++] = vi;
            tadjncy[txadj[vj]++] = ei - xadj[vi] + 1;  /* row-offset */
        }
    }
    SHIFTCSR(vi, nvtxs, txadj);

    return tgraph;
}


/*************************************************************************/
/*! Checks if the supports computed by the TC code is correct.
*/
/*************************************************************************/
void kt_CheckInitialSupport(params_t *params, vault_t *vault) {
    int32_t uvi, vi, vik, vj, vjk, vk, nvtxs, nh;
    ssize_t uei, ei, ej;
    ssize_t *xadj, *uxadj;
    int32_t *adjncy, *uadjncy, *uadjwgt;
    int32_t *map;

    nvtxs = vault->graph->nvtxs;
    xadj = vault->graph->xadj;
    adjncy = vault->graph->adjncy;

    uxadj = vault->ugraph->xadj;
    uadjncy = vault->ugraph->adjncy;
    uadjwgt = vault->ugraph->iadjwgt;

    map = gk_i32smalloc(nvtxs, -1, "map");

    for (uvi = 0; uvi < nvtxs; uvi++) {
        vi = vault->iperm[uvi];
        for (ei = xadj[vi]; ei < xadj[vi + 1]; ei++)
            map[adjncy[ei]] = vi;

        for (uei = uxadj[uvi]; uei < uxadj[uvi + 1]; uei++) {
            vj = vault->iperm[uadjncy[uei]];
            nh = uadjwgt[uei];
            for (ej = xadj[vj]; ej < xadj[vj + 1]; ej++)
                nh -= (map[adjncy[ej]] == vi ? 1 : 0);

            GKASSERT(nh == 0);
        }
    }

    gk_free((void **) &map, LTERM);
}

/*************************************************************************/
/*! Checks if the supports computed by the TC code is correct.
*/
/*************************************************************************/
void kt_CheckKTrussDecomposition(params_t *params, vault_t *vault) {
    int32_t k, vi, vj, vk, nvtxs, knvtxs, nh;
    ssize_t ei, ej, nedges;
    ssize_t *xadj;
    int32_t *adjncy;
    int32_t *map;
    ktedge_t *ktedges;

    nvtxs = vault->graph->nvtxs;
    nedges = vault->nedges;
    ktedges = vault->ktedges;

    for (k = 1; k <= vault->ktmax; k++) {
        xadj = gk_zsmalloc(nvtxs + 1, 0, "xadj");
        for (ei = 0; ei < nedges; ei++) {
            if (ktedges[ei].k >= k) {
                xadj[ktedges[ei].vi]++;
                xadj[ktedges[ei].vj]++;
            }
        }
        for (knvtxs = 0, vi = 0; vi < nvtxs; vi++)
            knvtxs += (xadj[vi] > 0 ? 1 : 0);
        MAKECSR(vi, nvtxs, xadj);

        adjncy = gk_i32malloc(xadj[nvtxs], "adjncy");
        for (ei = 0; ei < nedges; ei++) {
            if (ktedges[ei].k >= k) {
                adjncy[xadj[ktedges[ei].vi]++] = ktedges[ei].vj;
                adjncy[xadj[ktedges[ei].vj]++] = ktedges[ei].vi;
            }
        }
        SHIFTCSR(vi, nvtxs, xadj);

        map = gk_i32smalloc(nvtxs, -1, "map");
        for (vi = 0; vi < nvtxs; vi++) {
            for (ei = xadj[vi]; ei < xadj[vi + 1]; ei++)
                map[adjncy[ei]] = vi;

            for (ei = xadj[vi]; ei < xadj[vi + 1]; ei++) {
                vj = adjncy[ei];
                for (nh = 0, ej = xadj[vj]; ej < xadj[vj + 1]; ej++)
                    nh += (map[adjncy[ej]] == vi ? 1 : 0);

                GKASSERT(nh >= k);
            }
        }

        log_debug("k-truss: %4d, nvtxs: %7d, nedges: %8zu", k + 2, knvtxs, xadj[nvtxs]);

        gk_free((void **) &xadj, &adjncy, &map, LTERM);
    }
}


/*************************************************************************/
/*! Takes the sups[] array associated with the edges and creates the
    ktedges information in the vault.
*/
/*************************************************************************/
void kt_Sups2KTEdges(params_t *params, vault_t *vault, int32_t ktmax, int32_t *sups) {
    int32_t vi, nvtxs;
    ssize_t ei, eiend, ej, nedges;
    ssize_t *xadj;
    int32_t *adjncy, *adjwgt;

    if (params->outfile == NULL)
        return;

    nvtxs = vault->ugraph->nvtxs;
    xadj = vault->ugraph->xadj;
    adjncy = vault->ugraph->adjncy;
    adjwgt = vault->ugraph->iadjwgt;

    vault->nedges = xadj[nvtxs];
    vault->ktmax = ktmax;
    vault->ktedges = (ktedge_t *) gk_malloc(xadj[nvtxs] * sizeof(ktedge_t), "ktedges");

    for (ej = 0, nedges = 0, vi = 0; vi < nvtxs; vi++) {
        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend; ei++, ej++) {
            vault->ktedges[ej].vi = gk_min(vault->iperm[vi], vault->iperm[adjncy[ei]]);
            vault->ktedges[ej].vj = gk_max(vault->iperm[vi], vault->iperm[adjncy[ei]]);
            if (adjwgt[ei] > 0)
                vault->ktedges[ej].k = -sups[nedges++] + 2;
            else
                vault->ktedges[ej].k = 2;
        }
    }
}

/*************************************************************************/
/*! The hash-map-based edge-triangle-support counting routine that uses
    the JIK triangle enumeration scheme.

    This is the mapjikv2 tc version.
*/
/*************************************************************************/
int64_t kt_ComputeEdgeSupport(params_t *params, vault_t *vault) {
    int32_t vi, vj, vk, vl, nvtxs, nlocal;
    ssize_t ei, eiend, ej, ejstart, ejend;
    int64_t ntriangles, ntriangles2;
    ssize_t *xadj, *txadj;
    int32_t *adjncy, *tadjncy, *adjwgt;
    int32_t l, tnc, nc, hmsize, tlsize, tlstart, *hmap, *tmap;

    gk_startwctimer(vault->timer_2);

    nvtxs = vault->ugraph->nvtxs;
    xadj = vault->ugraph->xadj;
    adjncy = vault->ugraph->adjncy;
    adjwgt = vault->ugraph->iadjwgt;

    txadj = vault->lgraph->xadj;
    tadjncy = vault->lgraph->adjncy;


    /* determine the size of the hash-map and convert it into a format
       that is compatible with a bitwise AND operation */
    for (hmsize = 0, vi = 0; vi < nvtxs; vi++)
        hmsize = gk_max(hmsize, (int32_t) (xadj[vi + 1] - xadj[vi]));
    for (l = 1; hmsize > (1 << l); l++);
    hmsize = (1 << (l + 4)) - 1;
    hmap = gk_i32smalloc(hmsize + 1, -1, "hmap");
    log_debug("& compatible maximum hmsize: %""d", hmsize);

    /* determine the size of the tail-map and allocate memory for it */
    for (vi = (nvtxs >> 2); vi < nvtxs; vi++) {
        if ((txadj[vi + 1] - txadj[vi]) << 9 > vi)
            break;
        if ((xadj[vi + 1] - xadj[vi]) << 4 > nvtxs - vi)
            break;
    }
    tlsize = nvtxs - vi + 100;
    tlstart = nvtxs - tlsize;
    tmap = gk_i32smalloc(tlsize, -1, "tmap");
    tmap -= tlstart; /* make indexing simpler */
    log_debug("tlsize: %""d", tlsize);


    /* start counting triangles */
    if (params->dbglvl & 1)
        gk_startwctimer(vault->timer_4);

    /* use a combination of hmap and tmap */
    ntriangles = 0;
    hmsize = 0;
    tnc = 0;
    for (vj = 1; vj < tlstart; vj++) {
        if (xadj[vj + 1] == xadj[vj] || txadj[vj + 1] == txadj[vj])
            continue;

        /* if needed, increase the working hmsize */
        if ((xadj[vj + 1] - xadj[vj]) << 3 > 1 + (hmsize >> 4) + (hmsize >> 1)) {
            hmsize = xadj[vj + 1] - xadj[vj];
            for (l = 1; hmsize > (1 << l); l++);
            hmsize = (1 << (l + 4)) - 1;

            if (params->dbglvl & 1) {
                gk_stopwctimer(vault->timer_4);
                log_debug("vj: %9d tlstart: %d degree: %5zu %7zu hmsize: %6d tnc: %7d time: %5.2lfs",
                          vj, tlstart, xadj[vj + 1] - xadj[vj], txadj[vj + 1] - txadj[vj],
                          hmsize, tnc, gk_getwctimer(vault->timer_4));
                tnc = 0;
                gk_clearwctimer(vault->timer_4);
                gk_startwctimer(vault->timer_4);
            }
        }

        /* hash Adj(vj) using hmap for the front and tmap for the last tlsize indices */
        for (nc = 0, ej = ejstart = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
            if ((vk = adjncy[ej]) >= tlstart)
                break;
            for (l = (vk & hmsize); hmap[l] != -1; l = ((l + 1) & hmsize), nc++);
            hmap[l] = ej - ejstart;
        }
        for (; ej < ejend; ej++)
            tmap[adjncy[ej]] = ej - ejstart;

        tnc += nc;

        /* find intersections */
        if (nc > 0) { /* we had collisions */
            for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                vi = tadjncy[ej];
                for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                    if ((vk = adjncy[ei]) >= tlstart)
                        break;
                    l = vk & hmsize;
                    if (hmap[l] == -1)
                        continue;
                    if (adjncy[ejstart + hmap[l]] == vk) {
                        adjwgt[ei]++;
                        adjwgt[ejstart + hmap[l]]++;
                        nlocal++;
                        continue;
                    }
                    for (l = ((l + 1) & hmsize);
                         hmap[l] != -1 && adjncy[ejstart + hmap[l]] != vk; l = ((l + 1) & hmsize));
                    if (hmap[l] != -1 && adjncy[ejstart + hmap[l]] == vk) {
                        adjwgt[ei]++;
                        adjwgt[ejstart + hmap[l]]++;
                        nlocal++;
                    }
                }
                for (; ei < eiend; ei++) {
                    if (tmap[adjncy[ei]] != -1) {
                        //assert(adjncy[ejstart+tmap[adjncy[ei]]] == adjncy[ei]);
                        adjwgt[ei]++;
                        adjwgt[ejstart + tmap[adjncy[ei]]]++;
                        nlocal++;
                    }
                }

                if (nlocal > 0) {
                    ntriangles += nlocal;

                    //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
                    adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                }
            }

            /* reset hmap/tmap */
            for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
                if ((vk = adjncy[ej]) >= tlstart)
                    break;
                for (l = (vk & hmsize); hmap[l] == -1 || adjncy[ejstart + hmap[l]] != vk; l = ((l + 1) & hmsize));
                hmap[l] = -1;
            }
            for (; ej < ejend; ej++)
                tmap[adjncy[ej]] = -1;
        } else { /* there were no collisons */
            for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                vi = tadjncy[ej];

                for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                    if ((vk = adjncy[ei]) >= tlstart)
                        break;
                    if (hmap[vk & hmsize] != -1 && adjncy[ejstart + hmap[vk & hmsize]] == vk) {
                        adjwgt[ei]++;
                        adjwgt[ejstart + hmap[vk & hmsize]]++;
                        nlocal++;
                    }
                }
                for (; ei < eiend; ei++) {
                    if (tmap[adjncy[ei]] != -1) {
                        //assert(adjncy[ejstart+tmap[adjncy[ei]]] == adjncy[ei]);
                        adjwgt[ei]++;
                        adjwgt[ejstart + tmap[adjncy[ei]]]++;
                        nlocal++;
                    }
                }

                if (nlocal > 0) {
                    ntriangles += nlocal;

                    //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
                    adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                }
            }

            /* reset hmap/tmap */
            for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
                if ((vk = adjncy[ej]) >= tlstart)
                    break;
                hmap[vk & hmsize] = -1;
            }
            for (; ej < ejend; ej++)
                tmap[adjncy[ej]] = -1;
        }
    }

    log_debug("ntriangles: %""lld", ntriangles);

    if (params->dbglvl & 1) {
        gk_stopwctimer(vault->timer_4);
        log_debug("vj: %9d tlstart: %lld degree: %5zu %7zu hmsize: %6d tnc: %7d time: %5.2lfs",
                  vj, tlstart, xadj[vj + 1] - xadj[vj], txadj[vj + 1] - txadj[vj],
                  hmsize, tnc, gk_getwctimer(vault->timer_4));
        tnc = 0;
        gk_clearwctimer(vault->timer_4);
        gk_startwctimer(vault->timer_4);
    }

    /* use tmap for the last tlsize rows */
    for (; vj < nvtxs; vj++) {
        if (1 || xadj[vj + 1] - xadj[vj] < nvtxs - vj - 1) {
            /* hash Adj(vj) */
            for (ej = ejstart = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++)
                tmap[adjncy[ej]] = ej - ejstart;

            /* find intersections */
            for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                vi = tadjncy[ej];
                for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                    if (tmap[adjncy[ei]] != -1) {
                        adjwgt[ei]++;
                        adjwgt[ejstart + tmap[adjncy[ei]]]++;
                        nlocal++;
                    }
                }

                if (nlocal > 0) {
                    ntriangles += nlocal;

                    //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
                    adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                }
            }

            /* reset tmap */
            for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++)
                tmap[adjncy[ej]] = -1;
        } else { /* the row is dense */  /* TODO: This has not been updated */
            tnc++;
            /* find intersections */
            for (nlocal = 0, ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                vi = tadjncy[ej];
                nlocal += xadj[vi + 1] - xadj[vi] - tadjncy[ej + 1];
            }
            ntriangles += nlocal;
        }
    }
    gk_stopwctimer(vault->timer_2);

    if (params->dbglvl & 1) {
        gk_stopwctimer(vault->timer_4);

        vj = nvtxs - 2;
        log_debug("vj: %9d tlstart: %d degree: %5zu %7zu hmsize: %6d tnc: %7d time: %5.2lfs",
                  vj, tlstart, xadj[vj + 1] - xadj[vj], txadj[vj + 1] - txadj[vj],
                  hmsize, tnc, gk_getwctimer(vault->timer_4));

        for (ntriangles2 = 0, ei = 0; ei < xadj[nvtxs]; ei++)
            ntriangles2 += adjwgt[ei];

        log_debug("Sanity check: ntriangles: %""d"" %""d"" %""d", ntriangles, ntriangles2 / 3, ntriangles2 % 3);
    }

    tmap += tlstart;
    gk_free((void **) &hmap, &tmap, LTERM);

    return ntriangles;
}



/*************************************************************************/
/*! This is the baseline serial version of k-truss decomposition.
*/
/*************************************************************************/
int64_t kt_serial(params_t *params, vault_t *vault) {
    struct edge_s {
        int32_t vi, vj;
        ssize_t eij, eji;
    } *edges;

    struct aii_s {
        int32_t vj;
        int32_t inc, dec;
    } *aii;

    struct xaii_s {
        int64_t start, end;
    } *xaii;

    struct slist_s {
        ssize_t neid, peid;
        int32_t sup;
    } *slist;

    int32_t vi, vik, vj, vjk, vk, nvtxs, nltriangles, sup;
    ssize_t ti, ei, eistart, eiend, ej, ejstart, ejend;
    int64_t nedges, nleft, ntriangles;
    ssize_t *xadj;
    int32_t *adjncy, *adjwgt;
    int32_t k, nsups, *sups;
    ssize_t *ids, *shead;
    ssize_t nupdates, nmaxupdates, *updindices;

    double timer_currk = 0.;

    gk_startwctimer(vault->timer_tcsetup);
    vault->ugraph = kt_PreprocessAndExtractUpper(params, vault);
    vault->lgraph = kt_TransposeUforJIK(params, vault->ugraph);

    nvtxs = vault->ugraph->nvtxs;
    xadj = vault->ugraph->xadj;
    adjncy = vault->ugraph->adjncy;

    /* where the support values will be stored */
    adjwgt = vault->ugraph->iadjwgt = gk_i32smalloc(xadj[nvtxs], 0, "adjwgt");
    gk_stopwctimer(vault->timer_tcsetup);

    gk_startwctimer(vault->timer_esupport);
    ntriangles = kt_ComputeEdgeSupportPar(params, vault);
    gk_stopwctimer(vault->timer_esupport);

#if VERBOSE
    log_debug("supports:\n");
    for(int v=0; v < nvtxs; ++v) {
      for(ssize_t e=xadj[v]; e < xadj[v+1]; ++e) {
        log_debug("(%2d, %2d) perm[%2d, %2d] = %d\n",
            v+1, adjncy[e]+1,
            vault->iperm[v]+1, vault->iperm[adjncy[e]]+1,
            adjwgt[e]);
      }
    }
#endif

    gk_startwctimer(vault->timer_ktsetup);
    /* determine the number of edges with non-zero support */
    for (nedges = 0, ei = 0, eiend = xadj[nvtxs]; ei < eiend; ei++) {
        if (adjwgt[ei] > 0)
            nedges++;
    }

    /* allocate memory for the adjancency lists, which in addition to the
       adjancent vertex it will store the decrement (for skip-list) and
       the ID for priority queue */
    xaii = (struct xaii_s *) gk_malloc((nvtxs + 1) * sizeof(struct xaii_s), "xaii");
    aii = (struct aii_s *) gk_malloc((2 * nedges + 1) * sizeof(struct aii_s), "aii");
    edges = (struct edge_s *) gk_malloc((nedges + 1) * sizeof(struct edge_s), "edges");
    sups = gk_i32malloc(nedges, "sups");
    ids = gk_zmalloc(2 * nedges + 1, "ids");

    for (vi = 0; vi < nvtxs; vi++)
        xaii[vi].start = 0;

    /* determine sizes */
    for (nedges = 0, vi = 0; vi < nvtxs; vi++) {
        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend; ei++) {
            if (adjwgt[ei] > 0) {
                xaii[vi].start++;
                xaii[adjncy[ei]].start++;

                edges[nedges].vi = vi;
                edges[nedges].vj = adjncy[ei];
                sups[nedges] = adjwgt[ei];
                nedges++;
            }
        }
    }
    /* the MAKECSR equivalent */
    for (vi = 1; vi < nvtxs; vi++)
        xaii[vi].start += xaii[vi - 1].start;
    for (vi = nvtxs; vi > 0; vi--)
        xaii[vi].start = xaii[vi - 1].start;
    xaii[0].start = 0;

    /* populate it into two steps to ensure that the sorted order is maintained */
    for (nedges = 0, vi = 0; vi < nvtxs; vi++) {
        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend; ei++) {
            if (adjwgt[ei] > 0) {
                vj = adjncy[ei];
                aii[xaii[vj].start].vj = vi;
                aii[xaii[vj].start].inc = 1;
                aii[xaii[vj].start].dec = 1;
                ids[xaii[vj].start] = nedges;
                edges[nedges].eji = xaii[vj].start++;
                nedges++;
            }
        }
    }
    for (nedges = 0, vi = 0; vi < nvtxs; vi++) {
        for (ei = xadj[vi], eiend = xadj[vi + 1]; ei < eiend; ei++) {
            if (adjwgt[ei] > 0) {
                aii[xaii[vi].start].vj = adjncy[ei];
                aii[xaii[vi].start].inc = 1;
                aii[xaii[vi].start].dec = 1;
                ids[xaii[vi].start] = nedges;
                edges[nedges].eij = xaii[vi].start++;
                nedges++;
            }
        }
    }
    /* the SHIFTCSR equivalent */
    for (vi = nvtxs; vi > 0; vi--)
        xaii[vi].start = xaii[vi - 1].start;
    xaii[0].start = 0;

    /* record the end in xaii[vi] and from now own, you will be using that */
    for (vi = 0; vi < nvtxs; vi++)
        xaii[vi].end = xaii[vi + 1].start;

    /* setup the support buckets and all associated information */
    nsups = gk_i32max(nedges, sups, 1) + 1;
    log_debug("nsups: %d", nsups);

    /* the heads and "link list" that form the support buckets */
    shead = gk_zsmalloc(nsups, -1, "shead");
    slist = (struct slist_s *) gk_malloc((nedges + 1) * sizeof(struct slist_s), "slist");

    slist++;  /* this is to allow slist[-1] to be valid */
    for (ei = 0; ei < nedges; ei++) {
        slist[ei].sup = sups[ei];
        slist[ei].peid = -1;
        slist[ei].neid = shead[sups[ei]];
        if (shead[sups[ei]] != -1)
            slist[shead[sups[ei]]].peid = ei;
        shead[sups[ei]] = ei;
    }

    nmaxupdates = nedges + 2 * nvtxs;
    updindices = gk_zmalloc(nmaxupdates, "updindices");

    gk_stopwctimer(vault->timer_ktsetup);


    log_debug("#triangles before peeling: %""d", ntriangles);
    ntriangles = 0;
    nleft = nedges;

    gk_startwctimer(vault->timer_ktpeeling);
    /* get into the k-truss enumeration loop */
    for (k = 1; k < nsups && nleft > 0; k++) {
        nltriangles = 0;
        gk_clearwctimer(timer_currk);
        gk_startwctimer(timer_currk);

        BACK:
        nupdates = 0;
        for (ti = shead[k]; ti != -1; ti = slist[ti].neid) {
            if (nupdates + 2 * nvtxs > nmaxupdates)
                break;

            nleft--;

            vi = edges[ti].vi;
            vj = edges[ti].vj;

#if 0
            log_debug("(%d %d) = %d\n", vi+1, vj+1, sups[ti]);
#endif

            /* remove the edge from both adjacency lists */
            ei = edges[ti].eij;
            if (ei == xaii[vi].start)
                xaii[vi].start += aii[ei].inc;
            else
                aii[ei - aii[ei].dec].inc += aii[ei].inc;
            if (ei == xaii[vi].end - 1)
                xaii[vi].end -= aii[ei].dec;
            else
                aii[ei + aii[ei].inc].dec += aii[ei].dec;

            ej = edges[ti].eji;
            if (ej == xaii[vj].start)
                xaii[vj].start += aii[ej].inc;
            else
                aii[ej - aii[ej].dec].inc += aii[ej].inc;
            if (ej == xaii[vj].end - 1)
                xaii[vj].end -= aii[ej].dec;
            else
                aii[ej + aii[ej].inc].dec += aii[ej].dec;


            if (sups[ti] > 0) {
                sup = sups[ti];

                nltriangles += sup;

                ei = xaii[vi].end - 1;
                eistart = xaii[vi].start;
                vik = aii[ei].vj;

                ej = xaii[vj].end - 1;
                ejstart = xaii[vj].start;
                vjk = aii[ej].vj;

                /* decrease the support of the intersection */
                while (ei >= eistart && ej >= ejstart) {
                    if (vik > vjk) {
                        ei -= aii[ei].dec;
                        vik = aii[ei].vj;
                    } else if (vjk > vik) {
                        ej -= aii[ej].dec;
                        vjk = aii[ej].vj;
                    } else {
                        updindices[nupdates++] = ids[ei];
                        updindices[nupdates++] = ids[ej];

                        sups[ids[ei]]--;
                        ei -= aii[ei].dec;
                        vik = aii[ei].vj;

                        sups[ids[ej]]--;
                        ej -= aii[ej].dec;
                        vjk = aii[ej].vj;

                        if (--sup == 0)
                            break;
                    }
                }
                GKASSERT(sup == 0);
            }

            sups[ti] = -k;  /* this is used for encoding the maximal value of k of that edge */
        }

        /* update the shead[k] information, for the subsequent updates */
        shead[k] = ti;
        slist[ti].peid = -1;


        /* add up sups[:] */
        int64_t total_sup = 0;
#pragma omp parallel for schedule(static) reduction(+:total_sup)
        for (int64_t e = 0; e < nedges; ++e) {
            if (sups[e] >= 0) {
                total_sup += sups[e];
            }
        }
#if VERBOSE
        log_debug("  edges-left: %7""d"" (%5.2f%%), total-support: %7""d",
            nleft, 100. * (double)nleft / (double)nedges, total_sup);
#endif

        if (nupdates > 0) {
            gk_startwctimer(vault->timer_4);
            for (ei = 0; ei < nupdates; ei++) {
                ti = updindices[ei];

                if (sups[ti] < 0 || sups[ti] == slist[ti].sup)
                    continue; /* we have already deleted or updated this */

                /* remove ti from its current list */
                sup = (slist[ti].sup <= k ? k : slist[ti].sup);  /* see the comment in the "add" */
                if (shead[sup] != ti) { /* if ti was not the head */
                    slist[slist[ti].peid].neid = slist[ti].neid;
                    slist[slist[ti].neid].peid = slist[ti].peid;
                } else {
                    shead[sup] = slist[ti].neid;
                    slist[slist[ti].neid].peid = -1;
                }

                /* add ti to the head of the new list */
                sup = (sups[ti] <= k ? k : sups[ti]);  /* put all the <k support into the support
                                                  list that we are currently operating on */
                slist[ti].sup = sups[ti];
                slist[ti].peid = -1;
                slist[ti].neid = shead[sup];
                slist[shead[sup]].peid = ti;
                shead[sup] = ti;
            }
            gk_stopwctimer(vault->timer_4);
            goto BACK;
        }

        gk_stopwctimer(timer_currk);

        /* add up sups[:] */
        total_sup = 0;
#pragma omp parallel for schedule(static) reduction(+:total_sup)
        for (int64_t e = 0; e < nedges; ++e) {
            if (sups[e] >= 0) {
                total_sup += sups[e];
            }
        }

        log_info("k: %7d; edges-left: %7""d"" (%5.2f%%), total-support: %7""d"", "
                 "nltriangles: %7d, time (s): %6.3f",
                 k + 2, nleft, 100. * (double) nleft / (double) nedges, total_sup,
                 nltriangles, timer_currk);
        gk_clearwctimer(timer_currk);

        ntriangles += nltriangles;
    }
    gk_stopwctimer(vault->timer_ktpeeling);

    log_debug("#triangles after peeling: %""d", ntriangles);

    /* create the output of the decomposition */
    kt_Sups2KTEdges(params, vault, k - 1, sups);
    core_val_histogram(nedges, sups, [](int sup) { return -sup; }, true);
    slist--;
    gk_free((void **) &edges, &aii, &xaii, &ids, &sups, &shead, &slist, &updindices, LTERM);

    return ntriangles;
}


/*************************************************************************/
/*! The hash-map-based edge-triangle-support counting routine that uses
    the JIK triangle enumeration scheme.

    This is the mapjikv2 tc version.
*/
/*************************************************************************/
int64_t kt_ComputeEdgeSupportPar(params_t *params, vault_t *vault) {
    int32_t vi, vj, vk, vl, nvtxs, nlocal;
    ssize_t ei, eiend, ej, ejstart, ejend;
    int64_t ntriangles, ntriangles2;
    ssize_t *xadj, *txadj;
    int32_t *adjncy, *tadjncy, *adjwgt;
    int32_t l, tnc, nc, hmsize, tlsize, tlstart;

    gk_startwctimer(vault->timer_2);

    nvtxs = vault->ugraph->nvtxs;
    xadj = vault->ugraph->xadj;
    adjncy = vault->ugraph->adjncy;
    adjwgt = vault->ugraph->iadjwgt;

    txadj = vault->lgraph->xadj;
    tadjncy = vault->lgraph->adjncy;

    /* determine the size of the hash-map and convert it into a format
       that is compatible with a bitwise AND operation */
    for (hmsize = 0, vi = 0; vi < nvtxs; vi++)
        hmsize = gk_max(hmsize, (int32_t) (xadj[vi + 1] - xadj[vi]));
    for (l = 1; hmsize > (1 << l); l++);
    hmsize = (1 << (l + 4)) - 1;
    log_debug("& compatible maximum hmsize: %""d", hmsize);

    /* determine the size of the tail-map and allocate memory for it */
    for (vi = (nvtxs >> 2); vi < nvtxs; vi++) {
        if ((txadj[vi + 1] - txadj[vi]) << 9 > vi)
            break;
        if ((xadj[vi + 1] - xadj[vi]) << 4 > nvtxs - vi)
            break;
    }
    tlsize = nvtxs - vi + 100;
    tlstart = nvtxs - tlsize;
    log_debug("tlsize: %""d", tlsize);
    log_debug("tlstart: %""d", tlstart);

    /* start counting triangles */
    if (params->dbglvl & 1)
        gk_startwctimer(vault->timer_4);

    /* use a combination of hmap and tmap */
    ntriangles = 0;
    tnc = 0;
#pragma omp parallel default(none) shared(xadj, txadj, hmsize, params, tlstart, tlsize, adjncy, tadjncy, adjwgt) private(nc, ej, ejstart, ejend, l, nlocal, vi, vk, ei, eiend) reduction(+:ntriangles) reduction(+:tnc)
    {

        int32_t *hmap = gk_i32smalloc(hmsize + 1, -1, "hmap");
        int32_t *tmap = gk_i32smalloc(tlsize, -1, "tmap");
        tmap -= tlstart; /* make indexing simpler */
        int32_t hmsizel = 0;

#pragma omp for schedule(dynamic, DYNAMIC_CHUNK)
        for (vj = 1; vj < tlstart; vj++) {
            if (xadj[vj + 1] == xadj[vj] || txadj[vj + 1] == txadj[vj])
                continue;

            /* if needed, increase the working hmsize */
            if ((xadj[vj + 1] - xadj[vj]) << 3 > 1 + (hmsizel >> 4) + (hmsizel >> 1)) {
                hmsizel = xadj[vj + 1] - xadj[vj];
                for (l = 1; hmsizel > (1 << l); l++);
                hmsizel = (1 << (l + 4)) - 1;
            }

            /* hash Adj(vj) using hmap for the front and tmap for the last tlsize indices */
            for (nc = 0, ej = ejstart = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
                if ((vk = adjncy[ej]) >= tlstart)
                    break;
                for (l = (vk & hmsizel); hmap[l] != -1; l = ((l + 1) & hmsizel), nc++);
                hmap[l] = ej - ejstart;
            }
            for (; ej < ejend; ej++)
                tmap[adjncy[ej]] = ej - ejstart;

            /* find intersections */
            if (nc > 0) { /* we had collisions */
                for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                    vi = tadjncy[ej];
                    for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                        if ((vk = adjncy[ei]) >= tlstart)
                            break;
                        l = vk & hmsizel;
                        if (hmap[l] == -1)
                            continue;
                        if (adjncy[ejstart + hmap[l]] == vk) {
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + hmap[l]]++;
                            nlocal++;
                            continue;
                        }
                        for (l = ((l + 1) & hmsizel);
                             hmap[l] != -1 && adjncy[ejstart + hmap[l]] != vk; l = ((l + 1) & hmsizel));
                        if (hmap[l] != -1 && adjncy[ejstart + hmap[l]] == vk) {
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + hmap[l]]++;
                            nlocal++;
                        }
                    }
                    for (; ei < eiend; ei++) {
                        if (tmap[adjncy[ei]] != -1) {
                            //assert(adjncy[ejstart+tmap[adjncy[ei]]] == adjncy[ei]);
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + tmap[adjncy[ei]]]++;
                            nlocal++;
                        }
                    }

                    if (nlocal > 0) {
                        ntriangles += nlocal;

                        //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
#pragma omp atomic
                        adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                    }
                }

                /* reset hmap/tmap */
                for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
                    if ((vk = adjncy[ej]) >= tlstart)
                        break;
                    for (l = (vk & hmsizel); hmap[l] == -1 || adjncy[ejstart + hmap[l]] != vk; l = ((l + 1) & hmsizel));
                    hmap[l] = -1;
                }
                for (; ej < ejend; ej++)
                    tmap[adjncy[ej]] = -1;
            } else { /* there were no collisons */
                for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                    vi = tadjncy[ej];

                    for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                        if ((vk = adjncy[ei]) >= tlstart)
                            break;
                        if (hmap[vk & hmsizel] != -1 && adjncy[ejstart + hmap[vk & hmsizel]] == vk) {
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + hmap[vk & hmsizel]]++;
                            nlocal++;
                        }
                    }
                    for (; ei < eiend; ei++) {
                        if (tmap[adjncy[ei]] != -1) {
                            //assert(adjncy[ejstart+tmap[adjncy[ei]]] == adjncy[ei]);
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + tmap[adjncy[ei]]]++;
                            nlocal++;
                        }
                    }

                    if (nlocal > 0) {
                        ntriangles += nlocal;

                        //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
#pragma omp atomic
                        adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                    }
                }

                /* reset hmap/tmap */
                for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++) {
                    if ((vk = adjncy[ej]) >= tlstart)
                        break;
                    hmap[vk & hmsizel] = -1;
                }
                for (; ej < ejend; ej++)
                    tmap[adjncy[ej]] = -1;
            }
        }

        tmap += tlstart;
        gk_free((void **) &hmap, &tmap, LTERM);
    }

    int32_t tlstart_idx = tlstart;
    if (tlstart < 0)
        tlstart_idx = 0;

#pragma omp parallel default(none) shared(nvtxs, tlstart, tlstart_idx, tlsize, xadj, txadj, adjncy, tadjncy, adjwgt) private(nlocal, ej, ejend, ejstart, vi, ei, eiend) reduction(+:ntriangles) reduction(+:tnc)
    {
        int32_t *tmap1 = gk_i32smalloc(tlsize, -1, "tmap1");
        tmap1 -= tlstart; /* make indexing simpler */

        /* use tmap for the last tlsize rows */
#pragma omp for schedule(dynamic, DYNAMIC_CHUNK)
        for (vj = tlstart_idx; vj < nvtxs; vj++) {
            if (1 || xadj[vj + 1] - xadj[vj] < nvtxs - vj - 1) {
                /* hash Adj(vj) */
                for (ej = ejstart = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++)
                    tmap1[adjncy[ej]] = ej - ejstart;

                /* find intersections */
                for (ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                    vi = tadjncy[ej];
                    for (nlocal = 0, ei = xadj[vi] + tadjncy[ej + 1], eiend = xadj[vi + 1]; ei < eiend; ei++) {
                        if (tmap1[adjncy[ei]] != -1) {
#pragma omp atomic
                            adjwgt[ei]++;
#pragma omp atomic
                            adjwgt[ejstart + tmap1[adjncy[ei]]]++;
                            nlocal++;
                        }
                    }

                    if (nlocal > 0) {
                        ntriangles += nlocal;

                        //assert(adjncy[xadj[vi]+tadjncy[ej+1]-1] == vj);
#pragma omp atomic
                        adjwgt[xadj[vi] + tadjncy[ej + 1] - 1] += nlocal;
                    }
                }

                /* reset tmap */
                for (ej = xadj[vj], ejend = xadj[vj + 1]; ej < ejend; ej++)
                    tmap1[adjncy[ej]] = -1;
            } else { /* the row is dense */  /* TODO: This has not been updated */
                tnc++;
                /* find intersections */
                for (nlocal = 0, ej = txadj[vj], ejend = txadj[vj + 1]; ej < ejend; ej += 2) {
                    vi = tadjncy[ej];
                    nlocal += xadj[vi + 1] - xadj[vi] - tadjncy[ej + 1];
                }
                ntriangles += nlocal;
            }
        }

        tmap1 += tlstart;
        gk_free((void **) &tmap1, LTERM);
    }
    gk_stopwctimer(vault->timer_2);

    return ntriangles;
}
