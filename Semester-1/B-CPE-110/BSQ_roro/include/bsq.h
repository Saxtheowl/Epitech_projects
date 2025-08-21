/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** Header for BSQ - find the Biggest SQuare algorithm
*/

#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

#define ERROR_CODE 84
#define BUFFER_SIZE 4096
#define EMPTY_CHAR '.'
#define OBSTACLE_CHAR 'o'
#define SQUARE_CHAR 'x'

typedef struct {
    char **grid;
    size_t rows;
    size_t cols;
    size_t **dp_matrix;
} board_t;

typedef struct {
    size_t row;
    size_t col;
    size_t size;
} square_t;

int read_board_from_file(const char *filepath, board_t *board);
void free_board(board_t *board);
square_t find_biggest_square(board_t *board);
void fill_square_in_board(board_t *board, square_t square);
void print_board(board_t *board);

char *read_file_content(const char *filepath, size_t *size);
int parse_board_header(const char *content, size_t *num_lines, size_t *offset);
int parse_board_grid(const char *content, size_t offset, board_t *board);
int validate_board(board_t *board);

size_t get_min(size_t a, size_t b, size_t c);
int create_dp_matrix(board_t *board);
void free_dp_matrix(board_t *board);

size_t my_strlen(const char *str);
int my_atoi(const char *str);
void my_putchar(char c);
void my_putstr(const char *str);

#endif