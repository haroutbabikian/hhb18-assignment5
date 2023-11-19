#include "count_cache.h"
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
PrivateCount *private_counts;


void *count1s_thread_private(void *arg) {
    long thread_id = (long)arg;
    int chunk_size = length / num_threads;
    int start = thread_id * chunk_size;
    int end = (thread_id == num_threads - 1) ? length : (thread_id + 1) * chunk_size;

    // Private count for each thread
    int private_count = 0;

    for (int i = start; i < end; i++) {
        if (array[i] == 1) {
            private_count++;
        }
    }

    // Store the private count in the array
    private_counts[thread_id].private_count = private_count;

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

void run_tests_private(int num_threads, FILE *csv_file) {
    int correct_counts = 0;

    for (int test = 1; test <= NUM_TESTS; test++) {
        generate_random_array();

        // Allocate memory for private counts array
        private_counts = (PrivateCount *)malloc(num_threads * sizeof(PrivateCount));

        pthread_t threads[num_threads];
        clock_t start, end;

        start = clock();

        // Create threads with private counts
        for (long i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, count1s_thread_private, (void *)i);
        }

        // Join threads
        for (long i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        // Aggregate private counts
        int total_count = 0;
        for (int i = 0; i < num_threads; i++) {
            total_count += private_counts[i].private_count;
        }

        end = clock();

        // Verify the count
        int verified_count = verify_count();
        if (total_count == verified_count) {
            correct_counts++;
        }

        // Print data for each test to CSV file
        fprintf(csv_file, "%d,%d,%f,%d,%d\n",
                test, num_threads, ((double)(end - start)) / CLOCKS_PER_SEC, total_count, verified_count);

        // Free memory for private counts array
        free(private_counts);
        free(array);
    }

    // Print overall correctness rate
    printf("\nCorrectness rate: %d/%d\n", correct_counts, NUM_TESTS);
}

int main() {
    FILE *csv_file = fopen("results_private.csv", "w");
    if (csv_file == NULL) {
        fprintf(stderr, "Error opening CSV file for writing.\n");
        return 1;
    }

    fprintf(csv_file, "Test,Threads,Time,Count,Verified\n");

    // Run tests with different numbers of threads
    for (num_threads = 1; num_threads <= 32; num_threads *= 2) {
        printf("\nRunning tests with %d threads:\n", num_threads);
        run_tests_private(num_threads, csv_file);
    }

    fclose(csv_file);

    return 0;
}