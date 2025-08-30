/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main function for testing count_island (not delivered)
*/

#include "include/count_island.h"
#include <stdlib.h>

int main(void)
{
    char **world = malloc(sizeof(char *) * 4);
    int result = 0;
    int i = 0;

    world[0] = malloc(6);
    world[0][0] = '.';
    world[0][1] = 'X';
    world[0][2] = 'X';
    world[0][3] = '.';
    world[0][4] = 'X';
    world[0][5] = '\0';
    
    world[1] = malloc(6);
    world[1][0] = '.';
    world[1][1] = '.';
    world[1][2] = '.';
    world[1][3] = '.';
    world[1][4] = '.';
    world[1][5] = '\0';
    
    world[2] = malloc(6);
    world[2][0] = 'X';
    world[2][1] = 'X';
    world[2][2] = '.';
    world[2][3] = 'X';
    world[2][4] = 'X';
    world[2][5] = '\0';
    
    world[3] = NULL;
    
    my_putstr("Before:\n");
    for (i = 0; world[i] != NULL; i++) {
        my_putstr(world[i]);
        my_putchar('\n');
    }
    
    result = count_island(world);
    
    my_putstr("\nAfter:\n");
    for (i = 0; world[i] != NULL; i++) {
        my_putstr(world[i]);
        my_putchar('\n');
    }
    
    my_putstr("\nNumber of islands: ");
    my_putnbr(result);
    my_putchar('\n');
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
    
    return 0;
}