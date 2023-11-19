#include "count_mutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define ARRAY_SIZE 1000000 // Change this based on your experimentation
#define NUM_TESTS 100

int *array;
int length = ARRAY_SIZE;
int count = 0;
int num_threads = 1; // Change this based on your experimentation

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

void *count1s_thread(void *arg) {
    long thread_id = (long)arg;
    int chunk_size = length / num_threads;
    int start = thread_id * chunk_size;
    int end = (thread_id == num_threads - 1) ? length : (thread_id + 1) * chunk_size;

    for (int i = start; i < end; i++) {
        if (array[i] == 1) {
            count++;
        }
    }

    pthread_exit(NULL);
}

void generate_random_array() {
    array = (int *)malloc(length * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 6; // Values between 0 and 5
    }
}

int verify_count() {
    int verified_count = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] == 1) {
            verified_count++;
        }
    }
    return verified_count;
}

void *count1s_thread_mutex(void *arg) {
    long thread_id = (long)arg;
    int chunk_size = length / num_threads;
    int start = thread_id * chunk_size;
    int end = (thread_id == num_threads - 1) ? length : (thread_id + 1) * chunk_size;

    for (int i = start; i < end; i++) {
        if (array[i] == 1) {
            pthread_mutex_lock(&count_mutex);
            count++;
            pthread_mutex_unlock(&count_mutex);
        }
    }

    pthread_exit(NULL);
}

void run_tests_mutex(int threads) {
    int correct_counts = 0;

    for (int test = 1; test <= NUM_TESTS; test++) {
        generate_random_array();

        num_threads = threads;
        count = 0;
        pthread_t threads[num_threads];
        clock_t start, end;

        start = clock();

        // Create threads with mutex
        for (long i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, count1s_thread_mutex, (void *)i);
        }

        // Join threads
        for (long i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        end = clock();

        // Verify the count
        int verified_count = verify_count();
        if (count == verified_count) {
            correct_counts++;
        }

        // Print data for each test
        printf("Test: %d, Threads: %d, Time: %f seconds, Count: %d (Verified: %d)\n",
               test, num_threads, ((double)(end - start)) / CLOCKS_PER_SEC, count, verified_count);

        free(array);
    }

    // Print overall correctness rate
    printf("\nCorrectness rate: %d/%d\n", correct_counts, NUM_TESTS);
}

int main() {
    // Run tests with different number of threads
    for (num_threads = 1; num_threads <= 32; num_threads *= 2) {
        printf("\nRunning tests with %d threads:\n", num_threads);
        run_tests_mutex(num_threads);
    }

    return 0;
}