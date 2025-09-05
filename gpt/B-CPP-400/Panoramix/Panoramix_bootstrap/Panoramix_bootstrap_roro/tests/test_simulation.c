/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
** test_simulation.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "simulation.h"

Test(simulation, respects_single_capacity)
{
    int observed;

    cr_redirect_stdout();
    observed = run_simulation(5, 1, true);
    cr_assert_eq(observed, 1);
}

Test(simulation, respects_multi_capacity)
{
    int observed;

    cr_redirect_stdout();
    observed = run_simulation(6, 3, true);
    cr_assert_leq(observed, 3);
    cr_assert_geq(observed, 2);
}

