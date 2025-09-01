/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Parser for 42sh shell commands
*/

#include "shell.h"

static cmd_t *create_command(void)
{
    cmd_t *cmd = malloc(sizeof(cmd_t));
    
    if (!cmd) {
        return NULL;
    }
    
    cmd->args = malloc(sizeof(char*) * MAX_ARGS);
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = 0;
    cmd->background = 0;
    cmd->next = NULL;
    
    if (!cmd->args) {
        free(cmd);
        return NULL;
    }
    
    cmd->args[0] = NULL;
    return cmd;
}

static int add_argument(cmd_t *cmd, char *arg)
{
    int count = 0;
    
    while (cmd->args[count] && count < MAX_ARGS - 1) {
        count++;
    }
    
    if (count >= MAX_ARGS - 1) {
        return -1;
    }
    
    cmd->args[count] = my_strdup(arg);
    cmd->args[count + 1] = NULL;
    
    return 0;
}

static int parse_redirection(cmd_t *cmd, token_t **tokens)
{
    token_t *current = *tokens;
    token_type_t redir_type = current->type;
    
    current = current->next;
    if (!current || current->type != TOKEN_WORD) {
        return -1;
    }
    
    switch (redir_type) {
    case TOKEN_REDIRECT_IN:
        if (cmd->input_file) {
            free(cmd->input_file);
        }
        cmd->input_file = my_strdup(current->value);
        break;
    case TOKEN_REDIRECT_OUT:
        if (cmd->output_file) {
            free(cmd->output_file);
        }
        cmd->output_file = my_strdup(current->value);
        cmd->append_output = 0;
        break;
    case TOKEN_REDIRECT_APPEND:
        if (cmd->output_file) {
            free(cmd->output_file);
        }
        cmd->output_file = my_strdup(current->value);
        cmd->append_output = 1;
        break;
    case TOKEN_REDIRECT_ERR:
        // For simplicity, treat stderr redirection like stdout
        if (cmd->output_file) {
            free(cmd->output_file);
        }
        cmd->output_file = my_strdup(current->value);
        cmd->append_output = 0;
        break;
    default:
        return -1;
    }
    
    *tokens = current->next;
    return 0;
}

cmd_t *parse_command(token_t **tokens)
{
    cmd_t *cmd = create_command();
    token_t *current = *tokens;
    
    if (!cmd) {
        return NULL;
    }
    
    while (current && current->type != TOKEN_EOF && 
           current->type != TOKEN_PIPE && 
           current->type != TOKEN_SEMICOLON &&
           current->type != TOKEN_AND &&
           current->type != TOKEN_OR &&
           current->type != TOKEN_BACKGROUND) {
        
        if (current->type == TOKEN_WORD) {
            // Check if the argument contains glob patterns
            if (strchr(current->value, '*') || strchr(current->value, '?') || 
                strchr(current->value, '[')) {
                char **expanded = expand_glob(current->value);
                if (expanded && expanded[0]) {
                    for (int i = 0; expanded[i]; i++) {
                        if (add_argument(cmd, expanded[i]) != 0) {
                            free_glob_result(expanded);
                            free_command(cmd);
                            return NULL;
                        }
                    }
                    free_glob_result(expanded);
                } else {
                    // No expansion, use original
                    if (add_argument(cmd, current->value) != 0) {
                        free_command(cmd);
                        return NULL;
                    }
                    if (expanded) free_glob_result(expanded);
                }
            } else {
                if (add_argument(cmd, current->value) != 0) {
                    free_command(cmd);
                    return NULL;
                }
            }
            current = current->next;
        } else if (current->type == TOKEN_REDIRECT_IN ||
                   current->type == TOKEN_REDIRECT_OUT ||
                   current->type == TOKEN_REDIRECT_APPEND ||
                   current->type == TOKEN_REDIRECT_ERR) {
            if (parse_redirection(cmd, &current) != 0) {
                free_command(cmd);
                return NULL;
            }
        } else {
            break;
        }
    }
    
    *tokens = current;
    
    // Check if command is empty
    if (!cmd->args[0]) {
        free_command(cmd);
        return NULL;
    }
    
    return cmd;
}

pipeline_t *parse_pipeline(token_t **tokens)
{
    pipeline_t *pipeline = malloc(sizeof(pipeline_t));
    cmd_t *first_cmd, *current_cmd;
    token_t *current = *tokens;
    
    if (!pipeline) {
        return NULL;
    }
    
    pipeline->commands = NULL;
    pipeline->background = 0;
    pipeline->next = NULL;
    
    first_cmd = parse_command(&current);
    if (!first_cmd) {
        free(pipeline);
        return NULL;
    }
    
    pipeline->commands = first_cmd;
    current_cmd = first_cmd;
    
    // Parse pipe chain
    while (current && current->type == TOKEN_PIPE) {
        current = current->next; // Skip pipe token
        
        cmd_t *next_cmd = parse_command(&current);
        if (!next_cmd) {
            free_pipeline(pipeline);
            return NULL;
        }
        
        current_cmd->next = next_cmd;
        current_cmd = next_cmd;
    }
    
    // Check for background execution
    if (current && current->type == TOKEN_BACKGROUND) {
        pipeline->background = 1;
        // Also mark the last command as background
        if (current_cmd) {
            current_cmd->background = 1;
        }
        current = current->next;
    }
    
    *tokens = current;
    return pipeline;
}

void free_command(cmd_t *cmd)
{
    if (!cmd) {
        return;
    }
    
    if (cmd->args) {
        free_array(cmd->args);
    }
    
    if (cmd->input_file) {
        free(cmd->input_file);
    }
    
    if (cmd->output_file) {
        free(cmd->output_file);
    }
    
    free(cmd);
}

void free_pipeline(pipeline_t *pipeline)
{
    if (!pipeline) {
        return;
    }
    
    cmd_t *cmd = pipeline->commands;
    while (cmd) {
        cmd_t *next = cmd->next;
        free_command(cmd);
        cmd = next;
    }
    
    free(pipeline);
}