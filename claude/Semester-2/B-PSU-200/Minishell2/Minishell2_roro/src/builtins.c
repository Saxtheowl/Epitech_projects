/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Built-in commands implementation
*/

#include "../include/mysh.h"

int builtin_cd(shell_t *shell, char **args)
{
    char *path = args[1];
    char *home;
    char cwd[MAX_PATH_LENGTH];

    if (!path || my_strcmp(path, "~") == 0) {
        home = get_env_var(shell, "HOME");
        if (!home) {
            print_error("cd", "HOME not set");
            return 1;
        }
        path = home;
    }

    if (chdir(path) == -1) {
        print_error("cd", "can't cd to specified directory");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd))) {
        add_env_var(shell, "OLDPWD", get_env_var(shell, "PWD"));
        add_env_var(shell, "PWD", cwd);
    }

    return 0;
}

int builtin_env(shell_t *shell, char **args)
{
    env_t *current = shell->env_list;

    (void)args;

    while (current) {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }

    return 0;
}

int builtin_setenv(shell_t *shell, char **args)
{
    if (!args[1] || !args[2]) {
        print_error("setenv", "Too few arguments.");
        return 1;
    }

    if (args[3]) {
        print_error("setenv", "Too many arguments.");
        return 1;
    }

    add_env_var(shell, args[1], args[2]);
    return 0;
}

int builtin_unsetenv(shell_t *shell, char **args)
{
    if (!args[1]) {
        print_error("unsetenv", "Too few arguments.");
        return 1;
    }

    remove_env_var(shell, args[1]);
    return 0;
}

int builtin_exit(shell_t *shell, char **args)
{
    int exit_code = shell->last_status;

    if (args[1]) {
        exit_code = atoi(args[1]);
    }

    shell->running = 0;
    shell->last_status = exit_code;
    return exit_code;
}