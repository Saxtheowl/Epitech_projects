/*
** EPITECH PROJECT, 2024
** bsq.h
** File description:
** Header file for BSQ project
*/

#ifndef BSQ_H_
    #define BSQ_H_

#include <stddef.h>

#define EXIT_ERROR 84
#define EXIT_SUCCESS 0

typedef struct map_s {
    char **grid;
    int rows;
    int cols;
    int **dp;
} map_t;

typedef struct square_s {
    int row;
    int col;
    int size;
} square_t;

int read_file(char const *filename, char **content);
int parse_map(char const *content, map_t *map);
square_t find_biggest_square(map_t *map);
void print_result(map_t *map, square_t square);
void free_map(map_t *map);
int my_strlen(char const *str);
int my_atoi(char const *str);
void my_putstr(char const *str);
void my_putchar(char c);
int is_valid_char(char c);
int validate_map(map_t *map);

#endif /* !BSQ_H_ */