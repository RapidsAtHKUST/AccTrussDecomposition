## Steps

1. tc-comp
2. allocate and init dynamic graph
3. allocate `s-buckets`
4. while loop on the buckets
    * intersection on the dynamic graph, update g and store bucket changes
    * remove edge from dynamic graph `aii` (both for u and v)
    * apply bucket changes on the doubly link list (remove and add)

### Notes

4.1 and 4.2 form the logic of Frontier Generation.
4.3 is the Support Update or Bucket Update.


## Codes

```cpp
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
```

```cpp
int64_t kt_serial(params_t *params, vault_t *vault)
{

  int32_t vi, vik, vj, vjk, vk, nvtxs, nltriangles, sup;
  ssize_t ti, ei, eistart, eiend, ej, ejstart, ejend;
  int64_t nedges, nleft, ntriangles;
  ssize_t *xadj;
  int32_t *adjncy, *adjwgt;
  int32_t k, nsups, *sups;
  ssize_t *ids, *shead;
  ssize_t nupdates, nmaxupdates, *updindices;

  vault->ugraph = kt_PreprocessAndExtractUpper(params, vault);
  vault->lgraph = kt_TransposeUforJIK(params, vault->ugraph);

  nvtxs  = vault->ugraph->nvtxs;
  xadj   = vault->ugraph->xadj;
  adjncy = vault->ugraph->adjncy;

  /* where the support values will be stored */
  adjwgt = vault->ugraph->iadjwgt = gk_i32smalloc(xadj[nvtxs], 0, "adjwgt");


  ntriangles = kt_ComputeEdgeSupportPar(params, vault);

  /* determine the number of edges with non-zero support */
  for (nedges=0, ei=0, eiend=xadj[nvtxs]; ei<eiend; ei++) {
    if (adjwgt[ei] > 0)
      nedges++;
  }

  /* allocate memory for the adjancency lists, which in addition to the
     adjancent vertex it will store the decrement (for skip-list) and
     the ID for priority queue */
  xaii  = (struct xaii_s *)gk_malloc((nvtxs+1)*sizeof(struct xaii_s), "xaii");
  aii   = (struct aii_s *)gk_malloc((2*nedges+1)*sizeof(struct aii_s), "aii");
  edges = (struct edge_s *)gk_malloc((nedges+1)*sizeof(struct edge_s), "edges");
  sups  = gk_i32malloc(nedges, "sups");
  ids   = gk_zmalloc(2*nedges+1, "ids");

  for (vi=0; vi<nvtxs; vi++)
    xaii[vi].start = 0;

  /* determine sizes */
  for (nedges=0, vi=0; vi<nvtxs; vi++) {
    for (ei=xadj[vi], eiend=xadj[vi+1]; ei<eiend; ei++) {
      if (adjwgt[ei] > 0) {
        xaii[vi].start++;
        xaii[adjncy[ei]].start++;

        edges[nedges].vi = vi;
        edges[nedges].vj = adjncy[ei];
        sups[nedges]     = adjwgt[ei];
        nedges++;
      }
    }
  }
  /* the MAKECSR equivalent */
  for (vi=1; vi<nvtxs; vi++)
    xaii[vi].start += xaii[vi-1].start;
  for (vi=nvtxs; vi>0; vi--)
    xaii[vi].start = xaii[vi-1].start;
  xaii[0].start = 0;

  /* populate it into two steps to ensure that the sorted order is maintained */
  for (nedges=0, vi=0; vi<nvtxs; vi++) {
    for (ei=xadj[vi], eiend=xadj[vi+1]; ei<eiend; ei++) {
      if (adjwgt[ei] > 0) {
        vj = adjncy[ei];
        aii[xaii[vj].start].vj  = vi;
        aii[xaii[vj].start].inc = 1;
        aii[xaii[vj].start].dec = 1;
        ids[xaii[vj].start]     = nedges;
        edges[nedges].eji       = xaii[vj].start++;
        nedges++;
      }
    }
  }
  for (nedges=0, vi=0; vi<nvtxs; vi++) {
    for (ei=xadj[vi], eiend=xadj[vi+1]; ei<eiend; ei++) {
      if (adjwgt[ei] > 0) {
        aii[xaii[vi].start].vj  = adjncy[ei];
        aii[xaii[vi].start].inc = 1;
        aii[xaii[vi].start].dec = 1;
        ids[xaii[vi].start]     = nedges;
        edges[nedges].eij       = xaii[vi].start++;
        nedges++;
      }
    }
  }
  /* the SHIFTCSR equivalent */
  for (vi=nvtxs; vi>0; vi--)
    xaii[vi].start = xaii[vi-1].start;
  xaii[0].start = 0;

  /* record the end in xaii[vi] and from now own, you will be using that */
  for (vi=0; vi<nvtxs; vi++)
    xaii[vi].end = xaii[vi+1].start;

  /* setup the support buckets and all associated information */
  nsups = gk_i32max(nedges, sups, 1) + 1;

  /* the heads and "link list" that form the support buckets */
  shead = gk_zsmalloc(nsups, -1, "shead");
  slist = (struct slist_s *)gk_malloc((nedges+1)*sizeof(struct slist_s), "slist");

  slist++;  /* this is to allow slist[-1] to be valid */
  for (ei=0; ei<nedges; ei++) {
    slist[ei].sup  = sups[ei];
    slist[ei].peid = -1;
    slist[ei].neid = shead[sups[ei]];
    if (shead[sups[ei]] != -1)
      slist[shead[sups[ei]]].peid = ei;
    shead[sups[ei]] = ei;
  }

  nmaxupdates = nedges + 2*nvtxs;
  updindices = gk_zmalloc(nmaxupdates, "updindices");

  ntriangles = 0;
  nleft      = nedges;

  /* get into the k-truss enumeration loop */
  for (k=1; k<nsups && nleft>0; k++) {
    nltriangles = 0;

BACK:
    nupdates = 0;
    for (ti=shead[k]; ti!=-1; ti=slist[ti].neid) {
      if (nupdates + 2*nvtxs > nmaxupdates)
        break;

      nleft--;

      vi = edges[ti].vi;
      vj = edges[ti].vj;

      /* remove the edge from both adjacency lists */
      ei = edges[ti].eij;
      if (ei == xaii[vi].start)
        xaii[vi].start += aii[ei].inc;
      else
        aii[ei-aii[ei].dec].inc += aii[ei].inc;
      if (ei == xaii[vi].end-1)
        xaii[vi].end -= aii[ei].dec;
      else
        aii[ei+aii[ei].inc].dec += aii[ei].dec;

      ej = edges[ti].eji;
      if (ej == xaii[vj].start)
        xaii[vj].start += aii[ej].inc;
      else
        aii[ej-aii[ej].dec].inc += aii[ej].inc;
      if (ej == xaii[vj].end-1)
        xaii[vj].end -= aii[ej].dec;
      else
        aii[ej+aii[ej].inc].dec += aii[ej].dec;


      if (sups[ti] > 0) {
        sup = sups[ti];

        nltriangles += sup;

        ei      = xaii[vi].end-1;
        eistart = xaii[vi].start;
        vik     = aii[ei].vj;

        ej      = xaii[vj].end-1;
        ejstart = xaii[vj].start;
        vjk     = aii[ej].vj;

        /* decrease the support of the intersection */
        while (ei >= eistart && ej >= ejstart) {
          if (vik > vjk) {
            ei  -= aii[ei].dec;
            vik  = aii[ei].vj;
          }
          else if (vjk > vik) {
            ej  -= aii[ej].dec;
            vjk  = aii[ej].vj;
          }
          else {
            updindices[nupdates++] = ids[ei];
            updindices[nupdates++] = ids[ej];

            sups[ids[ei]]--;
            ei  -= aii[ei].dec;
            vik  = aii[ei].vj;

            sups[ids[ej]]--;
            ej  -= aii[ej].dec;
            vjk  = aii[ej].vj;

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
    for(int64_t e = 0; e < nedges; ++e) {
      if(sups[e] >= 0) {
        total_sup += sups[e];
      }
    }

    if (nupdates > 0) {
      for (ei=0; ei<nupdates; ei++) {
        ti = updindices[ei];

        if (sups[ti] < 0 || sups[ti] == slist[ti].sup)
          continue; /* we have already deleted or updated this */

        /* remove ti from its current list */
        sup = (slist[ti].sup <= k ? k : slist[ti].sup);  /* see the comment in the "add" */
        if (shead[sup] != ti) { /* if ti was not the head */
          slist[slist[ti].peid].neid = slist[ti].neid;
          slist[slist[ti].neid].peid = slist[ti].peid;
        }
        else {
          shead[sup] = slist[ti].neid;
          slist[slist[ti].neid].peid = -1;
        }

        /* add ti to the head of the new list */
        sup = (sups[ti] <= k ? k : sups[ti]);  /* put all the <k support into the support
                                                  list that we are currently operating on */
        slist[ti].sup  = sups[ti];
        slist[ti].peid = -1;
        slist[ti].neid = shead[sup];
        slist[shead[sup]].peid = ti;
        shead[sup] = ti;
      }
      goto BACK;
    }

    /* add up sups[:] */
    total_sup = 0;
    #pragma omp parallel for schedule(static) reduction(+:total_sup)
    for(int64_t e = 0; e < nedges; ++e) {
      if(sups[e] >= 0) {
        total_sup += sups[e];
      }
    }
    ntriangles += nltriangles;
  }
  /* create the output of the decomposition */
  kt_Sups2KTEdges(params, vault, k-1, sups);

  slist--;
  gk_free((void **)&edges, &aii, &xaii, &ids, &sups, &shead, &slist, &updindices, LTERM);

  return ntriangles;
}
```
