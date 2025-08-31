/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Player input handling functions
*/

#include "../include/matchstick.h"

static char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;

    read_chars = getline(&line, &len, stdin);
    if (read_chars == -1) {
        if (line)
            free(line);
        return NULL;
    }
    
    if (line[read_chars - 1] == '\n')
        line[read_chars - 1] = '\0';
        
    return line;
}

int get_player_line(void)
{
    char *input;
    int line;

    while (1) {
        printf("Line: ");
        input = read_line();
        if (!input)
            return -1;
            
        line = my_atoi(input);
        free(input);
        
        if (line > 0)
            return line;
            
        printf("Error: invalid input (positive number expected)\n");
    }
}

int get_player_matches(void)
{
    char *input;
    int matches;

    while (1) {
        printf("Matches: ");
        input = read_line();
        if (!input)
            return -1;
            
        matches = my_atoi(input);
        free(input);
        
        if (matches > 0)
            return matches;
            
        printf("Error: invalid input (positive number expected)\n");
    }
}