/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_str_islower.c
*/

int my_str_islower(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;

    while (str[i] != '\0') {
        if (!(str[i] >= 'a' && str[i] <= 'z'))
            return 0;
        i++;
    }

    return 1;
}