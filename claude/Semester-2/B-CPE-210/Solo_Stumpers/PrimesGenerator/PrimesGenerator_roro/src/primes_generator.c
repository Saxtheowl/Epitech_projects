/*
** EPITECH PROJECT, 2025
** PrimesGenerator
** File description:
** Primes generator implementation
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    int i;
    if (n < 2) return 0;
    for (i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main(int argc, char **argv) {
    int limit, i, first = 1;
    
    if (argc != 2) return 84;
    
    limit = atoi(argv[1]);
    if (limit < 2) return 84;
    
    for (i = 2; i <= limit; i++) {
        if (is_prime(i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");
    return 0;
}