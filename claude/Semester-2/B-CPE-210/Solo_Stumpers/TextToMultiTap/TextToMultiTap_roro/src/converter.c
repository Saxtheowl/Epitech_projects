/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Main logic for text_to_multi_tap
*/

#include "text_to_multi_tap.h"

int text_to_multi_tap(char *str)
{
    int i = 0;
    int last_key = -1;

    if (!str) {
        write_char('\n');
        return 0;
    }
    while (str[i]) {
        if (!is_valid_char(str[i]))
            return 84;
        if (is_upper(str[i])) {
            write_char('#');
            last_key = -1;
        }
        int current_key = get_key_for_char(to_lower(str[i]));
        int press_count = get_press_count(to_lower(str[i]));
        if (current_key == last_key && current_key != 0)
            write_char(' ');
        int j = 0;
        while (j < press_count) {
            write_char('0' + current_key);
            j++;
        }
        last_key = current_key;
        i++;
    }
    write_char('\n');
    return 0;
}