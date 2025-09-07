#include <stddef.h>
#include "include/my.h"

int my_advanced_sort_word_array(char **tab, int (*cmp)(char const *, char const *))
{
    int i = 0;
    int j;
    char *temp;
    int swapped;

    if (tab == NULL || cmp == NULL)
        return 0;

    while (tab[i] != NULL)
        i++;

    do {
        swapped = 0;
        for (j = 0; j < i - 1; j++) {
            if (cmp(tab[j], tab[j + 1]) > 0) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                swapped = 1;
            }
        }
        i--;
    } while (swapped && i > 1);

    return 0;
}