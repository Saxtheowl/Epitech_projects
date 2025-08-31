/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** main
*/

#include <stdio.h>
#include <math.h>
#include "groundhog.h"

static void print_line(double g, int r, double s, int sw)
{
    if (isnan(g))
        printf("g=nan ");
    else
        printf("g=%.2f ", g);
    if (r == 2147483647)
        printf("r=nan%% ");
    else
        printf("r=%d%% ", r);
    if (isnan(s))
        printf("s=nan");
    else
        printf("s=%.2f", s);
    if (sw)
        printf(" a switch occurs");
    printf("\n");
}

int main(int ac, char const **av)
{
    int period;
    gh_t gh;
    double v;
    int stop;
    double g;
    double s;
    int r;
    int st;
    int have_prev;
    double mean;

    st = parse_args(ac, av, &period);
    if (st < 0)
        return 0;
    if (st == 84)
        return 84;
    gh_init(&gh, period);
    while (1) {
        if (read_line(&v, &stop) != 0)
            break;
        if (stop)
            break;
        gh_push(&gh, v);
        have_prev = (gh.count >= (size_t)gh.period + 1);
        gh_compute(have_prev, &gh, &g, &r, &s);
        if (gh.count >= (size_t)gh.period) {
            gh_window_mean_s(&gh, gh.count - gh.period,
                (size_t)gh.period, &mean, &s);
            gh_record_weird(&gh, v, mean, s);
        }
        print_line(g, r, s, gh_switch_check(&gh, r));
    }
    printf("Global tendency switched %d times\n", gh.switches);
    gh_print_top5(&gh);
    gh_free(&gh);
    return 0;
}
