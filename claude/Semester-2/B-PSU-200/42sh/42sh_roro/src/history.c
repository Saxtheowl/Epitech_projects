/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Command history management
*/

#include "shell.h"

void add_history_entry(shell_t *shell, char *line)
{
    if (!line || strlen(line) == 0) {
        return;
    }
    
    // Don't add duplicate consecutive entries
    if (shell->history_count > 0 && 
        strcmp(shell->history[shell->history_count - 1], line) == 0) {
        return;
    }
    
    // If history is full, remove oldest entry
    if (shell->history_count >= MAX_HISTORY) {
        free(shell->history[0]);
        
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            shell->history[i] = shell->history[i + 1];
        }
        
        shell->history_count = MAX_HISTORY - 1;
    }
    
    shell->history[shell->history_count] = my_strdup(line);
    if (shell->history[shell->history_count]) {
        shell->history_count++;
    }
    
    // History added to internal storage
}

void print_history(shell_t *shell)
{
    for (int i = 0; i < shell->history_count; i++) {
        printf("%5d  %s\n", i + 1, shell->history[i]);
    }
}

void load_history(shell_t *shell)
{
    char *home = get_env_var(shell, "HOME");
    char history_file[MAX_PATH];
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    
    if (!home) {
        return;
    }
    
    snprintf(history_file, MAX_PATH, "%s/.42sh_history", home);
    
    file = fopen(history_file, "r");
    if (!file) {
        return;
    }
    
    while (getline(&line, &len, file) != -1 && 
           shell->history_count < MAX_HISTORY) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) > 0) {
            shell->history[shell->history_count] = my_strdup(line);
            if (shell->history[shell->history_count]) {
                shell->history_count++;
            }
        }
    }
    
    free(line);
    fclose(file);
}

void save_history(shell_t *shell)
{
    char *home = get_env_var(shell, "HOME");
    char history_file[MAX_PATH];
    FILE *file;
    
    if (!home) {
        return;
    }
    
    snprintf(history_file, MAX_PATH, "%s/.42sh_history", home);
    
    file = fopen(history_file, "w");
    if (!file) {
        return;
    }
    
    for (int i = 0; i < shell->history_count; i++) {
        fprintf(file, "%s\n", shell->history[i]);
    }
    
    fclose(file);
}