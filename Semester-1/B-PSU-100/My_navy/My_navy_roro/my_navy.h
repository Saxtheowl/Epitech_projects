#ifndef MY_NAVY_H
#define MY_NAVY_H

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GRID_SIZE 8
#define SHIP_COUNT 4

typedef struct {
    int length;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} ship_t;

typedef struct {
    char my_grid[GRID_SIZE][GRID_SIZE];
    char enemy_grid[GRID_SIZE][GRID_SIZE];
    ship_t ships[SHIP_COUNT];
    int ships_remaining;
    int enemy_ships_remaining;
    pid_t enemy_pid;
    int my_turn;
    int game_over;
    int attack_x;
    int attack_y;
    int attack_result;
    int signal_received;
} game_t;

extern game_t g_game;

int my_putchar(char c);
int my_putstr(char *str);
int my_strlen(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_atoi(char *str);

int parse_positions_file(char *filename);
int validate_ship_placement(ship_t *ship);
void place_ship(ship_t *ship);

void print_grid(char grid[GRID_SIZE][GRID_SIZE], char *title);
void print_game_state(void);

void setup_signals(void);
void signal_handler(int sig);
void send_attack(int x, int y);
void send_attack_result(int result);

int char_to_x(char c);
int char_to_y(char c);
char x_to_char(int x);
char y_to_char(int y);

int parse_attack_input(char *input, int *x, int *y);
int is_valid_position(int x, int y);

void game_loop(void);
int check_win_condition(void);

void print_usage(void);
int main(int ac, char **av);

#endif