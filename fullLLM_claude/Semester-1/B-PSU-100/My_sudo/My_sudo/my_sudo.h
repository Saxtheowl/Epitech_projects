/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Header file for my_sudo project
*/

#ifndef MY_SUDO_H_
#define MY_SUDO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <crypt.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    char *target_user;
    char *target_group;
    int shell_mode;
    int help_flag;
    char **command;
} sudo_args_t;

// Function prototypes
int parse_args(int argc, char **argv, sudo_args_t *args);
void print_usage(char *program_name);
int check_sudoers_permission(const char *username);
int authenticate_user(const char *username);
int execute_command(sudo_args_t *args);
void cleanup_args(sudo_args_t *args);
int set_user_group(const char *username, const char *groupname);

#endif /* !MY_SUDO_H_ */