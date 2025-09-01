/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Line editing with readline
*/

#include "shell.h"

char *line_editing_read(shell_t *shell)
{
    char *prompt = get_prompt(shell);
    char *line = NULL;
    size_t bufsize = 0;
    
    if (!prompt) {
        prompt = my_strdup("42sh$ ");
    }
    
    printf("%s", prompt);
    fflush(stdout);
    
    if (getline(&line, &bufsize, stdin) == -1) {
        free(prompt);
        if (line) {
            free(line);
        }
        return NULL;
    }
    
    // Remove newline
    line[strcspn(line, "\n")] = '\0';
    
    free(prompt);
    return line;
}


void setup_readline(shell_t *shell)
{
    (void)shell;
    
    // Simple setup without readline library
    // History and completion would need custom implementation
}