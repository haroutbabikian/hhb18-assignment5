#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

/**
 * NOTE: I immediately started with chunking the array. It was intuitive, since I've taken OS last year.
 * So I skipped the trivial solution, and started directly experimenting with different numbers of threads on
 * chunked arrays. I wrote the results to CSV files and plotted the data using python. The report is written in
 * Markdown.
**/

#define ARRAY_SIZE 1000 // Change this based on your experimentation
#define NUM_TESTS 100

int *array;
int length = ARRAY_SIZE;
int count = 0;
int num_threads = 1; // Change this based on your experimentation

// Thread function to count ones in a specific range
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

void run_tests(int threads) {
    int correct_counts = 0;

    for (int test = 1; test <= NUM_TESTS; test++) {
        generate_random_array();

        // Verify the count
        int verified_count = verify_count();
            num_threads = threads;
            count = 0;
            pthread_t threads[num_threads];
            clock_t start, end;

            start = clock();

            // Create threads
            for (long i = 0; i < num_threads; i++) {
                pthread_create(&threads[i], NULL, count1s_thread, (void *)i);
            }

            // Join threads
            for (long i = 0; i < num_threads; i++) {
                pthread_join(threads[i], NULL);
            }

            end = clock();

            printf("Test: %d, Threads: %d, Time: %f seconds, Count: %d (Verified: %d)\n",
                   test, num_threads, ((double)(end - start)) / CLOCKS_PER_SEC, count, verified_count);

            // Check correctness
            if (count == verified_count) {
                correct_counts++;
            }
        }

        free(array);
    

    // Print overall correctness rate
    printf("\nCorrectness rate: %.2f%%\n", (float)correct_counts / NUM_TESTS * 100);
}

int main(int argc, char *argv[]) {
    // Check if the user wants to run tests and check if second argument is an integer
    if (argc > 2 && strcmp(argv[1], "--test") == 0 && atoi(argv[2]) > 0) {
        run_tests(atoi(argv[2]));
    } else {
        generate_random_array();

        // Open a CSV file for writing
        FILE *csv_file = fopen("results.csv", "w");
        if (csv_file == NULL) {
            fprintf(stderr, "Error opening CSV file for writing.\n");
            return 1; // Return an error code
        }

        // Print CSV header
        fprintf(csv_file, "Threads,Time,Count\n");

        // Experiment with different number of threads
        for (num_threads = 1; num_threads <= 32; num_threads *= 2) {
            count = 0;
            pthread_t threads[num_threads];
            clock_t start, end;

            start = clock();

            // Create threads
            for (long i = 0; i < num_threads; i++) {
                pthread_create(&threads[i], NULL, count1s_thread, (void *)i);
            }

            // Join threads
            for (long i = 0; i < num_threads; i++) {
                pthread_join(threads[i], NULL);
            }

            end = clock();

            // Calculate and print the runtime
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Threads: %d, Time: %f seconds, Count: %d\n", num_threads, cpu_time_used, count);

            // Print data to CSV
            fprintf(csv_file, "%d,%f,%d\n", num_threads, cpu_time_used, count);
        }

        fclose(csv_file); // Close the CSV file

        free(array);
    }

    return 0;
}