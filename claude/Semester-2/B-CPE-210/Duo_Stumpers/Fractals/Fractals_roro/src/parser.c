/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** parser
*/

#include "fractals.h"

pattern_t parse_pattern(char *pattern_str)
{
    pattern_t pattern;
    int i = 0;
    int lines = 1;
    int line_width = 0;
    int current_width = 0;

    pattern.width = 0;
    pattern.height = 0;
    pattern.data = NULL;
    if (!pattern_str)
        return pattern;
    for (i = 0; pattern_str[i]; i++) {
        if (pattern_str[i] == '@') {
            if (current_width > line_width)
                line_width = current_width;
            current_width = 0;
            lines++;
        } else {
            current_width++;
        }
    }
    if (current_width > line_width)
        line_width = current_width;
    pattern.width = line_width;
    pattern.height = lines;
    pattern.data = malloc((line_width * lines + 1) * sizeof(char));
    if (!pattern.data)
        return pattern;
    int pos = 0;
    for (i = 0; pattern_str[i]; i++) {
        if (pattern_str[i] == '@') {
            while (pos % line_width != 0) {
                pattern.data[pos] = ' ';
                pos++;
            }
        } else {
            pattern.data[pos] = pattern_str[i];
            pos++;
        }
    }
    while (pos < line_width * lines) {
        pattern.data[pos] = ' ';
        pos++;
    }
    pattern.data[pos] = '\0';
    return pattern;
}

int parse_arguments(int argc, char **argv, int *iterations, 
    pattern_t *sharp_pattern, pattern_t *dot_pattern)
{
    if (argc != 4)
        return 84;
    *iterations = my_atoi(argv[1]);
    if (*iterations < 0)
        return 84;
    *sharp_pattern = parse_pattern(argv[2]);
    *dot_pattern = parse_pattern(argv[3]);
    if (!sharp_pattern->data || !dot_pattern->data)
        return 84;
    if (sharp_pattern->width != dot_pattern->width || 
        sharp_pattern->height != dot_pattern->height)
        return 84;
    return 0;
}