#include <stdlib.h>
#include <stdio.h>
#include "../int_list.h"

unsigned int int_list_get_size(int_list_t list)
{
    unsigned int size = 0;
    int_node_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

bool int_list_is_empty(int_list_t list)
{
    return list == NULL;
}

void int_list_dump(int_list_t list)
{
    int_node_t *current = list;

    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL)
            printf(" ");
        current = current->next;
    }
    printf("\n");
}

bool int_list_add_elem_at_front(int_list_t *front_ptr, int elem)
{
    int_node_t *new_node;

    if (front_ptr == NULL)
        return false;

    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;

    new_node->value = elem;
    new_node->next = *front_ptr;
    *front_ptr = new_node;
    return true;
}

bool int_list_add_elem_at_back(int_list_t *front_ptr, int elem)
{
    int_node_t *new_node;
    int_node_t *current;

    if (front_ptr == NULL)
        return false;

    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;

    new_node->value = elem;
    new_node->next = NULL;

    if (*front_ptr == NULL) {
        *front_ptr = new_node;
        return true;
    }

    current = *front_ptr;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
    return true;
}

bool int_list_add_elem_at_position(int_list_t *front_ptr, int elem, unsigned int position)
{
    int_node_t *new_node;
    int_node_t *current;
    unsigned int i = 0;

    if (front_ptr == NULL)
        return false;

    if (position == 0)
        return int_list_add_elem_at_front(front_ptr, elem);

    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;

    new_node->value = elem;

    current = *front_ptr;
    while (current != NULL && i < position - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        free(new_node);
        return false;
    }

    new_node->next = current->next;
    current->next = new_node;
    return true;
}

bool int_list_del_elem_at_front(int_list_t *front_ptr)
{
    int_node_t *to_delete;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;

    to_delete = *front_ptr;
    *front_ptr = (*front_ptr)->next;
    free(to_delete);
    return true;
}

bool int_list_del_elem_at_back(int_list_t *front_ptr)
{
    int_node_t *current;
    int_node_t *previous = NULL;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;

    if ((*front_ptr)->next == NULL) {
        free(*front_ptr);
        *front_ptr = NULL;
        return true;
    }

    current = *front_ptr;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    previous->next = NULL;
    free(current);
    return true;
}

bool int_list_del_elem_at_position(int_list_t *front_ptr, unsigned int position)
{
    int_node_t *current;
    int_node_t *to_delete;
    unsigned int i = 0;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;

    if (position == 0)
        return int_list_del_elem_at_front(front_ptr);

    current = *front_ptr;
    while (current != NULL && i < position - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL)
        return false;

    to_delete = current->next;
    current->next = to_delete->next;
    free(to_delete);
    return true;
}

void int_list_clear(int_list_t *front_ptr)
{
    if (front_ptr == NULL)
        return;

    while (*front_ptr != NULL)
        int_list_del_elem_at_front(front_ptr);
}

int int_list_get_elem_at_front(int_list_t list)
{
    if (list == NULL)
        return 0;
    return list->value;
}

int int_list_get_elem_at_back(int_list_t list)
{
    int_node_t *current = list;

    if (list == NULL)
        return 0;

    while (current->next != NULL)
        current = current->next;
    return current->value;
}

int int_list_get_elem_at_position(int_list_t list, unsigned int position)
{
    int_node_t *current = list;
    unsigned int i = 0;

    while (current != NULL && i < position) {
        current = current->next;
        i++;
    }

    if (current == NULL)
        return 0;
    return current->value;
}