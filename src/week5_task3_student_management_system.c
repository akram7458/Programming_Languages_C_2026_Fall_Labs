// week5_task3_student_management_system.c
// Name: Akram  Surname: Mammadov  Student ID: 251ADB131
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // TODO: Load existing data: count = load_students(students, MAX_STUDENTS);
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                // TODO: Call list_students()
                list_students(students, count);
                break;
            case 2:
                // TODO: Call add_student()
                add_student(students, &count);
                break;
            case 3:
                // TODO: Call save_students(). If it fails, print an error message.
                if (save_students(students, count) != 0) {
                    printf("Error: could not write to %s\n", DATA_FILE);
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// TODO: Implement load_students()
// Open DATA_FILE for reading. If it cannot be opened (e.g. first run), return 0.
// Read the file line by line with fgets(); parse "name,id,gpa" with
// sscanf(line, "%49[^,],%d,%f", ...) and keep only lines where sscanf returned 3.
// Stop when max records have been loaded. Close the file and return the number loaded.
int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;   // no file yet (first run) is not an error
    }

    char line[LINE_LEN];
    Student *slot = arr;        // points at the next free place in the array
    int loaded = 0;

    while (loaded < max && fgets(line, sizeof line, fp) != NULL) {
        Student candidate;
        memset(&candidate, 0, sizeof candidate);

        // A blank or malformed line gives a result other than 3 and is skipped
        int fields = sscanf(line, "%49[^,],%d,%f",
                            candidate.name, &candidate.id, &candidate.gpa);
        if (fields != 3) {
            continue;
        }

        *slot = candidate;
        slot++;
        loaded++;
    }

    fclose(fp);
    return loaded;
}

// TODO: Implement save_students()
// Open DATA_FILE for writing ("w"), return -1 if fopen() fails.
// Write one line per student: fprintf(fp, "%s,%d,%.2f\n", ...). Close the file and return 0.
int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    int status = 0;

    // "w" mode already emptied the file, so this overwrites all old records
    for (int i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            status = -1;
        }
    }

    // fclose() flushes the buffer, so a failure here also means data was lost
    if (fclose(fp) != 0) {
        status = -1;
    }

    return status;
}

// TODO: Implement add_student()
// 1. If *count >= MAX_STUDENTS, print "Cannot add more students (limit reached)." and return.
// 2. Use read_line() to ask "Enter name: ", "Enter ID: " and "Enter GPA: ".
//    If read_line() returns -1 (end of input), just return.
// 3. Validate: name not empty, no ',' in name, ID is an integer, GPA is a number in 0.0–4.0
//    (strtol / strtof are useful). Otherwise print "Invalid input. Student not added." and return.
// 4. Store the student at arr[*count], increase *count, print "Student added successfully!"
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name_text[LINE_LEN];
    char id_text[LINE_LEN];
    char gpa_text[LINE_LEN];

    // Ask all three questions first so no unread line is left for the menu
    if (read_line("Enter name: ", name_text, sizeof name_text) != 0) {
        return;
    }
    if (read_line("Enter ID: ", id_text, sizeof id_text) != 0) {
        return;
    }
    if (read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
        return;
    }

    int valid = 1;
    size_t name_len = strlen(name_text);
    char *end = NULL;
    long id_value = 0;
    float gpa_value = 0.0f;

    // Name: not empty, fits into name[NAME_LEN] with its '\0', and no comma
    if (name_len == 0 || name_len >= NAME_LEN || strchr(name_text, ',') != NULL) {
        valid = 0;
    }

    // ID: the whole text must be an integer that fits in an int
    if (valid) {
        id_value = strtol(id_text, &end, 10);
        if (end == id_text || *end != '\0' || id_value != (long)(int)id_value) {
            valid = 0;
        }
    }

    // GPA: the whole text must be a number from 0.0 to 4.0 (NaN fails this test too)
    if (valid) {
        gpa_value = strtof(gpa_text, &end);
        if (end == gpa_text || *end != '\0' || !(gpa_value >= 0.0f && gpa_value <= 4.0f)) {
            valid = 0;
        }
    }

    if (!valid) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // Everything is valid: fill the next free slot and grow the count
    Student *target = &arr[*count];
    memcpy(target->name, name_text, name_len + 1);   // +1 copies the '\0'
    target->id = (int)id_value;
    target->gpa = gpa_value;
    (*count)++;

    printf("Student added successfully!\n");
}

// TODO: Implement list_students()
// If count is 0 print "No students found."; otherwise print a header and one line per student,
// e.g. printf("%-5d %-20s %.2f\n", id, name, gpa);
void list_students(const Student arr[], int count) {
    if (count <= 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (const Student *p = arr; p < arr + count; p++) {
        printf("%-5d %-20s %.2f\n", p->id, p->name, p->gpa);
    }
}