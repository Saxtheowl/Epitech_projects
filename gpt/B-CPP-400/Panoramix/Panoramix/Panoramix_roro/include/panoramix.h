/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** panoramix.h
*/

#ifndef PANORAMIX_H
#define PANORAMIX_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct Panoramix {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int servings;
    int villagers_left;
    bool need_refill;
    bool druid_done;
    bool stop;
    pthread_mutex_t pot_mutex;
    pthread_mutex_t print_mutex;
    pthread_cond_t refilled;
    sem_t sem_refill;
} Panoramix;

typedef struct ThreadArg {
    Panoramix *px;
    int id;
} ThreadArg;

int run_panoramix(int nb_villagers, int pot_size, int nb_fights, int nb_refills);

void pano_init(Panoramix *px, int v, int p, int f, int r);
void pano_destroy(Panoramix *px);
void *druid_thread(void *arg);
void *villager_thread(void *arg);
void pano_printf(Panoramix *px, const char *fmt, ...);

#endif /* PANORAMIX_H */
