#ifndef COUNT_PRIVATE_H
#define COUNT_PRIVATE_H

#include <pthread.h>
#include <stdio.h>

extern int *array;
extern int length;
extern int *private_counts;
extern int num_threads;

void *count1s_thread_private(void *arg);
void generate_random_array();
int verify_count();
void run_tests_private(int num_threads, FILE *csv_file);

#endif