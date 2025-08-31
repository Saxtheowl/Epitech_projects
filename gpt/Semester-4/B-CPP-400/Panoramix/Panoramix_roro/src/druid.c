/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Druid thread
*/

#include <stdio.h>
#include "panoramix.h"

void *druid_thread(void *arg)
{
    sim_t *sim = (sim_t *)arg;
    int i = 0;

    printf("Druid: I’m ready... but sleepy...\n");
    while (1) {
        sem_wait(&sim->sem_call);
        if (sim->stop)
            break;
        pthread_mutex_lock(&sim->mtx);
        if (sim->nb_refills <= 0) {
            printf("Druid: I’m out of viscum. I’m going back to... zZz\n");
            pthread_mutex_unlock(&sim->mtx);
            break;
        }
        printf("Druid: Ah! Yes, yes, I’m awake! Working on it! Beware I can only make %d more\nrefills after this one.\n",
            sim->nb_refills - 1);
        if (sim->nb_refills - 1 == 0) {
            printf("Druid: I’m out of viscum. I’m going back to... zZz\n");
        }
        sim->servings = sim->pot_size;
        sim->druid_called = false;
        for (i = 0; i < sim->pot_size; ++i)
            sem_post(&sim->sem_refilled);
        sim->nb_refills -= 1;
        pthread_mutex_unlock(&sim->mtx);
    }
    return NULL;
}

