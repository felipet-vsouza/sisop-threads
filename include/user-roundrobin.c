#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <ucontext.h>
#include <signal.h>

#define STACK_SIZE 1024
#define THREADS_MAX 8
#define S_PERIOD 1
#define U_PERIOD 0

void urr_schedule(void);
int urr_create(void *(*start_routine)(void *), void *arg);
void urr_exit(void);
void __schedule_timer(void);
void __schedule(int i);

typedef struct urr_threads_t
{
    int used;
    ucontext_t context;
    char stack[STACK_SIZE];
    void *(*func)(void *arg);
    void *arg;
    void *exit_status;
} urr_threads_t;

static urr_threads_t urr_threads[THREADS_MAX];
static int current = 0;
static struct itimerval timer;
static int __timer_scheduled = 0;

void urr_schedule(void)
{
    if (!__timer_scheduled)
        __schedule_timer();

    int i;
    for (i = (current + 1) % THREADS_MAX; i != current; i = (i + 1) % THREADS_MAX)
        if (urr_threads[i].used)
            break;

    int prev = current;
    current = i;
    swapcontext(&urr_threads[prev].context, &urr_threads[current].context);
}

void urr_exit(void)
{
    void *exit_status = urr_threads[current].func(urr_threads[current].arg);
    urr_threads[current].exit_status = exit_status;
    urr_threads[current].used = 0;
    urr_schedule();
}

int urr_create(void *(*start_routine)(void *), void *arg)
{
    static int last_used = 0;
    int i, tid;

    for (i = (last_used + 1) % THREADS_MAX; i != last_used; i = (i + 1) % THREADS_MAX)
        if (!urr_threads[i].used)
            break;
    if (i == last_used)
        return -1;
    last_used = i;
    tid = i;

    getcontext(&urr_threads[tid].context);
    urr_threads[tid].context.uc_stack.ss_sp = urr_threads[tid].stack;
    urr_threads[tid].context.uc_stack.ss_size = sizeof(urr_threads[tid].stack);
    urr_threads[tid].context.uc_link = &urr_threads[0].context;

    urr_threads[i].used = 1;
    urr_threads[i].func = start_routine;
    urr_threads[i].arg = arg;
    urr_threads[i].exit_status = 0;

    makecontext(&urr_threads[i].context, urr_exit, 1, arg);
    return 0;
}

void __schedule_timer(void)
{
    timer.it_value.tv_sec = S_PERIOD;
    timer.it_interval.tv_sec = S_PERIOD;
    timer.it_value.tv_usec = U_PERIOD;
    timer.it_interval.tv_usec = U_PERIOD;

    setitimer(ITIMER_REAL, &timer, 0);
    signal(SIGALRM, __schedule);

    __timer_scheduled = 1;
}

void __schedule(int i)
{
    urr_schedule();
}