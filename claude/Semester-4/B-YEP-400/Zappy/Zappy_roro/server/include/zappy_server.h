/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Main server header file
*/

#ifndef ZAPPY_SERVER_H_
    #define ZAPPY_SERVER_H_

    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <time.h>

    #define MAX_CLIENTS 100
    #define MAX_TEAMS 10
    #define MAX_NAME_LEN 50
    #define BUFFER_SIZE 1024
    #define MAX_COMMANDS 10
    #define DEFAULT_FREQ 100

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

typedef enum resource_type_e {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NB_RESOURCES
} resource_type_t;

typedef struct tile_s {
    int resources[NB_RESOURCES];
} tile_t;

typedef struct player_s {
    int client_fd;
    int x;
    int y;
    int orientation;
    int level;
    int inventory[NB_RESOURCES];
    double life_units;
    char *team_name;
    int id;
    struct player_s *next;
} player_t;

typedef struct team_s {
    char name[MAX_NAME_LEN];
    int max_clients;
    int connected_clients;
    player_t *players;
} team_t;

typedef struct command_s {
    char *cmd;
    double end_time;
    struct command_s *next;
} command_t;

typedef struct client_s {
    int fd;
    char buffer[BUFFER_SIZE];
    int buffer_len;
    player_t *player;
    command_t *commands;
    int nb_commands;
} client_t;

typedef struct server_s {
    int server_fd;
    int port;
    int width;
    int height;
    int freq;
    team_t teams[MAX_TEAMS];
    int nb_teams;
    tile_t **world;
    client_t clients[MAX_CLIENTS];
    fd_set read_fds;
    fd_set write_fds;
    int max_fd;
    double current_time;
    int running;
} server_t;

extern server_t *g_server;

int parse_arguments(int argc, char **argv, server_t *server);
void display_help(void);
int init_server(server_t *server);
int init_world(server_t *server);
void spawn_resources(server_t *server);
int run_server(server_t *server);
void handle_new_connection(server_t *server);
void handle_client_data(server_t *server, int client_idx);
void process_client_commands(server_t *server, int client_idx);
void execute_command(server_t *server, client_t *client, char *command);
void cleanup_server(server_t *server);
double get_current_time(void);
void send_to_client(client_t *client, const char *message);
player_t *create_player(const char *team_name, int client_fd);
void add_player_to_team(server_t *server, player_t *player);
team_t *find_team(server_t *server, const char *team_name);
void process_all_commands(server_t *server);
void cleanup_player(server_t *server, player_t *player);

#endif /* !ZAPPY_SERVER_H_ */