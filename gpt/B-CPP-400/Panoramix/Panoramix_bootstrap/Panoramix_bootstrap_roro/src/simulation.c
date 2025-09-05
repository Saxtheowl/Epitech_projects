/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
** simulation.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "simulation.h"

typedef struct ThreadArg {
    int id;
    Simulation *sim;
} ThreadArg;

static void *train_thread(void *data)
{
    ThreadArg *arg;

    arg = (ThreadArg *)data;
    bridge_enter(arg->sim, arg->id);
    usleep(100000);
    bridge_leave(arg->sim, arg->id);
    return NULL;
}

void simulation_init(Simulation *sim, int nb_trains, int nb_max, bool quiet)
{
    sim->nb_trains = nb_trains;
    sim->nb_max = nb_max;
    sim->on_bridge = 0;
    sim->max_observed = 0;
    sim->quiet = quiet;
    pthread_mutex_init(&sim->bridge_mutex, NULL);
    pthread_cond_init(&sim->bridge_cond, NULL);
}

void simulation_destroy(Simulation *sim)
{
    pthread_mutex_destroy(&sim->bridge_mutex);
    pthread_cond_destroy(&sim->bridge_cond);
}

int run_simulation(int nb_trains, int nb_max, bool quiet)
{
    pthread_t *ths;
    ThreadArg *args;
    Simulation sim;
    int i;

    simulation_init(&sim, nb_trains, nb_max, quiet);
    ths = calloc((size_t)nb_trains, sizeof(pthread_t));
    args = calloc((size_t)nb_trains, sizeof(ThreadArg));
    if (!ths || !args) {
        free(ths);
        free(args);
        simulation_destroy(&sim);
        return 84;
    }
    for (i = 0; i < nb_trains; ++i) {
        args[i].id = i;
        args[i].sim = &sim;
        pthread_create(&ths[i], NULL, train_thread, &args[i]);
    }
    for (i = 0; i < nb_trains; ++i)
        pthread_join(ths[i], NULL);
    i = sim.max_observed;
    free(ths);
    free(args);
    simulation_destroy(&sim);
    return i;
}

