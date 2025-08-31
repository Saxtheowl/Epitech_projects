/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Simulation orchestration
*/

#include <stdlib.h>
#include <stdio.h>
#include "panoramix.h"

int run_sim(sim_t *sim)
{
    pthread_t druid;
    pthread_t *vill = NULL;
    villager_t *ctx = NULL;
    int i = 0;

    if (sim_init(sim) != 0)
        return -1;
    if (pthread_create(&druid, NULL, druid_thread, sim) != 0)
        return -1;
    vill = calloc((size_t)sim->nb_villagers, sizeof(pthread_t));
    ctx = calloc((size_t)sim->nb_villagers, sizeof(villager_t));
    if (!vill || !ctx)
        return -1;
    for (i = 0; i < sim->nb_villagers; ++i) {
        ctx[i].id = i;
        ctx[i].sim = sim;
        pthread_create(&vill[i], NULL, villager_thread, &ctx[i]);
    }
    for (i = 0; i < sim->nb_villagers; ++i)
        pthread_join(vill[i], NULL);
    pthread_mutex_lock(&sim->mtx);
    sim->stop = true;
    pthread_mutex_unlock(&sim->mtx);
    sem_post(&sim->sem_call);
    pthread_join(druid, NULL);
    sim_destroy(sim);
    free(vill);
    free(ctx);
    return 0;
}

