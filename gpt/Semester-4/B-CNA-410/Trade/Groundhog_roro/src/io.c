/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** io
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_line(double *out_v, int *is_stop)
{
    char *line;
    size_t cap;
    char *end;
    double v;

    line = NULL;
    cap = 0;
    if (getline(&line, &cap, stdin) == -1) {
        free(line);
        return 1;
    }
    if (strncmp(line, "STOP", 4) == 0) {
        *is_stop = 1;
        free(line);
        return 0;
    }
    *is_stop = 0;
    v = strtod(line, &end);
    free(line);
    *out_v = v;
    return 0;
}

