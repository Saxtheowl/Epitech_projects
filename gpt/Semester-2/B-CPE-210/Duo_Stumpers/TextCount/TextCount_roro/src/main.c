/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include "text_count.h"

void count_text(const char *s, int *lines, int *words, int *chars)
{
    int i;
    int in_word;

    *lines = 1;
    *words = 0;
    *chars = 0;
    i = 0;
    in_word = 0;
    while (s[i] != '\0') {
        *chars = *chars + 1;
        if (s[i] == '\n')
            *lines = *lines + 1;
        if (isspace((unsigned char)s[i])) {
            in_word = 0;
        } else if (!in_word) {
            *words = *words + 1;
            in_word = 1;
        }
        i = i + 1;
    }
}

int main(int argc, char **argv)
{
    int l;
    int w;
    int c;

    if (argc != 2)
        return 84;
    count_text(argv[1], &l, &w, &c);
    printf("Lines: %d\nWords: %d\nChars: %d\n", l, w, c);
    return 0;
}

