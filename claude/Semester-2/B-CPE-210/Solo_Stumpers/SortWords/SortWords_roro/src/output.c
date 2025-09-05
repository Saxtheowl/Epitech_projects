/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Output functions
*/

#include "sort_words.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

void print_words(word_t *words, int count)
{
    int i = 0;

    if (!words || count <= 0)
        return;
    while (i < count) {
        my_putstr(words[i].str);
        if (i < count - 1)
            my_putchar(' ');
        i++;
    }
    my_putchar('\n');
}

void free_words(word_t *words, int count)
{
    int i = 0;

    if (!words)
        return;
    while (i < count) {
        if (words[i].str)
            free(words[i].str);
        i++;
    }
    free(words);
}