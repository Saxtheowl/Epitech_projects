/*
** EPITECH PROJECT, 2024
** game_operations.c
** File description:
** Game operations (sa, sb, pa, pb, etc.) for Push Swap
*/

#include "../include/push_swap.h"

void sa(game_t *game)
{
    list_t *first;
    list_t *second;

    if (game == NULL || game->l_a == NULL || game->l_a->next == NULL)
        return;
    first = game->l_a;
    second = first->next;
    first->next = second->next;
    second->next = first;
    game->l_a = second;
    game_add_operation(game, "sa");
}

void sb(game_t *game)
{
    list_t *first;
    list_t *second;

    if (game == NULL || game->l_b == NULL || game->l_b->next == NULL)
        return;
    first = game->l_b;
    second = first->next;
    first->next = second->next;
    second->next = first;
    game->l_b = second;
    game_add_operation(game, "sb");
}

void sc(game_t *game)
{
    if (game == NULL)
        return;
    sa(game);
    sb(game);
    game->op_count--;
    game_add_operation(game, "sc");
}

void pa(game_t *game)
{
    int value;

    if (game == NULL || game->l_b == NULL)
        return;
    value = list_pop_front(&game->l_b);
    list_push_front(&game->l_a, value);
    game_add_operation(game, "pa");
}

void pb(game_t *game)
{
    int value;

    if (game == NULL || game->l_a == NULL)
        return;
    value = list_pop_front(&game->l_a);
    list_push_front(&game->l_b, value);
    game_add_operation(game, "pb");
}