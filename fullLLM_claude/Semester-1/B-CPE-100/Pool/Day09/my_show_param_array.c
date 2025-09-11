/*
** EPITECH PROJECT, 2024
** Day09 - B-CPE-100
** File description:
** my_show_param_array.c - TASK 04
*/

#include <stddef.h>

int my_putstr(char const *str);
void my_putchar(char c);
int my_putnbr(int nb);
int my_show_word_array(char * const *tab);

struct info_param
{
    int length;
    char *str;
    char *copy;
    char **word_array;
};

int my_show_param_array(struct info_param const *par)
{
    int i = 0;
    
    if (par == NULL)
        return 0;
    
    while (par[i].str != NULL) {
        my_putstr(par[i].str);
        my_putchar('\n');
        
        my_putnbr(par[i].length);
        my_putchar('\n');
        
        if (par[i].word_array != NULL)
            my_show_word_array(par[i].word_array);
        
        i++;
    }
    
    return 0;
}