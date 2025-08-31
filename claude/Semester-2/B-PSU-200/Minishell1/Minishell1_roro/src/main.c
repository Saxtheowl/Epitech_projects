/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Main function for mysh minishell
*/

#include "../include/mysh.h"

static void init_shell(shell_t *shell, char **environ)
{
    shell->env_list = NULL;
    shell->environ_copy = NULL;
    shell->last_status = 0;
    shell->running = 1;
    init_environment(shell, environ);
}

static void cleanup_shell(shell_t *shell)
{
    cleanup_environment(shell);
}

int main(int argc, char **argv, char **environ)
{
    shell_t shell;

    (void)argc;
    (void)argv;
    
    if (!isatty(STDIN_FILENO)) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read_chars;
        char **args;
        
        init_shell(&shell, environ);
        
        while ((read_chars = getline(&line, &len, stdin)) != -1) {
            if (line[read_chars - 1] == '\n')
                line[read_chars - 1] = '\0';
                
            args = parse_command(line);
            if (args && args[0]) {
                execute_command(&shell, args);
                free_args(args);
            }
        }
        
        if (line)
            free(line);
        cleanup_shell(&shell);
        return shell.last_status;
    }
    
    init_shell(&shell, environ);
    shell_loop(&shell);
    cleanup_shell(&shell);
    
    return shell.last_status;
}