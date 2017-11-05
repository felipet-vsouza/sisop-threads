#include <ucontext.h>

#define STACK_SIZE 1024
#define THREADS_MAX 8

int current = 0;

typedef struct us_threads_t
{
    int used;
    ucontext_t context;
    char stack[STACK_SIZE];
    void *(*func)(void *arg);
    void *arg;
    void *exit_status;
} us_threads_t;

static us_threads_t us_threads[THREADS_MAX];

void us_schedule(void)
{
    int i;
    for (i = (current + 1) % THREADS_MAX; i != current; i = (i + 1) % THREADS_MAX)
        if (us_threads[i].used)
            break;

    int prev = current;
    current = i;
    swapcontext(&us_threads[prev].context, &us_threads[current].context);
}

void us_exit(void)
{
    void *exit_status = us_threads[current].func(us_threads[current].arg);
    us_threads[current].exit_status = exit_status;
    us_threads[current].used = 0;
    us_schedule();
}

int us_create(void *(*start_routine)(void *), void *arg)
{
    static int last_used = 0;
    int i, tid;

    for (i = (last_used + 1) % THREADS_MAX; i != last_used; i = (i + 1) % THREADS_MAX)
        if (!us_threads[i].used)
            break;
    if (i == last_used)
        return -1;
    last_used = i;
    tid = i;

    getcontext(&us_threads[tid].context);
    us_threads[tid].context.uc_stack.ss_sp = us_threads[tid].stack;
    us_threads[tid].context.uc_stack.ss_size = sizeof(us_threads[tid].stack);
    us_threads[tid].context.uc_link = &us_threads[0].context;

    us_threads[i].used = 1;
    us_threads[i].func = start_routine;
    us_threads[i].arg = arg;
    us_threads[i].exit_status = 0;

    makecontext(&us_threads[i].context, us_exit, 1, arg);
    return 0;
}