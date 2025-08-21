/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Game initialization and management
*/

#include "../include/push_swap.h"

game_t *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));
    
    if (!game)
        return NULL;
    
    game->l_a = create_list();
    game->l_b = create_list();
    
    if (!game->l_a || !game->l_b) {
        if (game->l_a)
            free_list(game->l_a);
        if (game->l_b)
            free_list(game->l_b);
        free(game);
        return NULL;
    }
    
    game->operations = NULL;
    game->op_count = 0;
    game->op_capacity = 0;
    
    return game;
}

void free_game(game_t *game)
{
    if (!game)
        return;
    
    if (game->l_a)
        free_list(game->l_a);
    if (game->l_b)
        free_list(game->l_b);
    if (game->operations)
        free(game->operations);
    
    free(game);
}

static int has_duplicates(game_t *game)
{
    node_t *current;
    node_t *checker;
    
    if (!game || !game->l_a)
        return 0;
    
    current = game->l_a->head;
    while (current) {
        checker = current->next;
        while (checker) {
            if (current->value == checker->value)
                return 1;
            checker = checker->next;
        }
        current = current->next;
    }
    
    return 0;
}

int parse_arguments(game_t *game, int ac, char **av)
{
    int i;
    int value;
    
    if (!game || ac < 2)
        return -1;
    
    for (i = ac - 1; i >= 1; i--) {
        if (!is_valid_number(av[i])) {
            write(2, "Error\n", 6);
            return -1;
        }
        
        value = my_atoi(av[i]);
        push_front(game->l_a, value);
    }
    
    if (has_duplicates(game)) {
        write(2, "Error\n", 6);
        return -1;
    }
    
    return 0;
}