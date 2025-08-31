/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Advanced command execution with pipes and redirections
*/

#include "../include/mysh.h"

int is_builtin(const char *command)
{
    const char *builtins[] = {"cd", "env", "setenv", "unsetenv", "exit", NULL};
    int i = 0;

    while (builtins[i]) {
        if (my_strcmp(command, builtins[i]) == 0)
            return 1;
        i++;
    }
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

char *find_command_path(shell_t *shell, const char *command)
{
    char *path_env = get_env_var(shell, "PATH");
    char *path_copy;
    char *dir;
    char *full_path;
    char *saveptr;
    struct stat st;

    if (!path_env || command[0] == '/' || command[0] == '.') {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return my_strdup(command);
        return NULL;
    }

    path_copy = my_strdup(path_env);
    dir = strtok_r(path_copy, ":", &saveptr);

    while (dir) {
        full_path = malloc(my_strlen(dir) + my_strlen(command) + 2);
        if (full_path) {
            strcpy(full_path, dir);
            strcat(full_path, "/");
            strcat(full_path, command);

            if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
                free(path_copy);
                return full_path;
            }
            free(full_path);
        }
        dir = strtok_r(NULL, ":", &saveptr);
    }

    free(path_copy);
    return NULL;
}

int setup_redirects(command_t *cmd, int *saved_fds)
{
    int i;

    saved_fds[0] = dup(STDIN_FILENO);
    saved_fds[1] = dup(STDOUT_FILENO);
    saved_fds[2] = dup(STDERR_FILENO);

    for (i = 0; i < cmd->redirect_count; i++) {
        if (cmd->redirects[i].type == TOKEN_REDIRECT_IN) {
            cmd->redirects[i].fd = open(cmd->redirects[i].file, O_RDONLY);
            if (cmd->redirects[i].fd == -1) {
                print_error("mysh", "cannot open input file");
                return -1;
            }
            dup2(cmd->redirects[i].fd, STDIN_FILENO);
        } else if (cmd->redirects[i].type == TOKEN_REDIRECT_OUT) {
            cmd->redirects[i].fd = open(cmd->redirects[i].file, 
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmd->redirects[i].fd == -1) {
                print_error("mysh", "cannot create output file");
                return -1;
            }
            dup2(cmd->redirects[i].fd, STDOUT_FILENO);
        } else if (cmd->redirects[i].type == TOKEN_REDIRECT_APPEND) {
            cmd->redirects[i].fd = open(cmd->redirects[i].file, 
                O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (cmd->redirects[i].fd == -1) {
                print_error("mysh", "cannot create output file");
                return -1;
            }
            dup2(cmd->redirects[i].fd, STDOUT_FILENO);
        }
    }

    return 0;
}

void restore_redirects(int *saved_fds)
{
    dup2(saved_fds[0], STDIN_FILENO);
    dup2(saved_fds[1], STDOUT_FILENO);
    dup2(saved_fds[2], STDERR_FILENO);

    close(saved_fds[0]);
    close(saved_fds[1]);
    close(saved_fds[2]);
}

void close_redirects(command_t *cmd)
{
    int i;

    for (i = 0; i < cmd->redirect_count; i++) {
        if (cmd->redirects[i].fd != -1) {
            close(cmd->redirects[i].fd);
        }
    }
}

int execute_simple_command(shell_t *shell, command_t *cmd)
{
    int saved_fds[3];
    char **environ_array;
    char *command_path;
    pid_t pid;
    int status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return 0;

    if (setup_redirects(cmd, saved_fds) == -1) {
        restore_redirects(saved_fds);
        return 1;
    }

    if (is_builtin(cmd->args[0])) {
        status = execute_builtin(shell, cmd->args);
        close_redirects(cmd);
        restore_redirects(saved_fds);
        return status;
    }

    command_path = find_command_path(shell, cmd->args[0]);
    if (!command_path) {
        print_error(cmd->args[0], "command not found");
        close_redirects(cmd);
        restore_redirects(saved_fds);
        return 1;
    }

    environ_array = env_list_to_array(shell);
    pid = fork();

    if (pid == 0) {
        if (execve(command_path, cmd->args, environ_array) == -1) {
            print_error(cmd->args[0], "execution failed");
            exit(1);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
    } else {
        print_error("fork", "failed to create process");
        status = 1;
    }

    free(command_path);
    free(environ_array);
    close_redirects(cmd);
    restore_redirects(saved_fds);

    return WEXITSTATUS(status);
}

int execute_pipeline(shell_t *shell, pipeline_t *pipeline)
{
    command_t *current;
    int pipes[MAX_PIPES][2];
    pid_t pids[MAX_PIPES + 1];
    int i = 0;
    int status = 0;
    int final_status = 0;

    if (!pipeline || !pipeline->commands)
        return 0;

    if (pipeline->command_count == 1) {
        return execute_simple_command(shell, pipeline->commands);
    }

    for (i = 0; i < pipeline->command_count - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            print_error("pipe", "failed to create pipe");
            return 1;
        }
    }

    current = pipeline->commands;
    i = 0;

    while (current && i < pipeline->command_count) {
        char **environ_array = env_list_to_array(shell);
        char *command_path;

        if (is_builtin(current->args[0]) && pipeline->command_count == 1) {
            return execute_builtin(shell, current->args);
        }

        pids[i] = fork();

        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < pipeline->command_count - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < pipeline->command_count - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            setup_redirects(current, (int[3]){0, 1, 2});

            if (is_builtin(current->args[0])) {
                exit(execute_builtin(shell, current->args));
            }

            command_path = find_command_path(shell, current->args[0]);
            if (!command_path) {
                print_error(current->args[0], "command not found");
                exit(127);
            }

            if (execve(command_path, current->args, environ_array) == -1) {
                print_error(current->args[0], "execution failed");
                exit(126);
            }
        }

        free(environ_array);
        current = current->next;
        i++;
    }

    for (i = 0; i < pipeline->command_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (i = 0; i < pipeline->command_count; i++) {
        waitpid(pids[i], &status, 0);
        final_status = WEXITSTATUS(status);
    }

    return final_status;
}