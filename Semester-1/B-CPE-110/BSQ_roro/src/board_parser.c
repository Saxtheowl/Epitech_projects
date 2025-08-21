/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** Board parsing and validation functions
*/

#include "../include/bsq.h"

static int count_line_length(const char *content, size_t start)
{
    size_t length = 0;

    while (content[start + length] && content[start + length] != '\n')
        length++;

    return length;
}

static char *copy_line(const char *content, size_t start, size_t length)
{
    char *line;
    size_t i;

    line = malloc(length + 1);
    if (!line)
        return NULL;

    for (i = 0; i < length; i++)
        line[i] = content[start + i];
    line[length] = '\0';

    return line;
}

int parse_board_grid(const char *content, size_t offset, board_t *board)
{
    size_t current_pos = offset;
    size_t line_idx = 0;
    size_t line_length;

    board->grid = malloc(sizeof(char *) * board->rows);
    if (!board->grid)
        return -1;

    while (line_idx < board->rows && content[current_pos]) {
        line_length = count_line_length(content, current_pos);

        if (line_idx == 0)
            board->cols = line_length;
        else if (line_length != board->cols) {
            return -1;
        }

        board->grid[line_idx] = copy_line(content, current_pos, line_length);
        if (!board->grid[line_idx])
            return -1;

        current_pos += line_length;
        if (content[current_pos] == '\n')
            current_pos++;

        line_idx++;
    }

    return (line_idx == board->rows) ? 0 : -1;
}

int validate_board(board_t *board)
{
    size_t i;
    size_t j;

    if (!board || !board->grid || board->rows == 0 || board->cols == 0)
        return -1;

    for (i = 0; i < board->rows; i++) {
        if (!board->grid[i])
            return -1;
        for (j = 0; j < board->cols; j++) {
            if (board->grid[i][j] != EMPTY_CHAR &&
                board->grid[i][j] != OBSTACLE_CHAR)
                return -1;
        }
    }

    return 0;
}