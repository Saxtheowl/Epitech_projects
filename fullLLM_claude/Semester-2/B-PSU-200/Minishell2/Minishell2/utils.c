#include "mysh.h"

char *my_strdup(char *str)
{
    char *dup;
    int i = 0;

    if (!str)
        return NULL;

    dup = malloc(strlen(str) + 1);
    if (!dup)
        return NULL;

    while (str[i]) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';

    return dup;
}

void print_error(char *message)
{
    fprintf(stderr, "%s\n", message);
}

void free_command(cmd_t *cmd)
{
    int i;

    if (!cmd)
        return;

    if (cmd->args) {
        for (i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }

    if (cmd->input_redirect)
        free(cmd->input_redirect);
    
    if (cmd->output_redirect)
        free(cmd->output_redirect);

    free(cmd);
}

void free_pipeline(pipeline_t *pipeline)
{
    pipeline_t *temp_pipeline;
    cmd_t *cmd, *temp_cmd;

    while (pipeline) {
        cmd = pipeline->commands;
        while (cmd) {
            temp_cmd = cmd->next;
            free_command(cmd);
            cmd = temp_cmd;
        }
        temp_pipeline = pipeline->next;
        free(pipeline);
        pipeline = temp_pipeline;
    }
}

char **copy_env(char **env)
{
    int count = 0;
    int i;
    char **new_env;

    if (!env)
        return NULL;

    while (env[count])
        count++;

    new_env = malloc(sizeof(char*) * (count + 1));
    if (!new_env)
        return NULL;

    for (i = 0; i < count; i++) {
        new_env[i] = my_strdup(env[i]);
        if (!new_env[i]) {
            free_env(new_env);
            return NULL;
        }
    }
    new_env[count] = NULL;

    return new_env;
}

void free_env(char **env)
{
    int i;

    if (!env)
        return;

    for (i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}