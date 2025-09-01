/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
**   Public interfaces
*/

#ifndef PANORAMIX_BOOTSTRAP_H
#define PANORAMIX_BOOTSTRAP_H

#include <pthread.h>

#ifndef NB_TRAINS
#define NB_TRAINS 3
#endif

#ifndef NB_MAX
#define NB_MAX 1
#endif

typedef struct bridge_s {
    int slots;
    int max;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
} bridge_t;

typedef struct train_s {
    int id;
    bridge_t *bridge;
} train_t;

int panoramix_bootstrap_main(int ac, char **av);

#endif /* PANORAMIX_BOOTSTRAP_H */
