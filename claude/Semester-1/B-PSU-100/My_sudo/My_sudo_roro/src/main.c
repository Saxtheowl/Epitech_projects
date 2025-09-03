/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Main function for sudo implementation
*/

#include "my_sudo.h"

int main(int argc, char **argv)
{
    sudo_config_t config = {0};
    sudoers_entry_t *entries = NULL;
    struct passwd *pwd = NULL;
    
    if (parse_arguments(argc, argv, &config) != 0) {
        free_config(&config);
        return 84;
    }
    
    pwd = getpwuid(getuid());
    if (!pwd) {
        fprintf(stderr, "my_sudo: unable to determine user\n");
        free_config(&config);
        return 84;
    }
    
    if (read_sudoers(&entries) != 0) {
        free_config(&config);
        cleanup_sudoers(entries);
        return 84;
    }
    
    if (check_permissions(pwd->pw_name, entries) != 0) {
        fprintf(stderr, "%s is not in the my_sudoers file.\n", pwd->pw_name);
        free_config(&config);
        cleanup_sudoers(entries);
        return 84;
    }
    
    if (authenticate_user(pwd->pw_name) != 0) {
        free_config(&config);
        cleanup_sudoers(entries);
        return 84;
    }
    
    if (execute_command(&config) != 0) {
        free_config(&config);
        cleanup_sudoers(entries);
        return 84;
    }
    
    free_config(&config);
    cleanup_sudoers(entries);
    return 0;
}