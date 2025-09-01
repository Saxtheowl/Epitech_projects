/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Job control management
*/

#include "shell.h"

int add_job(shell_t *shell, pid_t pgid, char *command)
{
    job_t *job = malloc(sizeof(job_t));
    int next_id = 1;
    
    if (!job) {
        return -1;
    }
    
    // Find next available job ID
    job_t *current = shell->jobs;
    while (current) {
        if (current->id >= next_id) {
            next_id = current->id + 1;
        }
        current = current->next;
    }
    
    job->id = next_id;
    job->pgid = pgid;
    job->command = my_strdup(command);
    job->status = 0; // Running
    job->next = shell->jobs;
    
    if (!job->command) {
        free(job);
        return -1;
    }
    
    shell->jobs = job;
    printf("[%d] %d\n", job->id, pgid);
    
    return job->id;
}

void remove_job(shell_t *shell, int job_id)
{
    job_t *job = shell->jobs;
    job_t *prev = NULL;
    
    while (job) {
        if (job->id == job_id) {
            if (prev) {
                prev->next = job->next;
            } else {
                shell->jobs = job->next;
            }
            
            free(job->command);
            free(job);
            return;
        }
        
        prev = job;
        job = job->next;
    }
}

void update_jobs(shell_t *shell)
{
    job_t *job = shell->jobs;
    job_t *prev = NULL;
    
    while (job) {
        job_t *next = job->next;
        int status;
        pid_t result = waitpid(-job->pgid, &status, WNOHANG | WUNTRACED);
        
        if (result > 0) {
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                printf("[%d]  Done                    %s\n", 
                       job->id, job->command);
                
                // Remove completed job
                if (prev) {
                    prev->next = job->next;
                } else {
                    shell->jobs = job->next;
                }
                
                free(job->command);
                free(job);
                job = next;
                continue;
            } else if (WIFSTOPPED(status)) {
                job->status = 1; // Stopped
            }
        }
        
        prev = job;
        job = next;
    }
}

void print_jobs(shell_t *shell)
{
    job_t *job = shell->jobs;
    
    while (job) {
        char *status_str = (job->status == 0) ? "Running" : "Stopped";
        printf("[%d]  %s                    %s\n", 
               job->id, status_str, job->command);
        job = job->next;
    }
}

job_t *get_job(shell_t *shell, int job_id)
{
    job_t *job = shell->jobs;
    
    while (job) {
        if (job->id == job_id) {
            return job;
        }
        job = job->next;
    }
    
    return NULL;
}