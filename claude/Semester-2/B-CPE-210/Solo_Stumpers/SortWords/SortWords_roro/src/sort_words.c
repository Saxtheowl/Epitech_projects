/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Main logic for sort_words
*/

#include "sort_words.h"

int sort_words(char *str)
{
    word_t *words;
    int word_count = 0;

    if (!str)
        return 84;
    words = parse_words(str, &word_count);
    if (!words && word_count > 0)
        return 84;
    if (word_count == 0) {
        my_putchar('\n');
        return 0;
    }
    sort_word_array(words, word_count);
    print_words(words, word_count);
    free_words(words, word_count);
    return 0;
}