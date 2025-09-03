/*
** EPITECH PROJECT, 2025
** Strace
** File description:
** Main strace function
*/

#include "strace.h"

int main(int argc, char **argv)
{
    strace_t strace = {0};

    if (parse_arguments(argc, argv, &strace) != 0)
        return 84;
    if (run_strace(&strace) != 0)
        return 84;
    return 0;
}