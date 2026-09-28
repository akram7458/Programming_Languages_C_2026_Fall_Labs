#include <stdio.h>

// Iterative factorial: n! = n * (n-1) * ... * 1
long long factorial(int n) {
    long long product = 1;
    for (int k = n; k > 1; k--) {
        product *= k;
    }
    return product;
}

int main(void) {
    int n;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: factorial is not defined for negative numbers.\n");
        return 1;
    }

    if (n > 20) {
        printf("Error: %d! is too large for long long (max n is 20).\n", n);
        return 1;
    }

    printf("Factorial of %d is %lld\n", n, factorial(n));
    return 0;
}