#include "push_swap.h"

void sa(stack_t *stack)
{
    int first, second;

    if (!stack->l_a || !stack->l_a->next)
        return;
    first = pop_front(&stack->l_a);
    second = pop_front(&stack->l_a);
    push_front(&stack->l_a, first);
    push_front(&stack->l_a, second);
    add_operation(stack, "sa");
}

void sb(stack_t *stack)
{
    int first, second;

    if (!stack->l_b || !stack->l_b->next)
        return;
    first = pop_front(&stack->l_b);
    second = pop_front(&stack->l_b);
    push_front(&stack->l_b, first);
    push_front(&stack->l_b, second);
    add_operation(stack, "sb");
}

void sc(stack_t *stack)
{
    int first_a, second_a, first_b, second_b;

    if (stack->l_a && stack->l_a->next) {
        first_a = pop_front(&stack->l_a);
        second_a = pop_front(&stack->l_a);
        push_front(&stack->l_a, first_a);
        push_front(&stack->l_a, second_a);
    }
    if (stack->l_b && stack->l_b->next) {
        first_b = pop_front(&stack->l_b);
        second_b = pop_front(&stack->l_b);
        push_front(&stack->l_b, first_b);
        push_front(&stack->l_b, second_b);
    }
    add_operation(stack, "sc");
}

void pa(stack_t *stack)
{
    int value;

    if (!stack->l_b)
        return;
    value = pop_front(&stack->l_b);
    push_front(&stack->l_a, value);
    add_operation(stack, "pa");
}

void pb(stack_t *stack)
{
    int value;

    if (!stack->l_a)
        return;
    value = pop_front(&stack->l_a);
    push_front(&stack->l_b, value);
    add_operation(stack, "pb");
}