/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** command parser
*/

#include "fridge.h"

static void skip_whitespace(char *line, int *pos)
{
    while (line[*pos] && (line[*pos] == ' ' || line[*pos] == '\t'))
        (*pos)++;
}

static char *extract_word(char *line, int *pos)
{
    int start = *pos;
    int len = 0;
    char *word = NULL;

    skip_whitespace(line, pos);
    start = *pos;
    while (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t' && 
           line[*pos] != '\n')
        (*pos)++;
    len = *pos - start;
    if (len == 0)
        return NULL;
    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return NULL;
    for (int i = 0; i < len; i++)
        word[i] = line[start + i];
    word[len] = '\0';
    return word;
}

int parse_command(char *line, char **cmd, char **arg1, char **arg2)
{
    int pos = 0;

    *cmd = NULL;
    *arg1 = NULL;
    *arg2 = NULL;
    if (!line)
        return 1;
    *cmd = extract_word(line, &pos);
    if (!*cmd)
        return 1;
    *arg1 = extract_word(line, &pos);
    *arg2 = extract_word(line, &pos);
    return 0;
}