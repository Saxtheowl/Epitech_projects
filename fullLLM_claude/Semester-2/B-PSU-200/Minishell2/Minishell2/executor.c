#include "mysh.h"

int execute_pipeline(pipeline_t *pipeline, char **env)
{
    int status = 0;
    
    while (pipeline) {
        status = execute_single_pipeline(pipeline->commands, env);
        pipeline = pipeline->next;
    }
    return status;
}

int execute_single_pipeline(cmd_t *commands, char **env)
{
    cmd_t *cmd = commands;
    int pipe_fds[2];
    int prev_fd = -1;
    int status = 0;
    pid_t pid;

    while (cmd) {
        if (cmd->next) {
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                return 84;
            }
        }

        if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]) && !cmd->next && prev_fd == -1) {
            status = handle_builtin(cmd->args, env);
        } else {
            pid = fork();
            if (pid == -1) {
                perror("fork");
                return 84;
            } else if (pid == 0) {
                handle_child_process(cmd, env, prev_fd, cmd->next ? pipe_fds[1] : -1);
                exit(84);
            }
        }

        if (prev_fd != -1)
            close(prev_fd);
        
        if (cmd->next) {
            close(pipe_fds[1]);
            prev_fd = pipe_fds[0];
        }
        
        cmd = cmd->next;
    }

    if (prev_fd != -1)
        close(prev_fd);

    while (wait(&status) > 0);
    
    return WIFEXITED(status) ? WEXITSTATUS(status) : 84;
}

void handle_child_process(cmd_t *cmd, char **env, int input_fd, int output_fd)
{
    if (input_fd != -1) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    
    if (output_fd != -1) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    if (setup_redirections(cmd) != 0)
        exit(84);

    if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0])) {
        exit(handle_builtin(cmd->args, env));
    }

    execute_command(cmd, env);
}

int setup_redirections(cmd_t *cmd)
{
    int fd;

    if (cmd->input_redirect) {
        fd = open(cmd->input_redirect, O_RDONLY);
        if (fd == -1) {
            perror(cmd->input_redirect);
            return 84;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd->output_redirect) {
        if (cmd->append_output) {
            fd = open(cmd->output_redirect, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            fd = open(cmd->output_redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (fd == -1) {
            perror(cmd->output_redirect);
            return 84;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return 0;
}

int execute_command(cmd_t *cmd, char **env)
{
    char *command_path;

    if (!cmd->args || !cmd->args[0]) {
        exit(0);
    }

    command_path = find_command_path(cmd->args[0], env);
    if (!command_path) {
        fprintf(stderr, "%s: command not found\n", cmd->args[0]);
        exit(127);
    }

    execve(command_path, cmd->args, env);
    perror(command_path);
    if (command_path != cmd->args[0])
        free(command_path);
    exit(84);
}

char *find_command_path(char *command, char **env)
{
    char *path_env = NULL;
    char *path_copy;
    char *dir;
    char *full_path;
    char *saveptr;
    int i;

    if (command[0] == '/' || command[0] == '.') {
        if (access(command, X_OK) == 0)
            return command;
        return NULL;
    }

    for (i = 0; env[i]; i++) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path_env = env[i] + 5;
            break;
        }
    }

    if (!path_env)
        return NULL;

    path_copy = my_strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok_r(path_copy, ":", &saveptr);
    while (dir) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (full_path) {
            sprintf(full_path, "%s/%s", dir, command);
            if (access(full_path, X_OK) == 0) {
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