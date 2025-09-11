/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_str_isupper.c
*/

int my_str_isupper(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;

    while (str[i] != '\0') {
        if (!(str[i] >= 'A' && str[i] <= 'Z'))
            return 0;
        i++;
    }

    return 1;
}