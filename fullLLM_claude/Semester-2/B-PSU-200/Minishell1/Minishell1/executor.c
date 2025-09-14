#include "mysh.h"

int execute_command(char **args)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!args || !args[0]) {
        return 0;
    }

    if (is_builtin(args[0])) {
        if (strcmp(args[0], "cd") == 0) {
            return builtin_cd(args);
        } else if (strcmp(args[0], "setenv") == 0) {
            return builtin_setenv(args);
        } else if (strcmp(args[0], "unsetenv") == 0) {
            return builtin_unsetenv(args);
        } else if (strcmp(args[0], "env") == 0) {
            return builtin_env(args);
        } else if (strcmp(args[0], "exit") == 0) {
            return builtin_exit(args);
        }
    }

    if (access(args[0], F_OK) == 0) {
        cmd_path = args[0];
    } else {
        cmd_path = find_command_in_path(args[0]);
        if (!cmd_path) {
            fprintf(stderr, "%s: Command not found.\n", args[0]);
            g_shell.exit_status = 127;
            return 1;
        }
    }

    pid = fork();
    if (pid == 0) {
        execve(cmd_path, args, g_shell.environ);
        perror(args[0]);
        exit(127);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            g_shell.exit_status = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            g_shell.exit_status = 128 + WTERMSIG(status);
        }
    } else {
        perror("fork");
        g_shell.exit_status = 1;
        return 1;
    }

    if (cmd_path != args[0]) {
        free(cmd_path);
    }

    return 0;
}

int is_builtin(char *cmd)
{
    if (!cmd) {
        return 0;
    }

    return (strcmp(cmd, "cd") == 0 ||
            strcmp(cmd, "setenv") == 0 ||
            strcmp(cmd, "unsetenv") == 0 ||
            strcmp(cmd, "env") == 0 ||
            strcmp(cmd, "exit") == 0);
}