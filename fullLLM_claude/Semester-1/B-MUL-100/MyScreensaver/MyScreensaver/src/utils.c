/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Utility functions for MyScreensaver project
*/

#include "my_screensaver.h"

void display_help(void)
{
    printf("animation rendering in a CSFML window.\n");
    printf("USAGE\n");
    printf("    ./my_screensaver [OPTIONS] animation_id\n");
    printf("    animation_id    ID of the animation to process (between 1 and %d).\n\n", MAX_ANIMATIONS);
    printf("OPTIONS\n");
    printf("    -d    print the description of all the animations and quit.\n");
    printf("    -h    print the usage and quit.\n\n");
    printf("USER INTERACTIONS\n");
    printf("    LEFT_ARROW     switch to the previous animation.\n");
    printf("    RIGHT_ARROW    switch to the next animation.\n");
}

void display_descriptions(void)
{
    for (int i = 1; i <= MAX_ANIMATIONS; i++) {
        printf("%d: %s\n", i, get_animation_description(i));
    }
}

int parse_arguments(int ac, char **av, int *animation_id, int *show_descriptions)
{
    if (ac == 1) {
        fprintf(stderr, "./my_screensaver: bad arguments: 0 given but 1 is required\n");
        fprintf(stderr, "retry with -h\n");
        return -1;
    }

    if (ac == 2 && av[1] != NULL) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            display_help();
            return 1;
        }
        if (av[1][0] == '-' && av[1][1] == 'd' && av[1][2] == '\0') {
            *show_descriptions = 1;
            return 0;
        }
        *animation_id = atoi(av[1]);
        return 0;
    }

    fprintf(stderr, "Error: Invalid arguments\n");
    return -1;
}

float get_random_float(float min, float max)
{
    float random = (float)rand() / (float)RAND_MAX;
    return min + random * (max - min);
}

sfColor hsv_to_rgb(float h, float s, float v)
{
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;
    float r, g, b;

    if (h >= 0 && h < 60) {
        r = c; g = x; b = 0;
    } else if (h >= 60 && h < 120) {
        r = x; g = c; b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0; g = c; b = x;
    } else if (h >= 180 && h < 240) {
        r = 0; g = x; b = c;
    } else if (h >= 240 && h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    return sfColor_fromRGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}