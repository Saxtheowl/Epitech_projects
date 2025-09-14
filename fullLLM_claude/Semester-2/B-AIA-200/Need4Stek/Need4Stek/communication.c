#include "ai.h"

void send_command(const char *command)
{
    printf("%s\n", command);
    fflush(stdout);
}

char *read_response(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1) {
        if (line)
            free(line);
        return NULL;
    }

    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    
    return line;
}

int parse_response(char *response, char *status, float *data, int *data_count)
{
    char *token;
    char *saveptr;
    int field = 0;
    int value_id = 0;

    if (!response || !status)
        return -1;

    *data_count = 0;
    token = strtok_r(response, ":", &saveptr);
    
    while (token) {
        switch (field) {
            case 0: // VALUE_ID
                value_id = atoi(token);
                break;
            case 1: // STATUS
                strcpy(status, token);
                break;
            case 2: // CODE_STR
                break;
            default: // Data fields
                if (data && *data_count < LIDAR_COUNT) {
                    if (strcmp(token, "No further info") != 0 && 
                        strstr(token, "Cleared") == NULL &&
                        strstr(token, "CP") == NULL &&
                        strstr(token, "Lap") == NULL &&
                        strstr(token, "Track") == NULL) {
                        data[*data_count] = atof(token);
                        (*data_count)++;
                    }
                }
                break;
        }
        field++;
        token = strtok_r(NULL, ":", &saveptr);
    }

    return value_id;
}

void start_simulation(void)
{
    char *response;
    char status[64];

    send_command("START_SIMULATION");
    response = read_response();
    if (response) {
        parse_response(response, status, NULL, NULL);
        free(response);
    }
}

void stop_simulation(void)
{
    char *response;
    char status[64];

    send_command("STOP_SIMULATION");
    response = read_response();
    if (response) {
        parse_response(response, status, NULL, NULL);
        free(response);
    }
}

void set_car_forward(float speed)
{
    char command[64];
    char *response;
    char status[64];

    speed = clamp(speed, SPEED_MIN, SPEED_MAX);
    snprintf(command, sizeof(command), "CAR_FORWARD:%.2f", speed);
    send_command(command);
    
    response = read_response();
    if (response) {
        parse_response(response, status, NULL, NULL);
        free(response);
    }
}

void set_car_backward(float speed)
{
    char command[64];
    char *response;
    char status[64];

    speed = clamp(speed, SPEED_MIN, SPEED_MAX);
    snprintf(command, sizeof(command), "CAR_BACKWARDS:%.2f", speed);
    send_command(command);
    
    response = read_response();
    if (response) {
        parse_response(response, status, NULL, NULL);
        free(response);
    }
}

void set_wheels_direction(float direction)
{
    char command[64];
    char *response;
    char status[64];

    direction = clamp(direction, TURN_MIN, TURN_MAX);
    snprintf(command, sizeof(command), "WHEELS_DIR:%.2f", direction);
    send_command(command);
    
    response = read_response();
    if (response) {
        parse_response(response, status, NULL, NULL);
        free(response);
    }
}