/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Environment variable management
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

    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            free(current->value);
            current->value = my_strdup(value);
            return;
        }
        if (!current->next)
            break;
        current = current->next;
    }

    env_t *new_node = create_env_node(name, value);
    if (!new_node)
        return;

    if (!shell->env_list) {
        shell->env_list = new_node;
    } else {
        current->next = new_node;
    }
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
            if (prev) {
                prev->next = current->next;
            } else {
                shell->env_list = current->next;
            }
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
    int i = 0;
    char *eq_pos;
    char name[256];
    char *value;

    shell->env_list = NULL;

    while (environ[i]) {
        eq_pos = strchr(environ[i], '=');
        if (eq_pos) {
            int name_len = eq_pos - environ[i];
            strncpy(name, environ[i], name_len);
            name[name_len] = '\0';
            value = eq_pos + 1;
            add_env_var(shell, name, value);
        }
        i++;
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
}

char **env_list_to_array(shell_t *shell)
{
    int count = 0;
    env_t *current = shell->env_list;
    char **environ_array;
    int i = 0;

    while (current) {
        count++;
        current = current->next;
    }

    environ_array = malloc((count + 1) * sizeof(char *));
    if (!environ_array)
        return NULL;

    current = shell->env_list;
    while (current && i < count) {
        int len = my_strlen(current->name) + my_strlen(current->value) + 2;
        environ_array[i] = malloc(len);
        if (environ_array[i]) {
            strcpy(environ_array[i], current->name);
            strcat(environ_array[i], "=");
            strcat(environ_array[i], current->value);
        }
        current = current->next;
        i++;
    }

    environ_array[i] = NULL;
    return environ_array;
}