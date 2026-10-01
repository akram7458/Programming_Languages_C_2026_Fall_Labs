/*
 * Lab 3, Task 2
 * Name: Akram Mammadov
 * Student ID: 251ADB131
 */

#include <stdio.h>

// Function prototypes
void swap(int *x, int *y);
void modify_value(int *x);

int main(void) {
    int a = 3, b = 7;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After swap: a=%d, b=%d\n", a, b);

    modify_value(&a);
    printf("After modify_value: a=%d\n", a);

    return 0;
}

// Implement functions below
void swap(int *x, int *y) {
    if (x == y) {
        return; // same address: nothing to do, avoids corrupting the value
    }
    int old_x = *x;
    *x = *y;
    *y = old_x;
}

void modify_value(int *x) {
    *x += *x; // add value to itself instead of multiplying
}