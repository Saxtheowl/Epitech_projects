/*
** EPITECH PROJECT, 2024
** Day08 - B-CPE-100
** File description:
** concat_params.c - TASK 02
*/

#include <stdlib.h>
#include <stddef.h>

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strcat(char *dest, char const *src);

static int calculate_total_length(int argc, char **argv)
{
    int total_len = 0;
    int i = 0;
    
    while (i < argc) {
        total_len += my_strlen(argv[i]);
        if (i < argc - 1)
            total_len++;
        i++;
    }
    
    return total_len;
}

char *concat_params(int argc, char **argv)
{
    char *result;
    int total_len;
    int i = 0;
    
    if (argc == 0 || argv == NULL)
        return NULL;
    
    total_len = calculate_total_length(argc, argv);
    result = malloc(sizeof(char) * (total_len + 1));
    
    if (result == NULL)
        return NULL;
    
    my_strcpy(result, argv[0]);
    i = 1;
    
    while (i < argc) {
        my_strcat(result, "\n");
        my_strcat(result, argv[i]);
        i++;
    }
    
    return result;
}