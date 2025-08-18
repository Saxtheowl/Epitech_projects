#ifndef MY_SOKOBAN_H
#define MY_SOKOBAN_H

/* #include <ncurses.h> */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WALL '#'
#define PLAYER 'P'
#define BOX 'X'
#define STORAGE 'O'
#define SPACE ' '
#define NEWLINE '\n'

#define KEY_SPACE 32
#define KEY_ESC 27

typedef struct {
    int x;
    int y;
} position_t;

typedef struct {
    char **grid;
    char **original;
    int width;
    int height;
    position_t player;
    int boxes_count;
    int storage_count;
} map_t;

typedef struct {
    map_t *map;
    int game_over;
    int win;
    int moves;
} game_t;

int my_strlen(char *str);
char *my_strdup(char *str);
void my_putstr(char *str);

map_t *load_map(char *filename);
void free_map(map_t *map);
int validate_map(map_t *map);
int count_char(map_t *map, char c);

int init_ncurses(void);
void cleanup_ncurses(void);
void display_map(map_t *map);
void display_message(char *message);
int check_terminal_size(map_t *map);

int move_player(map_t *map, int dx, int dy);
int check_win(map_t *map);
int check_lose(map_t *map);
void reset_game(map_t *map);

void game_loop(map_t *map);
void print_usage(void);

#endif