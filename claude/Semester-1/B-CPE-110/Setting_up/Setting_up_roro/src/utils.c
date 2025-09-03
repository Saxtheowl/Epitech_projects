/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** utility functions
*/

#include "../include/setting_up.h"

int my_strlen(char *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;

    if (str == NULL)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

int is_valid_char(char c)
{
    return (c == '.' || c == 'o');
}