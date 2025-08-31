/*
** EPITECH PROJECT, 2025
** Minishell1
** File description:
** Entry and loop
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysh.h"

static void print_prompt(void)
{
    write(1, "$> ", 3);
}

int mysh_loop(env_t *env)
{
    char *line;
    size_t cap;
    ssize_t n;
    char **argv;

    line = NULL;
    cap = 0;
    while (1) {
        print_prompt();
        n = getline(&line, &cap, stdin);
        if (n == -1)
            break;
        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';
        argv = split_words(line);
        if (!argv)
            continue;
        run_command(env, argv);
        free_words(argv);
    }
    free(line);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    env_t *env;

    (void)argc;
    (void)argv;
    env = env_create(envp);
    if (!env)
        return 84;
    mysh_loop(env);
    env_destroy(env);
    return 0;
}

