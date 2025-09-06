/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Main program for Panoramix concurrent programming project
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int id;
    int nb_fights;
    int fights_left;
} villager_t;

typedef struct {
    int pot_size;
    int servings_left;
    int nb_refills;
    int refills_left;
    pthread_mutex_t pot_mutex;
    sem_t empty_pot_sem;
    sem_t full_pot_sem;
} shared_data_t;

shared_data_t *g_data = NULL;

void *druid_thread(void *arg)
{
    (void)arg;
    printf("Druid: I'm ready... but sleepy...\n");
    
    while (g_data->refills_left > 0) {
        sem_wait(&g_data->empty_pot_sem);
        
        pthread_mutex_lock(&g_data->pot_mutex);
        if (g_data->refills_left <= 0) {
            pthread_mutex_unlock(&g_data->pot_mutex);
            break;
        }
            
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make %d more refills after this one.\n", 
               g_data->refills_left - 1);
        
        g_data->servings_left = g_data->pot_size;
        g_data->refills_left--;
        pthread_mutex_unlock(&g_data->pot_mutex);
        
        if (g_data->refills_left == 0) {
            printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
        }
        
        for (int i = 0; i < g_data->pot_size; i++) {
            sem_post(&g_data->full_pot_sem);
        }
    }
    
    return NULL;
}

void *villager_thread(void *arg)
{
    villager_t *villager = (villager_t *)arg;
    
    printf("Villager %d: Going into battle!\n", villager->id);
    
    while (villager->fights_left > 0) {
        pthread_mutex_lock(&g_data->pot_mutex);
        
        while (g_data->servings_left == 0) {
            printf("Villager %d: I need a drink... I see 0 servings left.\n", villager->id);
            printf("Villager %d: Hey Pano wake up! We need more potion.\n", villager->id);
            pthread_mutex_unlock(&g_data->pot_mutex);
            
            sem_post(&g_data->empty_pot_sem);
            sem_wait(&g_data->full_pot_sem);
            
            pthread_mutex_lock(&g_data->pot_mutex);
        }
        
        if (g_data->servings_left > 0) {
            printf("Villager %d: I need a drink... I see %d servings left.\n", 
                   villager->id, g_data->servings_left);
            g_data->servings_left--;
        }
        pthread_mutex_unlock(&g_data->pot_mutex);
        
        villager->fights_left--;
        printf("Villager %d: Take that roman scum! Only %d left.\n", 
               villager->id, villager->fights_left);
    }
    
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
    return NULL;
}

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

int main(int argc, char **argv)
{
    if (check_args(argc, argv) != 0)
        return 84;
    
    int nb_villagers = atoi(argv[1]);
    int pot_size = atoi(argv[2]);
    int nb_fights = atoi(argv[3]);
    int nb_refills = atoi(argv[4]);
    
    g_data = malloc(sizeof(shared_data_t));
    if (!g_data)
        return 84;
    
    g_data->pot_size = pot_size;
    g_data->servings_left = pot_size;
    g_data->nb_refills = nb_refills;
    g_data->refills_left = nb_refills;
    
    pthread_mutex_init(&g_data->pot_mutex, NULL);
    sem_init(&g_data->empty_pot_sem, 0, 0);
    sem_init(&g_data->full_pot_sem, 0, 0);
    
    pthread_t druid;
    pthread_t *villagers = malloc(sizeof(pthread_t) * nb_villagers);
    villager_t *villager_data = malloc(sizeof(villager_t) * nb_villagers);
    
    if (!villagers || !villager_data) {
        free(g_data);
        return 84;
    }
    
    pthread_create(&druid, NULL, druid_thread, NULL);
    
    for (int i = 0; i < nb_villagers; i++) {
        villager_data[i].id = i;
        villager_data[i].nb_fights = nb_fights;
        villager_data[i].fights_left = nb_fights;
        pthread_create(&villagers[i], NULL, villager_thread, &villager_data[i]);
    }
    
    for (int i = 0; i < nb_villagers; i++) {
        pthread_join(villagers[i], NULL);
    }
    
    pthread_cancel(druid);
    pthread_join(druid, NULL);
    
    pthread_mutex_destroy(&g_data->pot_mutex);
    sem_destroy(&g_data->empty_pot_sem);
    sem_destroy(&g_data->full_pot_sem);
    
    free(villagers);
    free(villager_data);
    free(g_data);
    
    return 0;
}