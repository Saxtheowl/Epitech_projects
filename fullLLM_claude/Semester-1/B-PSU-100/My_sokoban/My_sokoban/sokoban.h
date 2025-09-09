#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define WALL '#'
#define PLAYER 'P'
#define BOX 'X'
#define STORAGE 'O'
#define EMPTY ' '
#define PLAYER_ON_STORAGE '+'
#define BOX_ON_STORAGE '*'

typedef struct position {
    int x;
    int y;
} position_t;

typedef struct sokoban_map {
    char **map;
    int width;
    int height;
    position_t player_pos;
    int boxes_count;
    int storage_count;
} sokoban_map_t;

typedef struct game_state {
    sokoban_map_t *map;
    int win;
    int lose;
    int reset;
} game_state_t;

int my_strlen(char const *str);
char *my_strdup(char const *str);
void my_putstr(char const *str);

sokoban_map_t *load_map(char const *filepath);
void free_map(sokoban_map_t *map);
sokoban_map_t *make_map_from_string(char const *str);
position_t *get_player_position(sokoban_map_t *map);

int is_valid_map(sokoban_map_t *map);
int check_win_condition(sokoban_map_t *map);
int check_lose_condition(sokoban_map_t *map);

int move_player(sokoban_map_t *map, int dx, int dy);
int can_move_box(sokoban_map_t *map, int x, int y, int dx, int dy);

void init_ncurses(void);
void cleanup_ncurses(void);
void display_map(sokoban_map_t *map);
void display_error_message(char const *msg);
int handle_input(void);

int game_loop(sokoban_map_t *map);
void handle_resize(int sig);

#endif