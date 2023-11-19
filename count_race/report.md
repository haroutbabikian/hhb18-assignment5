# Report on Parallel Counting Ones Program

## Introduction

The goal of this experiment is to parallelize a program that counts the number of ones in an array of integers using Posix threads. The array is randomly generated with values between 0 and 5. The primary objective is to investigate the impact of different array sizes and the number of threads on the program's runtime.

## Experimental Setup

### Array Sizes

Three different array sizes were used for experimentation:

- 1,000 integers
- 1,000,000 integers
- 1,000,000,000 integers

### Number of Threads

The program was executed with varying numbers of threads:

- 1 thread
- 2 threads
- 4 threads
- 8 threads
- 16 threads
- 32 threads

## Results

### Array Size: 1,000 Integers

#### Runtime vs Number of Threads (Array size: 1 thousand)

| Threads | Time (seconds) | Count |
| ------- | --------------- | ----- |
| 1       | 0.000070 | 164 |
| 2       | 0.000118 | 157 |
| 4       | 0.000213 | 164 |
| 8       | 0.000382 | 163 |
| 16      | 0.000738 | 163 |
| 32      | 0.001378 | 162 |

![Plot_1_1000](runtime_plot(1thousand).png)

### Array Size: 1,000,000 Integers

#### Runtime vs Number of Threads (Array size: 1 million)

| Threads | Time (seconds) | Count |
| ------- | --------------- | ----- |
| 1       | 0.004640 | 166961 |
| 2       | 0.009351 | 119378 |
| 4       | 0.014793 | 92454 |
| 8       | 0.014861 | 90733 |
| 16      | 0.013937 | 103955 |
| 32      | 0.010243 | 133629 |

![Plot_1_1000000](runtime_plot(1million).png)

### Array Size: 1,000,000,000 Integers

#### Runtime vs Number of Threads (Array size: 1 billion)

| Threads | Time (seconds)           | Count                   |
| ------- | ------------------------- | -----------------------|
| 1       | 10.783505 | 166661540 |
| 2       | 10.570230 | 147673698 |
| 4       | 12.549249 | 117481701 |
| 8       | 14.187834 | 77191886 |
| 16      | 13.348036 | 48229418 |
| 32      | 13.381254 | 25477702 |

![Plot_1_1000000000](runtime_plot(1billion).png)

## Testing

In order to run a test (100 runs), the user must specify the test flag, --test, with the desired number of threads.
Example: `./count_race --test 32` in order to test for 32 threads.

Performing the tests on an array size of 1000 is enough to show the unreliablility of using threads with a share count.

| Array Size | Correctness rate (1 thread)           |
| ------- | ------------------------- |
| 1000       | 100% |

| Array Size | Correctness rate (2 threads)           |
| ------- | ------------------------- |
| 1000       | 99% |

| Array Size | Correctness rate (4 threads)           |
| ------- | ------------------------- |
| 1000       | 76% |

| Array Size | Correctness rate (8 threads)           |
| ------- | ------------------------- |
| 1000       | 74% |

| Array Size | Correctness rate (16 threads)           |
| ------- | ------------------------- |
| 1000       | 58% |

| Array Size | Correctness rate (32 threads)           |
| ------- | ------------------------- |
| 1000       | 64% |

## Discussion

Increasing the number of threads did not always make the program faster due to a few reasons (I have taken Operating Systems):

    Thread Overhead: Creating and managing threads come with some overhead. If the workload of each thread is relatively small, the overhead of creating and managing threads might outweigh the benefits of parallelism.
    
    Contention: When multiple threads access shared resources concurrently, they might contend for those resources, leading to contention and potential slowdowns. For example, if multiple threads are incrementing a shared counter, they might need to lock the counter to ensure atomicity, introducing contention.

    Synchronization: Threads often need to communicate with each other, and this communication takes time. If threads frequently have to wait for each other, the overall efficiency of parallel processing decreases.

    Limited Cores: My laptop has two processing cores. If I use more threads than the number of cores, some threads might have to wait, reducing the advantage of parallel processing.
    
    Race Conditions: In my C code, the count variable is shared among threads without any protection mechanism (like locks). If multiple threads try to update count simultaneously, it can lead to a race condition, where the final value of count might not be accurate (it isn't).

## Conclusion

Adding more threads doesn't always mean things get done faster, especially on a dual-core laptop.
