/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Word operations functions
*/

#include "sort_words.h"

word_t *parse_words(char const *str, int *word_count)
{
    word_t *words;
    int i = 0, word_idx = 0, start;

    *word_count = count_words(str);
    if (*word_count == 0)
        return NULL;
    words = malloc(sizeof(word_t) * (*word_count));
    if (!words)
        return NULL;
    while (str[i]) {
        while (str[i] && is_separator(str[i]))
            i++;
        if (str[i]) {
            start = i;
            while (str[i] && !is_separator(str[i]))
                i++;
            words[word_idx].str = my_strdup(&str[start], i - start);
            words[word_idx].original_index = word_idx;
            word_idx++;
        }
    }
    return words;
}

void sort_word_array(word_t *words, int count)
{
    int i, j;
    word_t temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            int cmp = my_strcasecmp(words[j].str, words[j + 1].str);
            if (cmp > 0 || (cmp == 0 &&
                words[j].original_index > words[j + 1].original_index)) {
                temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}