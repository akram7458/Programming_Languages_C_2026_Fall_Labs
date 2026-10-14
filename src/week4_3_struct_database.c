/*
 * week4_3_struct_database.c
 * Author: Akram Mammadov
 * Student ID: 251ADB131
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Define struct Student with fields name (char[50]), id (int), grade (float)
//       (same definition as in Task 2)
struct Student {
    char name[50];
    int id;
    float grade;
};

// Helper: reads "<name> <id> <grade>" into *s. Returns 0 on success, -1 if any value is missing
static int read_student(struct Student *s) {
    if (scanf("%49s", s->name) != 1) {
        return -1;
    }
    if (scanf("%d", &s->id) != 1) {
        return -1;
    }
    if (scanf("%f", &s->grade) != 1) {
        return -1;
    }
    return 0;
}

int main(void) {
    int n;
    struct Student *students = NULL;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    // TODO: Allocate memory for n Student structs using malloc
    //       Example: students = malloc(n * sizeof(struct Student));
    students = malloc((size_t)n * sizeof *students);

    // TODO: Check allocation success
    // If students is NULL: print "Memory allocation failed." and return 1
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // TODO: Read student data in a loop. For student i (counting from 1):
    //       print "Enter data for student %d: ", then read
    //       name (scanf("%49s", ...)), id and grade.
    //       If a value cannot be read: print "Invalid input.",
    //       free the array and return 1
    int k = 1;
    while (k <= n) {
        printf("Enter data for student %d: ", k);
        if (read_student(&students[k - 1]) != 0) {
            printf("Invalid input.\n");
            free(students);
            return 1;
        }
        k++;
    }

    // TODO: Print an empty line, then the table:
    //       printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    //       and for each student:
    //       printf("%-6d %-11s %.1f\n", id, name, grade);
    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (int row = 0; row < n; row++) {
        printf("%-6d %-11s %.1f\n",
               students[row].id, students[row].name, students[row].grade);
    }

    // Optional (not autograded): after the table, print the average
    // grade or the top student
    double sum = 0.0;
    int lowest = 0;
    for (int j = 0; j < n; j++) {
        sum += students[j].grade;
        if (students[j].grade < students[lowest].grade) {
            lowest = j;
        }
    }
    printf("Average grade = %.2f\n", sum / n);
    printf("Lowest grade: %s (%.1f)\n", students[lowest].name, students[lowest].grade);

    // TODO: Free allocated memory
    free(students);
    students = NULL;

    return 0;
}