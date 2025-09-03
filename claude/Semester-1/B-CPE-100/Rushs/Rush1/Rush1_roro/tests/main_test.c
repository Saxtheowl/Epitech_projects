/*
** EPITECH PROJECT, 2025
** Rush1
** File description:
** main function for testing rush functions
*/

#include <stdio.h>
#include <stdlib.h>

void rush(int x, int y);

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s x y\n", argv[0]);
        return 84;
    }
    
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    
    if (x <= 0 || y <= 0) {
        printf("Error: x and y must be positive\n");
        return 84;
    }
    
    rush(x, y);
    return 0;
}