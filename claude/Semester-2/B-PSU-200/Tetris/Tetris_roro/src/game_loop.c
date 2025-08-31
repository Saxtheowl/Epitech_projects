/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Main game loop with input handling
*/

#include "../include/tetris.h"

void game_loop(game_t *game)
{
    while (game->state.running) {
        if (!game->state.paused) {
            clock_t current_time = clock();
            double elapsed = ((double)(current_time - game->state.last_fall)) / CLOCKS_PER_SEC * 1000;

            if (elapsed >= game->state.fall_speed) {
                if (!move_piece(game, 0, 1)) {
                    place_piece(game);
                    if (spawn_new_piece(game) != 0) {
                        game->state.running = 0;
                        break;
                    }
                }
                game->state.last_fall = current_time;
            }
        }

        handle_input(game);
        draw_game(game);
        napms(50);
    }

    mvprintw(LINES / 2, COLS / 2 - 5, "GAME OVER");
    mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Press any key to exit");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}

int handle_input(game_t *game)
{
    int ch = getch();

    if (ch == ERR)
        return 0;

    if (ch == game->config.key_quit) {
        game->state.running = 0;
        return 1;
    }

    if (ch == game->config.key_pause) {
        pause_game(game);
        return 1;
    }

    if (game->state.paused)
        return 0;

    if (ch == game->config.key_left) {
        move_piece(game, -1, 0);
    } else if (ch == game->config.key_right) {
        move_piece(game, 1, 0);
    } else if (ch == game->config.key_turn) {
        rotate_piece(game);
    } else if (ch == game->config.key_drop) {
        drop_piece(game);
    }

    return 1;
}

void pause_game(game_t *game)
{
    game->state.paused = !game->state.paused;
}