#ifndef MY_NAVY_H
#define MY_NAVY_H

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define GRID_SIZE 8
#define MAX_SHIPS 4
#define BUFFER_SIZE 1024

typedef struct {
    int length;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int hits;
} ship_t;

typedef struct {
    int grid[GRID_SIZE][GRID_SIZE];
    int enemy_grid[GRID_SIZE][GRID_SIZE];
    ship_t ships[MAX_SHIPS];
    int ship_count;
    int my_pid;
    int enemy_pid;
    int is_my_turn;
    int game_over;
    int i_won;
    int total_hits_received;
    int total_hits_made;
} game_state_t;

extern game_state_t g_game;

int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
void my_putchar(char c);
void my_putstr(char const *str);
void my_put_nbr(int nb);

int parse_positions_file(char const *filename);
int validate_ship_placement(ship_t *ship);
void init_game_state(void);
void display_grids(void);
void display_help(void);

void setup_signal_handlers(void);
void signal_handler(int sig, siginfo_t *info, void *context);
int send_coordinates(int x, int y);
int receive_coordinates(int *x, int *y);
int send_result(int hit);
int receive_result(void);

int process_attack(int x, int y);
int is_valid_coordinate(char const *coord);
int parse_coordinate(char const *coord, int *x, int *y);
void game_loop(void);

int count_remaining_ship_parts(void);
int all_ships_sunk(void);

#endif