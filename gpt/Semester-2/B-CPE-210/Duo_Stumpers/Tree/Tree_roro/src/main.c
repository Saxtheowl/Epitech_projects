/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

int parse_positive_int(const char *s, int *out)
{
    long v;
    int i;

    if (s == NULL || *s == '\0' || out == NULL)
        return 0;
    i = 0;
    while (s[i] != '\0') {
        if (!isdigit((unsigned char)s[i]))
            return 0;
        i = i + 1;
    }
    v = strtol(s, NULL, 10);
    if (v < 1 || v > 1000)
        return 0;
    *out = (int)v;
    return 1;
}

static void print_line(int spaces, int stars)
{
    int i;

    i = 0;
    while (i < spaces) {
        putchar(' ');
        i = i + 1;
    }
    i = 0;
    while (i < stars) {
        putchar('*');
        i = i + 1;
    }
    putchar('\n');
}

static void print_foliage(int size)
{
    int i;

    i = 0;
    while (i < size) {
        print_line(size - 1 - i, 2 * i + 1);
        i = i + 1;
    }
}

static void print_trunk(int size)
{
    int h;
    int i;

    h = size / 2 + 1;
    i = 0;
    while (i < h) {
        print_line(size - 1, 1);
        i = i + 1;
    }
}

void print_tree(int size)
{
    print_foliage(size);
    print_trunk(size);
}

int main(int argc, char **argv)
{
    int n;

    if (argc != 2 || !parse_positive_int(argv[1], &n))
        return 84;
    print_tree(n);
    return 0;
}

