/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Entry and loop (supports ';')
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh2.h"

static void prompt(void)
{
    write(1, "> ", 2);
}

int main(int argc, char **argv, char **envp)
{
    env_t *env = env_create(envp);
    char *line = NULL;
    size_t cap = 0;

    (void)argc; (void)argv;
    if (!env)
        return 84;
    while (1) {
        prompt();
        if (getline(&line, &cap, stdin) == -1)
            break;
        if (cap > 0 && line[0] != '\0') {
            size_t n = 0; while (line[n] != '\0') n++;
            if (n > 0 && line[n - 1] == '\n') line[n - 1] = '\0';
        }
        run_line(env, line);
    }
    free(line);
    env_destroy(env);
    return 0;
}

