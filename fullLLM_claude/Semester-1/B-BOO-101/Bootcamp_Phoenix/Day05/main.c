/*
** EPITECH PROJECT, 2024
** Day05 - Bootcamp Phoenix
** File description:
** main.c
*/

#include <unistd.h>

void my_putchar(char c);
int show_string(char const *str);
int to_number(char const *str);
void draw_star(int size);

void my_putchar(char c)
{
    write(1, &c, 1);
}

int show_string(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}

static int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int to_number(char const *str)
{
    int result = 0;
    int i = 0;

    while (str[i] != '\0' && is_digit(str[i])) {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

static int is_valid_number(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (!is_digit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int main(int ac, char **av)
{
    int size;

    if (ac != 2) {
        show_string("Usage: ./star <number>\n");
        return 84;
    }

    if (!is_valid_number(av[1])) {
        show_string("Usage: ./star <number>\n");
        return 84;
    }

    size = to_number(av[1]);
    
    if (size == 0)
        return 0;

    draw_star(size);
    return 0;
}