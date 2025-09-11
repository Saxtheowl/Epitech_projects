/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** parameters_to_array.c
*/

#include <stdlib.h>

struct info_param
{
    int length;
    char *str;
    char *copy;
    char **word_array;
};

char *duplicate_string(char const *src);
char **split_string(char const *str);

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

struct info_param *parameters_to_array(int ac, char **av)
{
    struct info_param *result;
    int i;

    result = malloc(sizeof(struct info_param) * (ac + 1));
    if (result == NULL)
        return NULL;

    for (i = 0; i < ac; i++) {
        result[i].length = my_strlen(av[i]);
        result[i].str = av[i];
        result[i].copy = duplicate_string(av[i]);
        result[i].word_array = split_string(av[i]);
        
        if (result[i].copy == NULL || result[i].word_array == NULL)
            return NULL;
    }

    result[i].str = NULL;
    result[i].copy = NULL;
    result[i].word_array = NULL;
    result[i].length = 0;

    return result;
}