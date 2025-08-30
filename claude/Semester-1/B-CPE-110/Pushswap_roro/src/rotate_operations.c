/*
** EPITECH PROJECT, 2024
** rotate_operations.c
** File description:
** Rotation operations for Push Swap
*/

#include "../include/push_swap.h"

static void rotate_list(list_t **list)
{
    list_t *first;
    list_t *last;

    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;
    first = *list;
    *list = first->next;
    last = *list;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL;
}

static void reverse_rotate_list(list_t **list)
{
    list_t *prev;
    list_t *last;

    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;
    prev = *list;
    while (prev->next->next)
        prev = prev->next;
    last = prev->next;
    prev->next = NULL;
    last->next = *list;
    *list = last;
}

void ra(game_t *game)
{
    if (game == NULL)
        return;
    rotate_list(&game->l_a);
    game_add_operation(game, "ra");
}

void rb(game_t *game)
{
    if (game == NULL)
        return;
    rotate_list(&game->l_b);
    game_add_operation(game, "rb");
}

void rr(game_t *game)
{
    if (game == NULL)
        return;
    rotate_list(&game->l_a);
    rotate_list(&game->l_b);
    game_add_operation(game, "rr");
}

void rra(game_t *game)
{
    if (game == NULL)
        return;
    reverse_rotate_list(&game->l_a);
    game_add_operation(game, "rra");
}

void rrb(game_t *game)
{
    if (game == NULL)
        return;
    reverse_rotate_list(&game->l_b);
    game_add_operation(game, "rrb");
}

void rrr(game_t *game)
{
    if (game == NULL)
        return;
    reverse_rotate_list(&game->l_a);
    reverse_rotate_list(&game->l_b);
    game_add_operation(game, "rrr");
}