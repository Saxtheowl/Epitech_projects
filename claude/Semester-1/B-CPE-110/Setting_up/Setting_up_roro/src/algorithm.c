/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** largest square algorithm using dynamic programming
*/

#include "../include/setting_up.h"

static int min_of_three(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

void find_largest_square(board_t *board)
{
    int **dp;
    int i;
    int j;

    if (board == NULL || board->grid == NULL)
        return;
    dp = malloc(sizeof(int *) * board->rows);
    if (dp == NULL)
        return;
    for (i = 0; i < board->rows; i++) {
        dp[i] = malloc(sizeof(int) * board->cols);
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++)
                free(dp[k]);
            free(dp);
            return;
        }
    }
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            if (board->grid[i][j] == 'o') {
                dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = min_of_three(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
            }
            if (dp[i][j] > board->max_square_size) {
                board->max_square_size = dp[i][j];
                board->max_square_row = i;
                board->max_square_col = j;
            } else if (dp[i][j] == board->max_square_size && i < board->max_square_row) {
                board->max_square_row = i;
                board->max_square_col = j;
            } else if (dp[i][j] == board->max_square_size && i == board->max_square_row && j < board->max_square_col) {
                board->max_square_col = j;
            }
        }
    }
    for (i = 0; i < board->rows; i++)
        free(dp[i]);
    free(dp);
}

void mark_square(board_t *board)
{
    int start_row;
    int start_col;
    int i;
    int j;

    if (board == NULL || board->max_square_size == 0)
        return;
    start_row = board->max_square_row - board->max_square_size + 1;
    start_col = board->max_square_col - board->max_square_size + 1;
    for (i = start_row; i <= board->max_square_row; i++) {
        for (j = start_col; j <= board->max_square_col; j++) {
            if (board->grid[i][j] == '.')
                board->grid[i][j] = 'x';
        }
    }
}

void print_board(board_t *board)
{
    int i;
    int j;

    if (board == NULL || board->grid == NULL)
        return;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            my_putchar(board->grid[i][j]);
        }
        my_putchar('\n');
    }
}