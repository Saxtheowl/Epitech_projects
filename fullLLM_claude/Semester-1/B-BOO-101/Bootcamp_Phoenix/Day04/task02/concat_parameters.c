/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** concat_parameters.c
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

static int total_length(int ac, char **av)
{
    int total = 0;
    int i = 0;

    while (i < ac) {
        total += my_strlen(av[i]);
        if (i < ac - 1)
            total += 1;
        i++;
    }
    return total;
}

char *concat_parameters(int ac, char **av)
{
    int total_len = total_length(ac, av);
    char *result = malloc(sizeof(char) * (total_len + 1));
    int pos = 0;
    int i, j;

    if (result == NULL)
        return NULL;

    for (i = 0; i < ac; i++) {
        j = 0;
        while (av[i][j] != '\0') {
            result[pos] = av[i][j];
            pos++;
            j++;
        }
        if (i < ac - 1) {
            result[pos] = '\n';
            pos++;
        }
    }
    result[pos] = '\0';

    return result;
}