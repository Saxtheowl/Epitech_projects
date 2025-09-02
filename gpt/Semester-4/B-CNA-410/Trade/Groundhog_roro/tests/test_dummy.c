/*
** EPITECH PROJECT, 2025
** Groundhog tests
** File description:
**   Functional tests for core computations
*/

#include <criterion/criterion.h>
#include <math.h>
#include "groundhog.h"

Test(args, help_flag)
{
    int period = 0;
    const char *av[] = {"./groundhog", "-h", NULL};
    int st = parse_args(2, av, &period);
    cr_assert_eq(st, -1);
}

Test(args, valid_and_invalid)
{
    int p = 0;
    const char *ok[] = {"./groundhog", "3", NULL};
    const char *bad1[] = {"./groundhog", "abc", NULL};
    const char *bad2[] = {"./groundhog", "0", NULL};
    cr_assert_eq(parse_args(2, ok, &p), 0);
    cr_assert_eq(p, 3);
    cr_assert_eq(parse_args(2, bad1, &p), 84);
    cr_assert_eq(parse_args(2, bad2, &p), 84);
}

Test(stats, mean_and_s)
{
    gh_t gh;
    double mean, s;
    gh_init(&gh, 3);
    gh_push(&gh, 1.0);
    gh_push(&gh, 2.0);
    gh_push(&gh, 3.0);
    gh_window_mean_s(&gh, 0, 3, &mean, &s);
    cr_assert_float_eq(mean, 2.0, 1e-6);
    cr_assert(fabs(s - 0.81649658) < 1e-6);
    gh_free(&gh);
}

Test(stats, compute_insufficient)
{
    gh_t gh;
    double g, s;
    int r;
    gh_init(&gh, 3);
    gh_push(&gh, 1.0);
    gh_push(&gh, 2.0);
    gh_compute(0, &gh, &g, &r, &s);
    cr_assert(isnan(g));
    cr_assert(isnan(s));
    cr_assert_eq(r, 2147483647);
    gh_free(&gh);
}

Test(stats, compute_with_prev)
{
    gh_t gh;
    double g, s;
    int r;
    gh_init(&gh, 3);
    gh_push(&gh, 1.0);
    gh_push(&gh, 2.0);
    gh_push(&gh, 4.0);
    gh_push(&gh, 8.0);
    gh_compute(1, &gh, &g, &r, &s);
    cr_assert_eq(r, 700);
    cr_assert(fabs(g - (7.0 / 3.0)) < 1e-6);
    gh_free(&gh);
}

Test(stats, switch_check)
{
    gh_t gh;
    gh_init(&gh, 3);
    /* first sign sets reference, no switch */
    cr_assert_eq(gh_switch_check(&gh, 5), 0);
    /* positive to negative -> switch */
    cr_assert_eq(gh_switch_check(&gh, -2), 1);
    /* negative to zero -> switch */
    cr_assert_eq(gh_switch_check(&gh, 0), 1);
    /* zero to zero -> no switch */
    cr_assert_eq(gh_switch_check(&gh, 0), 0);
    gh_free(&gh);
}

Test(weird, record_basic)
{
    gh_t gh;
    gh_init(&gh, 2);
    cr_assert_eq(gh.weird_n, (size_t)0);
    gh_record_weird(&gh, 3.0, 0.0, 0.0);
    cr_assert_eq(gh.weird_n, (size_t)0);
    gh_record_weird(&gh, 3.0, 0.0, 1.0);
    cr_assert_eq(gh.weird_n, (size_t)1);
    gh_free(&gh);
}
