/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Main function for my_sokoban warehouse keeper game
*/

#include "../include/my_sokoban.h"

int main(int argc, char **argv)
{
    game_t game = {0};

    if (parse_arguments(argc, argv) == -1)
        return 84;
    init_game(&game, argv[1]);
    if (!game.map)
        return 84;
    setup_ncurses();
    game_loop(&game);
    cleanup_ncurses();
    free_map(game.map);
    return game.win ? 0 : 1;
}