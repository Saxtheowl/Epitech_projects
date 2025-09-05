/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** druid.c
*/

#include <stdio.h>
#include <unistd.h>
#include "panoramix.h"

void *druid_thread(void *arg)
{
    Panoramix *px;
    int left;

    px = (Panoramix *)arg;
    pano_printf(px, "Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(&px->sem_refill);
        pthread_mutex_lock(&px->pot_mutex);
        if (px->stop) {
            pthread_mutex_unlock(&px->pot_mutex);
            break;
        }
        left = px->nb_refills;
        if (left <= 0) {
            pthread_mutex_unlock(&px->pot_mutex);
            break;
        }
        pano_printf(px, "Druid: Ah! Yes, yes, I'm awake! Working on it! "
                "Beware I can only make %d more\nrefills after this one.\n",
                left - 1);
        px->servings = px->pot_size;
        px->nb_refills -= 1;
        px->need_refill = false;
        pthread_cond_broadcast(&px->refilled);
        pthread_mutex_unlock(&px->pot_mutex);
        usleep(1000);
    }
    pano_printf(px, "Druid: I'm out of viscum. I'm going back to... zZz\n");
    px->druid_done = true;
    pthread_cond_broadcast(&px->refilled);
    return NULL;
}
