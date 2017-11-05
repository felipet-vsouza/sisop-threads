#include <stdio.h>
#include <time.h>
#include "../include/user-simple.h"
#include "../include/data_helper.h"
#include "../include/timediff.h"

/**
 * Analytical data process functions
*/
void us_process(arr_count_t **data);

static timediff_t *diff;

int main(int argc, char *argv[])
{
    arr_count_t *data;
    initialize_data(&data);

    us_process(&data);

    return 0;
}

void us_process(arr_count_t **data)
{
    init_timecounter(&diff);
    start_timecount(&diff);

    us_create(count_array_from_half_to_end, data);
    count_array_from_half_to_start(data);
    us_schedule();

    end_timecount(&diff);
    printf("O processamento com threads simples a nível usuário levou %.5f microsegundos.\n", get_timecount(&diff));
}