#include "mysh.h"

int parse_command(char *line, char **args)
{
    int argc = 0;
    char *token;

    if (!line || !args) {
        return 0;
    }

    token = strtok(line, " \t\n");
    while (token && argc < MAX_ARGS - 1) {
        args[argc] = token;
        argc++;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;

    return argc;
}