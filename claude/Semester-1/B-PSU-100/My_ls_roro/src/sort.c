/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** File sorting functionality
*/

#include "../include/my_ls.h"

static int compare_names(file_info_t *a, file_info_t *b, int reverse)
{
    int cmp = my_strcmp(a->name, b->name);

    return reverse ? -cmp : cmp;
}

static int compare_times(file_info_t *a, file_info_t *b, int reverse)
{
    time_t time_a = a->stat_info.st_mtime;
    time_t time_b = b->stat_info.st_mtime;

    if (time_a == time_b)
        return compare_names(a, b, reverse);
    if (time_a > time_b)
        return reverse ? 1 : -1;
    return reverse ? -1 : 1;
}

static file_info_t *merge_files(file_info_t *a, file_info_t *b, options_t *opts)
{
    file_info_t *result = NULL;
    int cmp;

    if (!a)
        return b;
    if (!b)
        return a;
    if (opts->t_flag)
        cmp = compare_times(a, b, opts->r_flag);
    else
        cmp = compare_names(a, b, opts->r_flag);
    if (cmp <= 0) {
        result = a;
        result->next = merge_files(a->next, b, opts);
    } else {
        result = b;
        result->next = merge_files(a, b->next, opts);
    }
    return result;
}

static void split_list(file_info_t *head, file_info_t **a, file_info_t **b)
{
    file_info_t *slow = head;
    file_info_t *fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *a = head;
    *b = slow->next;
    slow->next = NULL;
}

void sort_files(file_info_t **files, options_t *opts)
{
    file_info_t *head = *files;
    file_info_t *a;
    file_info_t *b;

    if (!head || !head->next)
        return;
    split_list(head, &a, &b);
    sort_files(&a, opts);
    sort_files(&b, opts);
    *files = merge_files(a, b, opts);
}