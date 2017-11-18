#include <stdio.h>
#include <time.h>
#include "../include/user-simple.h"
#include "../include/user-roundrobin.h"
#include "../include/kernel-simple.h"
#include "../include/data_helper.h"
#include "../include/timediff.h"

/**
 * Analytical data process functions
*/
void us_process(arr_count_t **data);
void urr_process(arr_count_t **data);
void urr_process_double(arr_count_t **data);
void ks_process(arr_count_t **data);
void ks_process_double(arr_count_t **data);

static timediff_t *diff;

int main(int argc, char *argv[])
{
    arr_count_t *data;

    // User level threads
    printf("User level:\n");
    us_process(&data);
    urr_process(&data);
    urr_process_double(&data);

    // Kernel level threads
    printf("\nKernel level:\n");
    ks_process(&data);
    ks_process_double(&data);

    return 0;
}

void us_process(arr_count_t **data)
{
    initialize_data(data);
    init_timecounter(&diff);
    start_timecount(&diff);

    us_create(count_array_from_half_to_end, data);
    us_schedule();
    count_array_from_half_to_start(data);

    end_timecount(&diff);
    printf("O processamento com threads simples a nível usuário levou %.5f us.\n", get_timecount(&diff));
}

void urr_process(arr_count_t **data)
{
    initialize_data(data);
    init_timecounter(&diff);
    start_timecount(&diff);

    urr_create(count_array_from_half_to_end, data);
    urr_schedule();
    count_array_from_half_to_start(data);

    end_timecount(&diff);
    printf("O processamento com threads a nível usuário usando round robin levou %.5f us.\n", get_timecount(&diff));
}

void urr_process_double(arr_count_t **data)
{
    initialize_data(data);
    init_timecounter(&diff);
    start_timecount(&diff);

    urr_create(count_array_from_half_to_end, data);
    urr_create(count_array_from_half_to_start, data);
    urr_schedule();

    end_timecount(&diff);
    printf("O processamento com threads duplas a nível usuário usando round robin levou %.5f us.\n", get_timecount(&diff));
}

void ks_process(arr_count_t **data)
{
    initialize_data(data);
    init_timecounter(&diff);
    start_timecount(&diff);

    ks_create(ks_count_array_from_half_to_end, data);
    ks_schedule();
    count_array_from_half_to_start(data);

    end_timecount(&diff);
    printf("O processamento com threads simples a nível kernel levou %.5f us.\n", get_timecount(&diff));
}

void ks_process_double(arr_count_t **data)
{
    initialize_data(data);
    init_timecounter(&diff);
    start_timecount(&diff);

    ks_create(ks_count_array_from_half_to_end, data);
    ks_create(ks_count_array_from_half_to_start, data);
    ks_schedule();

    end_timecount(&diff);
    printf("O processamento com threads duplas a nível kernel levou %.5f us.\n", get_timecount(&diff));
}