/*
** EPITECH PROJECT, 2024
** count_island.h
** File description:
** header file for count_island project
*/

#ifndef COUNT_ISLAND_H_
    #define COUNT_ISLAND_H_

    #include "my.h"

int count_island(char **world);
void flood_fill(char **world, int row, int col, char island_id);
int is_valid_position(char **world, int row, int col);
int get_grid_height(char **world);
int get_grid_width(char **world, int row);

#endif