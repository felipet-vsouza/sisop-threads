#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000

struct arr_count_t
{
    unsigned int array[ARRAY_SIZE];
    unsigned int result;
};

typedef struct arr_count_t arr_count_t;

void initialize_data(arr_count_t **data)
{
    *data = (arr_count_t *)malloc(sizeof(arr_count_t));
    unsigned int i;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        (*data)->array[i] = i;
    }
    (*data)->result = 0;
}

void *count_array_from_half_to_start(void *arg)
{
    arr_count_t **data = (arr_count_t **)arg;
    unsigned int count = 0;
    for (int i = (ARRAY_SIZE / 2) - 1; i >= 0; i--)
    {
        count = count + (*data)->array[i];
    }
    (*data)->result = (*data)->result + count;
}

void *count_array_from_half_to_end(void *arg)
{
    arr_count_t **data = (arr_count_t **)arg;
    unsigned int count = 0;
    for (int i = (ARRAY_SIZE / 2); i < ARRAY_SIZE; i++)
    {
        count = count + (*data)->array[i];
    }
    (*data)->result = (*data)->result + count;
}

/**
 * Data processing wrappers created due to necessity to call pthread_exit
*/
void *ks_count_array_from_half_to_start(void *arg)
{
    count_array_from_half_to_start(arg);
    pthread_exit(NULL);
}

void *ks_count_array_from_half_to_end(void *arg)
{
    count_array_from_half_to_start(arg);
    pthread_exit(NULL);
}