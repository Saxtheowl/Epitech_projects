/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** utils
*/

#include "tictactoe.h"

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return -1;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}