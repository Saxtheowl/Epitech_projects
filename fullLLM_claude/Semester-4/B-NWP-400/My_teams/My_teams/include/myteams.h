/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Main header file for My_teams project
*/

#pragma once

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
// #include <uuid/uuid.h> // Not available, using custom UUID generation
#include <stdbool.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 2048
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define UUID_STR_LEN 37

// Protocol commands
typedef enum {
    CMD_LOGIN,
    CMD_LOGOUT,
    CMD_USERS,
    CMD_USER,
    CMD_SEND,
    CMD_MESSAGES,
    CMD_SUBSCRIBE,
    CMD_SUBSCRIBED,
    CMD_UNSUBSCRIBE,
    CMD_USE,
    CMD_CREATE,
    CMD_LIST,
    CMD_INFO,
    CMD_HELP,
    CMD_UNKNOWN
} command_type_t;

// Context types
typedef enum {
    CONTEXT_NONE,
    CONTEXT_TEAM,
    CONTEXT_CHANNEL,
    CONTEXT_THREAD
} context_type_t;

// Data structures
typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH];
    bool is_connected;
    int socket_fd;
} user_t;

typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char creator_uuid[UUID_STR_LEN];
    time_t created_at;
} team_t;

typedef struct {
    char uuid[UUID_STR_LEN];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[UUID_STR_LEN];
    char creator_uuid[UUID_STR_LEN];
    time_t created_at;
} channel_t;

typedef struct {
    char uuid[UUID_STR_LEN];
    char title[MAX_NAME_LENGTH];
    char message[MAX_BODY_LENGTH];
    char channel_uuid[UUID_STR_LEN];
    char creator_uuid[UUID_STR_LEN];
    time_t created_at;
} thread_t;

typedef struct {
    char uuid[UUID_STR_LEN];
    char body[MAX_BODY_LENGTH];
    char thread_uuid[UUID_STR_LEN];
    char creator_uuid[UUID_STR_LEN];
    time_t created_at;
} comment_t;

typedef struct {
    char uuid[UUID_STR_LEN];
    char body[MAX_BODY_LENGTH];
    char sender_uuid[UUID_STR_LEN];
    char receiver_uuid[UUID_STR_LEN];
    time_t timestamp;
} message_t;

typedef struct {
    char user_uuid[UUID_STR_LEN];
    char team_uuid[UUID_STR_LEN];
} subscription_t;

// Client context
typedef struct {
    context_type_t type;
    char team_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
} client_context_t;

// Client structure
typedef struct {
    int socket_fd;
    char user_uuid[UUID_STR_LEN];
    client_context_t context;
    bool is_authenticated;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
} client_t;

// Server structure
typedef struct {
    int port;
    int server_fd;
    fd_set master_fds;
    fd_set read_fds;
    int max_fd;
    bool running;

    // Data storage
    user_t users[MAX_CLIENTS];
    team_t teams[MAX_CLIENTS];
    channel_t channels[MAX_CLIENTS * 10];
    thread_t threads[MAX_CLIENTS * 100];
    comment_t comments[MAX_CLIENTS * 1000];
    message_t messages[MAX_CLIENTS * 1000];
    subscription_t subscriptions[MAX_CLIENTS * 10];

    // Counts
    int user_count;
    int team_count;
    int channel_count;
    int thread_count;
    int comment_count;
    int message_count;
    int subscription_count;

    // Connected clients
    client_t clients[MAX_CLIENTS];
} server_t;

// Function prototypes
// Server
int init_server(server_t *server, int port);
void run_server(server_t *server);
void cleanup_server(server_t *server);
void handle_new_connection(server_t *server);
void handle_client_data(server_t *server, int client_fd);
void disconnect_client(server_t *server, int client_fd);

// Protocol
void process_command(server_t *server, client_t *client, const char *command);
void send_response(int fd, const char *response);
void send_error(int fd, const char *error_msg);

// Commands
void cmd_login(server_t *server, client_t *client, const char *username);
void cmd_logout(server_t *server, client_t *client);
void cmd_users(server_t *server, client_t *client);
void cmd_user(server_t *server, client_t *client, const char *user_uuid);
void cmd_send(server_t *server, client_t *client, const char *user_uuid, const char *message);
void cmd_messages(server_t *server, client_t *client, const char *user_uuid);
void cmd_subscribe(server_t *server, client_t *client, const char *team_uuid);
void cmd_subscribed(server_t *server, client_t *client, const char *team_uuid);
void cmd_unsubscribe(server_t *server, client_t *client, const char *team_uuid);
void cmd_use(server_t *server, client_t *client, const char *team_uuid, const char *channel_uuid, const char *thread_uuid);
void cmd_create(server_t *server, client_t *client, char **args);
void cmd_list(server_t *server, client_t *client);
void cmd_info(server_t *server, client_t *client);
void cmd_help(server_t *server, client_t *client);

// Utility functions
void generate_uuid(char *uuid_str);
user_t *find_user_by_uuid(server_t *server, const char *uuid);
user_t *find_user_by_name(server_t *server, const char *name);
team_t *find_team_by_uuid(server_t *server, const char *uuid);
channel_t *find_channel_by_uuid(server_t *server, const char *uuid);
thread_t *find_thread_by_uuid(server_t *server, const char *uuid);
bool is_user_subscribed(server_t *server, const char *user_uuid, const char *team_uuid);
client_t *find_client_by_fd(server_t *server, int fd);

// Data persistence
void save_data(server_t *server);
void load_data(server_t *server);

// Client
int init_client(const char *ip, int port);
void run_client(int server_fd);
void cleanup_client(int server_fd);