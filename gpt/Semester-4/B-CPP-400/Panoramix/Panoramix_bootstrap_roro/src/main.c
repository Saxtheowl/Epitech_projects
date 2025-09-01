/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
**   Trains and bridge (threads + mutex/cond)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "panoramix_bootstrap.h"

static void bridge_init(bridge_t *b, int max)
{
    b->slots = 0;
    b->max = max;
    pthread_mutex_init(&b->mtx, NULL);
    pthread_cond_init(&b->cv, NULL);
}

static void bridge_enter(bridge_t *b)
{
    pthread_mutex_lock(&b->mtx);
    while (b->slots >= b->max)
        pthread_cond_wait(&b->cv, &b->mtx);
    b->slots++;
    pthread_mutex_unlock(&b->mtx);
}

static void bridge_leave(bridge_t *b)
{
    pthread_mutex_lock(&b->mtx);
    b->slots--;
    pthread_cond_signal(&b->cv);
    pthread_mutex_unlock(&b->mtx);
}

static void *train_run(void *arg)
{
    train_t *t = (train_t *)arg;
    usleep(50000 * (t->id % 3));
    printf("train %d approaching\n", t->id);
    bridge_enter(t->bridge);
    printf("train %d entering bridge\n", t->id);
    usleep(80000);
    printf("train %d leaving bridge\n", t->id);
    bridge_leave(t->bridge);
    return NULL;
}

int panoramix_bootstrap_main(int ac, char **av)
{
    int n = NB_TRAINS;
    int max = NB_MAX;
    bridge_t bridge;
    pthread_t th[NB_TRAINS];
    train_t tr[NB_TRAINS];

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        printf("Simulates %d trains, max %d on bridge.\n", n, max);
        return 0;
    }
    if (max < 1) max = 1;
    bridge_init(&bridge, max);
    for (int i = 0; i < n; ++i) {
        tr[i].id = i;
        tr[i].bridge = &bridge;
        pthread_create(&th[i], NULL, train_run, &tr[i]);
    }
    for (int i = 0; i < n; ++i)
        pthread_join(th[i], NULL);
    return 0;
}

int main(int ac, char **av)
{
    return panoramix_bootstrap_main(ac, av);
}
