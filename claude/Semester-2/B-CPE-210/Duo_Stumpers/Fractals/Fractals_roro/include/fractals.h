/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** fractals
*/

#ifndef FRACTALS_H_
    #define FRACTALS_H_

    #include <stdlib.h>
    #include <unistd.h>

    typedef struct pattern_s {
        char *data;
        int width;
        int height;
    } pattern_t;

    int fractals(int argc, char **argv);
    int parse_arguments(int argc, char **argv, int *iterations, 
        pattern_t *sharp_pattern, pattern_t *dot_pattern);
    pattern_t parse_pattern(char *pattern_str);
    void generate_fractal(int iterations, pattern_t sharp_pattern, 
        pattern_t dot_pattern);
    char *apply_transformation(char *current, pattern_t sharp_pattern, 
        pattern_t dot_pattern, int *new_width, int *new_height);
    void print_pattern(char *pattern, int width, int height);
    void free_pattern(pattern_t *pattern);
    int my_strlen(char *str);
    int my_atoi(char *str);

#endif /* !FRACTALS_H_ */