#include "ai.h"

void make_decision(sensor_analysis_t *analysis, car_state_t *state)
{
    (void)state;
    float speed = 0.5f;
    float steering = 0.0f;

    // If obstacle ahead, decide how to react
    if (analysis->obstacle_detected) {
        // Very close obstacle - stop or reverse
        if (analysis->forward_distance < 300.0f) {
            set_car_forward(0.0f);
            
            // Try to turn away from obstacle
            if (analysis->left_distance > analysis->right_distance) {
                steering = -0.8f; // Turn left
            } else {
                steering = 0.8f; // Turn right
            }
            set_wheels_direction(steering);
            return;
        }
        
        // Moderate distance - slow down and steer
        speed = 0.2f;
        
        // Determine steering based on available space
        if (analysis->left_distance > analysis->right_distance) {
            if (analysis->left_distance > TURN_THRESHOLD) {
                steering = -0.6f; // Turn left
            } else {
                steering = -0.3f; // Slight left turn
            }
        } else {
            if (analysis->right_distance > TURN_THRESHOLD) {
                steering = 0.6f; // Turn right
            } else {
                steering = 0.3f; // Slight right turn
            }
        }
    } else {
        // No immediate obstacle - drive forward
        speed = 0.7f;
        
        // Keep car centered by subtle steering corrections
        float left_right_diff = analysis->left_distance - analysis->right_distance;
        
        if (fabs(left_right_diff) > 500.0f) {
            if (left_right_diff > 0) {
                steering = -0.1f; // Slight left to center
            } else {
                steering = 0.1f; // Slight right to center
            }
        }
    }

    // Apply decisions
    set_car_forward(speed);
    set_wheels_direction(steering);
}

void autonomous_drive(void)
{
    car_state_t car_state = {0};
    sensor_analysis_t sensor_analysis = {0};
    int consecutive_dead_ends = 0;
    int max_iterations = 10000;
    int iteration = 0;

    car_state.simulation_running = 1;
    
    while (car_state.simulation_running && iteration < max_iterations) {
        // Get sensor data
        if (!get_lidar_info(car_state.lidar_data)) {
            break;
        }

        // Analyze sensor data
        analyze_sensors(car_state.lidar_data, &sensor_analysis);

        // Check for dead end (all directions blocked)
        if (sensor_analysis.forward_distance < 900.0f &&
            sensor_analysis.left_distance < 900.0f &&
            sensor_analysis.right_distance < 900.0f) {
            consecutive_dead_ends++;
            
            // If stuck in dead end for too long, stop
            if (consecutive_dead_ends > 10) {
                set_car_forward(0.0f);
                break;
            }
            
            // Try to back out of dead end
            set_car_backward(0.3f);
            if (sensor_analysis.left_distance > sensor_analysis.right_distance) {
                set_wheels_direction(-0.5f);
            } else {
                set_wheels_direction(0.5f);
            }
        } else {
            consecutive_dead_ends = 0;
            // Make normal driving decision
            make_decision(&sensor_analysis, &car_state);
        }

        // Small delay to prevent overwhelming the simulator
        usleep(50000); // 50ms delay
        iteration++;
    }
}

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

void cleanup_and_exit(int exit_code)
{
    stop_simulation();
    exit(exit_code);
}