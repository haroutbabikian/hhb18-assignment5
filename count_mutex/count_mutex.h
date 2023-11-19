#ifndef COUNT_MUTEX_H
#define COUNT_MUTEX_H

#include <pthread.h>

extern int *array;
extern int length;
extern int count;
extern int num_threads;

void *count1s_thread_mutex(void *arg);
void generate_random_array();
int verify_count();
void run_tests_mutex(int num_threads);

#endif