/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Druid thread implementation
*/

#include "panoramix.h"

void *druid_thread(void *arg)
{
    druid_t *druid = (druid_t *)arg;
    panoramix_t *data = druid->data;

    safe_print(&data->print_mutex, "Druid: I'm ready... but sleepy...\n");

    while (data->refills_done < data->nb_refills) {
        // Wait to be called
        sem_wait(&data->empty_pot);

        pthread_mutex_lock(&data->pot_mutex);

        if (data->refills_done >= data->nb_refills) {
            pthread_mutex_unlock(&data->pot_mutex);
            break;
        }

        // Refill the pot
        safe_print(&data->print_mutex, "Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make %d more refills after this one.\n",
                  data->nb_refills - data->refills_done - 1);

        data->current_pot = data->pot_size;
        data->refills_done++;

        // Signal that pot is refilled
        for (int i = 0; i < data->nb_villagers; i++) {
            sem_post(&data->full_pot);
        }

        if (data->refills_done >= data->nb_refills) {
            safe_print(&data->print_mutex, "Druid: I'm out of viscum. I'm going back to... zZz\n");
        } else {
            data->druid_sleeping = 1;
        }

        pthread_mutex_unlock(&data->pot_mutex);
    }

    // If druid is out of refills, wake up any waiting villagers
    pthread_mutex_lock(&data->pot_mutex);
    for (int i = 0; i < data->nb_villagers; i++) {
        sem_post(&data->full_pot);
    }
    pthread_mutex_unlock(&data->pot_mutex);

    return NULL;
}