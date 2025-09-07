/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Header file for sokoban game
*/

#ifndef SOKOBAN_H_
    #define SOKOBAN_H_

    #include <ncurses.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <signal.h>
    #include <stdbool.h>

    #define WALL '#'
    #define PLAYER 'P'
    #define BOX 'X'
    #define TARGET 'O'
    #define EMPTY ' '
    #define BOX_ON_TARGET '*'
    #define PLAYER_ON_TARGET '+'

    #define MY_EXIT_SUCCESS 0
    #define MY_EXIT_FAILURE 84
    #define WIN_EXIT_CODE 0
    #define LOSE_EXIT_CODE 1

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct sokoban_map_s {
    char **grid;
    int width;
    int height;
    position_t player_pos;
    int boxes_count;
    int targets_count;
} sokoban_map_t;

typedef struct game_s {
    sokoban_map_t *map;
    int game_state;
    bool is_running;
} game_t;

/* Map functions */
sokoban_map_t *load_map_from_file(const char *filename);
sokoban_map_t *make_map_from_string(const char *map_string);
void free_map(sokoban_map_t *map);
int validate_map(sokoban_map_t *map);
position_t *get_player_position(sokoban_map_t *map);

/* Game functions */
game_t *init_game(const char *map_file);
void free_game(game_t *game);
int move_player(game_t *game, int dx, int dy);
int check_win_condition(sokoban_map_t *map);
int check_lose_condition(sokoban_map_t *map);
void reset_game(game_t *game, const char *map_file);

/* Display functions */
void init_display(void);
void cleanup_display(void);
void display_map(sokoban_map_t *map);
void display_help(void);
void display_resize_message(void);
int check_terminal_size(sokoban_map_t *map);

/* Utils functions */
void print_usage(void);
int my_strlen(const char *str);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *str);

/* Signal handlers */
void handle_resize(int sig);

#endif /* !SOKOBAN_H_ */