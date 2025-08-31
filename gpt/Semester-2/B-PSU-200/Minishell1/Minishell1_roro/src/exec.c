/*
** EPITECH PROJECT, 2025
** Minishell1
** File description:
** Command execution and builtins
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysh.h"

static int builtin_env(env_t *env, char **argv)
{
    int i;

    (void)argv;
    i = 0;
    while (env->vars && env->vars[i]) {
        puts(env->vars[i]);
        i = i + 1;
    }
    return 0;
}

static int builtin_setenv(env_t *env, char **argv)
{
    if (!argv[1] || !argv[2])
        return 1;
    return env_set(env, argv[1], argv[2]) ? 0 : 1;
}

static int builtin_unsetenv(env_t *env, char **argv)
{
    if (!argv[1])
        return 1;
    return env_unset(env, argv[1]) ? 0 : 1;
}

static int builtin_cd(env_t *env, char **argv)
{
    const char *path;

    path = argv[1] ? argv[1] : env_get(env, "HOME");
    if (!path || chdir(path) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

static int is_builtin(const char *cmd)
{
    return strcmp(cmd, "env") == 0 || strcmp(cmd, "setenv") == 0 ||
        strcmp(cmd, "unsetenv") == 0 || strcmp(cmd, "cd") == 0 ||
        strcmp(cmd, "exit") == 0;
}

static int run_builtin(env_t *env, char **argv)
{
    if (strcmp(argv[0], "env") == 0)
        return builtin_env(env, argv);
    if (strcmp(argv[0], "setenv") == 0)
        return builtin_setenv(env, argv);
    if (strcmp(argv[0], "unsetenv") == 0)
        return builtin_unsetenv(env, argv);
    if (strcmp(argv[0], "cd") == 0)
        return builtin_cd(env, argv);
    if (strcmp(argv[0], "exit") == 0)
        exit(0);
    return 1;
}

static char *join_path(const char *a, const char *b)
{
    size_t la;
    size_t lb;
    char *s;

    la = strlen(a);
    lb = strlen(b);
    s = malloc(la + 1 + lb + 1);
    if (!s)
        return NULL;
    memcpy(s, a, la);
    s[la] = '/';
    memcpy(s + la + 1, b, lb + 1);
    return s;
}

static char *find_in_path(env_t *env, const char *cmd)
{
    char *path;
    char *p;
    char *save;

    if (strchr(cmd, '/'))
        return strdup(cmd);
    path = env_get(env, "PATH");
    if (!path)
        return strdup(cmd);
    path = strdup(path);
    if (!path)
        return NULL;
    p = strtok_r(path, ":", &save);
    while (p) {
        char *full = join_path(p, cmd);
        if (full && access(full, X_OK) == 0) {
            free(path);
            return full;
        }
        free(full);
        p = strtok_r(NULL, ":", &save);
    }
    free(path);
    return strdup(cmd);
}

int run_command(env_t *env, char **argv)
{
    pid_t pid;
    int status;
    char *prog;

    if (!argv || !argv[0])
        return 0;
    if (is_builtin(argv[0]))
        return run_builtin(env, argv);
    prog = find_in_path(env, argv[0]);
    if (!prog)
        return 1;
    pid = fork();
    if (pid == 0) {
        execve(prog, argv, env->vars);
        perror(argv[0]);
        exit(1);
    }
    free(prog);
    if (pid < 0)
        return 1;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

