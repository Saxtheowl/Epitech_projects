#include "mysh.h"

shell_t g_shell = {0};

int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[MAX_ARGS];
    int interactive = isatty(STDIN_FILENO);

    (void)argc;
    (void)argv;

    init_env(envp);

    while (1) {
        if (interactive) {
            write(STDOUT_FILENO, "$> ", 3);
        }

        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            break;
        }

        if (line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        if (strlen(line) == 0) {
            continue;
        }

        if (parse_command(line, args) > 0) {
            execute_command(args);
        }
    }

    if (line) {
        free(line);
    }
    free_env();
    return g_shell.exit_status;
}