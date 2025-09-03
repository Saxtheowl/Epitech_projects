/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Server cleanup and memory management
*/

#include "zappy_server.h"

static void cleanup_commands(command_t *commands)
{
    command_t *current = commands;
    command_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->cmd);
        free(current);
        current = next;
    }
}

static void cleanup_players(team_t *team)
{
    player_t *current = team->players;
    player_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->team_name);
        free(current);
        current = next;
    }
    team->players = NULL;
    team->connected_clients = 0;
}

static void cleanup_clients(server_t *server)
{
    int i = 0;

    for (i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != -1) {
            close(server->clients[i].fd);
            server->clients[i].fd = -1;
        }
        if (server->clients[i].commands) {
            cleanup_commands(server->clients[i].commands);
            server->clients[i].commands = NULL;
        }
        server->clients[i].player = NULL;
        server->clients[i].nb_commands = 0;
    }
}

static void cleanup_world(server_t *server)
{
    int i = 0;

    if (!server->world)
        return;
    for (i = 0; i < server->height; i++) {
        if (server->world[i])
            free(server->world[i]);
    }
    free(server->world);
    server->world = NULL;
}

void cleanup_server(server_t *server)
{
    int i = 0;

    cleanup_clients(server);
    for (i = 0; i < server->nb_teams; i++)
        cleanup_players(&server->teams[i]);
    cleanup_world(server);
    if (server->server_fd != -1) {
        close(server->server_fd);
        server->server_fd = -1;
    }
}