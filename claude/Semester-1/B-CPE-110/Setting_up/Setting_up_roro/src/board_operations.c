/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** board creation and management functions
*/

#include "../include/setting_up.h"

board_t *new_board(int rows, int cols)
{
    board_t *board;
    int i;

    if (rows <= 0 || cols <= 0)
        return NULL;
    board = malloc(sizeof(board_t));
    if (board == NULL)
        return NULL;
    board->grid = malloc(sizeof(char *) * rows);
    if (board->grid == NULL) {
        free(board);
        return NULL;
    }
    for (i = 0; i < rows; i++) {
        board->grid[i] = malloc(sizeof(char) * (cols + 1));
        if (board->grid[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(board->grid[j]);
            free(board->grid);
            free(board);
            return NULL;
        }
        board->grid[i][cols] = '\0';
    }
    board->rows = rows;
    board->cols = cols;
    board->max_square_size = 0;
    board->max_square_row = 0;
    board->max_square_col = 0;
    return board;
}

void free_board(board_t *board)
{
    int i;

    if (board == NULL)
        return;
    if (board->grid != NULL) {
        for (i = 0; i < board->rows; i++) {
            if (board->grid[i] != NULL)
                free(board->grid[i]);
        }
        free(board->grid);
    }
    free(board);
}

int validate_board(board_t *board)
{
    int i;
    int j;

    if (board == NULL || board->grid == NULL)
        return -1;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            if (!is_valid_char(board->grid[i][j]))
                return -1;
        }
    }
    return 0;
}

board_t *create_board(int size, char *pattern)
{
    board_t *board;
    int pattern_len = my_strlen(pattern);
    int i;
    int j;

    if (size <= 0 || pattern_len == 0)
        return NULL;
    board = new_board(size, size);
    if (board == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board->grid[i][j] = pattern[(i * size + j) % pattern_len];
        }
    }
    return board;
}