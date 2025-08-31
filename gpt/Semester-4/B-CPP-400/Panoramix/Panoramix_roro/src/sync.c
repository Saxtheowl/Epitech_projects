/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Sync primitives lifecycle
*/

#include <stdlib.h>
#include <string.h>
#include "panoramix.h"

int sim_init(sim_t *sim)
{
    sim->servings = sim->pot_size;
    sim->druid_called = false;
    sim->stop = false;
    if (pthread_mutex_init(&sim->mtx, NULL) != 0)
        return -1;
    if (sem_init(&sim->sem_call, 0, 0) != 0)
        return -1;
    if (sem_init(&sim->sem_refilled, 0, 0) != 0)
        return -1;
    return 0;
}

void sim_destroy(sim_t *sim)
{
    pthread_mutex_destroy(&sim->mtx);
    sem_destroy(&sim->sem_call);
    sem_destroy(&sim->sem_refilled);
}
