#include "push_swap.h"

int main(int argc, char **argv)
{
    stack_t *stack;
    int i;
    int size;

    if (argc < 2) {
        return 0;
    }

    stack = init_stack();
    if (!stack)
        return 84;

    for (i = argc - 1; i >= 1; i--) {
        if (!is_valid_number(argv[i])) {
            free_stack(stack);
            return 84;
        }
        push_front(&stack->l_a, my_atoi(argv[i]));
    }

    if (is_sorted(stack->l_a)) {
        free_stack(stack);
        return 0;
    }

    size = list_size(stack->l_a);
    if (size <= 5)
        sort_small(stack, size);
    else
        sort_large(stack);

    print_operations(stack);
    free_stack(stack);
    return 0;
}