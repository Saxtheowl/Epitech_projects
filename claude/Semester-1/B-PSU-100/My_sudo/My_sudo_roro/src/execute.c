/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Command execution with privilege escalation
*/

#include "my_sudo.h"

int get_user_shell(const char *username, char **shell)
{
    struct passwd *pwd = getpwnam(username);
    
    if (!pwd) {
        *shell = strdup("/bin/sh");
        return 0;
    }
    
    *shell = strdup(pwd->pw_shell);
    return 0;
}

static int execute_shell(sudo_config_t *config)
{
    char *shell = getenv("SHELL");
    char *target_shell = NULL;
    
    if (!shell) {
        if (config->username) {
            get_user_shell(config->username, &target_shell);
            shell = target_shell;
        } else {
            shell = "/bin/sh";
        }
    }
    
    if (setgid(config->run_as_gid) != 0) {
        perror("my_sudo: setgid");
        free(target_shell);
        return -1;
    }
    
    if (setuid(config->run_as_uid) != 0) {
        perror("my_sudo: setuid");
        free(target_shell);
        return -1;
    }
    
    execl(shell, shell, NULL);
    perror("my_sudo: execl");
    free(target_shell);
    return -1;
}

static int execute_regular_command(sudo_config_t *config)
{
    if (setgid(config->run_as_gid) != 0) {
        perror("my_sudo: setgid");
        return -1;
    }
    
    if (setuid(config->run_as_uid) != 0) {
        perror("my_sudo: setuid");
        return -1;
    }
    
    execvp(config->command[0], config->command);
    perror("my_sudo: execvp");
    return -1;
}

int execute_command(sudo_config_t *config)
{
    pid_t pid = fork();
    int status = 0;
    
    if (pid == -1) {
        perror("my_sudo: fork");
        return -1;
    }
    
    if (pid == 0) {
        if (config->shell_mode) {
            return execute_shell(config);
        } else {
            return execute_regular_command(config);
        }
    }
    
    if (waitpid(pid, &status, 0) == -1) {
        perror("my_sudo: waitpid");
        return -1;
    }
    
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status);
    }
    
    return 0;
}

void free_config(sudo_config_t *config)
{
    int i = 0;
    
    free(config->username);
    free(config->group);
    
    if (config->command) {
        while (config->command[i]) {
            free(config->command[i]);
            i++;
        }
        free(config->command);
    }
}