#include <stdio.h>

// Adds up 1 + 2 + ... + n
int sum_to_n(int n) {
    int total = 0;
    for (int k = n; k >= 1; k--) {
        total += k;
    }
    return total;
}

int main(void) {
    int n;

    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be at least 1.\n");
        return 1;
    }

    printf("Sum of 1..%d is %d\n", n, sum_to_n(n));
    return 0;
}