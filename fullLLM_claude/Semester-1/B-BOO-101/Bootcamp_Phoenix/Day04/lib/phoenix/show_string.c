/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** show_string.c
*/

void my_putchar(char c);

int show_string(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}