/*
** EPITECH PROJECT, 2024
** Day10 - my_sort_word_array
** File description:
** Sorts word array in ASCII order - Task 03
*/

#include "include/my.h"

void my_sort_word_array(char **tab)
{
    char *temp;
    int i;
    int j;
    int size;

    if (tab == NULL)
        return;

    size = 0;
    while (tab[size] != NULL)
        size++;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (my_strcmp(tab[i], tab[j]) > 0) {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}