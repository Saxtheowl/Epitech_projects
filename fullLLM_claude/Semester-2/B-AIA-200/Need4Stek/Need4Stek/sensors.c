#include "ai.h"

int get_lidar_info(float *lidar_data)
{
    char *response;
    char status[64];
    int data_count = 0;

    send_command("GET_INFO_LIDAR");
    response = read_response();
    
    if (response) {
        parse_response(response, status, lidar_data, &data_count);
        free(response);
        
        if (strcmp(status, "OK") == 0 && data_count == LIDAR_COUNT) {
            return 1;
        }
    }
    return 0;
}

float get_current_speed(void)
{
    char *response;
    char status[64];
    float speed_data[1];
    int data_count = 0;

    send_command("GET_CURRENT_SPEED");
    response = read_response();
    
    if (response) {
        parse_response(response, status, speed_data, &data_count);
        free(response);
        
        if (strcmp(status, "OK") == 0 && data_count > 0) {
            return speed_data[0];
        }
    }
    return 0.0f;
}

float get_current_wheels(void)
{
    char *response;
    char status[64];
    float wheel_data[1];
    int data_count = 0;

    send_command("GET_CURRENT_WHEELS");
    response = read_response();
    
    if (response) {
        parse_response(response, status, wheel_data, &data_count);
        free(response);
        
        if (strcmp(status, "OK") == 0 && data_count > 0) {
            return wheel_data[0];
        }
    }
    return 0.0f;
}

void analyze_sensors(float *lidar_data, sensor_analysis_t *analysis)
{
    int i;
    float front_sector_sum = 0.0f;
    float left_sector_sum = 0.0f;
    float right_sector_sum = 0.0f;
    int front_count = 0;
    int left_count = 0;
    int right_count = 0;

    // Reset analysis
    analysis->forward_distance = MAX_LIDAR_RANGE;
    analysis->left_distance = MAX_LIDAR_RANGE;
    analysis->right_distance = MAX_LIDAR_RANGE;
    analysis->obstacle_detected = 0;

    // Analyze LIDAR data in sectors
    for (i = 0; i < LIDAR_COUNT; i++) {
        float angle = (i * 360.0f / LIDAR_COUNT) - 180.0f; // -180 to 180 degrees
        float distance = lidar_data[i];

        // Front sector (-30 to 30 degrees)
        if (angle >= -30.0f && angle <= 30.0f) {
            front_sector_sum += distance;
            front_count++;
            if (distance < analysis->forward_distance) {
                analysis->forward_distance = distance;
            }
        }
        // Left sector (30 to 150 degrees)
        else if (angle > 30.0f && angle <= 150.0f) {
            left_sector_sum += distance;
            left_count++;
        }
        // Right sector (-150 to -30 degrees)
        else if (angle >= -150.0f && angle < -30.0f) {
            right_sector_sum += distance;
            right_count++;
        }
    }

    // Calculate average distances
    if (left_count > 0) {
        analysis->left_distance = left_sector_sum / left_count;
    }
    if (right_count > 0) {
        analysis->right_distance = right_sector_sum / right_count;
    }

    // Check for obstacles
    if (analysis->forward_distance < SAFE_DISTANCE) {
        analysis->obstacle_detected = 1;
    }
}