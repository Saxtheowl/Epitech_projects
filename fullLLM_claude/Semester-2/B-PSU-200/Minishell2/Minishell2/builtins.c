#include "mysh.h"

int is_builtin(char *command)
{
    if (!command)
        return 0;
    
    if (strcmp(command, "cd") == 0 ||
        strcmp(command, "env") == 0 ||
        strcmp(command, "setenv") == 0 ||
        strcmp(command, "unsetenv") == 0 ||
        strcmp(command, "exit") == 0)
        return 1;
    return 0;
}

int handle_builtin(char **args, char **env)
{
    if (!args || !args[0])
        return 0;

    if (strcmp(args[0], "cd") == 0)
        return builtin_cd(args);
    else if (strcmp(args[0], "env") == 0)
        return builtin_env(env);
    else if (strcmp(args[0], "setenv") == 0)
        return builtin_setenv(args, &env);
    else if (strcmp(args[0], "unsetenv") == 0)
        return builtin_unsetenv(args, &env);
    else if (strcmp(args[0], "exit") == 0)
        return builtin_exit(args);
    
    return 0;
}

int builtin_cd(char **args)
{
    char *dir;
    char *home;

    if (!args[1]) {
        home = getenv("HOME");
        if (!home) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
        dir = home;
    } else {
        dir = args[1];
    }

    if (chdir(dir) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

int builtin_env(char **env)
{
    int i;

    if (!env)
        return 0;

    for (i = 0; env[i]; i++) {
        printf("%s\n", env[i]);
    }

    return 0;
}

int builtin_setenv(char **args, char ***env)
{
    (void)env;
    
    if (!args[1] || !args[2]) {
        fprintf(stderr, "setenv: not enough arguments\n");
        return 1;
    }

    if (setenv(args[1], args[2], 1) != 0) {
        perror("setenv");
        return 1;
    }

    return 0;
}

int builtin_unsetenv(char **args, char ***env)
{
    (void)env;
    
    if (!args[1]) {
        fprintf(stderr, "unsetenv: not enough arguments\n");
        return 1;
    }

    if (unsetenv(args[1]) != 0) {
        perror("unsetenv");
        return 1;
    }

    return 0;
}

int builtin_exit(char **args)
{
    int exit_code = 0;

    if (args[1]) {
        exit_code = atoi(args[1]);
    }

    exit(exit_code);
}