/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
** simulation.h
*/

#ifndef PANORAMIX_SIMULATION_H
#define PANORAMIX_SIMULATION_H

#include <pthread.h>
#include <stdbool.h>

typedef struct Simulation {
    int nb_trains;
    int nb_max;
    int on_bridge;
    int max_observed;
    bool quiet;
    pthread_mutex_t bridge_mutex;
    pthread_cond_t bridge_cond;
} Simulation;

int run_simulation(int nb_trains, int nb_max, bool quiet);
void simulation_init(Simulation *sim, int nb_trains, int nb_max, bool quiet);
void simulation_destroy(Simulation *sim);
void bridge_enter(Simulation *sim, int id);
void bridge_leave(Simulation *sim, int id);

#endif /* PANORAMIX_SIMULATION_H */

