/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Sorting algorithms implementation
*/

#include "../include/push_swap.h"

int find_min_position(list_t *list)
{
    node_t *current;
    int min_value;
    int min_pos;
    int current_pos;
    
    if (!list || !list->head)
        return -1;
    
    current = list->head;
    min_value = current->value;
    min_pos = 0;
    current_pos = 0;
    
    while (current) {
        if (current->value < min_value) {
            min_value = current->value;
            min_pos = current_pos;
        }
        current = current->next;
        current_pos++;
    }
    
    return min_pos;
}

int find_max_position(list_t *list)
{
    node_t *current;
    int max_value;
    int max_pos;
    int current_pos;
    
    if (!list || !list->head)
        return -1;
    
    current = list->head;
    max_value = current->value;
    max_pos = 0;
    current_pos = 0;
    
    while (current) {
        if (current->value > max_value) {
            max_value = current->value;
            max_pos = current_pos;
        }
        current = current->next;
        current_pos++;
    }
    
    return max_pos;
}

void sort_three(game_t *game)
{
    node_t *first;
    node_t *second;
    node_t *third;
    
    if (!game || !game->l_a || game->l_a->size != 3)
        return;
    
    first = game->l_a->head;
    second = first->next;
    third = second->next;
    
    if (first->value > second->value && second->value < third->value && first->value < third->value)
        sa(game);
    else if (first->value > second->value && second->value > third->value)
    {
        sa(game);
        rra(game);
    }
    else if (first->value > second->value && second->value < third->value && first->value > third->value)
        ra(game);
    else if (first->value < second->value && second->value > third->value && first->value < third->value)
    {
        sa(game);
        ra(game);
    }
    else if (first->value < second->value && second->value > third->value && first->value > third->value)
        rra(game);
}

void sort_small(game_t *game)
{
    int min_pos;
    int i;
    
    if (!game || !game->l_a)
        return;
    
    if (game->l_a->size == 2) {
        if (game->l_a->head->value > game->l_a->head->next->value)
            sa(game);
        return;
    }
    
    if (game->l_a->size == 3) {
        sort_three(game);
        return;
    }
    
    while (game->l_a->size > 3) {
        min_pos = find_min_position(game->l_a);
        
        if (min_pos <= game->l_a->size / 2) {
            for (i = 0; i < min_pos; i++)
                ra(game);
        } else {
            for (i = min_pos; i < game->l_a->size; i++)
                rra(game);
        }
        
        pb(game);
    }
    
    sort_three(game);
    
    while (!is_empty(game->l_b))
        pa(game);
}

void sort_large(game_t *game)
{
    int half_size;
    node_t *current;
    int median;
    int count;
    
    if (!game || !game->l_a || game->l_a->size <= 5) {
        sort_small(game);
        return;
    }
    
    half_size = game->l_a->size / 2;
    
    current = game->l_a->head;
    count = 0;
    while (current && count < half_size) {
        current = current->next;
        count++;
    }
    
    if (current)
        median = current->value;
    else
        median = game->l_a->head->value;
    
    while (game->l_a->size > 3) {
        if (game->l_a->head->value < median) {
            pb(game);
        } else {
            ra(game);
        }
    }
    
    sort_small(game);
    
    while (!is_empty(game->l_b))
        pa(game);
}

void solve_pushswap(game_t *game)
{
    if (!game || !game->l_a)
        return;
    
    if (game->l_a->size <= 5)
        sort_small(game);
    else
        sort_large(game);
}