/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
** bridge.c
*/

#include <stdio.h>
#include "simulation.h"

static void print_msg(Simulation *sim, int id, const char *msg)
{
    if (sim->quiet)
        return;
    printf("%d: %s\n", id, msg);
    fflush(stdout);
}

void bridge_enter(Simulation *sim, int id)
{
    pthread_mutex_lock(&sim->bridge_mutex);
    while (sim->on_bridge >= sim->nb_max) {
        pthread_cond_wait(&sim->bridge_cond, &sim->bridge_mutex);
    }
    sim->on_bridge += 1;
    if (sim->on_bridge > sim->max_observed)
        sim->max_observed = sim->on_bridge;
    print_msg(sim, id, "entering bridge");
    pthread_mutex_unlock(&sim->bridge_mutex);
}

void bridge_leave(Simulation *sim, int id)
{
    pthread_mutex_lock(&sim->bridge_mutex);
    print_msg(sim, id, "leaving bridge");
    sim->on_bridge -= 1;
    pthread_cond_broadcast(&sim->bridge_cond);
    pthread_mutex_unlock(&sim->bridge_mutex);
}

