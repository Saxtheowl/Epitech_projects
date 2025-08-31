/*
** EPITECH PROJECT, 2025
** Need4Stek
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "n4s.h"

Test(lidar, parse_basic)
{
    double vals[10];
    int n = parse_lidar("LIDAR:100:200:300;", vals, 10);
    cr_assert_eq(n, 3);
    cr_assert_float_eq(vals[0], 100.0, 0.001);
    cr_assert_float_eq(vals[2], 300.0, 0.001);
}

Test(control, steer_logic)
{
    double v[8] = {1000,1000,1000,1000,1000,1000,2000,2000};
    double speed; double steer;
    compute_controls(v, 8, &speed, &steer);
    cr_assert(speed > 0);
    cr_assert(steer < 0); /* steer left because left > right */
}

