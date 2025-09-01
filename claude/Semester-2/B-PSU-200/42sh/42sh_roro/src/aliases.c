/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Alias management
*/

#include "shell.h"

int add_alias(shell_t *shell, char *name, char *value)
{
    alias_t *alias = shell->aliases;
    
    // Check if alias already exists
    while (alias) {
        if (strcmp(alias->name, name) == 0) {
            free(alias->value);
            alias->value = my_strdup(value);
            return alias->value ? 0 : -1;
        }
        alias = alias->next;
    }
    
    // Create new alias
    alias = malloc(sizeof(alias_t));
    if (!alias) {
        return -1;
    }
    
    alias->name = my_strdup(name);
    alias->value = my_strdup(value);
    alias->next = shell->aliases;
    
    if (!alias->name || !alias->value) {
        free(alias->name);
        free(alias->value);
        free(alias);
        return -1;
    }
    
    shell->aliases = alias;
    return 0;
}

char *get_alias(shell_t *shell, char *name)
{
    alias_t *alias = shell->aliases;
    
    while (alias) {
        if (strcmp(alias->name, name) == 0) {
            return alias->value;
        }
        alias = alias->next;
    }
    
    return NULL;
}

int remove_alias(shell_t *shell, char *name)
{
    alias_t *alias = shell->aliases;
    alias_t *prev = NULL;
    
    while (alias) {
        if (strcmp(alias->name, name) == 0) {
            if (prev) {
                prev->next = alias->next;
            } else {
                shell->aliases = alias->next;
            }
            
            free(alias->name);
            free(alias->value);
            free(alias);
            return 0;
        }
        
        prev = alias;
        alias = alias->next;
    }
    
    return 1; // Alias not found
}

void print_aliases(shell_t *shell)
{
    alias_t *alias = shell->aliases;
    
    while (alias) {
        printf("%s=%s\n", alias->name, alias->value);
        alias = alias->next;
    }
}