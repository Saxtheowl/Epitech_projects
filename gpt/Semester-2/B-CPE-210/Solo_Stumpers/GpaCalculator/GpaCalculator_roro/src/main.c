/*
** EPITECH PROJECT, 2025
** GpaCalculator
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "gpa.h"

static double grade_value(const char *g)
{
    double base;
    int len;

    len = (int)strlen(g);
    if (len < 1)
        return -1.0;
    switch (toupper((unsigned char)g[0])) {
        case 'A': base = 4.0; break;
        case 'B': base = 3.0; break;
        case 'C': base = 2.0; break;
        case 'D': base = 1.0; break;
        case 'F': base = 0.0; break;
        default: return -1.0;
    }
    if (len >= 2) {
        if (g[1] == '+')
            base = base + 0.3;
        else if (g[1] == '-')
            base = base - 0.3;
    }
    if (base > 4.0)
        base = 4.0;
    if (base < 0.0)
        base = 0.0;
    return base;
}

int parse_grades(const char *in, double *avg)
{
    char token[8];
    int i;
    int t;
    int count;
    double sum;

    i = 0;
    t = 0;
    count = 0;
    sum = 0.0;
    while (in[i] != '\0') {
        if (in[i] == ',' || isspace((unsigned char)in[i])) {
            if (t > 0) {
                double v;

                token[t] = '\0';
                v = grade_value(token);
                if (v < 0.0)
                    return 0;
                sum = sum + v;
                count = count + 1;
                t = 0;
            }
        } else if (t < 7) {
            token[t] = in[i];
            t = t + 1;
        } else {
            return 0;
        }
        i = i + 1;
    }
    if (t > 0) {
        double v;

        token[t] = '\0';
        v = grade_value(token);
        if (v < 0.0)
            return 0;
        sum = sum + v;
        count = count + 1;
    }
    if (count == 0)
        return 0;
    *avg = sum / (double)count;
    return 1;
}

int main(int argc, char **argv)
{
    double avg;

    if (argc != 2 || !parse_grades(argv[1], &avg))
        return 84;
    printf("%.2f\n", avg);
    return 0;
}

