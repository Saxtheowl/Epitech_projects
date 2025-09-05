/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** main cesar program
*/

#include "cesar.h"

int cesar_main(int argc, char **argv)
{
    char *target = NULL;
    int key = 0;
    int is_file = 0;

    if (parse_args(argc, argv, &target, &key, &is_file) != 0)
        return 84;
    if (is_file)
        return encrypt_file(target, key);
    else
        return encrypt_string(target, key);
}