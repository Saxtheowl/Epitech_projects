/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** Check circular rotation
*/

#include <stdio.h>
#include <string.h>
#include "crocus.h"

int is_rotation(const char *a, const char *b)
{
    size_t la;
    char buf[4096];

    if (!a || !b)
        return 0;
    la = strlen(a);
    if (la != strlen(b))
        return 0;
    if (la == 0)
        return 1;
    if (la * 2 >= sizeof(buf))
        return 0;
    strcpy(buf, a);
    strcat(buf, a);
    return strstr(buf, b) != NULL;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;
    if (is_rotation(argv[1], argv[2]))
        puts("Yes");
    else
        puts("No");
    return 0;
}

