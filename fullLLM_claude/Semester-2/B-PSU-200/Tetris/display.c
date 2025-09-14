#include "tetris.h"

void init_ncurses(void)
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_YELLOW, COLOR_BLACK);
        init_pair(6, COLOR_GREEN, COLOR_BLACK);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(8, COLOR_RED, COLOR_BLACK);
    }
}

static void draw_border(int start_y, int start_x, int height, int width)
{
    // Top border
    mvaddch(start_y, start_x, '+');
    for (int i = 1; i < width - 1; i++)
        mvaddch(start_y, start_x + i, '-');
    mvaddch(start_y, start_x + width - 1, '+');
    
    // Side borders
    for (int i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, '|');
        mvaddch(start_y + i, start_x + width - 1, '|');
    }
    
    // Bottom border
    mvaddch(start_y + height - 1, start_x, '+');
    for (int i = 1; i < width - 1; i++)
        mvaddch(start_y + height - 1, start_x + i, '-');
    mvaddch(start_y + height - 1, start_x + width - 1, '+');
}

static void draw_game_board(game_t *game, int start_y, int start_x)
{
    // Draw border
    draw_border(start_y, start_x, game->rows + 2, game->cols + 2);
    
    // Draw grid content
    for (int row = 0; row < game->rows; row++) {
        for (int col = 0; col < game->cols; col++) {
            char ch = game->grid[row][col];
            if (ch != ' ') {
                attron(COLOR_PAIR(2));
                mvaddch(start_y + 1 + row, start_x + 1 + col, ch);
                attroff(COLOR_PAIR(2));
            } else {
                mvaddch(start_y + 1 + row, start_x + 1 + col, ' ');
            }
        }
    }
    
    // Draw current piece
    if (game->current_piece.tetrimino && game->current_piece.tetrimino->valid && !game->game_over) {
        int color_pair = game->current_piece.tetrimino->color;
        if (color_pair > 0 && color_pair <= 8)
            attron(COLOR_PAIR(color_pair));
        
        for (int row = 0; row < game->current_piece.tetrimino->height; row++) {
            for (int col = 0; col < game->current_piece.tetrimino->width; col++) {
                if (game->current_piece.tetrimino->shape[row][col] == '*') {
                    int draw_y = start_y + 1 + game->current_piece.y + row;
                    int draw_x = start_x + 1 + game->current_piece.x + col;
                    
                    if (draw_y >= start_y + 1 && draw_y < start_y + game->rows + 1 &&
                        draw_x >= start_x + 1 && draw_x < start_x + game->cols + 1) {
                        mvaddch(draw_y, draw_x, '*');
                    }
                }
            }
        }
        
        if (color_pair > 0 && color_pair <= 8)
            attroff(COLOR_PAIR(color_pair));
    }
}

static void draw_info_panel(game_t *game, int start_y, int start_x)
{
    int current_time = time(NULL) - game->start_time;
    int minutes = current_time / 60;
    int seconds = current_time % 60;
    
    draw_border(start_y, start_x, 10, 25);
    
    mvprintw(start_y + 1, start_x + 2, "High Score  %10d", game->high_score);
    mvprintw(start_y + 2, start_x + 2, "Score       %10d", game->score);
    mvprintw(start_y + 3, start_x + 2, " ");
    mvprintw(start_y + 4, start_x + 2, "Lines       %10d", game->lines_cleared);
    mvprintw(start_y + 5, start_x + 2, "Level       %10d", game->level);
    mvprintw(start_y + 6, start_x + 2, " ");
    mvprintw(start_y + 7, start_x + 2, "Timer    %02d:%02d", minutes, seconds);
    
    if (game->paused) {
        mvprintw(start_y + 8, start_x + 2, "*** PAUSED ***");
    } else if (game->game_over) {
        mvprintw(start_y + 8, start_x + 2, "*** GAME OVER ***");
    }
}

static void draw_next_piece(game_t *game, options_t *options, int start_y, int start_x)
{
    if (options->without_next || !game->next_piece.tetrimino || !game->next_piece.tetrimino->valid)
        return;
    
    draw_border(start_y, start_x, 6, 12);
    mvprintw(start_y, start_x + 1, "-next----");
    
    int color_pair = game->next_piece.tetrimino->color;
    if (color_pair > 0 && color_pair <= 8)
        attron(COLOR_PAIR(color_pair));
    
    for (int row = 0; row < game->next_piece.tetrimino->height; row++) {
        for (int col = 0; col < game->next_piece.tetrimino->width; col++) {
            if (game->next_piece.tetrimino->shape[row][col] == '*') {
                mvaddch(start_y + 1 + row, start_x + 2 + col, '*');
            }
        }
    }
    
    if (color_pair > 0 && color_pair <= 8)
        attroff(COLOR_PAIR(color_pair));
}

void draw_game(game_t *game, options_t *options)
{
    clear();
    
    int board_start_y = 2;
    int board_start_x = 2;
    int info_start_y = board_start_y;
    int info_start_x = board_start_x + game->cols + 5;
    int next_start_y = board_start_y;
    int next_start_x = info_start_x + 27;
    
    // Check if terminal is big enough
    int min_width = board_start_x + game->cols + 2 + 5 + 25 + 2;
    int min_height = board_start_y + game->rows + 2 + 2;
    
    if (!options->without_next)
        min_width += 15;
    
    if (COLS < min_width || LINES < min_height) {
        mvprintw(LINES/2, (COLS-40)/2, "Terminal too small! Please resize.");
        refresh();
        return;
    }
    
    draw_game_board(game, board_start_y, board_start_x);
    draw_info_panel(game, info_start_y, info_start_x);
    
    if (!options->without_next) {
        draw_next_piece(game, options, next_start_y, next_start_x);
    }
    
    refresh();
}