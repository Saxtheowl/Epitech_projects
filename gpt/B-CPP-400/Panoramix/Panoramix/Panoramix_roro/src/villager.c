/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** villager.c
*/

#include <stdio.h>
#include <unistd.h>
#include "panoramix.h"

static void call_druid(Panoramix *px, int id)
{
    pano_printf(px, "Villager %d: Hey Pano wake up! We need more potion.\n", id);
    if (!px->need_refill) {
        px->need_refill = true;
        sem_post(&px->sem_refill);
    }
}

static int try_drink(Panoramix *px, int id)
{
    int left;

    pthread_mutex_lock(&px->pot_mutex);
    left = px->servings;
    pano_printf(px, "Villager %d: I need a drink... I see %d servings left.\n",
            id, left);
    if (left == 0) {
        if (px->nb_refills > 0)
            call_druid(px, id);
        while (px->servings == 0 && px->nb_refills > 0)
            pthread_cond_wait(&px->refilled, &px->pot_mutex);
        if (px->servings == 0 && px->nb_refills == 0) {
            pthread_mutex_unlock(&px->pot_mutex);
            return 0;
        }
    }
    if (px->servings > 0)
        px->servings -= 1;
    pthread_mutex_unlock(&px->pot_mutex);
    return 1;
}

void *villager_thread(void *arg)
{
    ThreadArg *a;
    Panoramix *px;
    int id;
    int i;

    a = (ThreadArg *)arg;
    px = a->px;
    id = a->id;
    pano_printf(px, "Villager %d: Going into battle!\n", id);
    for (i = 0; i < px->nb_fights; ++i) {
        if (!try_drink(px, id))
            break;
        pano_printf(px, "Villager %d: Take that roman scum! Only %d left.\n",
                id, px->nb_fights - i - 1);
        usleep(1000);
    }
    pano_printf(px, "Villager %d: I'm going to sleep now.\n", id);
    pthread_mutex_lock(&px->pot_mutex);
    px->villagers_left -= 1;
    if (px->villagers_left == 0) {
        px->stop = true;
        pthread_cond_broadcast(&px->refilled);
        sem_post(&px->sem_refill);
    }
    pthread_mutex_unlock(&px->pot_mutex);
    return NULL;
}
