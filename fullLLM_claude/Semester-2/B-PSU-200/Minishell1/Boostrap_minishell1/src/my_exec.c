/*
** EPITECH PROJECT, 2024
** Minishell1 Bootstrap - my_exec
** File description:
** Simple bootstrap for process execution and argument parsing
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

int my_putchar(char c)
{
    return (write(1, &c, 1));
}

int my_putstr(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (-1);
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (i);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar((nb % 10) + '0');
}

/* Step 1: Display environment variables */
int step1_print_env(char **env)
{
    int i = 0;

    if (env == NULL)
        return (84);
    
    while (env[i] != NULL) {
        my_putstr(env[i]);
        my_putchar('\n');
        i++;
    }
    return (0);
}

/* Step 2: Simple execution of /bin/ls */
int step2_simple_exec(void)
{
    char *args[] = {"/bin/ls", NULL};
    
    if (execve("/bin/ls", args, NULL) == -1) {
        my_putstr("Error: execve failed\n");
        return (84);
    }
    return (0);
}

/* Step 3: Parse command line arguments */
char **step3_parse_args(char *input)
{
    char **args;
    int count = 0;
    int i = 0;
    int start = 0;
    int arg_index = 0;

    if (input == NULL)
        return (NULL);

    /* Count arguments */
    while (input[i] != '\0') {
        if (input[i] == ' ' && input[i + 1] != ' ' && input[i + 1] != '\0')
            count++;
        i++;
    }
    count++; /* For the last argument */

    args = malloc(sizeof(char *) * (count + 1));
    if (args == NULL)
        return (NULL);

    i = 0;
    start = 0;
    while (input[i] != '\0') {
        if (input[i] == ' ') {
            args[arg_index] = malloc(sizeof(char) * (i - start + 1));
            if (args[arg_index] == NULL)
                return (NULL);
            strncpy(args[arg_index], &input[start], i - start);
            args[arg_index][i - start] = '\0';
            arg_index++;
            
            /* Skip multiple spaces */
            while (input[i] == ' ')
                i++;
            start = i;
            continue;
        }
        i++;
    }
    
    /* Handle last argument */
    if (start < i) {
        args[arg_index] = malloc(sizeof(char) * (i - start + 1));
        if (args[arg_index] == NULL)
            return (NULL);
        strncpy(args[arg_index], &input[start], i - start);
        args[arg_index][i - start] = '\0';
        arg_index++;
    }
    
    args[arg_index] = NULL;
    return (args);
}

/* Step 4: Full execution with process management */
int step4_full_exec(char **args, char **env)
{
    pid_t pid;
    pid_t parent_pid;
    int status;

    if (args == NULL || args[0] == NULL)
        return (84);

    parent_pid = getpid();
    my_putstr("Program name: ");
    my_putstr(args[0]);
    my_putchar('\n');

    /* Count and display arguments */
    int arg_count = 0;
    while (args[arg_count] != NULL)
        arg_count++;
    
    my_putstr("Number of arguments: ");
    my_putnbr(arg_count);
    my_putchar('\n');

    my_putstr("Parent PID: ");
    my_putnbr(parent_pid);
    my_putchar('\n');

    pid = fork();
    if (pid == -1) {
        my_putstr("Error: fork failed\n");
        return (84);
    }
    
    if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, env) == -1) {
            my_putstr("Error: execve failed\n");
            exit(84);
        }
    } else {
        /* Parent process */
        my_putstr("Child PID: ");
        my_putnbr(pid);
        my_putchar('\n');
        
        wait(&status);
        
        if (WIFEXITED(status)) {
            my_putstr("Program terminated: OK\n");
        } else if (WIFSIGNALED(status)) {
            if (WTERMSIG(status) == SIGSEGV) {
                my_putstr("Program terminated: Segmentation fault\n");
            } else {
                my_putstr("Program terminated: Signal ");
                my_putnbr(WTERMSIG(status));
                my_putchar('\n');
            }
        }
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    char **args;

    /* Step 1: If no arguments, display environment */
    if (argc == 1) {
        return (step1_print_env(env));
    }

    /* Step 2: If argument is "simple", execute /bin/ls */
    if (argc == 2 && strcmp(argv[1], "simple") == 0) {
        return (step2_simple_exec());
    }

    /* Steps 3 & 4: Parse arguments and execute */
    if (argc == 2) {
        args = step3_parse_args(argv[1]);
        if (args == NULL) {
            my_putstr("Error: parsing failed\n");
            return (84);
        }
        
        return (step4_full_exec(args, env));
    }

    my_putstr("Usage: ./my_exec [simple] [\"command args...\"]\n");
    return (84);
}