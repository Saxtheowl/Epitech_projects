/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** argument parser
*/

#include "cesar.h"

int parse_args(int argc, char **argv, char **target, int *key, int *is_file)
{
    if (argc != 4) {
        write(STDERR_FILENO, "Usage: ./cesar -f filename key OR ./cesar -s \"string\" key\n", 59);
        return 84;
    }
    if (my_strcmp(argv[1], "-f") == 0) {
        *is_file = 1;
        *target = argv[2];
        *key = my_atoi(argv[3]);
    } else if (my_strcmp(argv[1], "-s") == 0) {
        *is_file = 0;
        *target = argv[2];
        *key = my_atoi(argv[3]);
    } else {
        write(STDERR_FILENO, "cesar: invalid option\n", 22);
        write(STDERR_FILENO, "Usage: ./cesar -f filename key OR ./cesar -s \"string\" key\n", 59);
        return 84;
    }
    return 0;
}