#include <stdio.h>
#include <stdlib.h>
#include "include/my.h"

int my_sort_word_array(char **tab);
int my_advanced_sort_word_array(char **tab, int (*cmp)(char const *, char const *));

void test_word_arrays(void)
{
    char *words[] = {"zebra", "apple", "banana", "cherry", NULL};
    char **test_array = malloc(5 * sizeof(char*));
    int i;

    for (i = 0; words[i] != NULL; i++) {
        test_array[i] = words[i];
    }
    test_array[i] = NULL;

    printf("=== Testing my_sort_word_array ===\n");
    printf("Before sorting:\n");
    my_show_word_array(test_array);

    my_sort_word_array(test_array);
    
    printf("After sorting:\n");
    my_show_word_array(test_array);

    printf("\n=== Testing my_advanced_sort_word_array ===\n");
    
    for (i = 0; words[i] != NULL; i++) {
        test_array[i] = words[i];
    }
    test_array[i] = NULL;

    printf("Before advanced sorting:\n");
    my_show_word_array(test_array);

    my_advanced_sort_word_array(test_array, my_strcmp);
    
    printf("After advanced sorting:\n");
    my_show_word_array(test_array);

    free(test_array);
}

int main(void)
{
    printf("=== Day10 Functions Test ===\n\n");
    test_word_arrays();
    return 0;
}