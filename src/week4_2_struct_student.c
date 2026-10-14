/*
 * week4_2_struct_student.c
 * Author: Akram Mammadov
 * Student ID: 251ADB131
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Define a 'Student' struct with name, id and grade, create two
 *   instances with the values from the instructions, and print them.
 *
 *   This program reads no input. Output must match the format in the
 *   Week 4 instructions exactly (it is checked by the autograder).
 */

#include <stdio.h>
#include <string.h>

// TODO: Define struct Student with fields: name (char[50]), id (int), grade (float)
// Example:
// struct Student {
//     char name[50];
//     int id;
//     float grade;
// };
struct Student {
    char name[50];
    int id;
    float grade;
};

// Helper: prints one student in the required format (k is the student number)
static void print_student(int k, struct Student s) {
    printf("Student %d: %s, ID: %d, Grade: %.1f\n", k, s.name, s.id, s.grade);
}

int main(void) {
    // TODO: Declare two Student variables
    struct Student alice;
    struct Student bob;

    // TODO: Assign the values (use strcpy for the name):
    //       Student 1: Alice Johnson, 1001, 9.1
    //       Student 2: Bob Smith,     1002, 8.7
    strcpy(alice.name, "Alice Johnson");
    alice.id = 1001;
    alice.grade = 9.1f;

    strcpy(bob.name, "Bob Smith");
    bob.id = 1002;
    bob.grade = 8.7f;

    // TODO: Print each student exactly as:
    //       Student <k>: <name>, ID: <id>, Grade: <grade with 1 decimal, %.1f>
    print_student(1, alice);
    print_student(2, bob);

    return 0;
}