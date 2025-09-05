/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** parser
*/

#include "tree.h"

int parse_options(int argc, char **argv, options_t *opts, char **path)
{
    int i = 1;

    opts->show_all = 0;
    opts->dirs_only = 0;
    opts->max_depth = -1;
    opts->show_full_path = 0;
    *path = ".";
    while (i < argc) {
        if (strcmp(argv[i], "-a") == 0) {
            opts->show_all = 1;
        } else if (strcmp(argv[i], "-d") == 0) {
            opts->dirs_only = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            opts->show_full_path = 1;
        } else if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) {
                write(STDERR_FILENO, "tree: option requires an argument -- L\n", 40);
                return 1;
            }
            opts->max_depth = my_atoi(argv[i + 1]);
            if (opts->max_depth < 0) {
                write(STDERR_FILENO, "tree: Invalid level, must be greater than 0.\n", 46);
                return 1;
            }
            i++;
        } else if (argv[i][0] != '-') {
            *path = argv[i];
        } else {
            write(STDERR_FILENO, "tree: invalid option -- '", 26);
            write(STDERR_FILENO, &argv[i][1], 1);
            write(STDERR_FILENO, "'\n", 2);
            return 1;
        }
        i++;
    }
    return 0;
}