/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Public interfaces
*/

#ifndef FTP_H
#define FTP_H

#include <stddef.h>
#include <stdbool.h>
#include <netinet/in.h>

#define MAX_CLIENTS 64
#define RECV_BUF 4096

typedef struct client_s {
    int fd;
    bool logged;
    bool has_user;
    char user[64];
    char cwd[512];
    int pasv_fd;            /* listening data socket */
    struct sockaddr_in pasv_addr;
    bool data_active;       /* active mode target set */
    struct sockaddr_in active_addr;
    bool rnfr_pending;
    char rnfr_path[512];
    bool data_ready;
    char inbuf[RECV_BUF];
    size_t inlen;
} client_t;

typedef struct server_s {
    int listen_fd;
    struct sockaddr_in addr;
    char home[512];
    client_t clients[MAX_CLIENTS];
} server_t;

/* server.c */
int server_init(server_t *srv, int port, const char *home);
void server_run(server_t *srv);
void server_close(server_t *srv);

/* poller.c */
int poll_once(server_t *srv);

/* client.c */
void client_init(client_t *c);
void client_accept(server_t *srv);
void client_close(client_t *c);
void client_handle_line(server_t *srv, client_t *c, const char *line);
void client_write(int fd, const char *msg);

/* commands */
void cmd_user(client_t *c, const char *arg);
void cmd_pass(client_t *c, const char *arg);
void cmd_quit(server_t *srv, client_t *c);
void cmd_pwd(client_t *c);
void cmd_cwd(client_t *c, const char *arg, const char *home);
void cmd_cdup(client_t *c, const char *home);
void cmd_pasv(client_t *c);
void cmd_list(client_t *c, const char *home, const char *arg);
void cmd_noop(client_t *c);
void cmd_syst(client_t *c);
void cmd_type(client_t *c, const char *arg);
void cmd_retr(client_t *c, const char *home, const char *arg);
void cmd_stor(client_t *c, const char *home, const char *arg);
void cmd_help(client_t *c);
void cmd_port(client_t *c, const char *arg);
void cmd_dele(client_t *c, const char *home, const char *arg);
void cmd_mkd(client_t *c, const char *home, const char *arg);
void cmd_rmd(client_t *c, const char *home, const char *arg);
void cmd_rnfr(client_t *c, const char *home, const char *arg);
void cmd_rnto(client_t *c, const char *home, const char *arg);

/* path.c */
int path_resolve(char *out, size_t out_cap, const char *home, const char *cwd,
    const char *inp);

/* util.c */
int str_ieq(const char *a, const char *b);
int starts_with(const char *s, const char *p);
size_t my_strlen(const char *s);
void my_strcpy(char *dst, const char *src, size_t cap);

#endif /* FTP_H */
