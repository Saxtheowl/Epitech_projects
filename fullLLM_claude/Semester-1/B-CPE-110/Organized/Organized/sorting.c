#include "organized.h"

static int compare_by_type(material_t *a, material_t *b, int reverse)
{
    char const *type_a = get_type_string(a->type);
    char const *type_b = get_type_string(b->type);
    int result = my_strcmp(type_a, type_b);
    
    return reverse ? -result : result;
}

static int compare_by_name(material_t *a, material_t *b, int reverse)
{
    int result = my_strcmp(a->name, b->name);
    
    return reverse ? -result : result;
}

static int compare_by_id(material_t *a, material_t *b, int reverse)
{
    int result = a->id - b->id;
    
    return reverse ? -result : result;
}

int compare_materials(material_t *a, material_t *b, char **sort_criteria)
{
    int i = 0;
    int result = 0;
    
    while (sort_criteria[i] && result == 0) {
        int reverse = 0;
        char *criterion = sort_criteria[i];
        
        if (i + 1 < count_args(sort_criteria) && 
            my_strcmp(sort_criteria[i + 1], "-r") == 0) {
            reverse = 1;
            i++;
        }
        
        if (my_strcmp(criterion, "TYPE") == 0) {
            result = compare_by_type(a, b, reverse);
        } else if (my_strcmp(criterion, "NAME") == 0) {
            result = compare_by_name(a, b, reverse);
        } else if (my_strcmp(criterion, "ID") == 0) {
            result = compare_by_id(a, b, reverse);
        }
        
        i++;
    }
    
    return result;
}

static material_t *merge_sorted_lists(material_t *left, material_t *right, char **sort_criteria)
{
    material_t *result = 0;
    material_t **tail = &result;
    
    while (left && right) {
        if (compare_materials(left, right, sort_criteria) <= 0) {
            *tail = left;
            left = left->next;
        } else {
            *tail = right;
            right = right->next;
        }
        tail = &((*tail)->next);
    }
    
    *tail = left ? left : right;
    
    return result;
}

static material_t *merge_sort_list(material_t *head, char **sort_criteria)
{
    material_t *slow, *fast, *prev;
    material_t *left, *right;
    
    if (!head || !head->next)
        return head;
    
    slow = fast = head;
    prev = 0;
    
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    prev->next = 0;
    
    left = merge_sort_list(head, sort_criteria);
    right = merge_sort_list(slow, sort_criteria);
    
    return merge_sorted_lists(left, right, sort_criteria);
}

void sort_materials(workshop_t *workshop, char **args)
{
    if (!workshop || !args)
        return;
    
    workshop->materials = merge_sort_list(workshop->materials, args);
}

int sort(void *data, char **args)
{
    workshop_t *workshop = (workshop_t *)data;
    
    if (!workshop || !args)
        return 84;
    
    sort_materials(workshop, args);
    return 0;
}