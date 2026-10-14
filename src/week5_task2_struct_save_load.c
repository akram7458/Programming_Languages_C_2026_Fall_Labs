// week5_task2_struct_save_load.c
// Name: Akram  Surname: Mammadov  Student ID: 251ADB131
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// TODO: Complete the function implementations and the file handling logic.
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int save_student(const Student *s, const char *filename);  // 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // 0 on success, -1 on error

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";
    int status;

    printf("Saving student to file...\n");
    // TODO: Call save_student(&s1, filename). If it fails, print an error and return EXIT_FAILURE.
    status = save_student(&s1, filename);
    if (status != 0) {
        fprintf(stderr, "Error: failed to save student to '%s'.\n", filename);
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    // TODO: Call load_student(filename, &loaded). If it fails, print an error and return EXIT_FAILURE.
    status = load_student(filename, &loaded);
    if (status != 0) {
        fprintf(stderr, "Error: failed to load student from '%s'.\n", filename);
        return EXIT_FAILURE;
    }

    // TODO: Print the loaded data in exactly this format:
    //       printf("Loaded student: %s, %d, GPA %.2f\n", ...);
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

// TODO: Implement save_student()
// Open the file for writing ("w"), return -1 if fopen() fails,
// write "name age gpa" on one line with fprintf(), close the file and return 0.
int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    int result = 0;

    // One line in the text format: name age gpa
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        result = -1;
    }

    // fclose() flushes the buffer, so a failure here also means the data was not saved
    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// TODO: Implement load_student()
// Open the file for reading ("r"), return -1 if fopen() fails,
// read the three fields with fscanf(fp, "%49s %d %f", ...) and check that it returned 3,
// close the file in every case, and return 0 on success / -1 on failure.
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // Read into a temporary struct first, so *out is untouched if the read fails
    Student tmp = {0};
    int result = -1;

    // %49s leaves room for the '\0' so a long name cannot overflow name[50]
    if (fscanf(fp, "%49s %d %f", tmp.name, &tmp.age, &tmp.gpa) == 3) {
        *out = tmp;
        result = 0;
    }

    // The file is closed in every case
    fclose(fp);

    return result;
}