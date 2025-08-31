/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Game state management
*/

#include "../include/tetris.h"

void init_game_state(game_t *game)
{
    int i;

    game->state.score = 0;
    game->state.high_score = 0;
    game->state.lines_cleared = 0;
    game->state.level = game->config.level;
    game->state.running = 1;
    game->state.paused = 0;
    game->state.start_time = time(NULL);
    game->state.current_piece = NULL;
    game->state.next_piece = NULL;
    game->state.current_x = 0;
    game->state.current_y = 0;
    game->state.current_rotation = 0;
    game->state.fall_speed = 1000.0 / game->state.level;
    game->state.last_fall = clock();

    game->state.board = malloc(game->config.map_rows * sizeof(int *));
    for (i = 0; i < game->config.map_rows; i++) {
        game->state.board[i] = malloc(game->config.map_cols * sizeof(int));
    }

    reset_board(game);
}

void reset_board(game_t *game)
{
    int i, j;

    for (i = 0; i < game->config.map_rows; i++) {
        for (j = 0; j < game->config.map_cols; j++) {
            game->state.board[i][j] = 0;
        }
    }
}

int spawn_new_piece(game_t *game)
{
    tetrimino_t *template;

    if (game->state.current_piece) {
        free_tetrimino(game->state.current_piece);
        free(game->state.current_piece);
    }

    if (game->state.next_piece) {
        game->state.current_piece = game->state.next_piece;
    } else {
        template = get_random_tetrimino(game);
        if (!template)
            return -1;
        game->state.current_piece = copy_tetrimino(template);
        if (!game->state.current_piece)
            return -1;
    }

    template = get_random_tetrimino(game);
    if (!template)
        return -1;
    game->state.next_piece = copy_tetrimino(template);
    if (!game->state.next_piece)
        return -1;

    game->state.current_x = game->config.map_cols / 2 - game->state.current_piece->width / 2;
    game->state.current_y = 0;
    game->state.current_rotation = 0;

    if (!can_place_piece(game, game->state.current_x, game->state.current_y, 0)) {
        game->state.running = 0;
        return -1;
    }

    return 0;
}

int can_place_piece(game_t *game, int x, int y, int rotation)
{
    tetrimino_t *rotated;
    int i, j;
    int result = 1;

    rotated = rotate_tetrimino(game->state.current_piece, rotation);
    if (!rotated)
        return 0;

    for (i = 0; i < rotated->height && result; i++) {
        for (j = 0; j < rotated->width && result; j++) {
            if (rotated->shape[i][j] != ' ' && rotated->shape[i][j] != '\0') {
                int board_x = x + j;
                int board_y = y + i;

                if (board_x < 0 || board_x >= game->config.map_cols ||
                    board_y < 0 || board_y >= game->config.map_rows ||
                    game->state.board[board_y][board_x] != 0) {
                    result = 0;
                }
            }
        }
    }

    free_tetrimino(rotated);
    free(rotated);
    return result;
}

void place_piece(game_t *game)
{
    tetrimino_t *rotated;
    int i, j;

    rotated = rotate_tetrimino(game->state.current_piece, game->state.current_rotation);
    if (!rotated)
        return;

    for (i = 0; i < rotated->height; i++) {
        for (j = 0; j < rotated->width; j++) {
            if (rotated->shape[i][j] != ' ' && rotated->shape[i][j] != '\0') {
                int board_x = game->state.current_x + j;
                int board_y = game->state.current_y + i;

                if (board_x >= 0 && board_x < game->config.map_cols &&
                    board_y >= 0 && board_y < game->config.map_rows) {
                    game->state.board[board_y][board_x] = rotated->color;
                }
            }
        }
    }

    free_tetrimino(rotated);
    free(rotated);

    int lines_cleared = check_lines(game);
    if (lines_cleared > 0) {
        game->state.lines_cleared += lines_cleared;
        game->state.score += lines_cleared * 100 * game->state.level;
        if (game->state.score > game->state.high_score) {
            game->state.high_score = game->state.score;
        }
        update_level(game);
    }
}

int check_lines(game_t *game)
{
    int lines_cleared = 0;
    int i, j;

    for (i = game->config.map_rows - 1; i >= 0; i--) {
        int line_full = 1;
        
        for (j = 0; j < game->config.map_cols; j++) {
            if (game->state.board[i][j] == 0) {
                line_full = 0;
                break;
            }
        }

        if (line_full) {
            clear_line(game, i);
            lines_cleared++;
            i++;
        }
    }

    return lines_cleared;
}

void clear_line(game_t *game, int line)
{
    int i, j;

    for (i = line; i > 0; i--) {
        for (j = 0; j < game->config.map_cols; j++) {
            game->state.board[i][j] = game->state.board[i - 1][j];
        }
    }

    for (j = 0; j < game->config.map_cols; j++) {
        game->state.board[0][j] = 0;
    }
}

void update_level(game_t *game)
{
    int new_level = game->config.level + game->state.lines_cleared / 10;
    
    if (new_level > game->state.level) {
        game->state.level = new_level;
        game->state.fall_speed = 1000.0 / game->state.level;
    }
}

void cleanup_game(game_t *game)
{
    int i;

    if (game->state.board) {
        for (i = 0; i < game->config.map_rows; i++) {
            free(game->state.board[i]);
        }
        free(game->state.board);
        game->state.board = NULL;
    }

    if (game->state.current_piece) {
        free_tetrimino(game->state.current_piece);
        free(game->state.current_piece);
        game->state.current_piece = NULL;
    }

    if (game->state.next_piece) {
        free_tetrimino(game->state.next_piece);
        free(game->state.next_piece);
        game->state.next_piece = NULL;
    }

    for (i = 0; i < game->tetrimino_count; i++) {
        free_tetrimino(&game->tetriminos[i]);
    }
}