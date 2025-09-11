/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_strlowcase.c
*/

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + ('a' - 'A');
        i++;
    }

    return str;
}