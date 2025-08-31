/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** NCurses display system
*/

#include "../include/tetris.h"

void init_ncurses(void)
{
    initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

void cleanup_ncurses(void)
{
    endwin();
}

int check_terminal_size(game_t *game)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int required_cols = game->config.map_cols + 40;
    int required_rows = game->config.map_rows + 5;

    if (rows < required_rows || cols < required_cols) {
        return -1;
    }

    return 0;
}

void draw_game(game_t *game)
{
    clear();
    draw_board(game);
    draw_current_piece(game);
    if (game->config.show_next) {
        draw_next_piece(game);
    }
    draw_info_panel(game);
    refresh();
}

void draw_board(game_t *game)
{
    int i, j;
    int start_y = 2;
    int start_x = 2;

    draw_border(start_y - 1, start_x - 1, game->config.map_rows + 2, game->config.map_cols + 2);

    for (i = 0; i < game->config.map_rows; i++) {
        for (j = 0; j < game->config.map_cols; j++) {
            int color = game->state.board[i][j];
            if (color > 0) {
                attron(COLOR_PAIR(color));
                mvaddch(start_y + i, start_x + j, '*');
                attroff(COLOR_PAIR(color));
            } else {
                mvaddch(start_y + i, start_x + j, ' ');
            }
        }
    }
}

void draw_current_piece(game_t *game)
{
    tetrimino_t *rotated;
    int i, j;
    int start_y = 2;
    int start_x = 2;

    if (!game->state.current_piece)
        return;

    rotated = rotate_tetrimino(game->state.current_piece, game->state.current_rotation);
    if (!rotated)
        return;

    attron(COLOR_PAIR(rotated->color));
    for (i = 0; i < rotated->height; i++) {
        for (j = 0; j < rotated->width; j++) {
            if (rotated->shape[i][j] != ' ' && rotated->shape[i][j] != '\0') {
                int y = start_y + game->state.current_y + i;
                int x = start_x + game->state.current_x + j;
                if (y >= start_y && y < start_y + game->config.map_rows &&
                    x >= start_x && x < start_x + game->config.map_cols) {
                    mvaddch(y, x, '*');
                }
            }
        }
    }
    attroff(COLOR_PAIR(rotated->color));

    free_tetrimino(rotated);
    free(rotated);
}

void draw_next_piece(game_t *game)
{
    int start_y = 2;
    int start_x = game->config.map_cols + 5;
    int i, j;

    if (!game->state.next_piece)
        return;

    mvprintw(start_y - 1, start_x, "/-next----\\");
    mvprintw(start_y + 4, start_x, "\\---------/");

    attron(COLOR_PAIR(game->state.next_piece->color));
    for (i = 0; i < game->state.next_piece->height; i++) {
        for (j = 0; j < game->state.next_piece->width; j++) {
            if (game->state.next_piece->shape[i][j] != ' ' && 
                game->state.next_piece->shape[i][j] != '\0') {
                mvaddch(start_y + i, start_x + 2 + j, '*');
            }
        }
    }
    attroff(COLOR_PAIR(game->state.next_piece->color));
}

void draw_info_panel(game_t *game)
{
    int start_y = 8;
    int start_x = game->config.map_cols + 5;
    time_t current_time = time(NULL);
    time_t elapsed = current_time - game->state.start_time;
    char *time_str = format_time(elapsed);

    draw_border(start_y - 1, start_x - 1, 8, 20);

    mvprintw(start_y, start_x, "High Score %6d", game->state.high_score);
    mvprintw(start_y + 1, start_x, "Score      %6d", game->state.score);
    mvprintw(start_y + 2, start_x, "");
    mvprintw(start_y + 3, start_x, "Lines      %6d", game->state.lines_cleared);
    mvprintw(start_y + 4, start_x, "Level      %6d", game->state.level);
    mvprintw(start_y + 5, start_x, "");
    mvprintw(start_y + 6, start_x, "Timer      %s", time_str);

    free(time_str);

    if (game->state.paused) {
        mvprintw(LINES / 2, COLS / 2 - 5, "PAUSED");
    }
}

void draw_border(int start_y, int start_x, int height, int width)
{
    int i;

    mvaddch(start_y, start_x, '+');
    mvaddch(start_y, start_x + width - 1, '+');
    mvaddch(start_y + height - 1, start_x, '+');
    mvaddch(start_y + height - 1, start_x + width - 1, '+');

    for (i = 1; i < width - 1; i++) {
        mvaddch(start_y, start_x + i, '-');
        mvaddch(start_y + height - 1, start_x + i, '-');
    }

    for (i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, '|');
        mvaddch(start_y + i, start_x + width - 1, '|');
    }
}