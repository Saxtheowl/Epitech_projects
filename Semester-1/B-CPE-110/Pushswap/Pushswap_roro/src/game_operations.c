/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Game operations implementation (sa, sb, pa, pb, ra, rb, rra, rrb)
*/

#include "../include/push_swap.h"

void sa(game_t *game)
{
    int first;
    int second;
    
    if (!game || !game->l_a || game->l_a->size < 2)
        return;
    
    first = pop_front(game->l_a);
    second = pop_front(game->l_a);
    push_front(game->l_a, first);
    push_front(game->l_a, second);
    
    add_operation(game, "sa");
}

void sb(game_t *game)
{
    int first;
    int second;
    
    if (!game || !game->l_b || game->l_b->size < 2)
        return;
    
    first = pop_front(game->l_b);
    second = pop_front(game->l_b);
    push_front(game->l_b, first);
    push_front(game->l_b, second);
    
    add_operation(game, "sb");
}

void sc(game_t *game)
{
    if (!game)
        return;
    
    if (game->l_a && game->l_a->size >= 2) {
        int first = pop_front(game->l_a);
        int second = pop_front(game->l_a);
        push_front(game->l_a, first);
        push_front(game->l_a, second);
    }
    
    if (game->l_b && game->l_b->size >= 2) {
        int first = pop_front(game->l_b);
        int second = pop_front(game->l_b);
        push_front(game->l_b, first);
        push_front(game->l_b, second);
    }
    
    add_operation(game, "sc");
}

void pa(game_t *game)
{
    int value;
    
    if (!game || !game->l_b || is_empty(game->l_b))
        return;
    
    value = pop_front(game->l_b);
    push_front(game->l_a, value);
    
    add_operation(game, "pa");
}

void pb(game_t *game)
{
    int value;
    
    if (!game || !game->l_a || is_empty(game->l_a))
        return;
    
    value = pop_front(game->l_a);
    push_front(game->l_b, value);
    
    add_operation(game, "pb");
}