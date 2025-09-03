/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** main function
*/

#include "../include/setting_up.h"

int main(int argc, char **argv)
{
    board_t *board = NULL;
    char *content = NULL;

    if (argc == 2) {
        if (read_file_to_string(argv[1], &content) == -1)
            return 84;
        board = parse_board_from_file(content);
        free(content);
        if (board == NULL)
            return 84;
    } else if (argc == 3) {
        int size = my_atoi(argv[1]);
        if (size <= 0)
            return 84;
        board = create_board(size, argv[2]);
        if (board == NULL)
            return 84;
    } else {
        return 84;
    }
    if (board == NULL)
        return 84;
    if (validate_board(board) == -1) {
        free_board(board);
        return 84;
    }
    find_largest_square(board);
    mark_square(board);
    print_board(board);
    free_board(board);
    return 0;
}