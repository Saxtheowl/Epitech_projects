/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** fractal
*/

#include "fractals.h"

void print_pattern(char *pattern, int width, int height)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            write(STDOUT_FILENO, &pattern[i * width + j], 1);
        }
        write(STDOUT_FILENO, "\n", 1);
    }
}

char *apply_transformation(char *current, pattern_t sharp_pattern, 
    pattern_t dot_pattern, int *new_width, int *new_height)
{
    int current_width = 0;
    int current_height = 0;
    char *result = NULL;
    int result_size = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int pos = 0;
    int line_start = 0;
    int line_len = 0;

    if (current[0] == '#' && current[1] == '\0') {
        current_width = 1;
        current_height = 1;
    } else {
        current_height = 1;
        for (i = 0; current[i]; i++) {
            if (current[i] == '\n') {
                if (current_height == 1)
                    current_width = i;
                current_height++;
            }
        }
        if (current_width == 0)
            current_width = my_strlen(current);
    }
    *new_width = current_width * sharp_pattern.width;
    *new_height = current_height * sharp_pattern.height;
    result_size = (*new_width) * (*new_height) + (*new_height) + 1;
    result = malloc(result_size * sizeof(char));
    if (!result)
        return NULL;
    pos = 0;
    for (i = 0; i < current_height; i++) {
        if (i == 0) {
            line_start = 0;
        } else {
            line_start = 0;
            for (j = 0, k = 0; j < i && current[k]; k++) {
                if (current[k] == '\n')
                    j++;
                if (j == i)
                    line_start = k + 1;
            }
        }
        for (line_len = 0; line_start + line_len < my_strlen(current) && 
            current[line_start + line_len] != '\n'; line_len++);
        for (j = 0; j < sharp_pattern.height; j++) {
            for (k = 0; k < current_width; k++) {
                char current_char = '#';
                if (k < line_len)
                    current_char = current[line_start + k];
                pattern_t *pattern_to_use = (current_char == '#') ? 
                    &sharp_pattern : &dot_pattern;
                for (int l = 0; l < pattern_to_use->width; l++) {
                    result[pos] = pattern_to_use->data[j * 
                        pattern_to_use->width + l];
                    pos++;
                }
            }
            result[pos] = '\n';
            pos++;
        }
    }
    result[pos - 1] = '\0';
    return result;
}

void generate_fractal(int iterations, pattern_t sharp_pattern, 
    pattern_t dot_pattern)
{
    char *current = malloc(2 * sizeof(char));
    char *new_pattern = NULL;
    int new_width = 0;
    int new_height = 0;
    int i = 0;

    if (!current)
        return;
    current[0] = '#';
    current[1] = '\0';
    if (iterations == 0) {
        write(STDOUT_FILENO, "#\n", 2);
        free(current);
        return;
    }
    for (i = 0; i < iterations; i++) {
        new_pattern = apply_transformation(current, sharp_pattern, 
            dot_pattern, &new_width, &new_height);
        if (!new_pattern) {
            free(current);
            return;
        }
        free(current);
        current = new_pattern;
    }
    write(STDOUT_FILENO, current, my_strlen(current));
    free(current);
}