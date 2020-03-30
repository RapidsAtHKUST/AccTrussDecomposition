#include "ulib.h"
#include <sys/time.h>

#define U_MB (1024*1024)

double u_wseconds(void)
{
#if defined(WIN32)
	return (double) timeGetTime() / 1000.0;
#else
	struct timeval tp;

	gettimeofday(&tp, NULL);

	return (double) tp.tv_sec + (double) tp.tv_usec / 1000000.0;
#endif
}

void * umalloc(long size, const char * msg)
{
	void * ptr;
	static long __u_tot_size=0;

	if (size == 0)
		return NULL;

	ptr = (void *) malloc(size);
	if (!ptr)
	{
		errexit("Memory allocation failed for '%s'.\nRequested size: %ld byte(s) [%.2lf MB]. Total allocated : %ld byte(s) [%.2lf MB]\n", msg, size, (double)size/(double)U_MB, __u_tot_size, (double)__u_tot_size/(double)U_MB);
	}
	__u_tot_size += size;

	return ptr;
}


void ufree(void *ptr1,...)
{
	va_list plist;
	void *ptr;

	va_start(plist, ptr1);

	while ((ptr = va_arg(plist, void *)) != NULL)
		usfree(ptr);

	va_end(plist);
}


int * imalloc(long size, const char * msg)
{
	int * ptr;

	ptr = (int * )umalloc(sizeof(int)*size, msg);
	return ptr;
}

#ifdef _DEBUG
static char _dbg_file_name[512];
#define DEFAULT_DEBUG_FILE "UMIT-DBG.TXT"
#endif

void uprintf(const char *f_str,...)
{
	va_list argp;
#ifdef _DEBUG
	char *name;
	static int cnt=0;
	FILE *ofp;
#endif

	fflush(stdout);
	fflush(stderr);
	va_start(argp, f_str);
	vfprintf(stdout, f_str, argp);
	va_end(argp);
	fflush(stdout);

	/* ugly: repeating udbgprintf here because I don't know how to call that */
#ifdef _DEBUG
	/* --------- print to debug file --------- */
	if (*_dbg_file_name)
		name = _dbg_file_name;
	else
		name = DEFAULT_DEBUG_FILE;

	if (cnt++==0)
	{
		time_t curtime;
		char    tst[26];

		ofp = ufopen(name, "w", "dbgprint");
		time(&curtime);
		strcpy(tst, ctime(&curtime));
		tst[24] = 0;
		fprintf(ofp, "\n\n\n----------------- %s -----------------\n\n", tst);
	}
	else
		ofp = ufopen(name, "a", "dbgprint");
	va_start(argp, f_str);
	vfprintf(ofp, f_str, argp);
	va_end(argp);
	ufclose(ofp);
#endif
}



/*************************************************************************
 * -------------------------- Error Exit ----------------------------------
 **************************************************************************/
void errexit(const char * f_str,...)
{
	va_list argp;

	fflush(stdout);
	fflush(stderr);
	fprintf(stderr, "\n****** Error:\n");
	va_start(argp, f_str);
	vfprintf(stderr, f_str, argp);
	va_end(argp);

	fprintf(stderr," ******\n");
	fflush(stderr);

	uprintf("Error in Execution\n");

	exit(1);
}


FILE *ufopen(const char * fname, const char * mode, const char * msg)
{
	FILE *fp;

	fp = fopen(fname, mode);
	if (fp != NULL)
		return fp;

	errexit("file: %s, mode: %s, [%s]", fname, mode, msg);
	return NULL;
}


void ufclose(FILE *fp)
{
	if (fp)
		fclose(fp);
}
