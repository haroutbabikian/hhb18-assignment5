#ifndef COUNT_RACE_H
#define COUNT_RACE_H

#include <pthread.h>

extern int *array;
extern int length;
extern int count;
extern int num_threads;

void *count1s_thread(void *arg);
void generate_random_array();
int verify_count();
void run_tests();

#endif