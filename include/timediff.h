#ifndef TIMEDIFF_H_
#define TIMEDIFF_H_

typedef struct timediff_t timediff_t;
void init_timecounter(timediff_t **diff);
void start_timecount(timediff_t **diff);
void end_timecount(timediff_t **diff);
float get_timecount(timediff_t **diff);

#endif
