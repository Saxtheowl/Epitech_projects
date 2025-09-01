/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Built-in commands implementation
*/

#include "shell.h"

int builtin_exit(shell_t *shell, char **args)
{
    int exit_code = 0;
    
    if (args[1]) {
        exit_code = atoi(args[1]);
    }
    
    shell->exit_status = exit_code;
    exit(exit_code);
    return 0;
}

int builtin_cd(shell_t *shell, char **args)
{
    char *dir = args[1];
    
    if (!dir) {
        dir = get_env_var(shell, "HOME");
        if (!dir) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    
    if (strcmp(dir, "-") == 0) {
        char *oldpwd = get_variable(shell, "OLDPWD");
        if (!oldpwd) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        dir = oldpwd;
        printf("%s\n", dir);
    }
    
    char old_cwd[MAX_PATH];
    getcwd(old_cwd, MAX_PATH);
    
    if (chdir(dir) != 0) {
        perror("cd");
        return 1;
    }
    
    // Update PWD and OLDPWD
    set_variable(shell, "OLDPWD", old_cwd);
    
    if (getcwd(shell->cwd, MAX_PATH)) {
        set_env_var(shell, "PWD", shell->cwd);
        set_variable(shell, "PWD", shell->cwd);
    }
    
    return 0;
}

int builtin_echo(shell_t *shell, char **args)
{
    int newline = 1;
    int start = 1;
    
    (void)shell;
    
    if (args[1] && strcmp(args[1], "-n") == 0) {
        newline = 0;
        start = 2;
    }
    
    for (int i = start; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i + 1]) {
            printf(" ");
        }
    }
    
    if (newline) {
        printf("\n");
    }
    
    return 0;
}

int builtin_env(shell_t *shell, char **args)
{
    (void)args;
    
    for (int i = 0; shell->env[i]; i++) {
        printf("%s\n", shell->env[i]);
    }
    
    return 0;
}

int builtin_setenv(shell_t *shell, char **args)
{
    if (!args[1]) {
        fprintf(stderr, "setenv: Too few arguments\n");
        return 1;
    }
    
    char *name = args[1];
    char *value = args[2] ? args[2] : "";
    
    return set_env_var(shell, name, value);
}

int builtin_unsetenv(shell_t *shell, char **args)
{
    if (!args[1]) {
        fprintf(stderr, "unsetenv: Too few arguments\n");
        return 1;
    }
    
    return unset_env_var(shell, args[1]);
}

int builtin_alias(shell_t *shell, char **args)
{
    if (!args[1]) {
        print_aliases(shell);
        return 0;
    }
    
    char *arg = args[1];
    char *equals = strchr(arg, '=');
    
    if (!equals) {
        // Display specific alias
        char *value = get_alias(shell, arg);
        if (value) {
            printf("%s=%s\n", arg, value);
        } else {
            fprintf(stderr, "alias: %s not found\n", arg);
            return 1;
        }
    } else {
        // Set alias
        *equals = '\0';
        char *name = arg;
        char *value = equals + 1;
        
        return add_alias(shell, name, value);
    }
    
    return 0;
}

int builtin_unalias(shell_t *shell, char **args)
{
    if (!args[1]) {
        fprintf(stderr, "unalias: Too few arguments\n");
        return 1;
    }
    
    return remove_alias(shell, args[1]);
}

int builtin_history(shell_t *shell, char **args)
{
    (void)args;
    print_history(shell);
    return 0;
}

int builtin_jobs(shell_t *shell, char **args)
{
    (void)args;
    print_jobs(shell);
    return 0;
}

int builtin_fg(shell_t *shell, char **args)
{
    int job_id = 1;
    
    if (args[1]) {
        job_id = atoi(args[1]);
    }
    
    job_t *job = get_job(shell, job_id);
    if (!job) {
        fprintf(stderr, "fg: job %d not found\n", job_id);
        return 1;
    }
    
    printf("[%d]  %s\n", job->id, job->command);
    
    // Move job to foreground
    tcsetpgrp(STDIN_FILENO, job->pgid);
    kill(-job->pgid, SIGCONT);
    
    int status;
    waitpid(-job->pgid, &status, WUNTRACED);
    
    // Restore shell to foreground
    tcsetpgrp(STDIN_FILENO, getpgrp());
    
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        remove_job(shell, job_id);
    }
    
    return 0;
}

int builtin_bg(shell_t *shell, char **args)
{
    int job_id = 1;
    
    if (args[1]) {
        job_id = atoi(args[1]);
    }
    
    job_t *job = get_job(shell, job_id);
    if (!job) {
        fprintf(stderr, "bg: job %d not found\n", job_id);
        return 1;
    }
    
    printf("[%d]  %s &\n", job->id, job->command);
    kill(-job->pgid, SIGCONT);
    
    return 0;
}

int builtin_set(shell_t *shell, char **args)
{
    if (!args[1]) {
        print_variables(shell);
        return 0;
    }
    
    char *arg = args[1];
    char *equals = strchr(arg, '=');
    
    if (!equals) {
        fprintf(stderr, "set: usage: set variable=value\n");
        return 1;
    }
    
    *equals = '\0';
    char *name = arg;
    char *value = equals + 1;
    
    return set_variable(shell, name, value);
}

int builtin_unset(shell_t *shell, char **args)
{
    if (!args[1]) {
        fprintf(stderr, "unset: Too few arguments\n");
        return 1;
    }
    
    return unset_variable(shell, args[1]);
}