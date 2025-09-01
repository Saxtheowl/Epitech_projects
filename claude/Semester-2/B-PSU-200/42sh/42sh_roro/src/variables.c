/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Shell variable management
*/

#include "shell.h"

int set_variable(shell_t *shell, char *name, char *value)
{
    var_t *var = shell->variables;
    
    // Check if variable already exists
    while (var) {
        if (strcmp(var->name, name) == 0) {
            free(var->value);
            var->value = my_strdup(value);
            return var->value ? 0 : -1;
        }
        var = var->next;
    }
    
    // Create new variable
    var = malloc(sizeof(var_t));
    if (!var) {
        return -1;
    }
    
    var->name = my_strdup(name);
    var->value = my_strdup(value);
    var->next = shell->variables;
    
    if (!var->name || !var->value) {
        free(var->name);
        free(var->value);
        free(var);
        return -1;
    }
    
    shell->variables = var;
    return 0;
}

char *get_variable(shell_t *shell, char *name)
{
    var_t *var = shell->variables;
    
    while (var) {
        if (strcmp(var->name, name) == 0) {
            return var->value;
        }
        var = var->next;
    }
    
    // Check environment variables as fallback
    return get_env_var(shell, name);
}

int unset_variable(shell_t *shell, char *name)
{
    var_t *var = shell->variables;
    var_t *prev = NULL;
    
    while (var) {
        if (strcmp(var->name, name) == 0) {
            if (prev) {
                prev->next = var->next;
            } else {
                shell->variables = var->next;
            }
            
            free(var->name);
            free(var->value);
            free(var);
            return 0;
        }
        
        prev = var;
        var = var->next;
    }
    
    return 1; // Variable not found
}

void print_variables(shell_t *shell)
{
    var_t *var = shell->variables;
    
    while (var) {
        printf("%s=%s\n", var->name, var->value);
        var = var->next;
    }
}