/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Main file for panoramix project
*/

#include "panoramix.h"

int check_args(int argc, char **argv)
{
    if (argc != 5) {
        fprintf(stderr, "USAGE: %s <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n", argv[0]);
        return 84;
    }

    for (int i = 1; i < 5; i++) {
        int value = atoi(argv[i]);
        if (value <= 0) {
            fprintf(stderr, "USAGE: %s <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n", argv[0]);
            fprintf(stderr, "Values must be >0.\n");
            return 84;
        }
    }
    return 0;
}

int init_panoramix(panoramix_t *data, char **argv)
{
    data->nb_villagers = atoi(argv[1]);
    data->pot_size = atoi(argv[2]);
    data->nb_fights = atoi(argv[3]);
    data->nb_refills = atoi(argv[4]);
    data->current_pot = data->pot_size;
    data->refills_done = 0;
    data->druid_sleeping = 1;

    if (pthread_mutex_init(&data->pot_mutex, NULL) != 0)
        return 84;
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return 84;
    if (sem_init(&data->empty_pot, 0, 0) != 0)
        return 84;
    if (sem_init(&data->full_pot, 0, 0) != 0)
        return 84;

    return 0;
}

void cleanup_panoramix(panoramix_t *data)
{
    pthread_mutex_destroy(&data->pot_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    sem_destroy(&data->empty_pot);
    sem_destroy(&data->full_pot);
}

int main(int argc, char **argv)
{
    panoramix_t data;
    pthread_t *villager_threads;
    pthread_t druid_thread_id;
    villager_t *villagers;
    druid_t druid_data;

    if (check_args(argc, argv) != 0)
        return 84;

    if (init_panoramix(&data, argv) != 0)
        return 84;

    villager_threads = malloc(sizeof(pthread_t) * data.nb_villagers);
    villagers = malloc(sizeof(villager_t) * data.nb_villagers);
    druid_data.data = &data;

    if (!villager_threads || !villagers)
        return 84;

    // Create druid thread
    if (pthread_create(&druid_thread_id, NULL, druid_thread, &druid_data) != 0)
        return 84;

    // Create villager threads
    for (int i = 0; i < data.nb_villagers; i++) {
        villagers[i].id = i;
        villagers[i].fights_left = data.nb_fights;
        villagers[i].data = &data;
        if (pthread_create(&villager_threads[i], NULL, villager_thread, &villagers[i]) != 0)
            return 84;
    }

    // Wait for all villager threads to finish
    for (int i = 0; i < data.nb_villagers; i++) {
        pthread_join(villager_threads[i], NULL);
    }

    // Wait for druid thread to finish
    pthread_join(druid_thread_id, NULL);

    free(villager_threads);
    free(villagers);
    cleanup_panoramix(&data);

    return 0;
}