/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Main entry point for autonomous car AI
*/

#include "ai.h"

static void print_usage(void)
{
    printf("USAGE: ./ai\n");
    printf("       Autonomous car AI for Need4Stek simulation\n\n");
    printf("This AI will:\n");
    printf("  - Connect to the simulation via n4s protocol\n");
    printf("  - Use LIDAR data for navigation\n");
    printf("  - Complete laps on the track\n");
    printf("  - Avoid obstacles and walls\n");
    printf("  - Stop safely when track is completed\n");
}

int main(int argc, char **argv)
{
    if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        print_usage();
        return 0;
    }
    
    if (argc != 1) {
        fprintf(stderr, "Error: Invalid arguments\n");
        print_usage();
        return 84;
    }
    
    debug_log("Starting Need4Stek AI...");
    
    run_ai_controller();
    
    debug_log("AI terminated successfully");
    return 0;
}