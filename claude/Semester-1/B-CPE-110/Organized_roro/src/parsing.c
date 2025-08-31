/*
** EPITECH PROJECT, 2024
** parsing.c
** File description:
** Command parsing functions for workshop shell commands
*/

#include "../include/organized.h"
#include <stdlib.h>

static int count_args(const char *input)
{
    int count = 0;
    int in_word = 0;
    int i = 0;

    if (!input)
        return 0;
    
    while (input[i]) {
        if (input[i] != ' ' && input[i] != ',' && input[i] != '\t') {
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

static char *extract_word(const char *input, int *pos)
{
    int start;
    int len;
    char *word;
    int i;

    while (input[*pos] && (input[*pos] == ' ' || input[*pos] == ',' || 
           input[*pos] == '\t'))
        (*pos)++;
    
    start = *pos;
    while (input[*pos] && input[*pos] != ' ' && input[*pos] != ',' && 
           input[*pos] != '\t')
        (*pos)++;
    
    len = *pos - start;
    if (len == 0)
        return NULL;
    
    word = malloc(len + 1);
    if (!word)
        return NULL;
    
    for (i = 0; i < len; i++)
        word[i] = input[start + i];
    word[len] = '\0';
    
    return word;
}

char **parse_command_args(const char *input)
{
    int arg_count;
    char **args;
    int pos = 0;
    int i;

    if (!input)
        return NULL;
    
    arg_count = count_args(input);
    if (arg_count == 0)
        return NULL;
    
    args = malloc((arg_count + 1) * sizeof(char*));
    if (!args)
        return NULL;
    
    for (i = 0; i < arg_count; i++) {
        args[i] = extract_word(input, &pos);
        if (!args[i]) {
            free_command_args(args);
            return NULL;
        }
    }
    args[arg_count] = NULL;
    
    return args;
}

void free_command_args(char **args)
{
    int i;

    if (!args)
        return;
    
    for (i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

int parse_sort_args(char **args, sort_params_t *params)
{
    int i = 1;
    int count = 0;

    if (!args || !params)
        return -1;
    
    while (args[i])
        i++;
    
    params->criteria = malloc(i * sizeof(sort_criterion_t));
    params->reverse_flags = malloc(i * sizeof(int));
    if (!params->criteria || !params->reverse_flags)
        return -1;
    
    i = 1;
    while (args[i]) {
        if (my_strcmp(args[i], "-r") == 0) {
            if (count > 0)
                params->reverse_flags[count - 1] = 1;
        } else {
            params->reverse_flags[count] = 0;
            if (my_strcmp(args[i], "TYPE") == 0)
                params->criteria[count] = SORT_TYPE;
            else if (my_strcmp(args[i], "NAME") == 0)
                params->criteria[count] = SORT_NAME;
            else if (my_strcmp(args[i], "ID") == 0)
                params->criteria[count] = SORT_ID;
            else
                return -1;
            count++;
        }
        i++;
    }
    
    params->count = count;
    return 0;
}

void free_sort_params(sort_params_t *params)
{
    if (!params)
        return;
    
    free(params->criteria);
    free(params->reverse_flags);
    params->criteria = NULL;
    params->reverse_flags = NULL;
    params->count = 0;
}