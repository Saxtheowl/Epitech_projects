/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Main server header file
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

#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024
#define MAX_TEAMS 10
#define MAX_TEAM_NAME 50
#define MAX_CMD_QUEUE 10

typedef enum {
    RESOURCE_FOOD = 0,
    RESOURCE_LINEMATE,
    RESOURCE_DERAUMERE,
    RESOURCE_SIBUR,
    RESOURCE_MENDIANE,
    RESOURCE_PHIRAS,
    RESOURCE_THYSTAME,
    NUM_RESOURCES
} resource_type_t;

typedef enum {
    ORIENTATION_NORTH = 1,
    ORIENTATION_EAST = 2,
    ORIENTATION_SOUTH = 3,
    ORIENTATION_WEST = 4
} orientation_t;

typedef enum {
    CLIENT_UNASSIGNED,
    CLIENT_AI,
    CLIENT_GUI
} client_type_t;

typedef struct {
    int quantities[NUM_RESOURCES];
} tile_t;

typedef struct {
    int x;
    int y;
    int level;
    orientation_t orientation;
    int inventory[NUM_RESOURCES];
    int life_units;
    char team_name[MAX_TEAM_NAME];
    int fd;
    time_t last_action;
    char cmd_buffer[BUFFER_SIZE];
    char *pending_commands[MAX_CMD_QUEUE];
    int cmd_count;
    int player_id;
    time_t incantation_start;
    int incantating;
} player_t;

typedef struct {
    char name[MAX_TEAM_NAME];
    int max_clients;
    int connected_clients;
    int available_slots;
} team_t;

typedef struct {
    int x;
    int y;
    int player_id;
    time_t hatch_time;
    char team_name[MAX_TEAM_NAME];
} egg_t;

typedef struct {
    int fd;
    client_type_t type;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    union {
        player_t *player;
        void *gui_data;
    };
} client_t;

typedef struct {
    int port;
    int width;
    int height;
    int freq;
    team_t teams[MAX_TEAMS];
    int team_count;
    int max_clients_per_team;

    int server_fd;
    fd_set master_fds;
    fd_set read_fds;
    int max_fd;

    tile_t **map;
    client_t clients[MAX_CLIENTS];
    player_t *players[MAX_CLIENTS];
    egg_t eggs[MAX_CLIENTS];
    int egg_count;
    int player_count;

    time_t last_resource_spawn;
    time_t game_start;
    int running;
} server_t;

// Function prototypes
int parse_arguments(int argc, char **argv, server_t *server);
int init_server(server_t *server);
void run_server(server_t *server);
void cleanup_server(server_t *server);

// Network functions
int setup_socket(server_t *server);
void handle_new_connection(server_t *server);
void handle_client_data(server_t *server, int client_fd);
void disconnect_client(server_t *server, int client_fd);

// Game logic
void init_map(server_t *server);
void spawn_resources(server_t *server);
void update_game_state(server_t *server);
int process_command(server_t *server, client_t *client, char *command);

// Player management
player_t *create_player(server_t *server, char *team_name, int fd);
void remove_player(server_t *server, player_t *player);
void update_player_life(server_t *server, player_t *player);

// Commands
void cmd_forward(server_t *server, player_t *player);
void cmd_right(server_t *server, player_t *player);
void cmd_left(server_t *server, player_t *player);
void cmd_look(server_t *server, player_t *player);
void cmd_inventory(server_t *server, player_t *player);
void cmd_broadcast(server_t *server, player_t *player, char *message);
void cmd_connect_nbr(server_t *server, player_t *player);
void cmd_fork(server_t *server, player_t *player);
void cmd_eject(server_t *server, player_t *player);
void cmd_take_object(server_t *server, player_t *player, char *object);
void cmd_set_object(server_t *server, player_t *player, char *object);
void cmd_incantation(server_t *server, player_t *player);

// GUI Protocol
void gui_msz(server_t *server, client_t *client);
void gui_bct(server_t *server, client_t *client, int x, int y);
void gui_mct(server_t *server, client_t *client);
void gui_tna(server_t *server, client_t *client);
void gui_pnw(server_t *server, client_t *client, player_t *player);
void gui_ppo(server_t *server, client_t *client, int player_id);
void gui_plv(server_t *server, client_t *client, int player_id);
void gui_pin(server_t *server, client_t *client, int player_id);

// Utility functions
void send_response(int fd, const char *response);
void send_to_all_guis(server_t *server, const char *message);
team_t *find_team(server_t *server, const char *name);
player_t *find_player_by_id(server_t *server, int player_id);
int calculate_sound_direction(int px, int py, int sx, int sy, int width, int height);
void print_usage(char *program_name);