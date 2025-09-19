/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Argument parsing for my_sudo
*/

#include "my_sudo.h"

void cleanup_args(sudo_args_t *args)
{
    if (args->target_user)
        free(args->target_user);
    if (args->target_group)
        free(args->target_group);
    if (args->command)
        free(args->command);
}

int parse_args(int argc, char **argv, sudo_args_t *args)
{
    int i = 1;

    // Initialize defaults
    args->target_user = strdup("root");
    args->target_group = NULL;
    args->shell_mode = 0;
    args->help_flag = 0;
    args->command = NULL;

    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-h") == 0) {
            args->help_flag = 1;
            return 0;
        } else if (strcmp(argv[i], "-u") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -u requires a username\n");
                return 84;
            }
            free(args->target_user);
            args->target_user = strdup(argv[++i]);
        } else if (strcmp(argv[i], "-g") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -g requires a group name\n");
                return 84;
            }
            args->target_group = strdup(argv[++i]);
        } else if (strcmp(argv[i], "-s") == 0) {
            args->shell_mode = 1;
        } else if (strncmp(argv[i], "-", 1) == 0) {
            // Parse combined flags like -ugEs
            for (int j = 1; argv[i][j]; j++) {
                if (argv[i][j] == 'u') {
                    if (i + 1 >= argc) {
                        fprintf(stderr, "Error: -u requires a username\n");
                        return 84;
                    }
                    free(args->target_user);
                    args->target_user = strdup(argv[++i]);
                    break;
                } else if (argv[i][j] == 'g') {
                    if (i + 1 >= argc) {
                        fprintf(stderr, "Error: -g requires a group name\n");
                        return 84;
                    }
                    args->target_group = strdup(argv[++i]);
                    break;
                } else if (argv[i][j] == 's') {
                    args->shell_mode = 1;
                } else if (argv[i][j] == 'E') {
                    // Environment preservation - not implemented in basic version
                } else {
                    fprintf(stderr, "Error: Unknown option -%c\n", argv[i][j]);
                    return 84;
                }
            }
        } else {
            break;
        }
        i++;
    }

    // Remaining arguments are the command
    if (i < argc && !args->shell_mode) {
        int cmd_count = argc - i;
        args->command = malloc(sizeof(char*) * (cmd_count + 1));
        for (int j = 0; j < cmd_count; j++) {
            args->command[j] = argv[i + j];
        }
        args->command[cmd_count] = NULL;
    }

    return 0;
}