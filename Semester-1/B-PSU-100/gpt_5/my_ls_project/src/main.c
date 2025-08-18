/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <unistd.h>
#include <stdlib.h>

static void print_error(const char *msg)
{
    my_write_str(2, msg);
    my_write_char(2, '\n');
}

int main(int argc, char **argv)
{
    options_t opts;
    int first_path = 1;
    int ret;

    if (parse_options(argc, argv, &opts, &first_path) < 0) {
        print_error("my_ls: invalid option");
        exit(84);
    }
    ret = my_ls_paths(argc, argv, first_path, &opts);
    if (ret < 0) {
        print_error("my_ls: error");
        exit(84);
    }
    return 0;
}
