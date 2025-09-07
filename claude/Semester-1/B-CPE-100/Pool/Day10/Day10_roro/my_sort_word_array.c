#include <stddef.h>
#include "include/my.h"

int my_sort_word_array(char **tab)
{
    int i = 0;
    int j;
    char *temp;
    int swapped;

    if (tab == NULL)
        return 0;

    while (tab[i] != NULL)
        i++;

    do {
        swapped = 0;
        for (j = 0; j < i - 1; j++) {
            if (my_strcmp(tab[j], tab[j + 1]) > 0) {
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