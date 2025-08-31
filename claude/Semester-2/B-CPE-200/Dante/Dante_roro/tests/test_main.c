/*
** EPITECH PROJECT, 2024
** Dante's Star
** File description:
** Test suite for Dante maze generator and solver
*/

#include <stdio.h>

int main(void)
{
    printf("Dante's Star Test Suite\n");
    printf("=======================\n\n");
    
    printf("Testing functionality:\n");
    printf("1. Generate perfect maze: ./generator 10 10 perfect\n");
    printf("2. Generate imperfect maze: ./generator 15 10\n");
    printf("3. Solve maze: ./solver maze.txt\n");
    printf("4. Pipeline test: ./generator 20 10 > maze.txt && ./solver maze.txt\n");
    
    return 0;
}