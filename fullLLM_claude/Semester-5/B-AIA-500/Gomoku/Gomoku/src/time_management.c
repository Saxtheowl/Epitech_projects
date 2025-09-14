/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Time management for search algorithms
*/

#include "gomoku.h"

void init_time_manager(time_manager_t *time_mgr, long time_limit_ms)
{
    gettimeofday(&time_mgr->start_time, NULL);
    time_mgr->time_limit_ms = time_limit_ms;
    time_mgr->max_depth = MAX_DEPTH;
}

long get_elapsed_time(const time_manager_t *time_mgr)
{
    struct timeval current_time;
    long elapsed_ms;
    
    gettimeofday(&current_time, NULL);
    
    elapsed_ms = (current_time.tv_sec - time_mgr->start_time.tv_sec) * 1000;
    elapsed_ms += (current_time.tv_usec - time_mgr->start_time.tv_usec) / 1000;
    
    return elapsed_ms;
}

int is_time_up(const time_manager_t *time_mgr)
{
    long elapsed = get_elapsed_time(time_mgr);
    
    // Leave some buffer time to ensure we don't exceed the limit
    return elapsed >= (time_mgr->time_limit_ms - 100);
}