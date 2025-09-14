/*
** EPITECH PROJECT, 2024
** Scrabble Calculator
** File description:
** Calculate the value of a word based on letter scores
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char to_uppercase(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

int is_only_letters(char *str)
{
    int i = 0;
    
    if (!str || str[0] == '\0')
        return 0;
    
    while (str[i]) {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
            return 0;
        i++;
    }
    
    return 1;
}

int *parse_values(char *values_str)
{
    int *values;
    char *token;
    char *values_copy;
    int i = 0;
    
    values = malloc(sizeof(int) * 26);
    if (!values)
        return NULL;
    
    values_copy = malloc(strlen(values_str) + 1);
    if (!values_copy) {
        free(values);
        return NULL;
    }
    
    strcpy(values_copy, values_str);
    token = strtok(values_copy, ",");
    
    while (token && i < 26) {
        values[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    
    free(values_copy);
    
    if (i != 26) {
        free(values);
        return NULL;
    }
    
    return values;
}

int calculate_word_value(char *word, int *values)
{
    int total = 0;
    int i = 0;
    char c;
    
    while (word[i]) {
        c = to_uppercase(word[i]);
        if (c >= 'A' && c <= 'Z') {
            total += values[c - 'A'];
        }
        i++;
    }
    
    return total;
}

int main(int argc, char **argv)
{
    int *values;
    int result;
    
    if (argc != 3) {
        return 84;
    }
    
    if (!is_only_letters(argv[2])) {
        return 84;
    }
    
    values = parse_values(argv[1]);
    if (!values) {
        return 84;
    }
    
    result = calculate_word_value(argv[2], values);
    printf("%d\n", result);
    
    free(values);
    return 0;
}