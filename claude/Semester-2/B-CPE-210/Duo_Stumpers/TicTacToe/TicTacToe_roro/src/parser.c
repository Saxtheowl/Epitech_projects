/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** parser
*/

#include "tictactoe.h"

int parse_arguments(int argc, char **argv, args_t *args)
{
    int i = 1;

    args->player1_char = 'X';
    args->player2_char = 'O';
    args->grid_size = 3;
    while (i < argc) {
        if (strcmp(argv[i], "-p1") == 0) {
            if (i + 1 >= argc || my_strlen(argv[i + 1]) != 1)
                return 84;
            args->player1_char = argv[i + 1][0];
            i += 2;
        } else if (strcmp(argv[i], "-p2") == 0) {
            if (i + 1 >= argc || my_strlen(argv[i + 1]) != 1)
                return 84;
            args->player2_char = argv[i + 1][0];
            i += 2;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 >= argc)
                return 84;
            args->grid_size = my_atoi(argv[i + 1]);
            if (args->grid_size <= 0)
                return 84;
            i += 2;
        } else {
            return 84;
        }
    }
    if (args->player1_char == args->player2_char)
        return 84;
    return 0;
}