/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Argument parsing for my_top
*/

#include "../include/my_top.h"

void print_usage(void)
{
    printf("USAGE: my_top [-U username] [-d delay] [-n frames]\n");
    printf("    -U username    Filter processes by username\n");
    printf("    -d delay       Set refresh delay in seconds\n");
    printf("    -n frames      Number of frames before exit\n");
}

static int parse_delay(const char *str, double *delay)
{
    char *endptr;
    double value;

    value = strtod(str, &endptr);
    if (*endptr != '\0' || value <= 0) {
        fprintf(stderr, "my_top: invalid delay '%s'\n", str);
        return 84;
    }
    *delay = value;
    return 0;
}

static int parse_frames(const char *str, int *frames)
{
    char *endptr;
    long value;

    value = strtol(str, &endptr, 10);
    if (*endptr != '\0' || value <= 0) {
        fprintf(stderr, "my_top: invalid frame count '%s'\n", str);
        return 84;
    }
    *frames = (int)value;
    return 0;
}

int parse_arguments(int argc, char **argv, top_state_t *state)
{
    int i = 1;

    while (i < argc) {
        if (strcmp(argv[i], "-U") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "my_top: option requires an argument -- 'U'\n");
                return 84;
            }
            state->filter_user = strdup(argv[++i]);
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "my_top: option requires an argument -- 'd'\n");
                return 84;
            }
            if (parse_delay(argv[++i], &state->delay) == 84)
                return 84;
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "my_top: option requires an argument -- 'n'\n");
                return 84;
            }
            if (parse_frames(argv[++i], &state->max_frames) == 84)
                return 84;
        } else {
            fprintf(stderr, "my_top: invalid option -- '%s'\n", argv[i]);
            print_usage();
            return 84;
        }
        i++;
    }
    return 0;
}