#include "mysh.h"

pipeline_t *parse_line(char *line)
{
    char *saveptr;
    char *token;
    pipeline_t *first_pipeline = NULL;
    pipeline_t *current_pipeline = NULL;
    pipeline_t *new_pipeline;

    token = strtok_r(line, ";", &saveptr);
    while (token) {
        while (*token == ' ')
            token++;
        
        if (*token != '\0') {
            new_pipeline = malloc(sizeof(pipeline_t));
            if (!new_pipeline)
                return first_pipeline;
            
            new_pipeline->commands = parse_command(token);
            new_pipeline->next = NULL;
            
            if (!first_pipeline) {
                first_pipeline = new_pipeline;
                current_pipeline = new_pipeline;
            } else {
                current_pipeline->next = new_pipeline;
                current_pipeline = new_pipeline;
            }
        }
        token = strtok_r(NULL, ";", &saveptr);
    }
    return first_pipeline;
}

cmd_t *parse_command(char *cmd_str)
{
    char **pipe_cmds;
    cmd_t *first_cmd = NULL;
    cmd_t *current_cmd = NULL;
    cmd_t *new_cmd;
    int i = 0;

    pipe_cmds = split_by_pipes(cmd_str);
    if (!pipe_cmds)
        return NULL;

    while (pipe_cmds[i]) {
        new_cmd = malloc(sizeof(cmd_t));
        if (!new_cmd)
            break;
        
        new_cmd->args = tokenize_command(pipe_cmds[i]);
        new_cmd->input_redirect = NULL;
        new_cmd->output_redirect = NULL;
        new_cmd->append_output = 0;
        new_cmd->next = NULL;
        
        parse_redirections(new_cmd);
        
        if (!first_cmd) {
            first_cmd = new_cmd;
            current_cmd = new_cmd;
        } else {
            current_cmd->next = new_cmd;
            current_cmd = new_cmd;
        }
        i++;
    }
    
    for (i = 0; pipe_cmds[i]; i++)
        free(pipe_cmds[i]);
    free(pipe_cmds);
    
    return first_cmd;
}

char **split_by_pipes(char *str)
{
    char **result = malloc(sizeof(char*) * MAX_PIPES);
    char *saveptr;
    char *token;
    int count = 0;

    if (!result)
        return NULL;

    token = strtok_r(str, "|", &saveptr);
    while (token && count < MAX_PIPES - 1) {
        while (*token == ' ')
            token++;
        result[count] = my_strdup(token);
        count++;
        token = strtok_r(NULL, "|", &saveptr);
    }
    result[count] = NULL;
    return result;
}

char **tokenize_command(char *cmd_str)
{
    char **args = malloc(sizeof(char*) * MAX_ARGS);
    char *saveptr;
    char *token;
    int count = 0;

    if (!args)
        return NULL;

    token = strtok_r(cmd_str, " \t\n", &saveptr);
    while (token && count < MAX_ARGS - 1) {
        args[count] = my_strdup(token);
        count++;
        token = strtok_r(NULL, " \t\n", &saveptr);
    }
    args[count] = NULL;
    return args;
}

void parse_redirections(cmd_t *cmd)
{
    int i, j;
    
    if (!cmd->args)
        return;

    for (i = 0; cmd->args[i]; i++) {
        if (strcmp(cmd->args[i], ">") == 0 && cmd->args[i + 1]) {
            cmd->output_redirect = my_strdup(cmd->args[i + 1]);
            cmd->append_output = 0;
            
            free(cmd->args[i]);
            free(cmd->args[i + 1]);
            for (j = i; cmd->args[j + 2]; j++)
                cmd->args[j] = cmd->args[j + 2];
            cmd->args[j] = NULL;
            cmd->args[j + 1] = NULL;
            i--;
        } else if (strcmp(cmd->args[i], ">>") == 0 && cmd->args[i + 1]) {
            cmd->output_redirect = my_strdup(cmd->args[i + 1]);
            cmd->append_output = 1;
            
            free(cmd->args[i]);
            free(cmd->args[i + 1]);
            for (j = i; cmd->args[j + 2]; j++)
                cmd->args[j] = cmd->args[j + 2];
            cmd->args[j] = NULL;
            cmd->args[j + 1] = NULL;
            i--;
        } else if (strcmp(cmd->args[i], "<") == 0 && cmd->args[i + 1]) {
            cmd->input_redirect = my_strdup(cmd->args[i + 1]);
            
            free(cmd->args[i]);
            free(cmd->args[i + 1]);
            for (j = i; cmd->args[j + 2]; j++)
                cmd->args[j] = cmd->args[j + 2];
            cmd->args[j] = NULL;
            cmd->args[j + 1] = NULL;
            i--;
        }
    }
}