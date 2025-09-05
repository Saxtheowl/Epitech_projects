/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** parser
*/

#include "crocus.h"

int parse_arguments(int argc, char **argv, args_t *args)
{
    int i = 1;

    args->number = NULL;
    args->string = "0";
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc)
                return 84;
            args->number = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 >= argc)
                return 84;
            args->string = argv[i + 1];
            i += 2;
        } else {
            return 84;
        }
    }
    if (!args->number)
        return 84;
    if (!is_valid_number(args->number))
        return 84;
    return 0;
}