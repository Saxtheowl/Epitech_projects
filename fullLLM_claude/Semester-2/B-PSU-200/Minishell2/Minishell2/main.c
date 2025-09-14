#include "mysh.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n$> ", 4);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    signal(SIGINT, handle_sigint);
    return main_shell_loop(env);
}

int main_shell_loop(char **env)
{
    char *line;
    pipeline_t *pipeline;
    int status = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            printf("$> ");
        line = get_line();
        if (!line)
            break;
        
        if (strlen(line) == 0) {
            free(line);
            continue;
        }

        pipeline = parse_line(line);
        if (pipeline) {
            status = execute_pipeline(pipeline, env);
            free_pipeline(pipeline);
        }
        free(line);
    }
    return status;
}

char *get_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1) {
        if (line)
            free(line);
        return NULL;
    }

    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    
    return line;
}