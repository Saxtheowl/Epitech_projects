/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_revstr.c
*/

static int my_strlen(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *my_revstr(char *str)
{
    int len = my_strlen(str);
    int i = 0;
    char temp;

    while (i < len / 2) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
        i++;
    }

    return str;
}