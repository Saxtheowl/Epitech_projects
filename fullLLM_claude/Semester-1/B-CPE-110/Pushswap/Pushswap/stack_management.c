#include "push_swap.h"

stack_t *init_stack(void)
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (!stack)
        return NULL;
    stack->l_a = NULL;
    stack->l_b = NULL;
    stack->operations = malloc(1024);
    if (!stack->operations) {
        free(stack);
        return NULL;
    }
    stack->operations[0] = '\0';
    stack->ops_size = 0;
    stack->ops_capacity = 1024;
    return stack;
}

void free_stack(stack_t *stack)
{
    if (!stack)
        return;
    free_list(stack->l_a);
    free_list(stack->l_b);
    free(stack->operations);
    free(stack);
}

void add_operation(stack_t *stack, const char *op)
{
    int op_len = 0;
    int i;

    while (op[op_len])
        op_len++;

    if (stack->ops_size + op_len + 2 >= stack->ops_capacity) {
        stack->ops_capacity *= 2;
        stack->operations = realloc(stack->operations, stack->ops_capacity);
        if (!stack->operations)
            return;
    }

    if (stack->ops_size > 0) {
        stack->operations[stack->ops_size] = ' ';
        stack->ops_size++;
    }

    for (i = 0; i < op_len; i++) {
        stack->operations[stack->ops_size] = op[i];
        stack->ops_size++;
    }
    stack->operations[stack->ops_size] = '\0';
}

void print_operations(stack_t *stack)
{
    if (stack->ops_size > 0) {
        write(1, stack->operations, stack->ops_size);
        write(1, "\n", 1);
    }
}