/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** show_parameters_array.c
*/

#include <stddef.h>
#include "phoenix.h"

struct info_param
{
    int length;
    char *str;
    char *copy;
    char **word_array;
};

int show_string_array(char * const *array);

int show_parameters_array(struct info_param const *par)
{
    int i = 0;

    while (par[i].str != NULL) {
        show_string(par[i].str);
        my_putchar('\n');
        
        show_number(par[i].length);
        my_putchar('\n');
        
        show_string_array(par[i].word_array);
        
        i++;
    }

    return 0;
}