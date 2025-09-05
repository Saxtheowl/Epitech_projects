/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Utility functions for scrabble calculator
*/

#include "scrabble_calculator.h"
#include <string.h>

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

int is_valid_word(char *word)
{
    int i = 0;

    if (!word || word[0] == '\0')
        return 0;
    while (word[i]) {
        if ((word[i] < 'A' || word[i] > 'Z') &&
            (word[i] < 'a' || word[i] > 'z'))
            return 0;
        i++;
    }
    return 1;
}

int *parse_letter_values(char *values_str)
{
    int *values = NULL;
    char *token = NULL;
    int i = 0;

    if (!values_str)
        return NULL;
    values = malloc(sizeof(int) * ALPHABET_SIZE);
    if (!values)
        return NULL;
    token = strtok(values_str, ",");
    while (token && i < ALPHABET_SIZE) {
        values[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    if (i != ALPHABET_SIZE) {
        free(values);
        return NULL;
    }
    return values;
}

int calculate_word_value(char *word, int *letter_values)
{
    int total_value = 0;
    int i = 0;
    char upper_char = 0;

    while (word[i]) {
        upper_char = to_upper(word[i]);
        total_value += letter_values[upper_char - 'A'];
        i++;
    }
    return total_value;
}