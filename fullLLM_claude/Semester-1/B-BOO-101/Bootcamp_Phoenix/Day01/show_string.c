/*
** EPITECH PROJECT, 2024
** show_string
** File description:
** Display the characters of a string one-by-one
*/

int my_putchar(char c);

int show_string(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}