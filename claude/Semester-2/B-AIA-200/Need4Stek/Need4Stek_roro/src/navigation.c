/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Navigation AI algorithms for autonomous driving
*/

#include "ai.h"

void update_ai_state(ai_context_t *context)
{
    lidar_data_t *lidar = &context->lidar;
    
    if (!lidar->has_data) {
        return;
    }
    
    // Check for emergency stop conditions
    if (lidar->front_distance < MIN_SAFE_DISTANCE) {
        context->state = STATE_EMERGENCY_STOP;
        debug_log("EMERGENCY STOP: Front distance %.1f < %.1f", 
                  lidar->front_distance, MIN_SAFE_DISTANCE);
        return;
    }
    
    // Check if we need to turn
    if (lidar->front_distance < TURN_THRESHOLD) {
        if (context->state != STATE_TURNING) {
            context->state = STATE_TURNING;
            debug_log("STATE: Turning (front distance: %.1f)", lidar->front_distance);
        }
        return;
    }
    
    // Normal driving
    if (context->state != STATE_DRIVING) {
        context->state = STATE_DRIVING;
        debug_log("STATE: Driving normally");
    }
}

void drive_straight(ai_context_t *context)
{
    float optimal_speed = calculate_optimal_speed(&context->lidar);
    
    // Minor steering corrections to stay centered
    float direction = 0.0;
    
    // Use side distances to keep centered
    float left_diff = context->lidar.left_distance;
    float right_diff = context->lidar.right_distance;
    
    // Gentle steering correction
    if (left_diff < right_diff - 100.0) {
        direction = 0.1;  // Slight right turn
    } else if (right_diff < left_diff - 100.0) {
        direction = -0.1; // Slight left turn
    }
    
    set_wheels_direction(direction);
    car_forward(optimal_speed);
    
    debug_log("Driving straight: speed=%.3f, direction=%.3f", optimal_speed, direction);
}

void navigate_turn(ai_context_t *context)
{
    float safe_direction = calculate_safe_direction(&context->lidar);
    float turn_speed = TURN_SPEED;
    
    // Adjust turn speed based on available space
    if (context->lidar.front_distance < MIN_SAFE_DISTANCE * 1.5) {
        turn_speed = MIN_SPEED;
    }
    
    set_wheels_direction(safe_direction);
    car_forward(turn_speed);
    
    debug_log("Navigating turn: speed=%.3f, direction=%.3f", turn_speed, safe_direction);
}

void emergency_stop(ai_context_t *context)
{
    // Stop the car
    car_forward(0.0);
    set_wheels_direction(0.0);
    
    debug_log("EMERGENCY STOP ACTIVATED");
    
    // Wait a bit then try to back up slightly
    cycle_wait(10);
    
    // Check if we can back up safely
    float back_distance = 0.0;
    for (int i = 28; i < LIDAR_POINTS; i++) {
        back_distance += context->lidar.distances[i];
    }
    back_distance /= 4.0;
    
    if (back_distance > MIN_SAFE_DISTANCE) {
        debug_log("Backing up to create space...");
        car_backwards(0.2);
        cycle_wait(20);
        car_forward(0.0);
    }
    
    // Try to find a way out
    context->state = STATE_TURNING;
}

float calculate_optimal_speed(const lidar_data_t *lidar)
{
    float speed = MAX_SPEED;
    
    // Reduce speed based on front distance
    if (lidar->front_distance < SAFE_DISTANCE * 2) {
        speed = MAX_SPEED * (lidar->front_distance / (SAFE_DISTANCE * 2));
    }
    
    // Ensure minimum speed
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }
    
    // Reduce speed in narrow passages
    float min_side_distance = fmin(lidar->left_distance, lidar->right_distance);
    if (min_side_distance < SAFE_DISTANCE) {
        speed *= 0.7;
    }
    
    return speed;
}