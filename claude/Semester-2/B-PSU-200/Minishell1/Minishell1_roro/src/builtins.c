/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Built-in command implementations
*/

#include "../include/mysh.h"

int is_builtin(const char *command)
{
    if (my_strcmp(command, "cd") == 0)
        return 1;
    if (my_strcmp(command, "env") == 0)
        return 1;
    if (my_strcmp(command, "setenv") == 0)
        return 1;
    if (my_strcmp(command, "unsetenv") == 0)
        return 1;
    if (my_strcmp(command, "exit") == 0)
        return 1;
    return 0;
}

int execute_builtin(shell_t *shell, char **args)
{
    if (my_strcmp(args[0], "cd") == 0)
        return builtin_cd(shell, args);
    if (my_strcmp(args[0], "env") == 0)
        return builtin_env(shell, args);
    if (my_strcmp(args[0], "setenv") == 0)
        return builtin_setenv(shell, args);
    if (my_strcmp(args[0], "unsetenv") == 0)
        return builtin_unsetenv(shell, args);
    if (my_strcmp(args[0], "exit") == 0)
        return builtin_exit(shell, args);
    return 1;
}

int builtin_cd(shell_t *shell, char **args)
{
    char *target_dir;
    char cwd[MAX_PATH_LENGTH];

    if (!args[1]) {
        target_dir = get_env_var(shell, "HOME");
        if (!target_dir) {
            print_error("cd", "HOME not set");
            return 1;
        }
    } else {
        target_dir = args[1];
    }
    
    if (chdir(target_dir) != 0) {
        print_error("cd", strerror(errno));
        return 1;
    }
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
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
        print_error("setenv", "usage: setenv VAR VALUE");
        return 1;
    }
    
    add_env_var(shell, args[1], args[2]);
    return 0;
}

int builtin_unsetenv(shell_t *shell, char **args)
{
    if (!args[1]) {
        print_error("unsetenv", "usage: unsetenv VAR");
        return 1;
    }
    
    remove_env_var(shell, args[1]);
    return 0;
}

int builtin_exit(shell_t *shell, char **args)
{
    int exit_code = 0;

    if (args[1]) {
        exit_code = atoi(args[1]);
    }
    
    shell->running = 0;
    shell->last_status = exit_code;
    return exit_code;
}