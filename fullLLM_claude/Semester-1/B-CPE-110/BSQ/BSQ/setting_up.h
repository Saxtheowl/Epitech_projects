#ifndef SETTING_UP_H
#define SETTING_UP_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct {
    char **board;
    int rows;
    int cols;
} board_t;

typedef struct {
    int row;
    int col;
    int size;
} square_t;

int my_strlen(char const *str);
char *my_strdup(char const *str);
void my_putstr(char const *str);
void my_put_nbr(int nb);
void my_putchar(char c);

board_t *read_board_from_file(char const *filename);
board_t *generate_board(int size, char const *pattern);
void free_board(board_t *board);
square_t find_largest_square(board_t *board);
void place_square_on_board(board_t *board, square_t square);
void print_board(board_t *board);

int is_valid_file(char const *content, int size);
char *read_file_content(char const *filename, int *size);

#endif