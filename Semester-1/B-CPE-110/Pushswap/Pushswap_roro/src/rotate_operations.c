/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Rotation operations implementation (ra, rb, rra, rrb, rr, rrr)
*/

#include "../include/push_swap.h"

static void rotate_list(list_t *list)
{
    node_t *current;
    int first_value;
    
    if (!list || list->size < 2)
        return;
    
    first_value = pop_front(list);
    
    if (!list->head) {
        push_front(list, first_value);
        return;
    }
    
    current = list->head;
    while (current->next)
        current = current->next;
    
    current->next = malloc(sizeof(node_t));
    if (current->next) {
        current->next->value = first_value;
        current->next->next = NULL;
        list->size++;
    }
}

static void reverse_rotate_list(list_t *list)
{
    node_t *current;
    node_t *prev;
    int last_value;
    
    if (!list || list->size < 2)
        return;
    
    if (list->size == 2) {
        rotate_list(list);
        return;
    }
    
    current = list->head;
    prev = NULL;
    
    while (current->next) {
        prev = current;
        current = current->next;
    }
    
    last_value = current->value;
    free(current);
    prev->next = NULL;
    list->size--;
    
    push_front(list, last_value);
}

void ra(game_t *game)
{
    if (!game || !game->l_a)
        return;
    
    rotate_list(game->l_a);
    add_operation(game, "ra");
}

void rb(game_t *game)
{
    if (!game || !game->l_b)
        return;
    
    rotate_list(game->l_b);
    add_operation(game, "rb");
}

void rr(game_t *game)
{
    if (!game)
        return;
    
    if (game->l_a)
        rotate_list(game->l_a);
    if (game->l_b)
        rotate_list(game->l_b);
    
    add_operation(game, "rr");
}

void rra(game_t *game)
{
    if (!game || !game->l_a)
        return;
    
    reverse_rotate_list(game->l_a);
    add_operation(game, "rra");
}

void rrb(game_t *game)
{
    if (!game || !game->l_b)
        return;
    
    reverse_rotate_list(game->l_b);
    add_operation(game, "rrb");
}

void rrr(game_t *game)
{
    if (!game)
        return;
    
    if (game->l_a)
        reverse_rotate_list(game->l_a);
    if (game->l_b)
        reverse_rotate_list(game->l_b);
    
    add_operation(game, "rrr");
}