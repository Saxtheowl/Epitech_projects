/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Utility functions
*/

#include "shell.h"

char *my_strdup(char *str)
{
    char *dup;
    int len, i;
    
    if (!str) {
        return NULL;
    }
    
    len = strlen(str);
    dup = malloc(len + 1);
    
    if (!dup) {
        return NULL;
    }
    
    for (i = 0; i <= len; i++) {
        dup[i] = str[i];
    }
    
    return dup;
}

char **my_strtok(char *str, char *delim)
{
    char **tokens = malloc(sizeof(char*) * MAX_ARGS);
    char *token;
    int count = 0;
    
    if (!tokens) {
        return NULL;
    }
    
    token = strtok(str, delim);
    while (token && count < MAX_ARGS - 1) {
        tokens[count] = my_strdup(token);
        if (!tokens[count]) {
            free_array(tokens);
            return NULL;
        }
        count++;
        token = strtok(NULL, delim);
    }
    
    tokens[count] = NULL;
    return tokens;
}

void free_array(char **array)
{
    if (!array) {
        return;
    }
    
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    
    free(array);
}

int count_array(char **array)
{
    int count = 0;
    
    if (!array) {
        return 0;
    }
    
    while (array[count]) {
        count++;
    }
    
    return count;
}

char *expand_variables(shell_t *shell, char *str)
{
    if (!str || !shell) {
        return NULL;
    }
    
    char *result = malloc(strlen(str) * 3 + 256);
    char *current = str;
    char *dest = result;
    
    if (!result) {
        return NULL;
    }
    
    while (*current) {
        if (*current == '$' && *(current + 1)) {
            current++; // Skip $
            
            // Handle special variables
            if (*current == '?') {
                char exit_str[16];
                snprintf(exit_str, 16, "%d", shell->exit_status);
                strcpy(dest, exit_str);
                dest += strlen(exit_str);
                current++;
            } else if (*current == '$') {
                char pid_str[16];
                snprintf(pid_str, 16, "%d", getpid());
                strcpy(dest, pid_str);
                dest += strlen(pid_str);
                current++;
            } else if (strncmp(current, "cwd", 3) == 0) {
                strcpy(dest, shell->cwd);
                dest += strlen(shell->cwd);
                current += 3;
            } else {
                // Extract variable name
                char var_name[256];
                int i = 0;
                
                while (*current && (isalnum(*current) || *current == '_') && 
                       i < 255) {
                    var_name[i++] = *current++;
                }
                var_name[i] = '\0';
                
                if (i > 0) {
                    char *value = get_variable(shell, var_name);
                    if (value) {
                        strcpy(dest, value);
                        dest += strlen(value);
                    }
                }
            }
        } else {
            *dest++ = *current++;
        }
    }
    
    *dest = '\0';
    
    // Reallocate to actual size
    char *final_result = my_strdup(result);
    free(result);
    return final_result;
}

char *get_prompt(shell_t *shell)
{
    (void)shell;
    return my_strdup("42sh$ ");
}