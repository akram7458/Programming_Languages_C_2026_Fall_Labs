// week5_task4_struct_binary_io.c   (BONUS)
// Name: Akram  Surname: Mammadov  Student ID: 251ADB131
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

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
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

int main(void) {
    Student s1 = {0};          // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    // TODO: save_student_binary(&s1, bin_file); handle failure
    if (save_student_binary(&s1, bin_file) != 0) {
        fprintf(stderr, "Error: could not write '%s'.\n", bin_file);
        return EXIT_FAILURE;
    }

    // TODO: Save the same record as text ("name age gpa") to txt_file for comparison
    char text_line[128];
    snprintf(text_line, sizeof text_line, "%s %d %.2f\n", s1.name, s1.age, s1.gpa);

    FILE *txt = fopen(txt_file, "w");
    if (txt == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }
    fputs(text_line, txt);
    if (fclose(txt) != 0) {
        fprintf(stderr, "Error: could not finish writing '%s'.\n", txt_file);
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    // TODO: load_student_binary(bin_file, &loaded); handle failure
    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Error: could not read '%s'.\n", bin_file);
        return EXIT_FAILURE;
    }

    // TODO: printf("Loaded student: %s, %d, GPA %.2f\n", ...);
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    // TODO: printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    // TODO: printf("Binary file size: %ld bytes\n", file_size(bin_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));

    return EXIT_SUCCESS;
}

// TODO: open with "wb", fwrite(s, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    int result = 0;

    // fwrite returns how many items it wrote; we asked for exactly one struct
    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        result = -1;
    }

    // fclose() flushes the buffer, so a failure here also means data was lost
    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// TODO: open with "rb", fread(out, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // Read into a temporary struct first, so *out is untouched if the read fails
    Student tmp;
    int result = -1;

    if (fread(&tmp, sizeof(Student), 1, fp) == 1) {
        *out = tmp;
        result = 0;
    }

    // The file is closed in every case
    fclose(fp);

    return result;
}

// TODO: open with "rb", fseek(fp, 0, SEEK_END), size = ftell(fp), close, return size (-1 on error)
long file_size(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    long size = -1;

    // Jump to the end; ftell then reports the position, which equals the size in bytes
    if (fseek(fp, 0, SEEK_END) == 0) {
        size = ftell(fp);   // stays -1 if ftell fails
    }

    fclose(fp);
    return size;
}