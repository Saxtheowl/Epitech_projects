/*
** EPITECH PROJECT, 2024
** Day08 - B-CPE-100
** File description:
** my_str_to_word_array.c - TASK 04
*/

#include <stdlib.h>
#include <stddef.h>

int my_str_isalpha(char const *str);
char *my_strdup(char const *src);

static int is_alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
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

static char *extract_word(char const *str, int start, int end)
{
    char *word;
    int len = end - start;
    int i;
    
    word = malloc(sizeof(char) * (len + 1));
    if (word == NULL)
        return NULL;
    
    for (i = 0; i < len; i++) {
        word[i] = str[start + i];
    }
    word[i] = '\0';
    
    return word;
}

char **my_str_to_word_array(char const *str)
{
    char **array;
    int word_count;
    int array_index = 0;
    int i = 0;
    int word_start = 0;
    int in_word = 0;
    
    if (str == NULL)
        return NULL;
    
    word_count = count_words(str);
    array = malloc(sizeof(char *) * (word_count + 1));
    
    if (array == NULL)
        return NULL;
    
    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                array[array_index] = extract_word(str, word_start, i);
                if (array[array_index] == NULL)
                    return NULL;
                array_index++;
                in_word = 0;
            }
        }
        i++;
    }
    
    if (in_word) {
        array[array_index] = extract_word(str, word_start, i);
        if (array[array_index] == NULL)
            return NULL;
        array_index++;
    }
    
    array[array_index] = NULL;
    return array;
}