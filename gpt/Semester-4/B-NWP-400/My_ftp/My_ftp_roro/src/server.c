/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Server lifecycle
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ftp.h"

int server_init(server_t *srv, int port, const char *home)
{
    int fd = -1;
    int yes = 1;

    memset(srv, 0, sizeof(*srv));
    if (!realpath(home, srv->home))
        my_strcpy(srv->home, home, sizeof(srv->home));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        return -1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    srv->addr.sin_family = AF_INET;
    srv->addr.sin_addr.s_addr = INADDR_ANY;
    srv->addr.sin_port = htons((uint16_t)port);
    if (bind(fd, (struct sockaddr *)&srv->addr, sizeof(srv->addr)) < 0)
        return -1;
    if (listen(fd, 16) < 0)
        return -1;
    srv->listen_fd = fd;
    return 0;
}

void server_close(server_t *srv)
{
    close(srv->listen_fd);
    for (int i = 0; i < MAX_CLIENTS; ++i)
        client_close(&srv->clients[i]);
}

void server_run(server_t *srv)
{
    while (1) {
        if (poll_once(srv) < 0)
            break;
    }
}
