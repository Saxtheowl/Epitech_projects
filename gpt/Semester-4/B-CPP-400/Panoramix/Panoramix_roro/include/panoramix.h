/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Public interfaces
*/

#ifndef PANORAMIX_H
#define PANORAMIX_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct sim_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int servings;
    bool druid_called;
    bool stop;
    pthread_mutex_t mtx;
    sem_t sem_call;
    sem_t sem_refilled;
} sim_t;

typedef struct villager_s {
    int id;
    sim_t *sim;
} villager_t;

/* strings.c */
int my_atoi_strict(const char *s, int *out);
int my_strcmp(const char *a, const char *b);
int my_dprintf(int fd, const char *s);

/* args.c */
int parse_args(int ac, char **av, sim_t *sim);
void usage(void);

/* sync.c */
int sim_init(sim_t *sim);
void sim_destroy(sim_t *sim);

/* druid.c */
void *druid_thread(void *arg);

/* villager.c */
void *villager_thread(void *arg);

/* sim.c */
int run_sim(sim_t *sim);

#define EXIT_ERR 84

#endif /* PANORAMIX_H */

