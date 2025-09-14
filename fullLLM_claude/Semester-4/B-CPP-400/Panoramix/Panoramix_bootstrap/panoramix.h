#ifndef PANORAMIX_H
#define PANORAMIX_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NB_TRAINS 3
#define NB_MAX 2
#define BRIDGE_LENGTH 4
#define TRACK_LENGTH 16

typedef struct {
    int train_id;
    int position;
    char display[TRACK_LENGTH + 1];
} train_t;

// Global variables
extern pthread_mutex_t bridge_mutex;
extern pthread_mutex_t display_mutex;
extern train_t trains[NB_TRAINS];
extern int bridge_capacity;
extern int trains_on_bridge;

// Function prototypes
void *train_thread(void *arg);
void display_trains(void);
void init_train(train_t *train, int id);
void move_train(train_t *train);
int is_on_bridge(train_t *train);

#endif