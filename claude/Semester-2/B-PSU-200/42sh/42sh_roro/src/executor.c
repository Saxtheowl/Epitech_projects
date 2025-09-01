/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Command execution engine
*/

#include "shell.h"

static char *find_command(shell_t *shell, char *cmd)
{
    char *path_env = get_env_var(shell, "PATH");
    char *path_copy, *token;
    char full_path[MAX_PATH];
    struct stat st;
    
    // Check if command is already a full path
    if (strchr(cmd, '/')) {
        return my_strdup(cmd);
    }
    
    if (!path_env) {
        return NULL;
    }
    
    path_copy = my_strdup(path_env);
    if (!path_copy) {
        return NULL;
    }
    
    token = strtok(path_copy, ":");
    while (token) {
        snprintf(full_path, MAX_PATH, "%s/%s", token, cmd);
        
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(path_copy);
            return my_strdup(full_path);
        }
        
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return NULL;
}

static int setup_redirections(cmd_t *cmd)
{
    if (cmd->input_file) {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1) {
            perror(cmd->input_file);
            return -1;
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(fd);
            return -1;
        }
        close(fd);
    }
    
    if (cmd->output_file) {
        int flags = O_WRONLY | O_CREAT;
        flags |= cmd->append_output ? O_APPEND : O_TRUNC;
        
        int fd = open(cmd->output_file, flags, 0644);
        if (fd == -1) {
            perror(cmd->output_file);
            return -1;
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(fd);
            return -1;
        }
        close(fd);
    }
    
    return 0;
}

static int is_builtin(char *cmd)
{
    char *builtins[] = {
        "exit", "cd", "echo", "env", "setenv", "unsetenv",
        "alias", "unalias", "history", "jobs", "fg", "bg",
        "set", "unset", "help", NULL
    };
    
    for (int i = 0; builtins[i]; i++) {
        if (strcmp(cmd, builtins[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int execute_builtin(shell_t *shell, cmd_t *cmd)
{
    char *name = cmd->args[0];
    
    if (strcmp(name, "exit") == 0) {
        return builtin_exit(shell, cmd->args);
    } else if (strcmp(name, "cd") == 0) {
        return builtin_cd(shell, cmd->args);
    } else if (strcmp(name, "echo") == 0) {
        return builtin_echo(shell, cmd->args);
    } else if (strcmp(name, "env") == 0) {
        return builtin_env(shell, cmd->args);
    } else if (strcmp(name, "setenv") == 0) {
        return builtin_setenv(shell, cmd->args);
    } else if (strcmp(name, "unsetenv") == 0) {
        return builtin_unsetenv(shell, cmd->args);
    } else if (strcmp(name, "alias") == 0) {
        return builtin_alias(shell, cmd->args);
    } else if (strcmp(name, "unalias") == 0) {
        return builtin_unalias(shell, cmd->args);
    } else if (strcmp(name, "history") == 0) {
        return builtin_history(shell, cmd->args);
    } else if (strcmp(name, "jobs") == 0) {
        return builtin_jobs(shell, cmd->args);
    } else if (strcmp(name, "fg") == 0) {
        return builtin_fg(shell, cmd->args);
    } else if (strcmp(name, "bg") == 0) {
        return builtin_bg(shell, cmd->args);
    } else if (strcmp(name, "set") == 0) {
        return builtin_set(shell, cmd->args);
    } else if (strcmp(name, "unset") == 0) {
        return builtin_unset(shell, cmd->args);
    } else if (strcmp(name, "help") == 0) {
        printf("42sh - Advanced Unix Shell\n");
        printf("Built-in commands:\n");
        printf("  cd [dir]      - Change directory\n");
        printf("  exit [code]   - Exit shell\n");
        printf("  echo [args]   - Display text\n");
        printf("  env           - Display environment\n");
        printf("  setenv var val- Set environment variable\n");
        printf("  unsetenv var  - Unset environment variable\n");
        printf("  alias [name[=value]] - Manage aliases\n");
        printf("  history       - Display command history\n");
        printf("  jobs          - Display active jobs\n");
        printf("  fg [job]      - Bring job to foreground\n");
        printf("  bg [job]      - Send job to background\n");
        return 0;
    }
    
    return -1;
}

int execute_command(shell_t *shell, cmd_t *cmd)
{
    if (!cmd || !cmd->args[0]) {
        return 0;
    }
    
    // Check for alias expansion
    char *alias_value = get_alias(shell, cmd->args[0]);
    if (alias_value) {
        // Simple alias expansion - just replace the command name
        free(cmd->args[0]);
        cmd->args[0] = my_strdup(alias_value);
    }
    
    if (is_builtin(cmd->args[0])) {
        return execute_builtin(shell, cmd);
    }
    
    char *path = find_command(shell, cmd->args[0]);
    if (!path) {
        fprintf(stderr, "42sh: %s: command not found\n", cmd->args[0]);
        return 127;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        free(path);
        return -1;
    }
    
    if (pid == 0) {
        // Child process
        setup_redirections(cmd);
        execve(path, cmd->args, shell->env);
        perror(path);
        exit(127);
    } else {
        // Parent process
        free(path);
        
        if (cmd->background) {
            // Background process - add to job list
            char command_str[1024];
            snprintf(command_str, 1024, "%s", cmd->args[0]);
            add_job(shell, pid, command_str);
            return 0;
        } else {
            // Foreground process - wait for completion
            int status;
            waitpid(pid, &status, 0);
            
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                return 128 + WTERMSIG(status);
            }
        }
    }
    
    return 0;
}

int execute_pipeline(shell_t *shell, pipeline_t *pipeline)
{
    if (!pipeline || !pipeline->commands) {
        return 0;
    }
    
    cmd_t *cmd = pipeline->commands;
    
    // Single command (no pipe)
    if (!cmd->next) {
        return execute_command(shell, cmd);
    }
    
    // Pipeline with multiple commands
    int pipefd[2];
    pid_t pid;
    int last_status = 0;
    int input_fd = STDIN_FILENO;
    
    while (cmd) {
        if (cmd->next) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                return -1;
            }
        }
        
        pid = fork();
        if (pid == -1) {
            perror("fork");
            return -1;
        }
        
        if (pid == 0) {
            // Child process
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            
            if (cmd->next) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                close(pipefd[0]);
            }
            
            setup_redirections(cmd);
            
            if (is_builtin(cmd->args[0])) {
                exit(execute_builtin(shell, cmd));
            } else {
                char *path = find_command(shell, cmd->args[0]);
                if (!path) {
                    fprintf(stderr, "42sh: %s: command not found\n", cmd->args[0]);
                    exit(127);
                }
                execve(path, cmd->args, shell->env);
                perror(path);
                exit(127);
            }
        } else {
            // Parent process
            if (input_fd != STDIN_FILENO) {
                close(input_fd);
            }
            
            if (cmd->next) {
                close(pipefd[1]);
                input_fd = pipefd[0];
            } else {
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)) {
                    last_status = WEXITSTATUS(status);
                }
            }
        }
        
        cmd = cmd->next;
    }
    
    return last_status;
}