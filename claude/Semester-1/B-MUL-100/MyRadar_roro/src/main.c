/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Main function for my_radar air traffic control simulation
*/

#include "../include/my_radar.h"

void print_usage(void)
{
    printf("Air traffic simulation panel\n");
    printf("USAGE\n");
    printf("    ./my_radar [OPTIONS] path_to_script\n");
    printf("        path_to_script    The path to the script file.\n");
    printf("OPTIONS\n");
    printf("    -h                    print the usage and quit.\n");
    printf("USER INTERACTIONS\n");
    printf("    'L' key               enable/disable hitboxes and areas.\n");
    printf("    'S' key               enable/disable sprites.\n");
}

static int parse_arguments(int argc, char **argv, char **script_path)
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 1;
    }
    if (argc != 2) {
        fprintf(stderr, "./my_radar: bad arguments: %d given but 84 is required\n", argc - 1);
        fprintf(stderr, "retry with -h\n");
        return 84;
    }
    *script_path = argv[1];
    return 0;
}

int main(int argc, char **argv)
{
    char *script_path = NULL;
    int arg_result;

    arg_result = parse_arguments(argc, argv, &script_path);
    if (arg_result != 0)
        return arg_result;
    return my_radar(script_path);
}