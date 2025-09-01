/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   USER/PASS/QUIT
*/

#include <string.h>
#include <unistd.h>
#include "ftp.h"

void cmd_user(client_t *c, const char *arg)
{
    c->has_user = false;
    c->logged = false;
    if (str_ieq(arg, "Anonymous")) {
        c->has_user = true;
        my_strcpy(c->user, arg, sizeof(c->user));
        client_write(c->fd, "331 User name okay, need password.\r\n");
    } else {
        client_write(c->fd, "530 Not logged in.\r\n");
    }
}

void cmd_pass(client_t *c, const char *arg)
{
    (void)arg;
    if (c->has_user) {
        c->logged = true;
        client_write(c->fd, "230 User logged in, proceed.\r\n");
    } else {
        client_write(c->fd, "503 Bad sequence of commands.\r\n");
    }
}

void cmd_quit(server_t *srv, client_t *c)
{
    (void)srv;
    client_write(c->fd, "221 Service closing control connection.\r\n");
    client_close(c);
}

