/*
 * Lab 3, Task 3
 * Name: Akram Mammadov
 * Student ID: 251ADB131
 */

#include <stdio.h>

// Function prototypes
int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

int main(void) {
    char test[] = "Programming in C";
    char copy[100];

    int len = my_strlen(test);
    printf("Length: %d\n", len);

    my_strcpy(copy, test);
    printf("Copy: %s\n", copy);

    return 0;
}

// Implement functions below
int my_strlen(const char *str) {
    const char *start = str;
    while (*str != '\0') {
        str++;
    }
    return (int)(str - start);
}

void my_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0') {
        // body intentionally empty: copy happens in the condition
    }
}