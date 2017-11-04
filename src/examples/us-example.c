#include <stdio.h>
#include <unistd.h>
#include "../../include/user-simple.h"

void *us_func1(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na func1, %d\n", i);
        sleep(1);
    }
    us_schedule();
}

void *us_func2(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na func2, %d\n", i);
        sleep(1);
    }
    us_schedule();
}

int main(int argc, char *argv[])
{
    us_create(us_func1, "us1 args");
    us_create(us_func2, "us2 args");

    us_schedule();

    int i;
    for (i = 0; i < 10; i++)
    {
        printf("estou na main, %d\n", i);
        sleep(1);
    }

    return 0;
}