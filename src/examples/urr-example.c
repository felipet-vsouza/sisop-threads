#include <stdio.h>
#include <unistd.h>
#include "../../include/user-roundrobin.h"

void *urr_func1(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na func1, %d\n", i);
        sleep(1);
    }
}

void *urr_func2(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na func2, %d\n", i);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    urr_create(urr_func1, "urr1 args");
    urr_create(urr_func2, "urr2 args");

    urr_schedule();

    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na main, %d\n", i);
        sleep(1);
    }

    return 0;
}