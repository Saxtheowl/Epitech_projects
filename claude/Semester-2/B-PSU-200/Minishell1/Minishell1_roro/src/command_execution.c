/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Command execution functions
*/

#include "../include/mysh.h"

char *find_command_path(shell_t *shell, const char *command)
{
    char *path_env = get_env_var(shell, "PATH");
    char *path_copy;
    char *token;
    char *full_path;
    struct stat st;

    if (!path_env)
        return NULL;
        
    if (strchr(command, '/') != NULL) {
        if (access(command, X_OK) == 0)
            return my_strdup(command);
        return NULL;
    }
    
    path_copy = my_strdup(path_env);
    if (!path_copy)
        return NULL;
        
    token = strtok(path_copy, ":");
    while (token) {
        full_path = malloc(my_strlen(token) + my_strlen(command) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }
        
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);
        
        if (stat(full_path, &st) == 0 && access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        
        free(full_path);
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return NULL;
}

static int execute_external_command(shell_t *shell, char **args)
{
    pid_t pid;
    int status;
    char *command_path;
    char **env_array;

    command_path = find_command_path(shell, args[0]);
    if (!command_path) {
        print_error(args[0], "command not found");
        return 127;
    }
    
    env_array = env_list_to_array(shell);
    if (!env_array) {
        free(command_path);
        return 1;
    }
    
    pid = fork();
    if (pid == 0) {
        if (execve(command_path, args, env_array) == -1) {
            perror(args[0]);
            exit(126);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        
        for (int i = 0; env_array[i]; i++)
            free(env_array[i]);
        free(env_array);
        free(command_path);
        
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            return 128 + WTERMSIG(status);
    } else {
        perror("fork");
        for (int i = 0; env_array[i]; i++)
            free(env_array[i]);
        free(env_array);
        free(command_path);
        return 1;
    }
    
    return 0;
}

int execute_command(shell_t *shell, char **args)
{
    int status;

    if (!args || !args[0])
        return 0;
        
    if (is_builtin(args[0])) {
        status = execute_builtin(shell, args);
    } else {
        status = execute_external_command(shell, args);
    }
    
    shell->last_status = status;
    return status;
}