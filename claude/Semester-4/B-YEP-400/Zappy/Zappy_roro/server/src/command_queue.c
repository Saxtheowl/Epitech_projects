/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Command queue processing and management
*/

#include "zappy_server.h"

static void add_command_to_queue(client_t *client, char *cmd_str,
    double execution_time)
{
    command_t *new_cmd = malloc(sizeof(command_t));
    command_t *current = NULL;

    if (!new_cmd)
        return;
    new_cmd->cmd = strdup(cmd_str);
    new_cmd->end_time = execution_time;
    new_cmd->next = NULL;
    if (!client->commands) {
        client->commands = new_cmd;
    } else {
        current = client->commands;
        while (current->next)
            current = current->next;
        current->next = new_cmd;
    }
    client->nb_commands++;
}

static int get_command_duration(char *command)
{
    char *cmd = strtok(command, " \n");

    if (!cmd)
        return 0;
    if (strcmp(cmd, "Forward") == 0)
        return 7;
    else if (strcmp(cmd, "Right") == 0 || strcmp(cmd, "Left") == 0)
        return 7;
    else if (strcmp(cmd, "Look") == 0)
        return 7;
    else if (strcmp(cmd, "Inventory") == 0)
        return 1;
    else if (strcmp(cmd, "Broadcast") == 0)
        return 7;
    else if (strcmp(cmd, "Connect_nbr") == 0)
        return 0;
    else if (strcmp(cmd, "Fork") == 0)
        return 42;
    else if (strcmp(cmd, "Eject") == 0)
        return 7;
    else if (strcmp(cmd, "Take") == 0 || strcmp(cmd, "Set") == 0)
        return 7;
    else if (strcmp(cmd, "Incantation") == 0)
        return 300;
    return 0;
}

void process_client_commands(server_t *server, int client_idx)
{
    client_t *client = &server->clients[client_idx];
    char *line = NULL;
    char *next_line = NULL;
    char *buffer_copy = NULL;
    int duration = 0;
    double execution_time = 0.0;

    buffer_copy = strdup(client->buffer);
    if (!buffer_copy)
        return;
    line = strtok(buffer_copy, "\n");
    while (line && client->nb_commands < MAX_COMMANDS) {
        duration = get_command_duration(line);
        execution_time = server->current_time + (duration / (double)server->freq);
        add_command_to_queue(client, line, execution_time);
        line = strtok(NULL, "\n");
    }
    next_line = strstr(client->buffer, "\n");
    if (next_line) {
        next_line++;
        memmove(client->buffer, next_line, strlen(next_line) + 1);
        client->buffer_len = strlen(client->buffer);
    } else {
        client->buffer[0] = '\0';
        client->buffer_len = 0;
    }
    free(buffer_copy);
    while (client->commands && client->commands->end_time <= server->current_time) {
        command_t *cmd = client->commands;
        execute_command(server, client, cmd->cmd);
        client->commands = cmd->next;
        client->nb_commands--;
        free(cmd->cmd);
        free(cmd);
    }
}

void process_all_commands(server_t *server)
{
    command_t *cmd = NULL;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == -1 || !server->clients[i].commands)
            continue;
        while (server->clients[i].commands && 
            server->clients[i].commands->end_time <= server->current_time) {
            cmd = server->clients[i].commands;
            execute_command(server, &server->clients[i], cmd->cmd);
            server->clients[i].commands = cmd->next;
            server->clients[i].nb_commands--;
            free(cmd->cmd);
            free(cmd);
        }
    }
}