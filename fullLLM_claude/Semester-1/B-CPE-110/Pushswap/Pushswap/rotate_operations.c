#include "push_swap.h"

static void rotate_list(list_t **list)
{
    list_t *first, *last;

    if (!*list || !(*list)->next)
        return;
    first = *list;
    *list = (*list)->next;
    last = *list;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL;
}

static void reverse_rotate_list(list_t **list)
{
    list_t *prev, *last;

    if (!*list || !(*list)->next)
        return;
    prev = NULL;
    last = *list;
    while (last->next) {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *list;
    *list = last;
}

void ra(stack_t *stack)
{
    rotate_list(&stack->l_a);
    add_operation(stack, "ra");
}

void rb(stack_t *stack)
{
    rotate_list(&stack->l_b);
    add_operation(stack, "rb");
}

void rr(stack_t *stack)
{
    rotate_list(&stack->l_a);
    rotate_list(&stack->l_b);
    add_operation(stack, "rr");
}

void rra(stack_t *stack)
{
    reverse_rotate_list(&stack->l_a);
    add_operation(stack, "rra");
}

void rrb(stack_t *stack)
{
    reverse_rotate_list(&stack->l_b);
    add_operation(stack, "rrb");
}

void rrr(stack_t *stack)
{
    reverse_rotate_list(&stack->l_a);
    reverse_rotate_list(&stack->l_b);
    add_operation(stack, "rrr");
}