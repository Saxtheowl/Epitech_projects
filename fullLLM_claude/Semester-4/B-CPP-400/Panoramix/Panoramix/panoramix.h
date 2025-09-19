/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Header file for panoramix project
*/

#ifndef PANORAMIX_H_
#define PANORAMIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int current_pot;
    int refills_done;
    pthread_mutex_t pot_mutex;
    pthread_mutex_t print_mutex;
    sem_t empty_pot;
    sem_t full_pot;
    int druid_sleeping;
} panoramix_t;

typedef struct {
    int id;
    int fights_left;
    panoramix_t *data;
} villager_t;

typedef struct {
    panoramix_t *data;
} druid_t;

// Function prototypes
int check_args(int argc, char **argv);
int init_panoramix(panoramix_t *data, char **argv);
void *villager_thread(void *arg);
void *druid_thread(void *arg);
void cleanup_panoramix(panoramix_t *data);
void safe_print(pthread_mutex_t *mutex, const char *format, ...);

#endif /* !PANORAMIX_H_ */