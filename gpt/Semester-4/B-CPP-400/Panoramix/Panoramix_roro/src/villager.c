/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Villager thread
*/

#include <stdio.h>
#include "panoramix.h"

static void call_druid_if_needed(sim_t *sim, int id)
{
    if (!sim->druid_called && sim->nb_refills > 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
        sim->druid_called = true;
        sem_post(&sim->sem_call);
    }
}

static void drink_and_fight(sim_t *sim, int id, int fights_left)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        id, sim->servings);
    sim->servings -= 1;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
        id, fights_left - 1);
}

void *villager_thread(void *arg)
{
    villager_t *v = (villager_t *)arg;
    sim_t *sim = v->sim;
    int f = 0;

    printf("Villager %d: Going into battle!\n", v->id);
    for (f = sim->nb_fights; f > 0; --f) {
        pthread_mutex_lock(&sim->mtx);
        if (sim->servings <= 0) {
            printf("Villager %d: I need a drink... I see 0 servings left.\n", v->id);
            call_druid_if_needed(sim, v->id);
            pthread_mutex_unlock(&sim->mtx);
            sem_wait(&sim->sem_refilled);
            pthread_mutex_lock(&sim->mtx);
        }
        if (sim->servings > 0) {
            drink_and_fight(sim, v->id, f);
            pthread_mutex_unlock(&sim->mtx);
        } else {
            pthread_mutex_unlock(&sim->mtx);
            --f; ++f; /* keep loop stable */
        }
    }
    printf("Villager %d: I’m going to sleep now.\n", v->id);
    return NULL;
}

