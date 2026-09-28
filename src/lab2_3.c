#include <stdio.h>

// Returns 1 if n is prime, 0 otherwise
int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }

    // only odd divisors up to sqrt(n)
    int d = 3;
    while (d * d <= n) {
        if (n % d == 0) {
            return 0;
        }
        d += 2;
    }
    return 1;
}

int main(void) {
    int n;

    printf("Enter an integer n (>= 2): ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 2) {
        printf("Error: n must be at least 2.\n");
        return 1;
    }

    printf("Primes up to %d:\n", n);
    int first = 1;
    for (int num = 2; num <= n; num++) {
        if (is_prime(num)) {
            if (!first) {
                printf(", ");
            }
            printf("%d", num);
            first = 0;
        }
    }
    printf("\n");

    return 0;
}