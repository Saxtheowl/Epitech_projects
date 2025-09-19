/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** FTP server implementation
*/

#include "myftp.h"

int init_server(server_t *server, int port, char *home_path)
{
    struct sockaddr_in addr;
    int opt = 1;

    server->port = port;
    server->home_path = strdup(home_path);
    server->client_count = 0;

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        perror("socket");
        return -1;
    }

    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server->socket);
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server->socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server->socket);
        return -1;
    }

    if (listen(server->socket, MAX_CLIENTS) == -1) {
        perror("listen");
        close(server->socket);
        return -1;
    }

    server->poll_fds[0].fd = server->socket;
    server->poll_fds[0].events = POLLIN;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].socket = -1;
        server->clients[i].data_socket = -1;
        server->clients[i].passive_socket = -1;
        server->clients[i].authenticated = 0;
        server->clients[i].user_valid = 0;
        server->clients[i].passive_mode = 0;
        server->poll_fds[i + 1].fd = -1;
    }

    return 0;
}

int run_server(server_t *server)
{
    int poll_count;

    while (1) {
        poll_count = poll(server->poll_fds, server->client_count + 1, -1);
        if (poll_count == -1) {
            perror("poll");
            return -1;
        }

        if (server->poll_fds[0].revents & POLLIN) {
            if (handle_new_client(server) == -1) {
                continue;
            }
        }

        for (int i = 0; i < server->client_count; i++) {
            if (server->poll_fds[i + 1].revents & POLLIN) {
                handle_client_command(server, i);
            }
            if (server->poll_fds[i + 1].revents & (POLLHUP | POLLERR)) {
                disconnect_client(server, i);
                i--;
            }
        }
    }

    return 0;
}

void cleanup_server(server_t *server)
{
    if (server->socket != -1) {
        close(server->socket);
    }

    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].socket != -1) {
            close(server->clients[i].socket);
        }
    }

    if (server->home_path) {
        free(server->home_path);
    }
}