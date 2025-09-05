/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Header file for sort_words project
*/

#ifndef SORT_WORDS_H_
    #define SORT_WORDS_H_

    #include <stdlib.h>
    #include <unistd.h>

typedef struct word_s {
    char *str;
    int original_index;
} word_t;

// Main function
int sort_words(char *str);

// Utility functions
int my_strlen(char const *str);
int my_strcasecmp(char const *s1, char const *s2);
int is_separator(char c);
int count_words(char const *str);
char *my_strdup(char const *str, int len);

// Word manipulation functions
word_t *parse_words(char const *str, int *word_count);
void sort_word_array(word_t *words, int count);
void print_words(word_t *words, int count);
void free_words(word_t *words, int count);

// Character functions
char to_lower(char c);
void my_putchar(char c);
void my_putstr(char const *str);

#endif /* !SORT_WORDS_H_ */