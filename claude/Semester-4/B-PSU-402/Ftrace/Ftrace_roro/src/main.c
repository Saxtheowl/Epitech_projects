/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Main function for ftrace project
*/

#include "ftrace.h"

void print_usage(void)
{
    printf("USAGE: ftrace <command>\n");
}

void print_error(const char *message)
{
    fprintf(stderr, "ftrace: %s\n", message);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        return EXIT_ERROR;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_usage();
        return EXIT_SUCCESS;
    }

    return ftrace_main(argv + 1);
}