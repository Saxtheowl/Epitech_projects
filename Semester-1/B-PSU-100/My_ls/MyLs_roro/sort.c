#include "my_ls.h"

static int compare_names(file_info_t *a, file_info_t *b, int reverse)
{
    int cmp = my_strcmp(a->name, b->name);
    return reverse ? -cmp : cmp;
}

static int compare_times(file_info_t *a, file_info_t *b, int reverse)
{
    if (a->st.st_mtime > b->st.st_mtime)
        return reverse ? 1 : -1;
    if (a->st.st_mtime < b->st.st_mtime)
        return reverse ? -1 : 1;
    return compare_names(a, b, reverse);
}

static file_info_t *merge_lists(file_info_t *left, file_info_t *right, options_t *opts)
{
    file_info_t *result = NULL;
    file_info_t **current = &result;
    int cmp;
    
    while (left && right) {
        if (opts->flags & OPT_TIME)
            cmp = compare_times(left, right, opts->flags & OPT_REV);
        else
            cmp = compare_names(left, right, opts->flags & OPT_REV);
        
        if (cmp <= 0) {
            *current = left;
            left = left->next;
        } else {
            *current = right;
            right = right->next;
        }
        current = &((*current)->next);
    }
    
    *current = left ? left : right;
    return result;
}

static file_info_t *merge_sort_list(file_info_t *list, options_t *opts)
{
    file_info_t *middle;
    file_info_t *left;
    file_info_t *right;
    file_info_t *slow = list;
    file_info_t *fast = list;
    file_info_t *prev = NULL;
    
    if (!list || !list->next)
        return list;
    
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    middle = slow;
    prev->next = NULL;
    
    left = merge_sort_list(list, opts);
    right = merge_sort_list(middle, opts);
    
    return merge_lists(left, right, opts);
}

file_info_t *sort_files(file_info_t *list, options_t *opts)
{
    if (!list)
        return NULL;
    return merge_sort_list(list, opts);
}