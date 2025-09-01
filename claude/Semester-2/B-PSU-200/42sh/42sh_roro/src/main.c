/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Main entry point for 42sh shell
*/

#include "shell.h"

shell_t *g_shell = NULL;

static void display_usage(void)
{
    printf("USAGE: ./42sh\n");
    printf("       Advanced Unix shell based on TCSH\n\n");
    printf("Features:\n");
    printf("  - Command line editing with history\n");
    printf("  - Job control (background/foreground)\n");
    printf("  - Aliases and variables\n");
    printf("  - Globbing and redirections\n");
    printf("  - Built-in commands\n");
}

int main(int ac, char **av, char **env)
{
    shell_t shell;

    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))) {
        display_usage();
        return 0;
    }

    if (init_shell(&shell, env) != 0) {
        fprintf(stderr, "42sh: Failed to initialize shell\n");
        return 84;
    }

    g_shell = &shell;
    setup_signals();
    
    if (isatty(STDIN_FILENO)) {
        shell.interactive = 1;
        setup_readline(&shell);
        printf("42sh - Advanced Unix Shell\n");
        printf("Type 'help' for available commands\n");
    }

    shell_loop(&shell);
    cleanup_shell(&shell);
    
    return shell.exit_status;
}