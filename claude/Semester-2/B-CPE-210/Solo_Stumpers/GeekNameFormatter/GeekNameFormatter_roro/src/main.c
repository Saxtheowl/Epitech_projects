/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Main function for geek name formatter
*/

#include "geek_name_formatter.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_putstr("Usage: geekNameFormatter string\n");
        return ERROR;
    }
    format_geek_name(argv[1]);
    my_putchar('\n');
    return SUCCESS;
}