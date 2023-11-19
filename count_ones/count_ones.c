#include <stdio.h>

#define ARRAY_SIZE 1000000

int array[ARRAY_SIZE];
int length;
int count;

int count1s() {
    int i;
    count = 0;
    for (i = 0; i < length; i++) {
        if (array[i] == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    length = ARRAY_SIZE;

    for (int i = 0; i < length; i++) {
        array[i] = i % 2;
    }

    int result = count1s();
    printf("Number of 1s in the array: %d\n", result);

    return 0;
}