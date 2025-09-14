/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Main function for MyHunter project
*/

#include "my_hunter.h"

int main(int ac, char **av)
{
    game_t game;
    int result;

    if (parse_arguments(ac, av) != 0)
        return 84;

    srand(time(NULL));

    if (init_game(&game) != 0) {
        fprintf(stderr, "Error: Failed to initialize game\n");
        return 84;
    }

    result = game_loop(&game);
    cleanup_game(&game);

    return result;
}