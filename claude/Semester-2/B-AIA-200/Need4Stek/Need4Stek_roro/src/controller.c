/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Main AI controller and simulation loop
*/

#include "ai.h"

int initialize_car(ai_context_t *context)
{
    // Initialize context
    memset(context, 0, sizeof(ai_context_t));
    context->state = STATE_STARTING;
    context->simulation_running = 0;
    
    // Get car specifications
    if (get_max_speed(&context->car.max_speed) != 0) {
        debug_log("Warning: Could not get max speed, using default");
        context->car.max_speed = 1.0;
    }
    
    if (get_min_speed(&context->car.min_speed) != 0) {
        debug_log("Warning: Could not get min speed, using default");
        context->car.min_speed = 0.0;
    }
    
    debug_log("Car initialized - Max speed: %.3f, Min speed: %.3f", 
              context->car.max_speed, context->car.min_speed);
    
    return 0;
}

void run_ai_controller(void)
{
    ai_context_t context;
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[512];
    int running = 1;
    
    debug_log("Initializing AI controller...");
    
    if (initialize_car(&context) != 0) {
        debug_log("Failed to initialize car");
        return;
    }
    
    // Start simulation
    if (start_simulation() != 0) {
        debug_log("Failed to start simulation");
        return;
    }
    
    context.simulation_running = 1;
    context.state = STATE_DRIVING;
    
    debug_log("Starting main AI loop...");
    
    while (running) {
        // Get LIDAR data
        if (get_lidar_data(&context.lidar) != 0) {
            debug_log("Failed to get LIDAR data, continuing...");
            cycle_wait(1);
            continue;
        }
        
        // Update AI state based on sensor data
        update_ai_state(&context);
        
        // Execute behavior based on current state
        switch (context.state) {
        case STATE_DRIVING:
            drive_straight(&context);
            break;
        case STATE_TURNING:
            navigate_turn(&context);
            break;
        case STATE_EMERGENCY_STOP:
            emergency_stop(&context);
            break;
        case STATE_FINISHED:
            debug_log("Track completed, stopping...");
            running = 0;
            break;
        default:
            debug_log("Unknown state, defaulting to driving");
            context.state = STATE_DRIVING;
            break;
        }
        
        // Wait for next cycle
        if (cycle_wait(1) != 0) {
            // Check if we got a response with checkpoint info
            if (read_response(response, sizeof(response)) == 0) {
                if (parse_response(response, &value_id, status, code_str, additional_info) == 0) {
                    // Check for checkpoint/lap completion
                    if (is_checkpoint_cleared(additional_info)) {
                        context.checkpoint_count++;
                        debug_log("Checkpoint cleared! Total: %d", context.checkpoint_count);
                    }
                    
                    if (is_lap_completed(additional_info)) {
                        context.lap_count++;
                        debug_log("Lap completed! Total: %d", context.lap_count);
                    }
                    
                    if (is_track_completed(additional_info)) {
                        debug_log("Track completed successfully!");
                        context.state = STATE_FINISHED;
                    }
                }
            }
        }
        
        // Safety check - if we're stuck for too long, try different approach
        static int stuck_counter = 0;
        if (context.lidar.front_distance < MIN_SAFE_DISTANCE * 2) {
            stuck_counter++;
            if (stuck_counter > 50) {  // Stuck for 50 cycles
                debug_log("Seems stuck, trying emergency maneuver");
                context.state = STATE_EMERGENCY_STOP;
                stuck_counter = 0;
            }
        } else {
            stuck_counter = 0;
        }
    }
    
    cleanup_ai(&context);
}

void cleanup_ai(ai_context_t *context)
{
    if (context->simulation_running) {
        debug_log("Stopping simulation...");
        car_forward(0.0);  // Stop the car
        stop_simulation();
        context->simulation_running = 0;
    }
    
    debug_log("AI controller cleaned up");
}