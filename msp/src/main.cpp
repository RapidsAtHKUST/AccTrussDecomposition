/*!
\file
\brief The entry point of the triangle counting code
\date Started 5/10/2017
\author George
\version\verbatim $Id: cmdline.c 20946 2017-05-10 23:12:48Z karypis $ \endverbatim
*/

extern "C"
{
#include "kt.h"
#include <locale.h>
}

#include "yche/core_histogram.h"
#include "yche/log.h"

/*************************************************************************
* The entry point
**************************************************************************/
int main(int argc, char *argv[]) {
    setlocale(LC_NUMERIC, "");

    int64_t ntriangles = 0;
    params_t *params;
    vault_t *vault;

    params = getcmdline_params(argc, argv);

    setvbuf(stdout, NULL, _IOLBF, 0);

    vault = loadData(params);

    log_trace("----------------");
    log_trace("infile: %s", params->infile);
    log_trace("outfile: %s", (params->outfile ? params->outfile : "NULL"));
    log_trace("#nvtxs: %'d", vault->graph->nvtxs);
    log_trace("kttype: %s", kttypenames[params->kttype]);
    log_trace("jbsize: %d, ibsize: %d", params->jbsize, params->ibsize);

    /* perform various initializations */
    srand(params->seed);

    gk_startwctimer(vault->timer_global);

    /* perform the k-truss decomposition */
    switch (params->kttype) {
        case KTTYPE_BASELINE:
            ntriangles = kt_serial(params, vault);
            break;
        case KTTYPE_MSP:
            ntriangles = kt_msp(params, vault);
            break;
        case KTTYPE_AND:
            ntriangles = kt_and(params, vault);
            break;
        default:
            errexit("Unknown kttype of %d\n", params->kttype);
    }

    gk_stopwctimer(vault->timer_global);


    if (vault->ktedges && params->dbglvl & 8)
        kt_CheckKTrussDecomposition(params, vault);
    writeResults(params, vault);

    log_trace("#triangles: %"
                      PRId64
                      "; rate: %.4lf MT/sec", ntriangles,
              ((double) ntriangles) / ((double) 1e6 * gk_getwctimer(vault->timer_2)));
    log_trace("ktmax (k-2): %d", vault->ktmax);
    log_trace("----------------------------");
    if (gk_getwctimer(vault->timer_1) > 0)
        log_trace("   timer_1: %7.2lfs", gk_getwctimer(vault->timer_1));
    if (gk_getwctimer(vault->timer_2) > 0)
        log_trace("   timer_2: %7.2lfs", gk_getwctimer(vault->timer_2));
    if (gk_getwctimer(vault->timer_3) > 0)
        log_trace("   timer_3: %7.2lfs", gk_getwctimer(vault->timer_3));
    if (gk_getwctimer(vault->timer_4) > 0)
        log_trace("   timer_4: %7.2lfs", gk_getwctimer(vault->timer_4));
    if (gk_getwctimer(vault->timer_5) > 0)
        log_trace("   timer_5: %7.2lfs", gk_getwctimer(vault->timer_5));
    if (gk_getwctimer(vault->timer_6) > 0)
        log_trace("   timer_6: %7.2lfs", gk_getwctimer(vault->timer_6));
    log_trace("----------------------------");
    log_trace("       i/o: %7.2lfs", gk_getwctimer(vault->timer_io));
    log_trace("   tcsetup: %7.2lfs", gk_getwctimer(vault->timer_tcsetup));
    log_trace("  esupport: %7.2lfs", gk_getwctimer(vault->timer_esupport));
    log_trace("   ktsetup: %7.2lfs", gk_getwctimer(vault->timer_ktsetup));
    log_trace(" ktpeeling: %7.2lfs", gk_getwctimer(vault->timer_ktpeeling));
    log_trace("    wclock: %7.2lfs", gk_getwctimer(vault->timer_global));
    log_trace("----------------------------");

    log_trace("RUNRESULT: %s %s %"
                      PRId64
                      " %.2lf %.2lf %.2lf %.2lf %.2lf",
              params->infile,
              kttypenames[params->kttype],
              ntriangles,
              gk_getwctimer(vault->timer_tcsetup),
              gk_getwctimer(vault->timer_esupport),
              gk_getwctimer(vault->timer_ktsetup),
              gk_getwctimer(vault->timer_ktpeeling),
              gk_getwctimer(vault->timer_global)
    );
}

