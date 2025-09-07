#include <stddef.h>
#include "../stack.h"

unsigned int stack_get_size(stack_t stack)
{
    return list_get_size(stack);
}

bool stack_is_empty(stack_t stack)
{
    return list_is_empty(stack);
}

bool stack_push(stack_t *stack_ptr, void *elem)
{
    if (stack_ptr == NULL)
        return false;
    return list_add_elem_at_front(stack_ptr, elem);
}

bool stack_pop(stack_t *stack_ptr)
{
    if (stack_ptr == NULL)
        return false;
    return list_del_elem_at_front(stack_ptr);
}

void stack_clear(stack_t *stack_ptr)
{
    if (stack_ptr == NULL)
        return;
    list_clear(stack_ptr);
}

void *stack_top(stack_t stack)
{
    return list_get_elem_at_front(stack);
}