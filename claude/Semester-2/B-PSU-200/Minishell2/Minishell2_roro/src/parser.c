/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Enhanced parser for pipes, redirections and semicolons
*/

#include "../include/mysh.h"

token_t *create_token(token_type_t type, const char *value)
{
    token_t *token = malloc(sizeof(token_t));

    if (!token)
        return NULL;

    token->type = type;
    token->value = value ? my_strdup(value) : NULL;
    token->next = NULL;

    return token;
}

void add_token(token_t **head, token_t *token)
{
    token_t *current = *head;

    if (!*head) {
        *head = token;
        return;
    }

    while (current->next) {
        current = current->next;
    }
    current->next = token;
}

token_t *tokenize_line(char *line)
{
    token_t *tokens = NULL;
    char *token_str;
    char *saveptr;
    int i;

    if (!line)
        return NULL;

    for (i = 0; line[i]; i++) {
        if (line[i] == '|' && line[i + 1] != '|') {
            memmove(&line[i + 1], &line[i], my_strlen(&line[i]) + 1);
            line[i] = ' ';
            line[i + 1] = '|';
            line[i + 2] = ' ';
            i += 2;
        } else if (line[i] == ';') {
            memmove(&line[i + 1], &line[i], my_strlen(&line[i]) + 1);
            line[i] = ' ';
            line[i + 1] = ';';
            line[i + 2] = ' ';
            i += 2;
        } else if (line[i] == '>' && line[i + 1] == '>') {
            memmove(&line[i + 2], &line[i], my_strlen(&line[i]) + 1);
            line[i] = ' ';
            line[i + 1] = '>';
            line[i + 2] = '>';
            line[i + 3] = ' ';
            i += 3;
        } else if (line[i] == '<' && line[i + 1] == '<') {
            memmove(&line[i + 2], &line[i], my_strlen(&line[i]) + 1);
            line[i] = ' ';
            line[i + 1] = '<';
            line[i + 2] = '<';
            line[i + 3] = ' ';
            i += 3;
        } else if (line[i] == '>' || line[i] == '<') {
            memmove(&line[i + 1], &line[i], my_strlen(&line[i]) + 1);
            line[i] = ' ';
            line[i + 2] = ' ';
            i += 2;
        }
    }

    token_str = strtok_r(line, " \t\n", &saveptr);
    while (token_str) {
        token_t *token = NULL;

        if (my_strcmp(token_str, "|") == 0) {
            token = create_token(TOKEN_PIPE, NULL);
        } else if (my_strcmp(token_str, ";") == 0) {
            token = create_token(TOKEN_SEMICOLON, NULL);
        } else if (my_strcmp(token_str, ">") == 0) {
            token = create_token(TOKEN_REDIRECT_OUT, NULL);
        } else if (my_strcmp(token_str, "<") == 0) {
            token = create_token(TOKEN_REDIRECT_IN, NULL);
        } else if (my_strcmp(token_str, ">>") == 0) {
            token = create_token(TOKEN_REDIRECT_APPEND, NULL);
        } else if (my_strcmp(token_str, "<<") == 0) {
            token = create_token(TOKEN_REDIRECT_HEREDOC, NULL);
        } else {
            token = create_token(TOKEN_COMMAND, token_str);
        }

        if (token) {
            add_token(&tokens, token);
        }

        token_str = strtok_r(NULL, " \t\n", &saveptr);
    }

    return tokens;
}

command_t *create_command(void)
{
    command_t *cmd = malloc(sizeof(command_t));

    if (!cmd)
        return NULL;

    cmd->args = malloc(MAX_ARGS * sizeof(char *));
    cmd->redirects = malloc(MAX_REDIRECTS * sizeof(redirect_t));

    if (!cmd->args || !cmd->redirects) {
        free(cmd->args);
        free(cmd->redirects);
        free(cmd);
        return NULL;
    }

    cmd->arg_count = 0;
    cmd->redirect_count = 0;
    cmd->next = NULL;

    return cmd;
}

command_t *parse_command_tokens(token_t **tokens)
{
    command_t *cmd = create_command();
    token_t *current = *tokens;

    if (!cmd)
        return NULL;

    while (current && current->type != TOKEN_PIPE && 
           current->type != TOKEN_SEMICOLON && current->type != TOKEN_END) {
        
        if (current->type == TOKEN_COMMAND) {
            if (cmd->arg_count < MAX_ARGS - 1) {
                cmd->args[cmd->arg_count++] = my_strdup(current->value);
            }
        } else if (is_redirect_token(current->type) && current->next) {
            if (cmd->redirect_count < MAX_REDIRECTS) {
                cmd->redirects[cmd->redirect_count].type = current->type;
                cmd->redirects[cmd->redirect_count].file = 
                    my_strdup(current->next->value);
                cmd->redirects[cmd->redirect_count].fd = -1;
                cmd->redirect_count++;
                current = current->next;
            }
        }
        current = current->next;
    }

    cmd->args[cmd->arg_count] = NULL;
    *tokens = current;
    return cmd;
}

pipeline_t *parse_tokens(token_t *tokens)
{
    pipeline_t *pipeline = malloc(sizeof(pipeline_t));
    command_t *cmd_head = NULL;
    command_t *cmd_tail = NULL;
    token_t *current = tokens;
    int cmd_count = 0;

    if (!pipeline)
        return NULL;

    while (current && current->type != TOKEN_SEMICOLON && 
           current->type != TOKEN_END) {
        command_t *cmd = parse_command_tokens(&current);

        if (cmd && cmd->arg_count > 0) {
            if (!cmd_head) {
                cmd_head = cmd;
                cmd_tail = cmd;
            } else {
                cmd_tail->next = cmd;
                cmd_tail = cmd;
            }
            cmd_count++;
        } else if (cmd) {
            free_command(cmd);
        }

        if (current && current->type == TOKEN_PIPE) {
            current = current->next;
        }
    }

    pipeline->commands = cmd_head;
    pipeline->command_count = cmd_count;
    pipeline->next = NULL;

    return pipeline;
}

int is_redirect_token(token_type_t type)
{
    return type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT ||
           type == TOKEN_REDIRECT_APPEND || type == TOKEN_REDIRECT_HEREDOC;
}

void free_tokens(token_t *tokens)
{
    token_t *current = tokens;
    token_t *next;

    while (current) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void free_command(command_t *command)
{
    int i;

    if (!command)
        return;

    for (i = 0; i < command->arg_count; i++) {
        free(command->args[i]);
    }
    free(command->args);

    for (i = 0; i < command->redirect_count; i++) {
        free(command->redirects[i].file);
    }
    free(command->redirects);

    free(command);
}

void free_pipeline(pipeline_t *pipeline)
{
    command_t *current = pipeline->commands;
    command_t *next;

    while (current) {
        next = current->next;
        free_command(current);
        current = next;
    }

    free(pipeline);
}