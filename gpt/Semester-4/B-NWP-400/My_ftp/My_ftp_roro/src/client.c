/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Client mgmt and command dispatch
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "ftp.h"

void client_init(client_t *c)
{
    memset(c, 0, sizeof(*c));
    c->fd = -1;
    c->pasv_fd = -1;
    c->data_active = false;
    c->rnfr_pending = false;
    c->rnfr_path[0] = '\0';
}

void client_write(int fd, const char *msg)
{
    write(fd, msg, my_strlen(msg));
}

void client_accept(server_t *srv)
{
    struct sockaddr_in cli;
    socklen_t sl = sizeof(cli);
    int cfd = accept(srv->listen_fd, (struct sockaddr *)&cli, &sl);
    if (cfd < 0)
        return;
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        client_t *c = &srv->clients[i];
        if (c->fd <= 0) {
            client_init(c);
            c->fd = cfd;
            my_strcpy(c->cwd, srv->home, sizeof(c->cwd));
            client_write(c->fd, "220 Service ready for new user.\r\n");
            return;
        }
    }
    client_write(cfd, "421 Too many users.\r\n");
    close(cfd);
}

void client_close(client_t *c)
{
    if (c->fd > 0) close(c->fd);
    if (c->pasv_fd > 0) close(c->pasv_fd);
    client_init(c);
}

static void parse_cmd(const char *line, char *cmd, size_t ccap, char *arg, size_t acap)
{
    size_t i = 0, j = 0;
    while (line[i] && line[i] != ' ' && j + 1 < ccap) cmd[j++] = line[i++];
    cmd[j] = '\0';
    while (line[i] == ' ') i++;
    j = 0;
    while (line[i] && j + 1 < acap) arg[j++] = line[i++];
    arg[j] = '\0';
}

void client_handle_line(server_t *srv, client_t *c, const char *line)
{
    char cmd[16];
    char arg[512];

    parse_cmd(line, cmd, sizeof(cmd), arg, sizeof(arg));
    if (str_ieq(cmd, "USER")) return cmd_user(c, arg);
    if (str_ieq(cmd, "PASS")) return cmd_pass(c, arg);
    if (str_ieq(cmd, "QUIT")) return cmd_quit(srv, c);
    if (!c->logged) {
        client_write(c->fd, "530 Not logged in.\r\n");
        return;
    }
    if (str_ieq(cmd, "PWD")) return cmd_pwd(c);
    if (str_ieq(cmd, "CWD")) return cmd_cwd(c, arg, srv->home);
    if (str_ieq(cmd, "CDUP")) return cmd_cdup(c, srv->home);
    if (str_ieq(cmd, "PASV")) return cmd_pasv(c);
    if (str_ieq(cmd, "LIST")) return cmd_list(c, srv->home, arg);
    if (str_ieq(cmd, "NOOP")) return cmd_noop(c);
    if (str_ieq(cmd, "SYST")) return cmd_syst(c);
    if (str_ieq(cmd, "TYPE")) return cmd_type(c, arg);
    if (str_ieq(cmd, "RETR")) return cmd_retr(c, srv->home, arg);
    if (str_ieq(cmd, "STOR")) return cmd_stor(c, srv->home, arg);
    if (str_ieq(cmd, "HELP")) return cmd_help(c);
    if (str_ieq(cmd, "PORT")) return cmd_port(c, arg);
    if (str_ieq(cmd, "DELE")) return cmd_dele(c, srv->home, arg);
    if (str_ieq(cmd, "MKD")) return cmd_mkd(c, srv->home, arg);
    if (str_ieq(cmd, "RMD")) return cmd_rmd(c, srv->home, arg);
    if (str_ieq(cmd, "RNFR")) return cmd_rnfr(c, srv->home, arg);
    if (str_ieq(cmd, "RNTO")) return cmd_rnto(c, srv->home, arg);
    client_write(c->fd, "502 Command not implemented.\r\n");
}
