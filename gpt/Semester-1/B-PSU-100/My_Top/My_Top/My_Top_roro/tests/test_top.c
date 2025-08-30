/*
** EPITECH PROJECT, 2025
** My_Top_roro
** File description:
** Simple tests for parsers
*/

#include <criterion/criterion.h>
#include "top.h"

Test(proc, meminfo)
{
    meminfo_t mi;
    cr_assert_eq(read_meminfo(&mi), 0);
    cr_assert(mi.mem_total_kb > 0);
}
