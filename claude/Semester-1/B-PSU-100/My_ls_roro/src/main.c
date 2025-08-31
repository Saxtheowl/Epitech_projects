/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Main function for my_ls command implementation
*/

#include "../include/my_ls.h"

int main(int argc, char **argv)
{
    options_t opts = {0, 0, 0, 0, 0, 0};
    int file_start = parse_options(argc, argv, &opts);

    if (file_start == -1)
        return 84;
    if (file_start == argc) {
        if (my_ls(&opts, NULL, 0) == -1)
            return 84;
    } else {
        if (my_ls(&opts, &argv[file_start], argc - file_start) == -1)
            return 84;
    }
    return 0;
}