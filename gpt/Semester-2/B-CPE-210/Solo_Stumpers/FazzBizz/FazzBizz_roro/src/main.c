/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fazzbizz.h"

int is_multiple(int a, int b)
{
    int res;

    if (b == 0)
        return 0;
    res = (a % b == 0);
    return res;
}

int parse_positive_int(const char *s, int *out)
{
    long val;
    int i;

    if (s == NULL || out == NULL)
        return 0;
    if (*s == '\0')
        return 0;
    i = 0;
    while (s[i] != '\0') {
        if (!isdigit((unsigned char)s[i]))
            return 0;
        i = i + 1;
    }
    val = strtol(s, NULL, 10);
    if (val <= 0 || val > 1000000000)
        return 0;
    *out = (int)val;
    return 1;
}

static void print_line(int i)
{
    int printed;

    printed = 0;
    if (is_multiple(i, 3)) {
        printf("Fazz");
        printed = 1;
    }
    if (is_multiple(i, 5)) {
        printf("Bizz");
        printed = 1;
    }
    if (!printed)
        printf("%d", i);
    putchar('\n');
}

void run_fazzbizz(int n)
{
    int i;

    i = 1;
    while (i <= n) {
        print_line(i);
        i = i + 1;
    }
}

int main(int argc, char **argv)
{
    int n;

    if (argc != 2 || !parse_positive_int(argv[1], &n))
        return 84;
    run_fazzbizz(n);
    return 0;
}

