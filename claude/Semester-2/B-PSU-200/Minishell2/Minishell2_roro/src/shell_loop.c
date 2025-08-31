/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Main shell loop with enhanced parsing
*/

#include "../include/mysh.h"

void display_prompt(void)
{
    write(STDOUT_FILENO, "$> ", 3);
}

int process_line(shell_t *shell, char *line)
{
    token_t *tokens = tokenize_line(line);
    token_t *current = tokens;
    pipeline_t *pipeline;
    int status = 0;

    while (current) {
        pipeline = parse_tokens(current);
        
        if (pipeline && pipeline->commands && pipeline->commands->arg_count > 0) {
            status = execute_pipeline(shell, pipeline);
            shell->last_status = status;
        }
        
        while (current && current->type != TOKEN_SEMICOLON && 
               current->type != TOKEN_END) {
            current = current->next;
        }
        
        if (current && current->type == TOKEN_SEMICOLON) {
            current = current->next;
        }
        
        if (pipeline) {
            free_pipeline(pipeline);
        }
        
        if (!current) {
            break;
        }
    }

    free_tokens(tokens);
    return status;
}

void shell_loop(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;

    while (shell->running) {
        if (isatty(STDIN_FILENO)) {
            display_prompt();
        }

        read_chars = getline(&line, &len, stdin);
        
        if (read_chars == -1) {
            if (isatty(STDIN_FILENO)) {
                write(STDOUT_FILENO, "\n", 1);
            }
            break;
        }

        if (line[read_chars - 1] == '\n') {
            line[read_chars - 1] = '\0';
        }

        if (my_strlen(line) > 0) {
            process_line(shell, line);
        }
    }

    if (line) {
        free(line);
    }
}