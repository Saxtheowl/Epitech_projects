/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** Communication protocol with n4s API
*/

#include "ai.h"

int send_command(const char *command)
{
    printf("%s\n", command);
    fflush(stdout);
    return 0;
}

int read_response(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }
    
    // Remove trailing newline
    buffer[strcspn(buffer, "\n")] = '\0';
    
    return 0;
}

int parse_response(const char *response, int *value_id, char *status, char *code_str, char *additional_info)
{
    char *token;
    char *response_copy = strdup(response);
    int field_count = 0;
    
    if (!response_copy) {
        return -1;
    }
    
    token = strtok(response_copy, ":");
    while (token && field_count < 4) {
        switch (field_count) {
        case 0:
            *value_id = atoi(token);
            break;
        case 1:
            strcpy(status, token);
            break;
        case 2:
            strcpy(code_str, token);
            break;
        case 3:
            strcpy(additional_info, token);
            break;
        }
        token = strtok(NULL, ":");
        field_count++;
    }
    
    free(response_copy);
    return field_count >= 3 ? 0 : -1;
}

int start_simulation(void)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("START_SIMULATION");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    if (strcmp(status, "OK") != 0) {
        debug_log("Failed to start simulation: %s", code_str);
        return -1;
    }
    
    debug_log("Simulation started successfully");
    return 0;
}

int stop_simulation(void)
{
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    send_command("STOP_SIMULATION");
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    if (strcmp(status, "OK") != 0) {
        debug_log("Failed to stop simulation: %s", code_str);
        return -1;
    }
    
    debug_log("Simulation stopped successfully");
    return 0;
}

int cycle_wait(int cycles)
{
    char command[COMMAND_BUFFER_SIZE];
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    snprintf(command, sizeof(command), "CYCLE_WAIT:%d", cycles);
    send_command(command);
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int car_forward(float power)
{
    char command[COMMAND_BUFFER_SIZE];
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    // Clamp power to valid range [0, 1]
    if (power < 0.0) power = 0.0;
    if (power > 1.0) power = 1.0;
    
    snprintf(command, sizeof(command), "CAR_FORWARD:%.3f", power);
    send_command(command);
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int car_backwards(float power)
{
    char command[COMMAND_BUFFER_SIZE];
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    // Clamp power to valid range [0, 1]
    if (power < 0.0) power = 0.0;
    if (power > 1.0) power = 1.0;
    
    snprintf(command, sizeof(command), "CAR_BACKWARDS:%.3f", power);
    send_command(command);
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}

int set_wheels_direction(float direction)
{
    char command[COMMAND_BUFFER_SIZE];
    char response[RESPONSE_BUFFER_SIZE];
    int value_id;
    char status[64], code_str[128], additional_info[256];
    
    // Clamp direction to valid range [-1, 1]
    if (direction < -1.0) direction = -1.0;
    if (direction > 1.0) direction = 1.0;
    
    snprintf(command, sizeof(command), "WHEELS_DIR:%.3f", direction);
    send_command(command);
    
    if (read_response(response, sizeof(response)) != 0) {
        return -1;
    }
    
    if (parse_response(response, &value_id, status, code_str, additional_info) != 0) {
        return -1;
    }
    
    return strcmp(status, "OK") == 0 ? 0 : -1;
}