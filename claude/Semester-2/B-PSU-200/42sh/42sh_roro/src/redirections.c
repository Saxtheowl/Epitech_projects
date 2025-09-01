/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Input/Output redirection handling
*/

#include "shell.h"

static int setup_input_redirection(char *filename)
{
    int fd;
    
    if (!filename) {
        return 0;
    }
    
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror(filename);
        return -1;
    }
    
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }
    
    close(fd);
    return 0;
}

static int setup_output_redirection(char *filename, int append)
{
    int fd;
    int flags = O_WRONLY | O_CREAT;
    
    if (!filename) {
        return 0;
    }
    
    flags |= append ? O_APPEND : O_TRUNC;
    
    fd = open(filename, flags, 0644);
    if (fd == -1) {
        perror(filename);
        return -1;
    }
    
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }
    
    close(fd);
    return 0;
}

int setup_redirections_full(cmd_t *cmd)
{
    if (setup_input_redirection(cmd->input_file) != 0) {
        return -1;
    }
    
    if (setup_output_redirection(cmd->output_file, cmd->append_output) != 0) {
        return -1;
    }
    
    return 0;
}