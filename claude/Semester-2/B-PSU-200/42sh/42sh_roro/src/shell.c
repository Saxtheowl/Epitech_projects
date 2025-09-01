/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Core shell functions
*/

#include "shell.h"

int init_shell(shell_t *shell, char **env)
{
    shell->env = copy_env(env);
    shell->aliases = NULL;
    shell->variables = NULL;
    shell->jobs = NULL;
    shell->history = malloc(sizeof(char*) * MAX_HISTORY);
    shell->history_count = 0;
    shell->exit_status = 0;
    shell->interactive = 0;
    shell->prompt = NULL;
    
    if (!shell->env || !shell->history) {
        return -1;
    }
    
    if (getcwd(shell->cwd, MAX_PATH) == NULL) {
        strcpy(shell->cwd, "/");
    }
    
    // Initialize special variables
    set_variable(shell, "cwd", shell->cwd);
    set_variable(shell, "term", "42sh");
    
    // load_history(shell); // Disabled for now
    return 0;
}

void cleanup_shell(shell_t *shell)
{
    if (shell->env) {
        free_array(shell->env);
    }
    
    alias_t *alias = shell->aliases;
    while (alias) {
        alias_t *next = alias->next;
        free(alias->name);
        free(alias->value);
        free(alias);
        alias = next;
    }
    
    var_t *var = shell->variables;
    while (var) {
        var_t *next = var->next;
        free(var->name);
        free(var->value);
        free(var);
        var = next;
    }
    
    job_t *job = shell->jobs;
    while (job) {
        job_t *next = job->next;
        free(job->command);
        free(job);
        job = next;
    }
    
    if (shell->history) {
        for (int i = 0; i < shell->history_count; i++) {
            free(shell->history[i]);
        }
        free(shell->history);
    }
    
    if (shell->prompt) {
        free(shell->prompt);
    }
    
    // save_history(shell); // Disabled for now
}

void shell_loop(shell_t *shell)
{
    char *line;
    
    while (1) {
        update_jobs(shell);
        
        if (shell->interactive) {
            line = line_editing_read(shell);
        } else {
            line = read_line();
        }
        
        if (!line) {
            if (shell->interactive) {
                printf("exit\n");
            }
            break;
        }
        
        if (strlen(line) > 0) {
            add_history_entry(shell, line);
            execute_line(shell, line);
        }
        
        free(line);
    }
}

char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    
    if (getline(&line, &bufsize, stdin) == -1) {
        if (line) {
            free(line);
        }
        return NULL;
    }
    
    // Remove newline
    line[strcspn(line, "\n")] = '\0';
    
    return line;
}

int execute_line(shell_t *shell, char *line)
{
    token_t *tokens;
    pipeline_t *pipeline;
    int status = 0;
    
    // Expand variables and aliases
    char *expanded = expand_variables(shell, line);
    if (!expanded) {
        return -1;
    }
    
    tokens = tokenize(expanded);
    free(expanded);
    
    if (!tokens) {
        return 0;
    }
    
    while (tokens && tokens->type != TOKEN_EOF) {
        pipeline = parse_pipeline(&tokens);
        if (pipeline) {
            status = execute_pipeline(shell, pipeline);
            free_pipeline(pipeline);
        }
        
        // Skip semicolons
        while (tokens && tokens->type == TOKEN_SEMICOLON) {
            token_t *next = tokens->next;
            free(tokens->value);
            free(tokens);
            tokens = next;
        }
    }
    
    free_tokens(tokens);
    return status;
}