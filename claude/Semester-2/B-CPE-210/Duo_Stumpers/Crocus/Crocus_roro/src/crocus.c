/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** crocus
*/

#include "crocus.h"

int crocus(int argc, char **argv)
{
    args_t args;

    if (parse_arguments(argc, argv, &args) != 0) {
        write(STDERR_FILENO, "Invalid arguments\n", 18);
        return 84;
    }
    display_numbers(args.number, args.string);
    return 0;
}