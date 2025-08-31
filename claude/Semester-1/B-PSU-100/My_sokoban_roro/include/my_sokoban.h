/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Header file for my_sokoban warehouse keeper game
*/

#ifndef MY_SOKOBAN_H
    #define MY_SOKOBAN_H

    #define _GNU_SOURCE

    #include <ncurses.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <signal.h>
    #include <string.h>

    #define WALL '#'
    #define EMPTY ' '
    #define PLAYER 'P'
    #define BOX 'X'
    #define STORAGE 'O'
    #define PLAYER_ON_STORAGE '+'
    #define BOX_ON_STORAGE '*'

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct map_s {
    char **grid;
    int width;
    int height;
    position_t player_pos;
    int boxes_count;
    int storages_count;
    int boxes_on_storage;
} map_t;

typedef struct game_s {
    map_t *map;
    int game_over;
    int win;
    int terminal_too_small;
} game_t;

int parse_arguments(int argc, char **argv);
map_t *load_map(char *filename);
void free_map(map_t *map);
int validate_map(map_t *map);
void init_game(game_t *game, char *map_file);
void game_loop(game_t *game);
void display_game(game_t *game);
void handle_input(game_t *game, int key);
int move_player(game_t *game, int dx, int dy);
int can_move_to(map_t *map, int x, int y);
int can_push_box(map_t *map, int x, int y, int dx, int dy);
void push_box(map_t *map, int from_x, int from_y, int to_x, int to_y);
int check_win_condition(map_t *map);
int check_lose_condition(map_t *map);
void reset_game(game_t *game, char *map_file);
void check_terminal_size(game_t *game);
void setup_ncurses(void);
void cleanup_ncurses(void);
void print_usage(void);
position_t *get_player_position(map_t *map);
map_t *make_map_from_string(const char *map_str);
int count_char_in_map(map_t *map, char c);
void update_box_storage_count(map_t *map);

#endif