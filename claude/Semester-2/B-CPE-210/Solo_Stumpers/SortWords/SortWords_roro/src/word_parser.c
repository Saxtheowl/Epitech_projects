/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Word parsing functions
*/

#include "sort_words.h"

int is_separator(char c)
{
    return (c == ' ' || c == '\t');
}

int count_words(char const *str)
{
    int count = 0;
    int i = 0;
    int in_word = 0;

    while (str[i]) {
        if (!is_separator(str[i]) && !in_word) {
            count++;
            in_word = 1;
        } else if (is_separator(str[i])) {
            in_word = 0;
        }
        i++;
    }
    return count;
}

char *my_strdup(char const *str, int len)
{
    char *dup;
    int i = 0;

    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}