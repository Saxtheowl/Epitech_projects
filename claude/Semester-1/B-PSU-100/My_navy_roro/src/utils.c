/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Utility functions for my_navy
*/

#include "../include/my_navy.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar('0' + nb % 10);
}

int my_strlen(const char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

void my_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (!dest || !src)
        return;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int is_valid_position(char *pos)
{
    if (my_strlen(pos) != 2)
        return 0;
    if (pos[0] < 'A' || pos[0] > 'H')
        return 0;
    if (pos[1] < '1' || pos[1] > '8')
        return 0;
    return 1;
}

void parse_position(char *pos, int *x, int *y)
{
    *x = pos[0] - 'A';
    *y = pos[1] - '1';
}

char *position_to_string(int x, int y)
{
    static char pos[3];

    pos[0] = 'A' + x;
    pos[1] = '1' + y;
    pos[2] = '\0';
    return pos;
}