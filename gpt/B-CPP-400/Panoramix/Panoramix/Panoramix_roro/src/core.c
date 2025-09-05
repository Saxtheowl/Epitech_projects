/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** core.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "panoramix.h"

/* ThreadArg defined in header */

void pano_printf(Panoramix *px, const char *fmt, ...)
{
    va_list ap;

    pthread_mutex_lock(&px->print_mutex);
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    fflush(stdout);
    pthread_mutex_unlock(&px->print_mutex);
}

void pano_init(Panoramix *px, int v, int p, int f, int r)
{
    px->nb_villagers = v;
    px->pot_size = p;
    px->nb_fights = f;
    px->nb_refills = r;
    px->servings = p;
    px->villagers_left = v;
    px->need_refill = false;
    px->druid_done = false;
    px->stop = false;
    pthread_mutex_init(&px->pot_mutex, NULL);
    pthread_mutex_init(&px->print_mutex, NULL);
    pthread_cond_init(&px->refilled, NULL);
    sem_init(&px->sem_refill, 0, 0);
}

void pano_destroy(Panoramix *px)
{
    pthread_mutex_destroy(&px->pot_mutex);
    pthread_mutex_destroy(&px->print_mutex);
    pthread_cond_destroy(&px->refilled);
    sem_destroy(&px->sem_refill);
}

int run_panoramix(int v, int p, int f, int r)
{
    Panoramix px;
    pthread_t druid;
    pthread_t *vill;
    ThreadArg *args;
    int i;

    pano_init(&px, v, p, f, r);
    vill = calloc((size_t)v, sizeof(pthread_t));
    args = calloc((size_t)v, sizeof(ThreadArg));
    if (!vill || !args) {
        free(vill);
        free(args);
        pano_destroy(&px);
        return 84;
    }
    pthread_create(&druid, NULL, druid_thread, &px);
    for (i = 0; i < v; ++i) {
        args[i].px = &px;
        args[i].id = i;
        pthread_create(&vill[i], NULL, villager_thread, &args[i]);
    }
    for (i = 0; i < v; ++i)
        pthread_join(vill[i], NULL);
    /* Wake druid so it can exit if still sleeping */
    pthread_mutex_lock(&px.pot_mutex);
    px.stop = true;
    pthread_mutex_unlock(&px.pot_mutex);
    sem_post(&px.sem_refill);
    pthread_join(druid, NULL);
    free(vill);
    free(args);
    pano_destroy(&px);
    return 0;
}
