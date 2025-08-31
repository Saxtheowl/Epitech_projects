/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Command parsing functions
*/

#include "../include/mysh.h"

static int count_args(char *line)
{
    int count = 0;
    int in_word = 0;
    int i = 0;

    while (line[i]) {
        if (line[i] == ' ' || line[i] == '\t') {
            in_word = 0;
        } else {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        }
        i++;
    }
    
    return count;
}

static char *extract_word(char *line, int *pos)
{
    int start, len = 0;
    char *word;

    while (line[*pos] == ' ' || line[*pos] == '\t')
        (*pos)++;
        
    if (line[*pos] == '\0')
        return NULL;
        
    start = *pos;
    while (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t') {
        len++;
        (*pos)++;
    }
    
    word = malloc(len + 1);
    if (!word)
        return NULL;
        
    strncpy(word, &line[start], len);
    word[len] = '\0';
    
    return word;
}

char **parse_command(char *line)
{
    int arg_count = count_args(line);
    char **args;
    int pos = 0;
    int i = 0;

    if (arg_count == 0)
        return NULL;
        
    args = malloc(sizeof(char *) * (arg_count + 1));
    if (!args)
        return NULL;
        
    while (i < arg_count) {
        args[i] = extract_word(line, &pos);
        if (!args[i]) {
            free_args(args);
            return NULL;
        }
        i++;
    }
    
    args[i] = NULL;
    return args;
}

void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;
        
    while (args[i]) {
        free(args[i]);
        i++;
    }
    
    free(args);
}