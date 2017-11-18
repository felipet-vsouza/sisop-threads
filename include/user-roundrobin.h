#ifndef USER_LEVEL_ROUNDROBIN_H_
#define USER_LEVEL_ROUNDROBIN_H_

void urr_schedule(void);
int urr_create(void *(*fn)(void *), void *arg);

#endif