/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** sudo implementation header
*/

#ifndef MY_SUDO_H_
    #define MY_SUDO_H_

    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <pwd.h>
    #include <grp.h>
    #include <shadow.h>
    #include <crypt.h>
    #include <sys/wait.h>
    #include <termios.h>
    #include <errno.h>

    #define MAX_ATTEMPTS 3
    #define MAX_LINE_LEN 1024
    #define MAX_USERS 100

    typedef struct sudo_config_s {
        char *username;
        char *group;
        int shell_mode;
        int env_mode;
        char **command;
        uid_t run_as_uid;
        gid_t run_as_gid;
    } sudo_config_t;

    typedef struct sudoers_entry_s {
        char *user_or_group;
        int is_group;
        int is_uid;
        int is_gid;
        uid_t uid;
        gid_t gid;
        struct sudoers_entry_s *next;
    } sudoers_entry_t;

    int parse_arguments(int argc, char **argv, sudo_config_t *config);
    void display_help(void);
    int read_sudoers(sudoers_entry_t **entries);
    int check_permissions(const char *username, sudoers_entry_t *entries);
    int authenticate_user(const char *username);
    int execute_command(sudo_config_t *config);
    char *read_password(void);
    void cleanup_sudoers(sudoers_entry_t *entries);
    int is_user_in_group(const char *username, const char *groupname);
    int get_user_shell(const char *username, char **shell);
    void free_config(sudo_config_t *config);

#endif /* !MY_SUDO_H_ */