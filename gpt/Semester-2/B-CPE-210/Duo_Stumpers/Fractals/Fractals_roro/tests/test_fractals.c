/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "fractals.h"

Test(fractals, level1)
{
    char out[1024];

    sierpinski(1, out, 1024);
    cr_assert_str_eq(out,
        "###\n# #\n###");
}

