#include "mysh.h"

int builtin_cd(char **args)
{
    char *dir;
    char *home;

    if (!args[1] || strlen(args[1]) == 0) {
        home = get_env_var("HOME");
        dir = home ? home : "/";
    } else {
        dir = args[1];
    }

    if (chdir(dir) != 0) {
        perror("cd");
        g_shell.exit_status = 1;
        return 1;
    }

    g_shell.exit_status = 0;
    return 0;
}

int builtin_setenv(char **args)
{
    if (!args[1]) {
        fprintf(stderr, "setenv: Too few arguments.\n");
        g_shell.exit_status = 1;
        return 1;
    }

    if (!args[2]) {
        set_env_var(args[1], "");
    } else {
        set_env_var(args[1], args[2]);
    }

    g_shell.exit_status = 0;
    return 0;
}

int builtin_unsetenv(char **args)
{
    int i;

    if (!args[1]) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        g_shell.exit_status = 1;
        return 1;
    }

    for (i = 1; args[i]; i++) {
        unset_env_var(args[i]);
    }

    g_shell.exit_status = 0;
    return 0;
}

int builtin_env(char **args)
{
    int i;

    (void)args;

    if (!g_shell.environ) {
        g_shell.exit_status = 1;
        return 1;
    }

    for (i = 0; g_shell.environ[i]; i++) {
        printf("%s\n", g_shell.environ[i]);
    }

    g_shell.exit_status = 0;
    return 0;
}

int builtin_exit(char **args)
{
    int exit_code = 0;

    if (args[1]) {
        exit_code = atoi(args[1]);
    } else {
        exit_code = g_shell.exit_status;
    }

    free_env();
    exit(exit_code);
}