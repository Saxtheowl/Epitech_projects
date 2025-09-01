/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Utility functions for AI debugging and checkpoint detection
*/

#include "ai.h"
#include <stdarg.h>

void debug_log(const char *format, ...)
{
    va_list args;
    
    // Print timestamp and debug prefix
    fprintf(stderr, "[AI_DEBUG] ");
    
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    fflush(stderr);
}

int is_checkpoint_cleared(const char *additional_info)
{
    return strstr(additional_info, "CP Cleared") != NULL ||
           strstr(additional_info, "First CP Cleared") != NULL;
}

int is_lap_completed(const char *additional_info)
{
    return strstr(additional_info, "Lap Cleared") != NULL;
}

int is_track_completed(const char *additional_info)
{
    return strstr(additional_info, "Track Cleared") != NULL;
}