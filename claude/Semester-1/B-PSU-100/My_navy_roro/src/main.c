/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Main function for my_navy battleship game
*/

#include "../include/my_navy.h"

game_t *g_game = NULL;

int main(int argc, char **argv)
{
    game_t game = {0};
    
    g_game = &game;
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    if (parse_arguments(argc, argv, &game) == -1)
        return 84;
    if (parse_navy_file(argv[argc - 1], &game) == -1)
        return 84;
    if (validate_ship_placement(&game) == -1)
        return 84;
    init_boards(&game);
    place_ships(&game);
    setup_signal_handlers();
    if (start_game(&game) == -1)
        return 84;
    return game.winner == 0 ? 0 : 1;
}