/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Environment variable management
*/

#include "shell.h"

char **copy_env(char **env)
{
    int count = 0;
    char **new_env;
    
    while (env[count]) {
        count++;
    }
    
    new_env = malloc(sizeof(char*) * (count + 1));
    if (!new_env) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        new_env[i] = my_strdup(env[i]);
        if (!new_env[i]) {
            free_array(new_env);
            return NULL;
        }
    }
    
    new_env[count] = NULL;
    return new_env;
}

char *get_env_var(shell_t *shell, char *name)
{
    int name_len = strlen(name);
    
    for (int i = 0; shell->env[i]; i++) {
        if (strncmp(shell->env[i], name, name_len) == 0 && 
            shell->env[i][name_len] == '=') {
            return shell->env[i] + name_len + 1;
        }
    }
    
    return NULL;
}

int set_env_var(shell_t *shell, char *name, char *value)
{
    int name_len = strlen(name);
    int value_len = strlen(value);
    char *new_var;
    int count = 0;
    
    // Create new variable string
    new_var = malloc(name_len + value_len + 2);
    if (!new_var) {
        return -1;
    }
    
    snprintf(new_var, name_len + value_len + 2, "%s=%s", name, value);
    
    // Find existing variable
    for (int i = 0; shell->env[i]; i++) {
        if (strncmp(shell->env[i], name, name_len) == 0 && 
            shell->env[i][name_len] == '=') {
            free(shell->env[i]);
            shell->env[i] = new_var;
            return 0;
        }
        count++;
    }
    
    // Add new variable
    char **new_env = realloc(shell->env, sizeof(char*) * (count + 2));
    if (!new_env) {
        free(new_var);
        return -1;
    }
    
    shell->env = new_env;
    shell->env[count] = new_var;
    shell->env[count + 1] = NULL;
    
    return 0;
}

int unset_env_var(shell_t *shell, char *name)
{
    int name_len = strlen(name);
    int found = -1;
    
    // Find variable to remove
    for (int i = 0; shell->env[i]; i++) {
        if (strncmp(shell->env[i], name, name_len) == 0 && 
            shell->env[i][name_len] == '=') {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        return 1; // Variable not found
    }
    
    // Free the variable
    free(shell->env[found]);
    
    // Shift remaining variables
    while (shell->env[found + 1]) {
        shell->env[found] = shell->env[found + 1];
        found++;
    }
    
    shell->env[found] = NULL;
    return 0;
}