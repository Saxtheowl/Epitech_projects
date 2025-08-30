/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Utils
*/

#include <stdlib.h>
#include "my_ls.h"

void free_entries(entry_t *arr, int n)
{
    int i;

    if (!arr)
        return;
    for (i = 0; i < n; ++i) {
        free(arr[i].name);
        free(arr[i].path);
    }
    free(arr);
}
