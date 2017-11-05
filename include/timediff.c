#include <time.h>
#include <stdlib.h>

struct timediff_t
{
    struct timespec *tstart;
    struct timespec *tend;
};

typedef struct timediff_t timediff_t;

void init_timecounter(timediff_t **diff)
{
    *diff = (timediff_t *)malloc(sizeof(timediff_t));
    (*diff)->tstart = (struct timespec *)malloc(sizeof(struct timespec));
    (*diff)->tend = (struct timespec *)malloc(sizeof(struct timespec));
}

void start_timecount(timediff_t **diff)
{
    (*diff)->tstart->tv_sec = 0;
    (*diff)->tstart->tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, (*diff)->tstart);
}

void end_timecount(timediff_t **diff)
{
    (*diff)->tend->tv_sec = 0;
    (*diff)->tend->tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, (*diff)->tend);
}

float get_timecount(timediff_t **diff)
{
    return ((double)1.0e-3 * (*diff)->tend->tv_nsec) -
           ((double)1.0e-3 * (*diff)->tstart->tv_nsec);
}