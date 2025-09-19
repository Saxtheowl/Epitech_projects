#ifndef MYFTP_H
#define MYFTP_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <strings.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define CMD_SIZE 256

typedef struct client_s {
    int socket;
    int data_socket;
    int passive_socket;
    char current_dir[1024];
    char home_dir[1024];
    int authenticated;
    int user_valid;
    int passive_mode;
    struct sockaddr_in data_addr;
} client_t;

typedef struct server_s {
    int socket;
    int port;
    char *home_path;
    client_t clients[MAX_CLIENTS];
    struct pollfd poll_fds[MAX_CLIENTS + 1];
    int client_count;
} server_t;

/* main.c */
void print_usage(void);

/* server.c */
int init_server(server_t *server, int port, char *home_path);
int run_server(server_t *server);
void cleanup_server(server_t *server);

/* client.c */
int handle_new_client(server_t *server);
void handle_client_command(server_t *server, int client_idx);
void disconnect_client(server_t *server, int client_idx);

/* commands.c */
void handle_user(client_t *client, char *arg);
void handle_pass(client_t *client, char *arg);
void handle_pwd(client_t *client);
void handle_cwd(client_t *client, char *path);
void handle_list(client_t *client, char *path);
void handle_pasv(client_t *client);
void handle_quit(client_t *client);

/* utils.c */
void send_response(int socket, char *response);
int is_valid_path(char *base, char *path);
char *get_absolute_path(char *base, char *path);

#endif