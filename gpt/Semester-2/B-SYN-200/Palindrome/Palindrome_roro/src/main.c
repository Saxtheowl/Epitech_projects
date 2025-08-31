/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "palindrome.h"

static int parse_int(const char *s, long *out)
{
    char *end;
    long v;

    if (s == NULL || *s == '\0' || out == NULL)
        return 0;
    v = strtol(s, &end, 10);
    if (*end != '\0')
        return 0;
    *out = v;
    return 1;
}

int parse_args(int argc, char **argv, long *n, int *base, int *imax)
{
    int i;

    *n = -1;
    *base = 10;
    *imax = 100;
    i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            long v;
            if (!parse_int(argv[i + 1], &v))
                return 0;
            *n = v;
            i = i + 2;
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            long v;
            if (!parse_int(argv[i + 1], &v))
                return 0;
            *base = (int)v;
            i = i + 2;
        } else if (strcmp(argv[i], "-imax") == 0 && i + 1 < argc) {
            long v;
            if (!parse_int(argv[i + 1], &v))
                return 0;
            *imax = (int)v;
            i = i + 2;
        } else {
            return 0;
        }
    }
    if (*n < 0 || *base < 2 || *base > 36 || *imax < 0)
        return 0;
    return 1;
}

static int to_digits(long n, int base, int *digits, int *len)
{
    int i;

    if (n == 0) {
        digits[0] = 0;
        *len = 1;
        return 1;
    }
    i = 0;
    while (n > 0 && i < 64) {
        digits[i] = (int)(n % base);
        n = n / base;
        i = i + 1;
    }
    *len = i;
    return 1;
}

static long from_digits(const int *digits, int len, int base)
{
    long n;
    int i;

    n = 0;
    i = len - 1;
    while (i >= 0) {
        n = n * base + digits[i];
        i = i - 1;
    }
    return n;
}

int is_palindrome_base(long n, int base)
{
    int d[64];
    int len;
    int i;

    to_digits(n, base, d, &len);
    i = 0;
    while (i < len / 2) {
        if (d[i] != d[len - 1 - i])
            return 0;
        i = i + 1;
    }
    return 1;
}

long reverse_in_base(long n, int base)
{
    int d[64];
    int len;

    to_digits(n, base, d, &len);
    return from_digits(d, len, base);
}

long add_reverse_step(long n, int base)
{
    long r;

    r = reverse_in_base(n, base);
    return n + r;
}

int find_palindrome(long n, int base, int imax, long *res, int *iters)
{
    int i;

    if (is_palindrome_base(n, base)) {
        *res = n;
        *iters = 0;
        return 1;
    }
    i = 0;
    while (i < imax) {
        n = add_reverse_step(n, base);
        if (is_palindrome_base(n, base)) {
            *res = n;
            *iters = i + 1;
            return 1;
        }
        i = i + 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    long n;
    int base;
    int imax;
    long res;
    int it;

    if (!parse_args(argc, argv, &n, &base, &imax))
        return 84;
    if (!find_palindrome(n, base, imax, &res, &it))
        return 84;
    printf("%ld %d %ld\n", n, it, res);
    return 0;
}

