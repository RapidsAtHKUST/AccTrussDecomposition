/*!
\file
\brief This file contains routines for reading in the data set
\date Started 5/10/2017
\author George
\version\verbatim $Id: io.c 21138 2017-06-08 03:33:03Z karypis $ \endverbatim
*/

#include "kt.h"
#include "yche/yche_helper.h"
#include "yche/log.h"


/**************************************************************************/
/*! Reads the input data */
/**************************************************************************/
vault_t *loadData(params_t *params) {
    vault_t *vault;

    vault = (vault_t *) gk_malloc(sizeof(vault_t), "loadData: vault");
    memset(vault, 0, sizeof(vault_t));

    gk_startwctimer(vault->timer_io);
    /* read the graph */
    log_trace("Reading graph %s...", params->infile);
//    GKASSERT(gk_fexists(params->infile));

    switch (params->iftype) {

        case IFTYPE_TSV:
            vault->graph = gk_graph_Read(params->infile, GK_GRAPH_FMT_IJV, 1, 1, 0, 0, 0);
            gk_free((void **) &(vault->graph->iadjwgt), LTERM);
            break;

        case IFTYPE_METIS:
            vault->graph = gk_graph_Read(params->infile, GK_GRAPH_FMT_METIS, -1, -1, 0, 0, 0);
            break;

        default:
            vault->graph = gk_graph_Read_bin_edge_lst(params->infile);
//            errexit("Unknown iftype of %d\n", params->iftype);
    }
    gk_stopwctimer(vault->timer_io);

    return vault;
}


/**************************************************************************/
/*! Writes the k-truss decomposition */
/**************************************************************************/
void writeResults(params_t *params, vault_t *vault) {
    ssize_t ei;
    FILE *fpout;

    if (params->outfile == NULL)
        return;

    fpout = gk_fopen(params->outfile, "w", "fpout");
    for (ei = 0; ei < vault->nedges; ei++) {
        fprintf(fpout, "%7d %7d %4d\n",
                gk_min(vault->ktedges[ei].vi, vault->ktedges[ei].vj) + 1,
                gk_max(vault->ktedges[ei].vi, vault->ktedges[ei].vj) + 1,
                vault->ktedges[ei].k);
    }
    gk_fclose(fpout);
}
