/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Formatting logic for geek name formatter
*/

#include "geek_name_formatter.h"

static int is_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void format_geek_name(char *name)
{
    int i = 0;
    int letter_index = 0;
    char formatted_char = 0;

    if (!name)
        return;
    while (name[i]) {
        if (is_letter(name[i])) {
            if (letter_index % 2 == 0)
                formatted_char = to_upper(name[i]);
            else
                formatted_char = to_lower(name[i]);
            formatted_char = replace_geek_char(formatted_char);
            my_putchar(formatted_char);
            letter_index++;
        } else {
            my_putchar(name[i]);
            letter_index = 0;
        }
        i++;
    }
}