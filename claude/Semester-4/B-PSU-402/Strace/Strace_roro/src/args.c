/*
** EPITECH PROJECT, 2025
** Strace
** File description:
** Command line arguments parsing
*/

#include "strace.h"

void display_help(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
}

static int parse_pid(const char *str)
{
    int pid = 0;
    char *endptr = NULL;

    pid = strtol(str, &endptr, 10);
    if (*endptr != '\0' || pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", str);
        return -1;
    }
    return pid;
}

static int count_command_args(char **argv, int start)
{
    int count = 0;

    while (argv[start + count])
        count++;
    return count;
}

int parse_arguments(int argc, char **argv, strace_t *strace)
{
    int i = 1;
    int command_start = -1;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "--help") == 0)) {
        display_help();
        return -1;
    }
    
    strace->detailed_mode = 0;
    strace->attach_mode = 0;
    strace->target_pid = -1;
    strace->command = NULL;
    
    while (i < argc) {
        if (strcmp(argv[i], "-s") == 0) {
            strace->detailed_mode = 1;
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            strace->attach_mode = 1;
            strace->target_pid = parse_pid(argv[++i]);
            if (strace->target_pid == -1)
                return -1;
        } else {
            command_start = i;
            break;
        }
        i++;
    }
    
    if (!strace->attach_mode) {
        if (command_start == -1) {
            fprintf(stderr, "Error: No command specified\n");
            return -1;
        }
        int cmd_count = count_command_args(argv, command_start);
        strace->command = malloc(sizeof(char *) * (cmd_count + 1));
        if (!strace->command)
            return -1;
        for (int j = 0; j < cmd_count; j++)
            strace->command[j] = argv[command_start + j];
        strace->command[cmd_count] = NULL;
    }
    
    return 0;
}