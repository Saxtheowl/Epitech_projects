/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Command line arguments parsing
*/

#include "my_sudo.h"

void display_help(void)
{
    printf("usage: ./my_sudo -h\n");
    printf("usage: ./my_sudo [-ugEs] [command [args ...]]\n");
}

static int set_run_as_user(sudo_config_t *config, const char *username)
{
    struct passwd *pwd = getpwnam(username);
    
    if (!pwd) {
        fprintf(stderr, "my_sudo: unknown user: %s\n", username);
        return -1;
    }
    
    config->username = strdup(username);
    config->run_as_uid = pwd->pw_uid;
    config->run_as_gid = pwd->pw_gid;
    return 0;
}

static int set_run_as_group(sudo_config_t *config, const char *groupname)
{
    struct group *grp = getgrnam(groupname);
    
    if (!grp) {
        fprintf(stderr, "my_sudo: unknown group: %s\n", groupname);
        return -1;
    }
    
    config->group = strdup(groupname);
    config->run_as_gid = grp->gr_gid;
    return 0;
}

static int copy_command(sudo_config_t *config, char **argv, int start)
{
    int i = 0;
    int count = 0;
    
    while (argv[start + count])
        count++;
    
    if (count == 0)
        return -1;
    
    config->command = malloc(sizeof(char *) * (count + 1));
    if (!config->command)
        return -1;
    
    for (i = 0; i < count; i++)
        config->command[i] = strdup(argv[start + i]);
    config->command[count] = NULL;
    
    return 0;
}

int parse_arguments(int argc, char **argv, sudo_config_t *config)
{
    int i = 1;
    
    config->run_as_uid = 0;
    config->run_as_gid = 0;
    config->shell_mode = 0;
    config->env_mode = 0;
    
    if (argc < 2) {
        fprintf(stderr, "my_sudo: a command is required\n");
        return -1;
    }
    
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        display_help();
        return -1;
    }
    
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-u") == 0 && i + 1 < argc) {
            if (set_run_as_user(config, argv[++i]) != 0)
                return -1;
        } else if (strcmp(argv[i], "-g") == 0 && i + 1 < argc) {
            if (set_run_as_group(config, argv[++i]) != 0)
                return -1;
        } else if (strcmp(argv[i], "-s") == 0) {
            config->shell_mode = 1;
        } else if (strcmp(argv[i], "-E") == 0) {
            config->env_mode = 1;
        } else {
            fprintf(stderr, "my_sudo: invalid option -- '%s'\n", argv[i]);
            return -1;
        }
        i++;
    }
    
    if (!config->shell_mode && i >= argc) {
        fprintf(stderr, "my_sudo: a command is required\n");
        return -1;
    }
    
    if (!config->shell_mode && copy_command(config, argv, i) != 0)
        return -1;
    
    return 0;
}