/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** LIDAR data processing for autonomous navigation
*/

#include "ai.h"

int get_lidar_data(lidar_data_t *lidar)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("GET_INFO_LIDAR");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    // Parse response format: VALUE_ID:STATUS:CODE_STR[:float]*32:ADDITIONAL_INFO
    char *token = strtok(response, ":");
    
    // Skip VALUE_ID, STATUS, CODE_STR
    for (int i = 0; i < 3 && token; i++) {
        if (i == 0) value_id = atoi(token);
        else if (i == 1) strcpy(status, token);
        else if (i == 2) strcpy(code_str, token);
        token = strtok(NULL, ":");
    }
    
    if (strcmp(status, "OK") != 0) {
        debug_log("Failed to get LIDAR data: %s", code_str);
        return -1;
    }
    
    // Parse 32 LIDAR distance values
    for (int i = 0; i < LIDAR_POINTS && token; i++) {
        lidar->distances[i] = atof(token);
        token = strtok(NULL, ":");
    }
    
    // Process LIDAR data
    process_lidar_data(lidar);
    lidar->has_data = 1;
    
    return 0;
}

void process_lidar_data(lidar_data_t *lidar)
{
    // Calculate key distances for navigation
    lidar->front_distance = get_front_distance(lidar);
    lidar->left_distance = get_left_distance(lidar);
    lidar->right_distance = get_right_distance(lidar);
    
    debug_log("LIDAR - Front: %.1f, Left: %.1f, Right: %.1f", 
              lidar->front_distance, lidar->left_distance, lidar->right_distance);
}

float get_front_distance(const lidar_data_t *lidar)
{
    // Front sensors are around index 15-17 (center of 32-point array)
    float front_sum = 0.0;
    int front_count = 0;
    
    for (int i = 14; i <= 17; i++) {
        if (i < LIDAR_POINTS) {
            front_sum += lidar->distances[i];
            front_count++;
        }
    }
    
    return front_count > 0 ? front_sum / front_count : MAX_LIDAR_RANGE;
}

float get_left_distance(const lidar_data_t *lidar)
{
    // Left sensors are around index 0-7
    float left_sum = 0.0;
    int left_count = 0;
    
    for (int i = 0; i < 8; i++) {
        left_sum += lidar->distances[i];
        left_count++;
    }
    
    return left_count > 0 ? left_sum / left_count : MAX_LIDAR_RANGE;
}

float get_right_distance(const lidar_data_t *lidar)
{
    // Right sensors are around index 24-31
    float right_sum = 0.0;
    int right_count = 0;
    
    for (int i = 24; i < LIDAR_POINTS; i++) {
        right_sum += lidar->distances[i];
        right_count++;
    }
    
    return right_count > 0 ? right_sum / right_count : MAX_LIDAR_RANGE;
}

int detect_wall_ahead(const lidar_data_t *lidar, float threshold)
{
    return lidar->front_distance < threshold;
}

float calculate_safe_direction(const lidar_data_t *lidar)
{
    float direction = 0.0;
    
    // If there's more space on the left, turn left
    if (lidar->left_distance > lidar->right_distance + 200.0) {
        direction = -0.5; // Turn left
    }
    // If there's more space on the right, turn right
    else if (lidar->right_distance > lidar->left_distance + 200.0) {
        direction = 0.5;  // Turn right
    }
    // If both sides are similar, choose based on front distance
    else if (lidar->front_distance < SAFE_DISTANCE) {
        // Turn towards the side with more space
        direction = (lidar->left_distance > lidar->right_distance) ? -0.3 : 0.3;
    }
    
    debug_log("Calculated safe direction: %.3f", direction);
    return direction;
}

int get_current_speed(float *speed)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("GET_CURRENT_SPEED");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    char *token = strtok(response, ":");
    for (int i = 0; i < 4 && token; i++) {
        if (i == 1) strcpy(status, token);
        else if (i == 3) *speed = atof(token);
        token = strtok(NULL, ":");
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int get_current_wheels(float *direction)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("GET_CURRENT_WHEELS");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    char *token = strtok(response, ":");
    for (int i = 0; i < 4 && token; i++) {
        if (i == 1) strcpy(status, token);
        else if (i == 3) *direction = atof(token);
        token = strtok(NULL, ":");
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int get_max_speed(float *max_speed)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("GET_CAR_SPEED_MAX");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    char *token = strtok(response, ":");
    for (int i = 0; i < 4 && token; i++) {
        if (i == 1) strcpy(status, token);
        else if (i == 3) *max_speed = atof(token);
        token = strtok(NULL, ":");
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int get_min_speed(float *min_speed)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("GET_CAR_SPEED_MIN");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    char *token = strtok(response, ":");
    for (int i = 0; i < 4 && token; i++) {
        if (i == 1) strcpy(status, token);
        else if (i == 3) *min_speed = atof(token);
        token = strtok(NULL, ":");
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}