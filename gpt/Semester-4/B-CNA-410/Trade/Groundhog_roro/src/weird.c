/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** weirdness tracking
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "groundhog.h"

static void *xrealloc(void *p, size_t sz)
{
    void *n = realloc(p, sz);
    if (!n) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(84);
    }
    return n;
}

void gh_record_weird(gh_t *gh, double v, double mean, double s)
{
    double sc;

    if (isnan(s) || s <= 0.0)
        return;
    sc = fabs((v - mean) / s);
    if (gh->weird_n == gh->weird_cap) {
        gh->weird_cap = gh->weird_cap ? gh->weird_cap * 2 : 16;
        gh->weird_score = xrealloc(gh->weird_score,
            gh->weird_cap * sizeof(double));
        gh->weird_value = xrealloc(gh->weird_value,
            gh->weird_cap * sizeof(double));
    }
    gh->weird_score[gh->weird_n] = sc;
    gh->weird_value[gh->weird_n] = v;
    gh->weird_n += 1;
}

static void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

void gh_print_top5(const gh_t *gh)
{
    size_t i;
    size_t j;
    double *score;
    double *value;
    size_t n;
    size_t k;

    n = gh->weird_n;
    if (n == 0) {
        printf("5 weirdest values are []\n");
        return;
    }
    score = malloc(n * sizeof(double));
    value = malloc(n * sizeof(double));
    for (i = 0; i < n; ++i) {
        score[i] = gh->weird_score[i];
        value[i] = gh->weird_value[i];
    }
    /* partial selection sort for top 5 */
    k = n < 5 ? n : 5;
    for (i = 0; i < k; ++i) {
        size_t max = i;
        for (j = i + 1; j < n; ++j)
            if (score[j] > score[max])
                max = j;
        swap(&score[i], &score[max]);
        swap(&value[i], &value[max]);
    }
    printf("5 weirdest values are [");
    for (i = 0; i < k; ++i) {
        printf("%.1f%s", value[i], (i + 1 < k) ? ", " : "]\n");
    }
    free(score);
    free(value);
}

