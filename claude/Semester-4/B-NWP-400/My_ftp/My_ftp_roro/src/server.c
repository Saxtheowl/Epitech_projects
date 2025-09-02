/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Server initialization and main loop
*/

#include "myftp.h"

int init_server(server_t *server, int port, const char *path)
{
    struct sockaddr_in addr;
    int opt = 1;

    memset(server, 0, sizeof(server_t));
    server->port = port;
    strncpy(server->root_path, path, PATH_SIZE - 1);

    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd < 0) {
        perror("socket");
        return -1;
    }

    if (setsockopt(server->socket_fd, SOL_SOCKET, SO_REUSEADDR, 
                   &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server->socket_fd);
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server->socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server->socket_fd);
        return -1;
    }

    if (listen(server->socket_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server->socket_fd);
        return -1;
    }

    server->fds[0].fd = server->socket_fd;
    server->fds[0].events = POLLIN;
    server->client_count = 1;

    return 0;
}

int run_server(server_t *server)
{
    int poll_result;

    while (1) {
        poll_result = poll(server->fds, server->client_count, -1);
        
        if (poll_result < 0) {
            if (errno == EINTR)
                continue;
            perror("poll");
            return -1;
        }

        if (server->fds[0].revents & POLLIN) {
            if (accept_new_client(server) < 0)
                continue;
        }

        for (int i = 1; i < server->client_count; i++) {
            if (server->fds[i].revents & POLLIN) {
                if (handle_client_data(server, i) < 0) {
                    disconnect_client(server, i);
                    i--;
                }
            }
        }
    }

    return 0;
}

void cleanup_server(server_t *server)
{
    if (server->socket_fd >= 0)
        close(server->socket_fd);

    for (int i = 1; i < server->client_count; i++) {
        if (server->fds[i].fd >= 0)
            close(server->fds[i].fd);
        if (server->clients[i].data_fd >= 0)
            close(server->clients[i].data_fd);
    }
}