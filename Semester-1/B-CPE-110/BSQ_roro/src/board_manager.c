/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** Board management and memory operations
*/

#include "../include/bsq.h"

int read_board_from_file(const char *filepath, board_t *board)
{
    char *content;
    size_t file_size;
    size_t offset;

    content = read_file_content(filepath, &file_size);
    if (!content)
        return -1;

    if (parse_board_header(content, &board->rows, &offset) != 0) {
        free(content);
        return -1;
    }

    if (parse_board_grid(content, offset, board) != 0) {
        free(content);
        return -1;
    }

    free(content);
    return 0;
}

void free_board(board_t *board)
{
    size_t i;

    if (!board)
        return;

    if (board->grid) {
        for (i = 0; i < board->rows; i++) {
            if (board->grid[i])
                free(board->grid[i]);
        }
        free(board->grid);
        board->grid = NULL;
    }

    free_dp_matrix(board);
    board->rows = 0;
    board->cols = 0;
}

void print_board(board_t *board)
{
    size_t i;
    size_t j;

    if (!board || !board->grid)
        return;

    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            my_putchar(board->grid[i][j]);
        }
        my_putchar('\n');
    }
}

void fill_square_in_board(board_t *board, square_t square)
{
    size_t i;
    size_t j;

    if (!board || !board->grid)
        return;

    for (i = square.row; i < square.row + square.size; i++) {
        for (j = square.col; j < square.col + square.size; j++) {
            if (i < board->rows && j < board->cols)
                board->grid[i][j] = SQUARE_CHAR;
        }
    }
}