/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Command execution for my_sudo
*/

#include "my_sudo.h"

int set_user_group(const char *username, const char *groupname)
{
    struct passwd *pw;
    struct group *gr;

    pw = getpwnam(username);
    if (!pw) {
        fprintf(stderr, "Error: User %s not found\n", username);
        return -1;
    }

    // Set primary group
    if (groupname) {
        gr = getgrnam(groupname);
        if (!gr) {
            fprintf(stderr, "Error: Group %s not found\n", groupname);
            return -1;
        }
        if (setgid(gr->gr_gid) != 0) {
            perror("setgid");
            return -1;
        }
    } else {
        if (setgid(pw->pw_gid) != 0) {
            perror("setgid");
            return -1;
        }
    }

    // Set user
    if (setuid(pw->pw_uid) != 0) {
        perror("setuid");
        return -1;
    }

    return 0;
}

char *get_shell(const char *username)
{
    char *shell;
    struct passwd *pw;

    // Check SHELL environment variable first
    shell = getenv("SHELL");
    if (shell)
        return strdup(shell);

    // Get user's default shell
    pw = getpwnam(username);
    if (pw && pw->pw_shell && strlen(pw->pw_shell) > 0)
        return strdup(pw->pw_shell);

    // Default shell
    return strdup("/bin/sh");
}

int execute_shell(sudo_args_t *args)
{
    char *shell;
    pid_t pid;
    int status;

    shell = get_shell(args->target_user);
    if (!shell)
        return -1;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(shell);
        return -1;
    }

    if (pid == 0) {
        // Child process
        if (set_user_group(args->target_user, args->target_group) != 0) {
            free(shell);
            exit(84);
        }

        execl(shell, shell, (char *)NULL);
        perror("execl");
        free(shell);
        exit(84);
    } else {
        // Parent process
        free(shell);
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int execute_command(sudo_args_t *args)
{
    pid_t pid;
    int status;

    if (args->shell_mode) {
        return execute_shell(args);
    }

    if (!args->command) {
        fprintf(stderr, "Error: No command specified\n");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // Child process
        if (set_user_group(args->target_user, args->target_group) != 0) {
            exit(84);
        }

        execvp(args->command[0], args->command);
        perror("execvp");
        exit(84);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}