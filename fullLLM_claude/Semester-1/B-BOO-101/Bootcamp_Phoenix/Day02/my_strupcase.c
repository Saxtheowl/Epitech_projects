/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** my_strupcase.c
*/

char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - ('a' - 'A');
        i++;
    }

    return str;
}