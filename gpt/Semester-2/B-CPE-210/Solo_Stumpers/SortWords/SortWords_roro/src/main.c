/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sort_words.h"

int split_words(const char *s, char words[][64], int max)
{
    int i;
    int j;
    int w;

    i = 0;
    j = 0;
    w = 0;
    while (s[i] != '\0' && w < max) {
        if (!isspace((unsigned char)s[i])) {
            words[w][j] = s[i];
            j = j + 1;
            if (j >= 63) {
                words[w][j] = '\0';
                w = w + 1;
                j = 0;
            }
        } else if (j > 0) {
            words[w][j] = '\0';
            w = w + 1;
            j = 0;
        }
        i = i + 1;
    }
    if (j > 0 && w < max) {
        words[w][j] = '\0';
        w = w + 1;
    }
    return w;
}

void sort_words(char words[][64], int count)
{
    int i;
    int j;

    i = 0;
    while (i < count) {
        j = i + 1;
        while (j < count) {
            if (strcmp(words[i], words[j]) > 0) {
                char tmp[64];
                strcpy(tmp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], tmp);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int main(int argc, char **argv)
{
    char words[128][64];
    int count;
    int i;

    if (argc != 2)
        return 84;
    count = split_words(argv[1], words, 128);
    sort_words(words, count);
    i = 0;
    while (i < count) {
        printf("%s", words[i]);
        if (i + 1 < count)
            putchar(' ');
        i = i + 1;
    }
    putchar('\n');
    return 0;
}
