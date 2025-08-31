/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "anagram.h"

static int char_cmp(const void *a, const void *b)
{
    const unsigned char *pa;
    const unsigned char *pb;

    pa = (const unsigned char *)a;
    pb = (const unsigned char *)b;
    if (*pa < *pb)
        return -1;
    if (*pa > *pb)
        return 1;
    return 0;
}

void normalize(const char *src, char *dst, int max)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (src[i] != '\0' && j < max - 1) {
        if (isalpha((unsigned char)src[i])) {
            dst[j] = (char)tolower((unsigned char)src[i]);
            j = j + 1;
        }
        i = i + 1;
    }
    dst[j] = '\0';
}

int is_anagram(const char *a, const char *b)
{
    char na[1024];
    char nb[1024];

    normalize(a, na, 1024);
    normalize(b, nb, 1024);
    if (strlen(na) != strlen(nb))
        return 0;
    qsort(na, strlen(na), 1, char_cmp);
    qsort(nb, strlen(nb), 1, char_cmp);
    if (strcmp(na, nb) == 0)
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;
    if (is_anagram(argv[1], argv[2]))
        printf("Anagram\n");
    else
        printf("Not anagram\n");
    return 0;
}
