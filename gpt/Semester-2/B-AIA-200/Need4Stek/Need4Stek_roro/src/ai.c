/*
** EPITECH PROJECT, 2025
** Need4Stek
** File description:
** Core AI loop: parse LIDAR lines, output commands
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "n4s.h"

static void trim_newline(char *s)
{
    size_t n;

    if (!s)
        return;
    n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

int parse_lidar(const char *line, double *out, int max)
{
    const char *p;
    int c;
    char *end;

    if (strncmp(line, "LIDAR:", 6) != 0)
        return 0;
    p = line + 6;
    c = 0;
    while (*p != '\0' && c < max) {
        while (*p == ':' || *p == ';' || isspace((unsigned char)*p))
            p = p + 1;
        if (*p == '\0')
            break;
        out[c] = strtod(p, &end);
        if (end == p)
            break;
        c = c + 1;
        p = end;
        while (*p == ':' || *p == ';' || isspace((unsigned char)*p))
            p = p + 1;
    }
    return c;
}

void compute_controls(const double *lidar, int n, double *speed, double *steer)
{
    double left;
    double right;
    double center;

    if (n <= 0) {
        *speed = 0.0;
        *steer = 0.0;
        return;
    }
    center = lidar[n / 2];
    left = lidar[n * 3 / 4];
    right = lidar[n / 4];
    if (center < 500.0)
        *speed = 0.1;
    else if (center < 1500.0)
        *speed = 0.3;
    else
        *speed = 0.6;
    *steer = 0.0;
    if (left - right > 100.0)
        *steer = -0.2;
    else if (right - left > 100.0)
        *steer = 0.2;
}

int ai_loop(void)
{
    char *line;
    size_t cap;
    double lidar[64];
    int n;
    double speed;
    double steer;

    line = NULL;
    cap = 0;
    while (getline(&line, &cap, stdin) != -1) {
        trim_newline(line);
        if (strcmp(line, "STOP") == 0)
            break;
        n = parse_lidar(line, lidar, 64);
        if (n > 0) {
            compute_controls(lidar, n, &speed, &steer);
            printf("CAR_FORWARD:%.3f\n", speed);
            printf("WHEELS_DIR:%.3f\n", steer);
            fflush(stdout);
        }
    }
    free(line);
    return 0;
}

