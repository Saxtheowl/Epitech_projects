/*
** EPITECH PROJECT, 2025
** My_Top_roro
** File description:
** Minimal top-like summary (single snapshot)
*/

#include <stdio.h>
#include "top.h"

int main(void)
{
    meminfo_t mi;
    int procs;

    if (read_meminfo(&mi) != 0)
        return ERR_CODE;
    procs = count_processes();
    if (procs < 0)
        return ERR_CODE;
    printf("Tasks: %d total\n", procs);
    printf("Mem: %ldk total, %ldk free, %ldk avail\n",
        mi.mem_total_kb, mi.mem_free_kb, mi.mem_available_kb);
    return 0;
}
