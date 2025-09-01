/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Signal handling
*/

#include "shell.h"

void sigchld_handler(int sig)
{
    (void)sig;
    
    while (1) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        
        if (pid <= 0) {
            break;
        }
        
        // Update job status if we have job control
        if (g_shell && g_shell->jobs) {
            job_t *job = g_shell->jobs;
            while (job) {
                if (job->pgid == pid) {
                    if (WIFEXITED(status) || WIFSIGNALED(status)) {
                        printf("[%d]  Done                    %s\n", 
                               job->id, job->command);
                    }
                    break;
                }
                job = job->next;
            }
        }
    }
}

void sigint_handler(int sig)
{
    (void)sig;
    
    if (g_shell && g_shell->interactive) {
        printf("\n42sh$ ");
        fflush(stdout);
    }
}

void setup_signals(void)
{
    struct sigaction sa_chld;
    struct sigaction sa_int;
    
    // Setup SIGCHLD handler for job control
    sa_chld.sa_handler = sigchld_handler;
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa_chld, NULL);
    
    // Setup SIGINT handler for interactive mode
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
    
    // Ignore SIGTSTP and SIGTTOU in interactive mode
    if (g_shell && g_shell->interactive) {
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
    }
}