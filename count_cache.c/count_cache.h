#ifndef COUNT_PRIVATE_H
#define COUNT_PRIVATE_H

#include <pthread.h>
#include <stdio.h>

extern int *array;
extern int length;
extern int num_threads;

// Define the cache line size
#define CACHE_LINE_SIZE 32768

// Struct to fill the cache line
typedef struct {
    int private_count;
    char padding[CACHE_LINE_SIZE - sizeof(int)];
} PrivateCount;

extern PrivateCount *private_counts;

void *count1s_thread_private(void *arg);
void generate_random_array();
int verify_count();
void run_tests_private(int num_threads, FILE *csv_file);

#endif