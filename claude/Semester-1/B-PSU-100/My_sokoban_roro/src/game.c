/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Game initialization and main loop for my_sokoban
*/

#include "../include/my_sokoban.h"

void init_game(game_t *game, char *map_file)
{
    game->map = load_map(map_file);
    game->game_over = 0;
    game->win = 0;
    game->terminal_too_small = 0;
}

void reset_game(game_t *game, char *map_file)
{
    free_map(game->map);
    init_game(game, map_file);
}

void check_terminal_size(game_t *game)
{
    int term_height, term_width;

    getmaxyx(stdscr, term_height, term_width);
    if (term_width < game->map->width || term_height < game->map->height) {
        game->terminal_too_small = 1;
    } else {
        game->terminal_too_small = 0;
    }
}

void display_game(game_t *game)
{
    int i, j;
    int start_y, start_x;
    int term_height, term_width;

    clear();
    check_terminal_size(game);
    if (game->terminal_too_small) {
        getmaxyx(stdscr, term_height, term_width);
        mvprintw(term_height / 2, (term_width - 25) / 2, 
                 "Terminal too small");
        mvprintw(term_height / 2 + 1, (term_width - 25) / 2, 
                 "Please enlarge window");
        refresh();
        return;
    }
    getmaxyx(stdscr, term_height, term_width);
    start_y = (term_height - game->map->height) / 2;
    start_x = (term_width - game->map->width) / 2;
    for (i = 0; i < game->map->height; i++) {
        for (j = 0; j < game->map->width; j++) {
            mvaddch(start_y + i, start_x + j, game->map->grid[i][j]);
        }
    }
    refresh();
}

void game_loop(game_t *game)
{
    int key;

    while (!game->game_over) {
        display_game(game);
        key = getch();
        handle_input(game, key);
    }
}