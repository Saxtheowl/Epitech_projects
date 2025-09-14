#ifndef AI_H_
#define AI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define LIDAR_COUNT 32
#define MAX_LIDAR_RANGE 3010.0
#define SAFE_DISTANCE 1000.0
#define TURN_THRESHOLD 1500.0
#define SPEED_MAX 1.0
#define SPEED_MIN 0.0
#define TURN_MAX 1.0
#define TURN_MIN -1.0

typedef struct {
    float lidar_data[LIDAR_COUNT];
    float current_speed;
    float current_wheel;
    int simulation_running;
    int track_completed;
} car_state_t;

typedef struct {
    float forward_distance;
    float left_distance;
    float right_distance;
    int obstacle_detected;
} sensor_analysis_t;

// Communication functions
void send_command(const char *command);
char *read_response(void);
int parse_response(char *response, char *status, float *data, int *data_count);

// Control functions
void start_simulation(void);
void stop_simulation(void);
void set_car_forward(float speed);
void set_car_backward(float speed);
void set_wheels_direction(float direction);

// Sensor functions
int get_lidar_info(float *lidar_data);
float get_current_speed(void);
float get_current_wheels(void);

// AI functions
void analyze_sensors(float *lidar_data, sensor_analysis_t *analysis);
void make_decision(sensor_analysis_t *analysis, car_state_t *state);
void autonomous_drive(void);

// Utility functions
float clamp(float value, float min, float max);
void cleanup_and_exit(int exit_code);

#endif