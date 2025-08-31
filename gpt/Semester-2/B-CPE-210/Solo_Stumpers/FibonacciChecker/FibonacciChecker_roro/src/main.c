/*
** EPITECH PROJECT, 2025
** FibonacciChecker
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fib_checker.h"

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
    if (val < 0 || val > 2000000000)
        return 0;
    *out = (int)val;
    return 1;
}

int is_fibonacci(int n)
{
    int a;
    int b;
    int c;

    if (n == 0 || n == 1)
        return 1;
    a = 0;
    b = 1;
    while (b < n) {
        c = a + b;
        a = b;
        b = c;
    }
    return b == n;
}

int main(int argc, char **argv)
{
    int n;

    if (argc != 2 || !parse_positive_int(argv[1], &n))
        return 84;
    if (is_fibonacci(n))
        printf("Fibonacci\n");
    else
        printf("Not Fibonacci\n");
    return 0;
}

