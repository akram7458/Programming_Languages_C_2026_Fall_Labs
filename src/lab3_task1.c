/*
 * Lab 3, Task 1
 * Name: Akram Mammadov
 * Student ID: 251ADB131
 */

#include <stdio.h>

// Function prototypes
int array_min(int arr[], int size);
int array_max(int arr[], int size);
int array_sum(int arr[], int size);
float array_avg(int arr[], int size);

int main(void) {
    int arr[] = {10, 20, 5, 30, 15};
    int size = 5;

    printf("Min: %d\n", array_min(arr, size));
    printf("Max: %d\n", array_max(arr, size));
    printf("Sum: %d\n", array_sum(arr, size));
    printf("Avg: %.2f\n", array_avg(arr, size));

    return 0;
}

// Implement functions below
int array_min(int arr[], int size) {
    int *p = arr;
    int *end = arr + size;
    int min = *p;

    for (p = arr + 1; p < end; p++) {
        if (*p < min) {
            min = *p;
        }
    }
    return min;
}

int array_max(int arr[], int size) {
    int *p = arr;
    int *end = arr + size;
    int max = *p;

    for (p = arr + 1; p < end; p++) {
        if (*p > max) {
            max = *p;
        }
    }
    return max;
}

int array_sum(int arr[], int size) {
    int total = 0;
    int *p;

    for (p = arr; p < arr + size; p++) {
        total += *p;
    }
    return total;
}

float array_avg(int arr[], int size) {
    // Cast to float BEFORE dividing so the result isn't truncated
    return (float)array_sum(arr, size) / (float)size;
}