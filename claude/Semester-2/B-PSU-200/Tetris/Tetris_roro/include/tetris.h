/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Header file for ncurses-based Tetris game
*/

#ifndef TETRIS_H_
#define TETRIS_H_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <dirent.h>
#include <sys/stat.h>
#include <getopt.h>

#define MAX_TETRIMINOS 20
#define MAX_NAME_LENGTH 64
#define MAX_PATH_LENGTH 256
#define DEFAULT_ROWS 20
#define DEFAULT_COLS 10
#define DEFAULT_LEVEL 1

#define KEY_UP_ARROW 259
#define KEY_DOWN_ARROW 258
#define KEY_LEFT_ARROW 260
#define KEY_RIGHT_ARROW 261

typedef struct tetrimino_s {
    char name[MAX_NAME_LENGTH];
    int width;
    int height;
    int color;
    char **shape;
    int valid;
} tetrimino_t;

typedef struct game_config_s {
    int level;
    int key_left;
    int key_right;
    int key_turn;
    int key_drop;
    int key_quit;
    int key_pause;
    int map_rows;
    int map_cols;
    int show_next;
    int debug_mode;
} game_config_t;

typedef struct game_state_s {
    int **board;
    int score;
    int high_score;
    int lines_cleared;
    int level;
    int running;
    int paused;
    time_t start_time;
    tetrimino_t *current_piece;
    tetrimino_t *next_piece;
    int current_x;
    int current_y;
    int current_rotation;
    double fall_speed;
    clock_t last_fall;
} game_state_t;

typedef struct game_s {
    game_config_t config;
    game_state_t state;
    tetrimino_t tetriminos[MAX_TETRIMINOS];
    int tetrimino_count;
} game_t;

/* Main game functions */
int main(int argc, char **argv);
void init_game(game_t *game);
void cleanup_game(game_t *game);
void game_loop(game_t *game);

/* Configuration */
void init_default_config(game_config_t *config);
int parse_arguments(int argc, char **argv, game_config_t *config);
void print_help(void);
void debug_mode(game_t *game);

/* Tetrimino management */
int load_tetriminos(game_t *game);
int load_tetrimino_file(const char *filepath, tetrimino_t *tetrimino);
void free_tetrimino(tetrimino_t *tetrimino);
tetrimino_t *get_random_tetrimino(game_t *game);
tetrimino_t *copy_tetrimino(tetrimino_t *original);

/* Game state */
void init_game_state(game_t *game);
void reset_board(game_t *game);
int spawn_new_piece(game_t *game);
int can_place_piece(game_t *game, int x, int y, int rotation);
void place_piece(game_t *game);
int check_lines(game_t *game);
void clear_line(game_t *game, int line);
void update_level(game_t *game);

/* Movement and rotation */
int move_piece(game_t *game, int dx, int dy);
int rotate_piece(game_t *game);
void drop_piece(game_t *game);
tetrimino_t *rotate_tetrimino(tetrimino_t *tetrimino, int rotation);

/* Display */
void init_ncurses(void);
void cleanup_ncurses(void);
void draw_game(game_t *game);
void draw_board(game_t *game);
void draw_current_piece(game_t *game);
void draw_next_piece(game_t *game);
void draw_info_panel(game_t *game);
void draw_border(int start_y, int start_x, int height, int width);
int check_terminal_size(game_t *game);

/* Input handling */
int handle_input(game_t *game);
void pause_game(game_t *game);

/* Utility functions */
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *s);
int my_strlen(const char *s);
void print_error(const char *message);
char *format_time(time_t seconds);

#endif /* !TETRIS_H_ */