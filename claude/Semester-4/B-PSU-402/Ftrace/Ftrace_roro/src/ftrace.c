/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Main ftrace implementation
*/

#include "ftrace.h"

static ftrace_t *init_ftrace(char **argv)
{
    ftrace_t *ftrace = malloc(sizeof(ftrace_t));

    if (!ftrace)
        return NULL;
    ftrace->child_pid = 0;
    ftrace->status = 0;
    ftrace->symbols = NULL;
    ftrace->binary_path = strdup(argv[0]);
    ftrace->in_syscall = 0;
    ftrace->last_syscall = 0;
    if (!ftrace->binary_path) {
        free(ftrace);
        return NULL;
    }
    if (load_symbols(ftrace) != 0) {
        free(ftrace->binary_path);
        free(ftrace);
        return NULL;
    }
    return ftrace;
}

static void cleanup_ftrace(ftrace_t *ftrace)
{
    if (!ftrace)
        return;
    free_symbols(ftrace->symbols);
    free(ftrace->binary_path);
    free(ftrace);
}

int ftrace_main(char **argv)
{
    ftrace_t *ftrace = init_ftrace(argv);
    int result = EXIT_ERROR;

    if (!ftrace) {
        print_error("Failed to initialize ftrace");
        return EXIT_ERROR;
    }

    ftrace->child_pid = fork();
    if (ftrace->child_pid == -1) {
        print_error("Failed to fork");
        cleanup_ftrace(ftrace);
        return EXIT_ERROR;
    }

    if (ftrace->child_pid == 0) {
        result = setup_child(argv);
    } else {
        result = trace_child(ftrace);
    }

    cleanup_ftrace(ftrace);
    return result;
}