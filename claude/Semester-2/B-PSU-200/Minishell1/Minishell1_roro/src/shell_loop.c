/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Main shell loop and prompt display
*/

#include "../include/mysh.h"

void display_prompt(void)
{
    write(1, "$> ", 3);
}

void shell_loop(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;
    char **args;

    while (shell->running) {
        display_prompt();
        
        read_chars = getline(&line, &len, stdin);
        if (read_chars == -1) {
            if (feof(stdin)) {
                write(1, "\n", 1);
                break;
            }
            continue;
        }
        
        if (line[read_chars - 1] == '\n')
            line[read_chars - 1] = '\0';
            
        if (my_strlen(line) == 0)
            continue;
            
        args = parse_command(line);
        if (args && args[0]) {
            execute_command(shell, args);
            free_args(args);
        }
    }
    
    if (line)
        free(line);
}