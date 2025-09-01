/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Header file for autonomous car AI
*/

#ifndef AI_H_
#define AI_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define LIDAR_POINTS 32
#define MAX_LIDAR_RANGE 3010
#define SAFE_DISTANCE 800.0
#define MIN_SAFE_DISTANCE 400.0
#define TURN_THRESHOLD 1200.0
#define MAX_SPEED 1.0
#define MIN_SPEED 0.1
#define TURN_SPEED 0.3

#define RESPONSE_BUFFER_SIZE 1024
#define COMMAND_BUFFER_SIZE 256

typedef enum {
    STATE_STARTING,
    STATE_DRIVING,
    STATE_TURNING,
    STATE_EMERGENCY_STOP,
    STATE_FINISHED
} car_state_t;

typedef struct {
    float distances[LIDAR_POINTS];
    float front_distance;
    float left_distance;
    float right_distance;
    int has_data;
} lidar_data_t;

typedef struct {
    float speed;
    float wheel_direction;
    float max_speed;
    float min_speed;
} car_status_t;

typedef struct {
    lidar_data_t lidar;
    car_status_t car;
    car_state_t state;
    int checkpoint_count;
    int lap_count;
    int simulation_running;
} ai_context_t;

// Protocol functions
int send_command(const char *command);
int read_response(char *buffer, size_t size);
int parse_response(const char *response, int *value_id, char *status, char *code_str, char *additional_info);

// Simulation control
int start_simulation(void);
int stop_simulation(void);
int cycle_wait(int cycles);

// Car control
int car_forward(float power);
int car_backwards(float power);
int set_wheels_direction(float direction);

// Sensor data
int get_lidar_data(lidar_data_t *lidar);
int get_current_speed(float *speed);
int get_current_wheels(float *direction);
int get_max_speed(float *max_speed);
int get_min_speed(float *min_speed);

// LIDAR processing
void process_lidar_data(lidar_data_t *lidar);
float get_front_distance(const lidar_data_t *lidar);
float get_left_distance(const lidar_data_t *lidar);
float get_right_distance(const lidar_data_t *lidar);
int detect_wall_ahead(const lidar_data_t *lidar, float threshold);
float calculate_safe_direction(const lidar_data_t *lidar);

// Navigation AI
void update_ai_state(ai_context_t *context);
void drive_straight(ai_context_t *context);
void navigate_turn(ai_context_t *context);
void emergency_stop(ai_context_t *context);
float calculate_optimal_speed(const lidar_data_t *lidar);

// Controller
void run_ai_controller(void);
int initialize_car(ai_context_t *context);
void cleanup_ai(ai_context_t *context);

// Utils
void debug_log(const char *format, ...);
int is_checkpoint_cleared(const char *additional_info);
int is_lap_completed(const char *additional_info);
int is_track_completed(const char *additional_info);

#endif /* !AI_H_ */