/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Villager thread implementation
*/

#include "panoramix.h"
#include <stdarg.h>

void safe_print(pthread_mutex_t *mutex, const char *format, ...)
{
    va_list args;

    pthread_mutex_lock(mutex);
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
    pthread_mutex_unlock(mutex);
}

void *villager_thread(void *arg)
{
    villager_t *villager = (villager_t *)arg;
    panoramix_t *data = villager->data;

    safe_print(&data->print_mutex, "Villager %d: Going into battle!\n", villager->id);

    while (villager->fights_left > 0) {
        pthread_mutex_lock(&data->pot_mutex);

        // Check if pot is empty
        if (data->current_pot == 0) {
            safe_print(&data->print_mutex, "Villager %d: Hey Pano wake up! We need more potion.\n", villager->id);

            // Wake up druid if sleeping
            if (data->druid_sleeping) {
                data->druid_sleeping = 0;
                sem_post(&data->empty_pot);
            }

            pthread_mutex_unlock(&data->pot_mutex);

            // Wait for refill
            sem_wait(&data->full_pot);

            pthread_mutex_lock(&data->pot_mutex);
        }

        // Check if druid has run out of refills and pot is empty
        if (data->current_pot == 0 && data->refills_done >= data->nb_refills) {
            pthread_mutex_unlock(&data->pot_mutex);
            break;
        }

        // Drink potion
        if (data->current_pot > 0) {
            safe_print(&data->print_mutex, "Villager %d: I need a drink... I see %d servings left.\n",
                      villager->id, data->current_pot);
            data->current_pot--;
        }

        pthread_mutex_unlock(&data->pot_mutex);

        // Fight
        villager->fights_left--;
        safe_print(&data->print_mutex, "Villager %d: Take that roman scum! Only %d left.\n",
                  villager->id, villager->fights_left);

        usleep(1000); // Small delay to make output more readable
    }

    safe_print(&data->print_mutex, "Villager %d: I'm going to sleep now.\n", villager->id);
    return NULL;
}