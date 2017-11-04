#ifndef USER_LEVEL_SIMPLE_H_
#define USER_LEVEL_SIMPLE_H_

void us_schedule(void);

void us_exit(void);

int us_create(void *(*fn)(void *), void *arg);

#endif