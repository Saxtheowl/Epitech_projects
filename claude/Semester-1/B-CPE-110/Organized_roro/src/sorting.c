/*
** EPITECH PROJECT, 2024
** sorting.c
** File description:
** Sorting algorithms and comparison functions for materials
*/

#include "../include/organized.h"
#include <stdlib.h>

static int compare_by_criterion(material_t *a, material_t *b, 
                               sort_criterion_t criterion)
{
    switch (criterion) {
        case SORT_TYPE:
            return a->type - b->type;
        case SORT_NAME:
            return my_strcmp(a->name, b->name);
        case SORT_ID:
            return a->id - b->id;
        default:
            return 0;
    }
}

int compare_materials(material_t *a, material_t *b, sort_params_t *params)
{
    int result;
    int i;

    if (!a || !b || !params)
        return 0;
    
    for (i = 0; i < params->count; i++) {
        result = compare_by_criterion(a, b, params->criteria[i]);
        if (result != 0) {
            if (params->reverse_flags[i])
                result = -result;
            return result;
        }
    }
    return 0;
}

static material_t *merge_sorted_lists(material_t *a, material_t *b, 
                                     sort_params_t *params)
{
    material_t dummy;
    material_t *tail = &dummy;

    dummy.next = NULL;
    
    while (a && b) {
        if (compare_materials(a, b, params) <= 0) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    
    tail->next = a ? a : b;
    return dummy.next;
}

static material_t *merge_sort_list(material_t *head, sort_params_t *params)
{
    material_t *slow;
    material_t *fast;
    material_t *prev;
    material_t *left;
    material_t *right;

    if (!head || !head->next)
        return head;
    
    slow = head;
    fast = head;
    prev = NULL;
    
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    prev->next = NULL;
    
    left = merge_sort_list(head, params);
    right = merge_sort_list(slow, params);
    
    return merge_sorted_lists(left, right, params);
}

void workshop_sort(workshop_t *workshop, sort_params_t *params)
{
    if (!workshop || !params || params->count == 0)
        return;
    
    workshop->materials = merge_sort_list(workshop->materials, params);
}