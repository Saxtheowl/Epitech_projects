/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Main function for push_swap program
*/

#include "../include/push_swap.h"

int main(int ac, char **av)
{
    game_t *game;

    if (ac < 2)
        return 0;

    game = init_game();
    if (!game)
        return 84;

    if (parse_arguments(game, ac, av) != 0) {
        free_game(game);
        return 84;
    }

    if (is_sorted(game->l_a)) {
        free_game(game);
        return 0;
    }

    solve_pushswap(game);

    if (game->operations) {
        my_putstr(game->operations);
        my_putchar('\n');
    }

    free_game(game);
    return 0;
}