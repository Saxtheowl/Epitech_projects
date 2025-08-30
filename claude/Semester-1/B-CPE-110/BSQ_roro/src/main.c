/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Main function for BSQ project
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/bsq.h"

int main(int ac, char **av)
{
    char *content = NULL;
    map_t map = {NULL, 0, 0, NULL};
    square_t square;

    if (ac != 2) {
        write(2, "Usage: ./bsq map_file\n", 22);
        return EXIT_ERROR;
    }
    
    if (read_file(av[1], &content) == -1) {
        write(2, "map error\n", 10);
        return EXIT_ERROR;
    }
    
    if (parse_map(content, &map) == -1) {
        write(2, "map error\n", 10);
        free(content);
        free_map(&map);
        return EXIT_ERROR;
    }
    
    square = find_biggest_square(&map);
    
    if (square.size == 0) {
        write(2, "map error\n", 10);
        free(content);
        free_map(&map);
        return EXIT_ERROR;
    }
    
    print_result(&map, square);
    
    free(content);
    free_map(&map);
    return EXIT_SUCCESS;
}