#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define DEFAULT_ROWS 20
#define DEFAULT_COLS 10
#define DEFAULT_LEVEL 1
#define MAX_TETRIMINOS 10
#define MAX_NAME_LEN 50
#define MAX_SHAPE_SIZE 10

typedef struct {
    char name[MAX_NAME_LEN];
    int width;
    int height;
    int color;
    char shape[MAX_SHAPE_SIZE][MAX_SHAPE_SIZE];
    int valid;
} tetrimino_t;

typedef struct {
    int x, y;
    tetrimino_t *tetrimino;
    int rotation;
} piece_t;

typedef struct {
    char **grid;
    int rows, cols;
    int score;
    int high_score;
    int lines_cleared;
    int level;
    int start_time;
    int paused;
    int game_over;
    piece_t current_piece;
    piece_t next_piece;
    tetrimino_t tetriminos[MAX_TETRIMINOS];
    int tetrimino_count;
} game_t;

typedef struct {
    int key_left;
    int key_right;
    int key_turn;
    int key_drop;
    int key_quit;
    int key_pause;
    int level;
    int rows, cols;
    int without_next;
    int debug;
} options_t;

// Function prototypes
int parse_args(int argc, char **argv, options_t *options);
void print_usage(char *program_name);
int load_tetriminos(tetrimino_t *tetriminos, int *count);
void print_debug_info(options_t *options, tetrimino_t *tetriminos, int count);
int init_game(game_t *game, options_t *options);
void init_ncurses(void);
void cleanup(game_t *game);
int game_loop(game_t *game, options_t *options);
void draw_game(game_t *game, options_t *options);
int move_piece(game_t *game, int dx, int dy);
int rotate_piece(game_t *game);
void place_piece(game_t *game);
int check_lines(game_t *game);
void spawn_next_piece(game_t *game);
int can_place_piece(game_t *game, piece_t *piece, int x, int y);
tetrimino_t *get_random_tetrimino(tetrimino_t *tetriminos, int count);
void rotate_tetrimino_shape(char shape[MAX_SHAPE_SIZE][MAX_SHAPE_SIZE], int size);

#endif