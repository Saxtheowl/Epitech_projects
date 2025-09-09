#include "push_swap.h"

list_t *create_node(int value)
{
    list_t *node = malloc(sizeof(list_t));
    if (!node)
        return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

void push_front(list_t **list, int value)
{
    list_t *new_node = create_node(value);
    if (!new_node)
        return;
    new_node->next = *list;
    *list = new_node;
}

int pop_front(list_t **list)
{
    list_t *temp;
    int value;

    if (!*list)
        return 0;
    temp = *list;
    value = temp->value;
    *list = (*list)->next;
    free(temp);
    return value;
}

int list_size(list_t *list)
{
    int size = 0;
    while (list) {
        size++;
        list = list->next;
    }
    return size;
}

int is_sorted(list_t *list)
{
    if (!list || !list->next)
        return 1;
    while (list->next) {
        if (list->value > list->next->value)
            return 0;
        list = list->next;
    }
    return 1;
}

void free_list(list_t *list)
{
    list_t *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp);
    }
}