/*!
\file
\brief This file contains various constant definitions
\date Started 5/10/17
\author George
\version\verbatim $Id: defs.h 21158 2017-06-10 22:36:08Z karypis $ \endverbatim
*/

#ifndef __DEF_H__
#define __DEF_H__

#define MAXLINE         1024*128
#define MAX_STRLEN      1024*128


/* command-line options */
#define CMD_KTTYPE              1
#define CMD_IFTYPE              3
#define CMD_LOGFILE             4

#define CMD_IBSIZE              10
#define CMD_JBSIZE              11

#define CMD_SEED                70
#define CMD_DBGLVL              100
#define CMD_HELP                200

/* kttypes */

typedef enum {
  KTTYPE_BASELINE,
  KTTYPE_MSP,
  KTTYPE_AND
} kttype_e;


/* iftype */
#define IFTYPE_TSV              1
#define IFTYPE_METIS            2
#define IFTYPE_BIN              3

/* The text labels for the different tctypes */
static char kttypenames[][20] = {"", "base", "msp", "and", ""};


/* The text labels for the different iftypes */
static char iftypenames[][10] = {"", "tsv", "metis", ""};

#endif

