/*
** EPITECH PROJECT, 2024
** Day10 - my_advanced_sort_word_array
** File description:
** Sorts word array with custom comparison function - Task 04
*/

#include "include/my.h"

void my_advanced_sort_word_array(char **tab, int (*cmp)(char const *, char const *))
{
    char *temp;
    int i;
    int j;
    int size;

    if (tab == NULL || cmp == NULL)
        return;

    size = 0;
    while (tab[size] != NULL)
        size++;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if ((*cmp)(tab[i], tab[j]) > 0) {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}