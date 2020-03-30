#ifndef _ULIB_H_
#define _ULIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <fcntl.h>
#include <limits.h>
#include <float.h>


#define umax(a, b)      (((a) >= (b)) ? (a) : (b))
#define umin(a, b)      (((a) >= (b)) ? (b) : (a))


#ifdef __cplusplus
extern "C" {
#endif
/* --------------------- Exit : Functions ---------------------------- */
void errexit(const char *fmt,...);
double u_wseconds(void);


void uprintf(const char *f_str,...);
void * umalloc(long size, const char * msg);
int * imalloc(long size, const char * msg);
void ufree(void *ptr1,...);
#define usfree(ptr)  { if (ptr) free(ptr); }

FILE *ufopen(const char * fname, const char * mode, const char * msg);
void ufclose(FILE *fp);


#ifdef __cplusplus
}
#endif
#endif
