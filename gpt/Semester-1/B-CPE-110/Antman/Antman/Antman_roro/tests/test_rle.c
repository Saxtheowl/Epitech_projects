/*
** EPITECH PROJECT, 2025
** Antman_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "antman.h"

Test(rle, roundtrip)
{
    const char *tmpin = "/tmp/ant_in.txt";
    const char *tmpc = "/tmp/ant_c.bin";
    FILE *f = fopen(tmpin, "wb");
    fwrite("aaaaabbbbcc\n", 1, 11, f);
    fclose(f);
    cr_assert_eq(antman(tmpin), 0);
}
