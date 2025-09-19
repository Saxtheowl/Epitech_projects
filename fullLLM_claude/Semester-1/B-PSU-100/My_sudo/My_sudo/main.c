/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Main file for my_sudo project
*/

#include "my_sudo.h"

void print_usage(char *program_name)
{
    printf("usage: %s -h\n", program_name);
    printf("usage: %s [-ugEs] [command [args ...]]\n", program_name);
}

int main(int argc, char **argv)
{
    sudo_args_t args = {0};
    char *current_user;
    struct passwd *pw;

    if (parse_args(argc, argv, &args) != 0)
        return 84;

    if (args.help_flag) {
        print_usage(argv[0]);
        return 0;
    }

    // Get current user
    pw = getpwuid(getuid());
    if (!pw) {
        fprintf(stderr, "Error: Unable to get current user\n");
        return 84;
    }
    current_user = pw->pw_name;

    // Authenticate user first
    if (!authenticate_user(current_user)) {
        return 84;
    }

    // Check sudoers permissions after authentication
    if (!check_sudoers_permission(current_user)) {
        printf("%s is not in the my_sudoers file.\n", current_user);
        return 84;
    }

    // Execute command
    if (execute_command(&args) != 0) {
        cleanup_args(&args);
        return 84;
    }

    cleanup_args(&args);
    return 0;
}