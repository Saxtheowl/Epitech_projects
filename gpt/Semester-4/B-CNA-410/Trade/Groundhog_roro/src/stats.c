/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** stats
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

void gh_init(gh_t *gh, int period)
{
    gh->period = period;
    gh->vals = NULL;
    gh->count = 0;
    gh->cap = 0;
    gh->switches = 0;
    gh->prev_r_sign = 2;
    gh->weird_score = NULL;
    gh->weird_value = NULL;
    gh->weird_n = 0;
    gh->weird_cap = 0;
}

void gh_free(gh_t *gh)
{
    free(gh->vals);
    free(gh->weird_score);
    free(gh->weird_value);
}

int gh_push(gh_t *gh, double v)
{
    if (gh->count == gh->cap) {
        gh->cap = gh->cap ? gh->cap * 2 : 16;
        gh->vals = xrealloc(gh->vals, gh->cap * sizeof(double));
    }
    gh->vals[gh->count++] = v;
    return 0;
}

static void compute_mean_s(const double *a, size_t n, double *mean, double *s)
{
    size_t i;
    double sum;
    double sum2;

    sum = 0.0;
    sum2 = 0.0;
    for (i = 0; i < n; ++i) {
        sum += a[i];
        sum2 += a[i] * a[i];
    }
    *mean = sum / (double)n;
    *s = sqrt((sum2 / (double)n) - (*mean) * (*mean));
}

void gh_window_mean_s(const gh_t *gh, size_t offset, size_t n, double *mean,
    double *s)
{
    compute_mean_s(&gh->vals[offset], n, mean, s);
}

static double compute_g(const double *a, size_t n)
{
    size_t i;
    double acc;

    acc = 0.0;
    for (i = 1; i < n; ++i) {
        double d = a[i] - a[i - 1];
        if (d > 0.0)
            acc += d;
    }
    /* n values produce (n-1) diffs; divide by period (= n-1) */
    if (n <= 1)
        return 0.0;
    return acc / (double)(n - 1);
}

void gh_compute(int have_prev, const gh_t *gh, double *g, int *r, double *s)
{
    double mean;
    size_t n;

    n = (size_t)gh->period;
    if (gh->count < n) {
        *g = NAN;
        *r = 2147483647;
        *s = NAN;
        return;
    }
    compute_mean_s(&gh->vals[gh->count - n], n, &mean, s);
    if (!have_prev) {
        *g = NAN;
        *r = 2147483647;
    } else {
        double v_old = gh->vals[gh->count - n - 1];
        double v_new = gh->vals[gh->count - 1];
        double rr = (v_new - v_old) / v_old * 100.0;
        *r = (int)llround(rr);
        *g = compute_g(&gh->vals[gh->count - n - 1], n + 1);
    }
}

int gh_switch_check(gh_t *gh, int r)
{
    int sign;
    int sw;

    if (r == 2147483647)
        return 0;
    sign = (r > 0) ? 1 : (r < 0 ? -1 : 0);
    sw = 0;
    if (gh->prev_r_sign != 2 && sign != gh->prev_r_sign && (sign == 0 || gh->prev_r_sign == 0 || (sign * gh->prev_r_sign) < 0))
        sw = 1;
    if (gh->prev_r_sign != 2 && ((gh->prev_r_sign > 0 && sign <= 0) || (gh->prev_r_sign < 0 && sign >= 0)))
        sw = 1;
    gh->prev_r_sign = sign;
    if (sw)
        gh->switches += 1;
    return sw;
}
