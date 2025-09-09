#include "push_swap.h"

int find_min_position(list_t *list)
{
    int min, pos = 0, min_pos = 0;
    
    if (!list)
        return 0;
    
    min = list->value;
    while (list) {
        if (list->value < min) {
            min = list->value;
            min_pos = pos;
        }
        pos++;
        list = list->next;
    }
    return min_pos;
}

int find_max_position(list_t *list)
{
    int max, pos = 0, max_pos = 0;
    
    if (!list)
        return 0;
    
    max = list->value;
    while (list) {
        if (list->value > max) {
            max = list->value;
            max_pos = pos;
        }
        pos++;
        list = list->next;
    }
    return max_pos;
}

static void sort_three(stack_t *stack)
{
    int first, second, third;

    if (!stack->l_a || !stack->l_a->next || !stack->l_a->next->next)
        return;

    first = stack->l_a->value;
    second = stack->l_a->next->value;
    third = stack->l_a->next->next->value;

    if (first > second && second < third && first < third)
        sa(stack);
    else if (first > second && second > third)
        sa(stack), rra(stack);
    else if (first > second && second < third && first > third)
        ra(stack);
    else if (first < second && second > third && first < third)
        sa(stack), ra(stack);
    else if (first < second && second > third && first > third)
        rra(stack);
}

void sort_small(stack_t *stack, int size)
{
    int min_pos;
    int rotations;

    if (size == 2) {
        if (stack->l_a && stack->l_a->next && 
            stack->l_a->value > stack->l_a->next->value)
            sa(stack);
        return;
    }
    if (size == 3) {
        sort_three(stack);
        return;
    }
    
    while (size > 3) {
        min_pos = find_min_position(stack->l_a);
        if (min_pos <= size / 2) {
            rotations = min_pos;
            while (rotations-- > 0)
                ra(stack);
        } else {
            rotations = size - min_pos;
            while (rotations-- > 0)
                rra(stack);
        }
        pb(stack);
        size--;
    }
    sort_three(stack);
    while (stack->l_b)
        pa(stack);
}

void sort_large(stack_t *stack)
{
    int size = list_size(stack->l_a);
    
    while (size > 3) {
        int min_pos = find_min_position(stack->l_a);
        int rotations;
        
        if (min_pos <= size / 2) {
            rotations = min_pos;
            while (rotations-- > 0)
                ra(stack);
        } else {
            rotations = size - min_pos;
            while (rotations-- > 0)
                rra(stack);
        }
        pb(stack);
        size--;
    }
    
    sort_three(stack);
    
    while (stack->l_b)
        pa(stack);
}