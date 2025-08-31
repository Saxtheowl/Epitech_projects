/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** header
*/

#ifndef GROUNDHOG_H
    #define GROUNDHOG_H

    #include <stddef.h>
    #include <stdbool.h>

    typedef struct gh_s {
        int period;
        double *vals;
        size_t count;
        size_t cap;
        int switches;
        int prev_r_sign; /* -1, 0, 1, 2 = undefined */
        /* weirdness tracking */
        double *weird_score;
        double *weird_value;
        size_t weird_n;
        size_t weird_cap;
    } gh_t;

    /* args */
    int parse_args(int ac, char const **av, int *period);
    void print_help(void);

    /* stats */
    void gh_init(gh_t *gh, int period);
    void gh_free(gh_t *gh);
    int gh_push(gh_t *gh, double v);
    void gh_compute(int have_prev, const gh_t *gh, double *g, int *r,
        double *s);
    int gh_switch_check(gh_t *gh, int r);
    void gh_window_mean_s(const gh_t *gh, size_t offset, size_t n,
        double *mean, double *s);

    /* weird */
    void gh_record_weird(gh_t *gh, double v, double mean, double s);
    void gh_print_top5(const gh_t *gh);

    /* io */
    int read_line(double *out_v, int *is_stop);

#endif /* GROUNDHOG_H */
