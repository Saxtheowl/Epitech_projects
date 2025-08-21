/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** Main function for BSQ - find the Biggest SQuare
*/

#include "../include/bsq.h"

int main(int argc, char **argv)
{
    board_t board = {0};
    square_t biggest_square;

    if (argc != 2) {
        write(2, "Usage: ./bsq file\n", 18);
        return ERROR_CODE;
    }

    if (read_board_from_file(argv[1], &board) != 0) {
        free_board(&board);
        return ERROR_CODE;
    }

    if (validate_board(&board) != 0) {
        write(2, "Invalid board format\n", 21);
        free_board(&board);
        return ERROR_CODE;
    }

    biggest_square = find_biggest_square(&board);
    if (biggest_square.size == 0) {
        write(2, "No square found\n", 16);
        free_board(&board);
        return ERROR_CODE;
    }

    fill_square_in_board(&board, biggest_square);
    print_board(&board);
    free_board(&board);

    return 0;
}