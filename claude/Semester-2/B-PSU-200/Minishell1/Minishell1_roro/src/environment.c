/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Environment management functions
*/

#include "../include/mysh.h"

env_t *create_env_node(const char *name, const char *value)
{
    env_t *node = malloc(sizeof(env_t));
    
    if (!node)
        return NULL;
        
    node->name = my_strdup(name);
    node->value = my_strdup(value);
    node->next = NULL;
    
    if (!node->name || !node->value) {
        free(node->name);
        free(node->value);
        free(node);
        return NULL;
    }
    
    return node;
}

void add_env_var(shell_t *shell, const char *name, const char *value)
{
    env_t *current = shell->env_list;
    env_t *new_node;

    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            free(current->value);
            current->value = my_strdup(value);
            return;
        }
        current = current->next;
    }
    
    new_node = create_env_node(name, value);
    if (!new_node)
        return;
        
    new_node->next = shell->env_list;
    shell->env_list = new_node;
}

char *get_env_var(shell_t *shell, const char *name)
{
    env_t *current = shell->env_list;

    while (current) {
        if (my_strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    
    return NULL;
}

void remove_env_var(shell_t *shell, const char *name)
{
    env_t *current = shell->env_list;
    env_t *prev = NULL;

    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            if (prev)
                prev->next = current->next;
            else
                shell->env_list = current->next;
                
            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void init_environment(shell_t *shell, char **environ)
{
    int i;
    char *eq_pos;
    char name[256];
    char *value;

    for (i = 0; environ[i]; i++) {
        eq_pos = strchr(environ[i], '=');
        if (eq_pos) {
            strncpy(name, environ[i], eq_pos - environ[i]);
            name[eq_pos - environ[i]] = '\0';
            value = eq_pos + 1;
            add_env_var(shell, name, value);
        }
    }
}

void cleanup_environment(shell_t *shell)
{
    env_t *current = shell->env_list;
    env_t *next;

    while (current) {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    
    shell->env_list = NULL;
    
    if (shell->environ_copy) {
        for (int i = 0; shell->environ_copy[i]; i++)
            free(shell->environ_copy[i]);
        free(shell->environ_copy);
        shell->environ_copy = NULL;
    }
}

char **env_list_to_array(shell_t *shell)
{
    env_t *current = shell->env_list;
    int count = 0;
    int i = 0;
    char **env_array;
    char *env_string;
    int name_len, value_len;

    while (current) {
        count++;
        current = current->next;
    }
    
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return NULL;
        
    current = shell->env_list;
    while (current && i < count) {
        name_len = my_strlen(current->name);
        value_len = my_strlen(current->value);
        env_string = malloc(name_len + value_len + 2);
        
        if (env_string) {
            strcpy(env_string, current->name);
            strcat(env_string, "=");
            strcat(env_string, current->value);
            env_array[i] = env_string;
            i++;
        }
        current = current->next;
    }
    
    env_array[i] = NULL;
    return env_array;
}