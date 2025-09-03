/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** setting_up header file
*/

#ifndef SETTING_UP_H
    #define SETTING_UP_H

    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>

typedef struct board_s {
    char **grid;
    int rows;
    int cols;
    int max_square_size;
    int max_square_row;
    int max_square_col;
} board_t;

/* File operations */
int read_file_to_string(char *filename, char **content);
board_t *parse_board_from_file(char *content);
board_t *create_board(int size, char *pattern);

/* Board operations */
board_t *new_board(int rows, int cols);
void free_board(board_t *board);
int validate_board(board_t *board);

/* Algorithm */
void find_largest_square(board_t *board);
void mark_square(board_t *board);
void print_board(board_t *board);

/* Utils */
int my_strlen(char *str);
int my_atoi(char *str);
void my_putchar(char c);
void my_putstr(char *str);
int is_valid_char(char c);

#endif