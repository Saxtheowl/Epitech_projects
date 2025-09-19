/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** AI client header file
*/

#pragma once

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_INVENTORY 10

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
    STATE_CONNECTING,
    STATE_EXPLORING,
    STATE_COLLECTING,
    STATE_SEEKING_ELEVATION,
    STATE_INCANTING,
    STATE_BROADCASTING
} ai_state_t;

typedef struct {
    int socket_fd;
    char *server_ip;
    int server_port;
    char *team_name;

    // Game state
    int level;
    int x, y;
    int map_width, map_height;
    orientation_t orientation;
    int inventory[NUM_RESOURCES];
    int life_units;

    // AI state
    ai_state_t state;
    time_t last_action;
    bool connected;
    int client_slots;

    // Exploration
    int target_x, target_y;
    bool has_target;

    // Communication
    char buffer[BUFFER_SIZE];
    int buffer_pos;
} ai_client_t;

// Function prototypes
int parse_ai_arguments(int argc, char **argv, ai_client_t *ai);
int connect_to_server(ai_client_t *ai);
void run_ai_client(ai_client_t *ai);
void cleanup_ai_client(ai_client_t *ai);

// Network functions
int send_command(ai_client_t *ai, const char *command);
int receive_response(ai_client_t *ai, char *response, size_t size);
void handle_server_response(ai_client_t *ai, const char *response);

// AI behavior
void update_ai_state(ai_client_t *ai);
void execute_ai_action(ai_client_t *ai);
void explore_map(ai_client_t *ai);
void collect_resources(ai_client_t *ai);
void attempt_elevation(ai_client_t *ai);

// Game actions
void move_forward(ai_client_t *ai);
void turn_left(ai_client_t *ai);
void turn_right(ai_client_t *ai);
void look_around(ai_client_t *ai);
void take_object(ai_client_t *ai, const char *object);
void set_object(ai_client_t *ai, const char *object);
void broadcast_message(ai_client_t *ai, const char *message);
void check_inventory(ai_client_t *ai);
void start_incantation(ai_client_t *ai);

// Utility functions
void parse_inventory_response(ai_client_t *ai, const char *response);
void parse_look_response(ai_client_t *ai, const char *response);
bool has_elevation_resources(ai_client_t *ai);
int get_required_resource_count(int level, resource_type_t resource);
void print_ai_usage(char *program_name);