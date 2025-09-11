/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** to_number.c
*/

static int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int to_number(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }

    while (str[i] != '\0' && is_digit(str[i])) {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}