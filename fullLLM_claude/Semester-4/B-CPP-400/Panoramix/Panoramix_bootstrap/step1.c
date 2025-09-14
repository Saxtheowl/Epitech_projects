#include "panoramix.h"

// Global variables
pthread_mutex_t bridge_mutex;
pthread_mutex_t display_mutex;
train_t trains[NB_TRAINS];
int bridge_capacity = 1; // Step 1: Only one train at a time
int trains_on_bridge = 0;

void init_train(train_t *train, int id)
{
    train->train_id = id;
    train->position = 0;
    
    // Initialize display string
    memset(train->display, '=', TRACK_LENGTH);
    train->display[0] = '#';  // Train starts at position 0
    train->display[5] = '|';  // Bridge start
    train->display[6] = '-';
    train->display[7] = '-';
    train->display[8] = '-';
    train->display[9] = '-';
    train->display[10] = '|'; // Bridge end
    train->display[TRACK_LENGTH] = '\0';
}

int is_on_bridge(train_t *train)
{
    return (train->position >= 5 && train->position <= 10);
}

void move_train(train_t *train)
{
    // Clear current position
    if (train->position < TRACK_LENGTH) {
        if (train->position >= 5 && train->position <= 10) {
            // On bridge - restore bridge character
            if (train->position == 5 || train->position == 10) {
                train->display[train->position] = '|';
            } else {
                train->display[train->position] = '-';
            }
        } else {
            // On track
            train->display[train->position] = '=';
        }
    }
    
    // Move to next position
    train->position++;
    
    // Set new position
    if (train->position < TRACK_LENGTH) {
        train->display[train->position] = '#';
    }
}

void display_trains(void)
{
    printf("\033[H\033[J"); // Clear screen and move cursor to top
    printf("0123456789012345\n");
    printf("------------------\n");
    
    for (int i = 0; i < NB_TRAINS; i++) {
        printf("%d: %s\n", i, trains[i].display);
    }
    printf("\n");
}

void *train_thread(void *arg)
{
    int train_id = *(int *)arg;
    train_t *train = &trains[train_id];
    
    while (train->position < TRACK_LENGTH) {
        // Check if approaching bridge
        if (train->position == 4) {
            // About to enter bridge - acquire mutex
            pthread_mutex_lock(&bridge_mutex);
            trains_on_bridge++;
        }
        
        // Move train
        move_train(train);
        
        // Update display
        pthread_mutex_lock(&display_mutex);
        display_trains();
        pthread_mutex_unlock(&display_mutex);
        
        // Check if leaving bridge
        if (train->position == 11) {
            // Just left bridge - release mutex
            trains_on_bridge--;
            pthread_mutex_unlock(&bridge_mutex);
        }
        
        // Small delay to see animation
        usleep(500000); // 500ms
    }
    
    return NULL;
}

int main(void)
{
    pthread_t threads[NB_TRAINS];
    int train_ids[NB_TRAINS];
    
    // Initialize mutexes
    pthread_mutex_init(&bridge_mutex, NULL);
    pthread_mutex_init(&display_mutex, NULL);
    
    // Initialize trains
    for (int i = 0; i < NB_TRAINS; i++) {
        init_train(&trains[i], i);
        train_ids[i] = i;
    }
    
    // Display initial state
    display_trains();
    sleep(1);
    
    // Create threads
    for (int i = 0; i < NB_TRAINS; i++) {
        pthread_create(&threads[i], NULL, train_thread, &train_ids[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < NB_TRAINS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Cleanup
    pthread_mutex_destroy(&bridge_mutex);
    pthread_mutex_destroy(&display_mutex);
    
    printf("All trains have finished crossing!\n");
    return 0;
}