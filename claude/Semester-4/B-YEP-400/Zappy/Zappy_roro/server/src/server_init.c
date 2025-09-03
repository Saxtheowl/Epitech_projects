/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Server initialization functions
*/

#include "zappy_server.h"

int init_server(server_t *server)
{
    struct sockaddr_in addr;
    int opt = 1;

    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == -1) {
        perror("socket");
        return -1;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server->server_fd);
        return -1;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server->server_fd);
        return -1;
    }
    if (listen(server->server_fd, MAX_CLIENTS) == -1) {
        perror("listen");
        close(server->server_fd);
        return -1;
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].fd = -1;
        server->clients[i].player = NULL;
        server->clients[i].commands = NULL;
        server->clients[i].nb_commands = 0;
    }
    return 0;
}

int init_world(server_t *server)
{
    int i = 0;
    int j = 0;

    server->world = malloc(sizeof(tile_t *) * server->height);
    if (!server->world)
        return -1;
    for (i = 0; i < server->height; i++) {
        server->world[i] = malloc(sizeof(tile_t) * server->width);
        if (!server->world[i]) {
            for (j = 0; j < i; j++)
                free(server->world[j]);
            free(server->world);
            return -1;
        }
        for (j = 0; j < server->width; j++) {
            memset(server->world[i][j].resources, 0, 
                sizeof(server->world[i][j].resources));
        }
    }
    return 0;
}