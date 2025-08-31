/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include "clean_str.h"

void clean_string(const char *src, char *dst, int max)
{
    int i;
    int j;
    int in_space;

    i = 0;
    j = 0;
    in_space = 1;
    while (src[i] != '\0' && j < max - 1) {
        if (isalnum((unsigned char)src[i])) {
            dst[j] = (char)tolower((unsigned char)src[i]);
            j = j + 1;
            in_space = 0;
        } else if (!in_space) {
            dst[j] = ' ';
            j = j + 1;
            in_space = 1;
        }
        i = i + 1;
    }
    if (j > 0 && dst[j - 1] == ' ')
        j = j - 1;
    dst[j] = '\0';
}

int main(int argc, char **argv)
{
    char out[2048];

    if (argc != 2)
        return 84;
    clean_string(argv[1], out, 2048);
    printf("%s\n", out);
    return 0;
}

