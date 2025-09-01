/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   FS commands (PWD/CWD/CDUP)
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ftp.h"

void cmd_pwd(client_t *c)
{
    char fmt[600];
    snprintf(fmt, sizeof(fmt), "257 \"%s\"\r\n", c->cwd);
    client_write(c->fd, fmt);
}

void cmd_cwd(client_t *c, const char *arg, const char *home)
{
    char resolved[512];

    if (!*arg) {
        client_write(c->fd, "501 Syntax error in parameters.\r\n");
        return;
    }
    if (path_resolve(resolved, sizeof(resolved), home, c->cwd, arg) == 0) {
        my_strcpy(c->cwd, resolved, sizeof(c->cwd));
        client_write(c->fd, "250 Requested file action okay, completed.\r\n");
    } else {
        client_write(c->fd, "550 Failed to change directory.\r\n");
    }
}

void cmd_cdup(client_t *c, const char *home)
{
    (void)home;
    return cmd_cwd(c, "..", home);
}

void cmd_noop(client_t *c)
{
    client_write(c->fd, "200 NOOP ok.\\r\\n");
}

void cmd_syst(client_t *c)
{
    client_write(c->fd, "215 UNIX Type: L8\\r\\n");
}
