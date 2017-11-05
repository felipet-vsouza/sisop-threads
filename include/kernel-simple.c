#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

typedef struct ks_threads_t
{
    int used;
    pthread_t tid;
    void *(*func)(void *arg);
    void *arg;
    void *exit_status;
} ks_threads_t;

static int current = 0;
static ks_threads_t ks_threads[NUM_THREADS];

void ks_schedule(void)
{
    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        if (ks_threads[i].used)
        {
            int te = pthread_create(&ks_threads[i].tid, NULL, ks_threads[i].func, ks_threads[i].arg);
            if (te)
            {
                perror("Erro na criação de thread!");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int ks_create(void *(*fn)(void *), void *arg)
{
    int i = 0;
    for (i = (current + 1) % NUM_THREADS; i != current; i = (i + 1) % NUM_THREADS)
        if (!ks_threads[i].used)
            break;
    if (i == current)
        return -1;
    current = i;

    ks_threads[current].used = 1;
    ks_threads[current].func = fn;
    ks_threads[current].arg = arg;
    ks_threads[current].exit_status = 0;

    return 0;
}