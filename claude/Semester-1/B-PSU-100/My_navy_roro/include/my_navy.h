/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Header file for my_navy battleship game implementation
*/

#ifndef MY_NAVY_H
    #define MY_NAVY_H

    #define _GNU_SOURCE

    #include <sys/types.h>
    #include <signal.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <string.h>
    #include <time.h>

    #define BOARD_SIZE 8
    #define NB_SHIPS 4

typedef struct ship_s {
    int length;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int hits;
} ship_t;

typedef struct game_s {
    char my_board[BOARD_SIZE][BOARD_SIZE];
    char enemy_board[BOARD_SIZE][BOARD_SIZE];
    ship_t ships[NB_SHIPS];
    pid_t enemy_pid;
    int turn;
    int game_over;
    int winner;
    int attack_x;
    int attack_y;
    int result_received;
    int attack_result;
} game_t;

extern game_t *g_game;

int parse_arguments(int argc, char **argv, game_t *game);
int parse_navy_file(char *filename, game_t *game);
int validate_ship_placement(game_t *game);
void init_boards(game_t *game);
void place_ships(game_t *game);
void display_boards(game_t *game);
int start_game(game_t *game);
int is_valid_position(char *pos);
void parse_position(char *pos, int *x, int *y);
char *position_to_string(int x, int y);
void setup_signal_handlers(void);
void signal_handler(int sig);
void send_position(pid_t pid, int x, int y);
int receive_position(void);
int check_hit(game_t *game, int x, int y);
void update_enemy_board(game_t *game, int x, int y, int hit);
int check_game_over(game_t *game);
int play_turn(game_t *game);
void print_usage(void);
int my_strlen(const char *str);
int my_strcmp(const char *s1, const char *s2);
void my_strcpy(char *dest, const char *src);
void my_putchar(char c);
void my_putstr(const char *str);
void my_putnbr(int nb);

#endif