/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** split_string.c
*/

#include <stdlib.h>

static int is_alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9'));
}

static int count_words(char const *str)
{
    int count = 0;
    int in_word = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        i++;
    }
    return count;
}

static int word_length(char const *str, int start)
{
    int len = 0;
    
    while (str[start + len] != '\0' && is_alphanum(str[start + len]))
        len++;
    return len;
}

static char *copy_word(char const *str, int start, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (word == NULL)
        return NULL;

    while (i < len) {
        word[i] = str[start + i];
        i++;
    }
    word[i] = '\0';
    return word;
}

char **split_string(char const *str)
{
    int word_count = count_words(str);
    char **result = malloc(sizeof(char *) * (word_count + 1));
    int word_idx = 0;
    int i = 0;
    int len;

    if (result == NULL)
        return NULL;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            len = word_length(str, i);
            result[word_idx] = copy_word(str, i, len);
            if (result[word_idx] == NULL)
                return NULL;
            word_idx++;
            i += len;
        } else {
            i++;
        }
    }
    result[word_idx] = NULL;

    return result;
}