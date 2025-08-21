/*
** EPITECH PROJECT, 2024
** Count_island
** File description:
** Header file for count island functions
*/

#ifndef MY_H_
    #define MY_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stddef.h>

/* Count island function prototype */
int count_island(char **world);

/* Helper functions */
int my_strlen(char const *str);
int my_putstr(char const *str);
int my_putchar(char c);
int my_putnbr(int nb);
void flood_fill(char **world, int x, int y, int rows, int cols, int island_id);
int is_valid_position(char **world, int x, int y, int rows, int cols);

#endif /* !MY_H_ */