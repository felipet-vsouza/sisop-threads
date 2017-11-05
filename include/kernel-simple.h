#ifndef KERNEL_LEVEL_SIMPLE_H_
#define KERNEL_LEVEL_SIMPLE_H_

void ks_schedule(void);

int ks_create(void *(*fn)(void *), void *arg);

#endif