/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Test suite for Tetris game
*/

#include <stdio.h>

int main(void)
{
    printf("Tetris Test Suite\n");
    printf("=================\n\n");
    
    printf("Testing functionality:\n");
    printf("1. Help display: ./tetris --help\n");
    printf("2. Debug mode: ./tetris -d\n");
    printf("3. Custom keys: ./tetris -kd 'x' --key-turn=' '\n");
    printf("4. Custom map size: ./tetris --map-size=15,8\n");
    printf("5. Game controls: arrows for movement, space for pause\n");
    
    return 0;
}