#include <stdio.h>
#include <stdlib.h>

long fib(int n);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    printf("%d -> %ld\n", n, fib(n));
}

// Returns the nth Fibonacci number using recursion
long fib(int n) {
    if (n == 1 || n == 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}