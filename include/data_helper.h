#ifndef DATA_HELPER_H_
#define DATA_HELPER_H_

typedef struct arr_count_t arr_count_t;
void initialize_data(arr_count_t **data);
void *count_array_from_half_to_start(void *arg);
void *count_array_from_half_to_end(void *arg);
void *ks_count_array_from_half_to_start(void *arg);
void *ks_count_array_from_half_to_end(void *arg);
#endif
