/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Main header file for FTP server
*/

#ifndef MYFTP_H_
#define MYFTP_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <strings.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 4096
#define PATH_SIZE 1024
#define MAX_COMMAND_SIZE 512

typedef enum {
    CLIENT_DISCONNECTED,
    CLIENT_CONNECTED,
    CLIENT_AUTHENTICATED
} client_state_t;

typedef enum {
    MODE_ACTIVE,
    MODE_PASSIVE
} transfer_mode_t;

typedef struct client_s {
    int socket_fd;
    client_state_t state;
    char username[256];
    char current_dir[PATH_SIZE];
    char root_dir[PATH_SIZE];
    transfer_mode_t mode;
    int data_fd;
    struct sockaddr_in data_addr;
    int data_port;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
} client_t;

typedef struct server_s {
    int socket_fd;
    int port;
    char root_path[PATH_SIZE];
    struct pollfd fds[MAX_CLIENTS];
    client_t clients[MAX_CLIENTS];
    int client_count;
} server_t;

// Server functions
int init_server(server_t *server, int port, const char *path);
int run_server(server_t *server);
void cleanup_server(server_t *server);

// Client management
int accept_new_client(server_t *server);
void disconnect_client(server_t *server, int index);
int handle_client_data(server_t *server, int index);

// FTP commands
int execute_command(server_t *server, int client_index, const char *command);
void send_response(int fd, int code, const char *message);

// Command implementations
void cmd_user(server_t *server, int client_index, const char *args);
void cmd_pass(server_t *server, int client_index, const char *args);
void cmd_pwd(server_t *server, int client_index, const char *args);
void cmd_cwd(server_t *server, int client_index, const char *args);
void cmd_list(server_t *server, int client_index, const char *args);
void cmd_retr(server_t *server, int client_index, const char *args);
void cmd_stor(server_t *server, int client_index, const char *args);
void cmd_quit(server_t *server, int client_index, const char *args);
void cmd_port(server_t *server, int client_index, const char *args);
void cmd_pasv(server_t *server, int client_index, const char *args);
void cmd_type(server_t *server, int client_index, const char *args);
void cmd_mode(server_t *server, int client_index, const char *args);
void cmd_stru(server_t *server, int client_index, const char *args);
void cmd_noop(server_t *server, int client_index, const char *args);

// Utility functions
void display_help(void);
char *get_absolute_path(const char *root, const char *current, const char *target);
int is_valid_path(const char *root, const char *path);
void format_file_list(char *buffer, const char *path);

#endif /* !MYFTP_H_ */