#include <stdlib.h>
#include <stdio.h>
#include "../list.h"

unsigned int list_get_size(list_t list)
{
    unsigned int size = 0;
    node_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

bool list_is_empty(list_t list)
{
    return list == NULL;
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    node_t *current = list;

    while (current != NULL) {
        if (val_disp != NULL)
            val_disp(current->value);
        current = current->next;
    }
}

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    node_t *new_node;

    if (front_ptr == NULL)
        return false;

    new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        return false;

    new_node->value = elem;
    new_node->next = *front_ptr;
    *front_ptr = new_node;
    return true;
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    node_t *new_node;
    node_t *current;

    if (front_ptr == NULL)
        return false;

    new_node = malloc(sizeof(node_t));
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

bool list_add_elem_at_position(list_t *front_ptr, void *elem, unsigned int position)
{
    node_t *new_node;
    node_t *current;
    unsigned int i = 0;

    if (front_ptr == NULL)
        return false;

    if (position == 0)
        return list_add_elem_at_front(front_ptr, elem);

    new_node = malloc(sizeof(node_t));
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

bool list_del_elem_at_front(list_t *front_ptr)
{
    node_t *to_delete;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;

    to_delete = *front_ptr;
    *front_ptr = (*front_ptr)->next;
    free(to_delete);
    return true;
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    node_t *current;
    node_t *previous = NULL;

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

bool list_del_elem_at_position(list_t *front_ptr, unsigned int position)
{
    node_t *current;
    node_t *to_delete;
    unsigned int i = 0;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;

    if (position == 0)
        return list_del_elem_at_front(front_ptr);

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

void list_clear(list_t *front_ptr)
{
    if (front_ptr == NULL)
        return;

    while (*front_ptr != NULL)
        list_del_elem_at_front(front_ptr);
}

void *list_get_elem_at_front(list_t list)
{
    if (list == NULL)
        return NULL;
    return list->value;
}

void *list_get_elem_at_back(list_t list)
{
    node_t *current = list;

    if (list == NULL)
        return NULL;

    while (current->next != NULL)
        current = current->next;
    return current->value;
}

void *list_get_elem_at_position(list_t list, unsigned int position)
{
    node_t *current = list;
    unsigned int i = 0;

    while (current != NULL && i < position) {
        current = current->next;
        i++;
    }

    if (current == NULL)
        return NULL;
    return current->value;
}