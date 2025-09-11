/*
** EPITECH PROJECT, 2024
** Day09 - B-CPE-100
** File description:
** my_params_to_array.c - TASK 03
*/

#include <stdlib.h>
#include <stddef.h>

int my_strlen(char const *str);
char *my_strdup(char const *src);
char **my_str_to_word_array(char const *str);

struct info_param
{
    int length;
    char *str;
    char *copy;
    char **word_array;
};

struct info_param *my_params_to_array(int ac, char **av)
{
    struct info_param *array;
    int i = 0;
    
    if (ac <= 0 || av == NULL)
        return NULL;
    
    array = malloc(sizeof(struct info_param) * (ac + 1));
    if (array == NULL)
        return NULL;
    
    while (i < ac) {
        array[i].length = my_strlen(av[i]);
        array[i].str = av[i];
        array[i].copy = my_strdup(av[i]);
        array[i].word_array = my_str_to_word_array(av[i]);
        
        if (array[i].copy == NULL || array[i].word_array == NULL)
            return NULL;
        
        i++;
    }
    
    array[i].length = 0;
    array[i].str = NULL;
    array[i].copy = NULL;
    array[i].word_array = NULL;
    
    return array;
}