/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Main function for Push Swap project
*/

#include <unistd.h>
#include "../include/push_swap.h"

static int has_duplicates(list_t *list)
{
    list_t *current = list;
    list_t *check;

    while (current) {
        check = current->next;
        while (check) {
            if (current->value == check->value)
                return 1;
            check = check->next;
        }
        current = current->next;
    }
    return 0;
}

int parse_arguments(int ac, char **av, game_t *game)
{
    int i = ac - 1;

    if (ac < 2)
        return -1;
    while (i >= 1) {
        if (!is_valid_number(av[i])) {
            write(2, "Error\n", 6);
            return -1;
        }
        list_push_front(&game->l_a, my_atoi(av[i]));
        i--;
    }
    if (has_duplicates(game->l_a)) {
        write(2, "Error\n", 6);
        return -1;
    }
    return 0;
}

int main(int ac, char **av)
{
    game_t *game;

    game = game_init();
    if (game == NULL)
        return EXIT_ERROR;
    
    if (parse_arguments(ac, av, game) == -1) {
        game_free(game);
        return EXIT_ERROR;
    }
    
    if (list_is_sorted(game->l_a)) {
        game_free(game);
        return EXIT_SUCCESS;
    }
    
    choose_sort_algorithm(game);
    game_print_operations(game);
    
    game_free(game);
    return EXIT_SUCCESS;
}