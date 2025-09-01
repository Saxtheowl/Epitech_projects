/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   poll loop
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include "ftp.h"

static void client_read_line(server_t *srv, client_t *c)
{
    char *nl = NULL;
    ssize_t r = read(c->fd, c->inbuf + c->inlen, RECV_BUF - c->inlen - 1);
    if (r <= 0) {
        client_close(c);
        return;
    }
    c->inlen += (size_t)r;
    c->inbuf[c->inlen] = '\0';
    while ((nl = strchr(c->inbuf, '\n')) != NULL) {
        *nl = '\0';
        if (nl > c->inbuf && *(nl - 1) == '\r')
            *(nl - 1) = '\0';
        client_handle_line(srv, c, c->inbuf);
        size_t rem = c->inlen - ((nl - c->inbuf) + 1);
        memmove(c->inbuf, nl + 1, rem);
        c->inlen = rem;
        c->inbuf[c->inlen] = '\0';
    }
}

int poll_once(server_t *srv)
{
    struct pollfd fds[1 + MAX_CLIENTS];
    int nfds = 0;

    fds[nfds].fd = srv->listen_fd;
    fds[nfds].events = POLLIN;
    nfds++;
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (srv->clients[i].fd > 0) {
            fds[nfds].fd = srv->clients[i].fd;
            fds[nfds].events = POLLIN;
            nfds++;
        }
    }
    if (poll(fds, nfds, -1) < 0)
        return -1;
    int idx = 0;
    if (fds[idx++].revents & POLLIN)
        client_accept(srv);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        client_t *c = &srv->clients[i];
        if (c->fd <= 0)
            continue;
        if (fds[idx].revents & POLLIN)
            client_read_line(srv, c);
        idx++;
    }
    return 0;
}

