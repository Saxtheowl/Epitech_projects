/*
** EPITECH PROJECT, 2025
** PrimesGenerator
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "primes_generator.h"

int parse_positive_int(const char *s, int *out)
{
    long val;
    int i;

    if (s == NULL || out == NULL || *s == '\0')
        return 0;
    i = 0;
    while (s[i] != '\0') {
        if (!isdigit((unsigned char)s[i]))
            return 0;
        i = i + 1;
    }
    val = strtol(s, NULL, 10);
    if (val < 2 || val > 2000000000)
        return 0;
    *out = (int)val;
    return 1;
}

int is_prime(int n)
{
    int i;

    if (n < 2)
        return 0;
    if (n % 2 == 0)
        return n == 2;
    i = 3;
    while (i <= (int)sqrt((double)n)) {
        if (n % i == 0)
            return 0;
        i = i + 2;
    }
    return 1;
}

int generate_primes_up_to(int n, int *out, int max)
{
    int i;
    int c;

    c = 0;
    i = 2;
    while (i <= n && c < max) {
        if (is_prime(i)) {
            out[c] = i;
            c = c + 1;
        }
        i = i + 1;
    }
    return c;
}

int main(int argc, char **argv)
{
    int n;
    int primes[100000];
    int count;
    int i;

    if (argc != 2 || !parse_positive_int(argv[1], &n))
        return 84;
    count = generate_primes_up_to(n, primes, 100000);
    i = 0;
    while (i < count) {
        printf("%d", primes[i]);
        if (i + 1 < count)
            putchar(' ');
        i = i + 1;
    }
    putchar('\n');
    return 0;
}

