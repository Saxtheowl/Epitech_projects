/*
** EPITECH PROJECT, 2024
** algorithms.c
** File description:
** Sorting algorithms for Push Swap
*/

#include "../include/push_swap.h"

void sort_small(game_t *game)
{
    int size = list_size(game->l_a);

    if (size <= 1 || list_is_sorted(game->l_a))
        return;
    if (size == 2) {
        if (game->l_a->value > game->l_a->next->value)
            sa(game);
    } else if (size == 3) {
        list_t *first = game->l_a;
        list_t *second = first->next;
        list_t *third = second->next;

        if (first->value > second->value && first->value < third->value)
            sa(game);
        else if (first->value > third->value && second->value < third->value)
            ra(game);
        else if (first->value < second->value && first->value > third->value)
            rra(game);
        else if (first->value > second->value && second->value > third->value) {
            sa(game);
            rra(game);
        } else if (first->value < second->value && second->value > third->value) {
            sa(game);
            ra(game);
        }
    }
}

void sort_medium(game_t *game)
{
    int size = list_size(game->l_a);
    int pushed = 0;

    while (size > 3) {
        pb(game);
        pushed++;
        size--;
    }
    sort_small(game);
    while (pushed > 0) {
        pa(game);
        pushed--;
    }
}

void sort_large(game_t *game)
{
    sort_medium(game);
}

void choose_sort_algorithm(game_t *game)
{
    int size = list_size(game->l_a);

    if (list_is_sorted(game->l_a))
        return;
    if (size <= 3)
        sort_small(game);
    else if (size <= 100)
        sort_medium(game);
    else
        sort_large(game);
}