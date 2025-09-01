/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Process wrapper
*/

#ifndef PLAZZA_PROCESS_HPP
#define PLAZZA_PROCESS_HPP

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

class PlzProcess {
public:
    static pid_t fork() { return ::fork(); }
    static pid_t waitpid(pid_t pid, int *status, int options) { return ::waitpid(pid, status, options); }
};

#endif
