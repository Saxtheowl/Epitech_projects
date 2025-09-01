/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   string helpers
*/

int my_strcmp(const char *a, const char *b)
{
    int i = 0;
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    while (a[i] && b[i] && a[i] == b[i]) i++;
    return ((unsigned char)a[i] - (unsigned char)b[i]);
}

