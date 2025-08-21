/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** BSQ algorithm implementation using dynamic programming
*/

#include "../include/bsq.h"

int create_dp_matrix(board_t *board)
{
    size_t i;

    board->dp_matrix = malloc(sizeof(size_t *) * board->rows);
    if (!board->dp_matrix)
        return -1;

    for (i = 0; i < board->rows; i++) {
        board->dp_matrix[i] = malloc(sizeof(size_t) * board->cols);
        if (!board->dp_matrix[i]) {
            while (i > 0) {
                i--;
                free(board->dp_matrix[i]);
            }
            free(board->dp_matrix);
            board->dp_matrix = NULL;
            return -1;
        }
    }

    return 0;
}

void free_dp_matrix(board_t *board)
{
    size_t i;

    if (!board || !board->dp_matrix)
        return;

    for (i = 0; i < board->rows; i++) {
        if (board->dp_matrix[i])
            free(board->dp_matrix[i]);
    }
    free(board->dp_matrix);
    board->dp_matrix = NULL;
}

static void fill_dp_matrix(board_t *board)
{
    size_t i;
    size_t j;

    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            if (board->grid[i][j] == OBSTACLE_CHAR) {
                board->dp_matrix[i][j] = 0;
            } else if (i == 0 || j == 0) {
                board->dp_matrix[i][j] = (board->grid[i][j] == EMPTY_CHAR) ? 1 : 0;
            } else {
                board->dp_matrix[i][j] = get_min(
                    board->dp_matrix[i - 1][j],
                    board->dp_matrix[i][j - 1],
                    board->dp_matrix[i - 1][j - 1]
                ) + 1;
            }
        }
    }
}

square_t find_biggest_square(board_t *board)
{
    square_t best_square = {0, 0, 0};
    size_t i;
    size_t j;
    size_t top_row;
    size_t left_col;

    if (create_dp_matrix(board) != 0)
        return best_square;

    fill_dp_matrix(board);

    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            if (board->dp_matrix[i][j] > best_square.size) {
                best_square.size = board->dp_matrix[i][j];
                best_square.row = i - best_square.size + 1;
                best_square.col = j - best_square.size + 1;
            } else if (board->dp_matrix[i][j] == best_square.size && board->dp_matrix[i][j] > 0) {
                top_row = i - board->dp_matrix[i][j] + 1;
                left_col = j - board->dp_matrix[i][j] + 1;
                if (top_row < best_square.row || 
                    (top_row == best_square.row && left_col < best_square.col)) {
                    best_square.row = top_row;
                    best_square.col = left_col;
                }
            }
        }
    }

    return best_square;
}