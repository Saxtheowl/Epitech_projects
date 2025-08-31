/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Main entry point for enhanced minishell
*/

#include "../include/mysh.h"

int main(int argc, char **argv, char **environ)
{
    shell_t shell = {0};

    (void)argc;
    (void)argv;

    init_environment(&shell, environ);
    shell.running = 1;
    shell.last_status = 0;

    shell_loop(&shell);

    cleanup_environment(&shell);
    return shell.last_status;
}