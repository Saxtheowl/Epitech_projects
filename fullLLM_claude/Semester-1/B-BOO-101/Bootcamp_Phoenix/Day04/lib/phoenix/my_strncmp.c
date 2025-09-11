/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** my_strncmp.c
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }

    if (i < n)
        return (s1[i] - s2[i]);

    return 0;
}