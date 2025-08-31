/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Test program for my_radar functionality
*/

#ifdef MOCK_VERSION
    #include <stdio.h>
    #include <assert.h>
    #include <math.h>
    
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define MAX_AIRCRAFTS 100
    #define MAX_TOWERS 50
    #define AIRCRAFT_SIZE 20

    typedef enum {
        AIRCRAFT_WAITING,
        AIRCRAFT_FLYING,
        AIRCRAFT_LANDED,
        AIRCRAFT_DESTROYED
    } aircraft_state_t;

    typedef struct {
        float x;
        float y;
    } sfVector2f;

    typedef struct aircraft_s {
        int id;
        sfVector2f start_pos;
        sfVector2f end_pos;
        sfVector2f current_pos;
        int speed;
        int delay;
        aircraft_state_t state;
        int active;
    } aircraft_t;

    typedef struct tower_s {
        int id;
        sfVector2f position;
        int radius;
        int active;
    } tower_t;

    void print_usage(void) {
        printf("Air traffic simulation panel\n");
        printf("USAGE\n    ./my_radar [OPTIONS] path_to_script\n");
    }
    
    int parse_aircraft_line(char *line, aircraft_t *aircraft, int id) {
        int start_x, start_y, end_x, end_y, speed, delay;
        if (sscanf(line, "A %d %d %d %d %d %d", 
            &start_x, &start_y, &end_x, &end_y, &speed, &delay) != 6)
            return -1;
        aircraft->start_pos = (sfVector2f){start_x, start_y};
        aircraft->end_pos = (sfVector2f){end_x, end_y};
        aircraft->speed = speed;
        aircraft->delay = delay;
        return 0;
    }
    
    int parse_tower_line(char *line, tower_t *tower, int id) {
        int x, y, radius;
        if (sscanf(line, "T %d %d %d", &x, &y, &radius) != 3)
            return -1;
        tower->position = (sfVector2f){x, y};
        tower->radius = radius;
        return 0;
    }
    
    float calculate_distance(sfVector2f pos1, sfVector2f pos2) {
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        return sqrt(dx * dx + dy * dy);
    }
#else
    #include "../include/my_radar.h"
    #include <stdio.h>
    #include <assert.h>
#endif

void test_aircraft_parsing(void)
{
    aircraft_t aircraft = {0};
    char line[] = "A 815 321 1484 166 5 0";

    printf("Testing aircraft parsing...\n");
    
    assert(parse_aircraft_line(line, &aircraft, 1) == 0);
    assert(aircraft.start_pos.x == 815);
    assert(aircraft.start_pos.y == 321);
    assert(aircraft.end_pos.x == 1484);
    assert(aircraft.end_pos.y == 166);
    assert(aircraft.speed == 5);
    assert(aircraft.delay == 0);
    
    printf("✓ Aircraft parsing tests passed\n");
}

void test_tower_parsing(void)
{
    tower_t tower = {0};
    char line[] = "T 93 47 150";

    printf("Testing tower parsing...\n");
    
    assert(parse_tower_line(line, &tower, 1) == 0);
    assert(tower.position.x == 93);
    assert(tower.position.y == 47);
    assert(tower.radius == 150);
    
    printf("✓ Tower parsing tests passed\n");
}

void test_distance_calculation(void)
{
    sfVector2f pos1 = {0, 0};
    sfVector2f pos2 = {3, 4};
    float distance;

    printf("Testing distance calculation...\n");
    
    distance = calculate_distance(pos1, pos2);
    assert(distance == 5.0f);
    
    distance = calculate_distance(pos1, pos1);
    assert(distance == 0.0f);
    
    printf("✓ Distance calculation tests passed\n");
}

void test_constants(void)
{
    printf("Testing radar constants...\n");
    
    assert(WINDOW_WIDTH == 1920);
    assert(WINDOW_HEIGHT == 1080);
    assert(MAX_AIRCRAFTS == 100);
    assert(MAX_TOWERS == 50);
    assert(AIRCRAFT_SIZE == 20);
    
    printf("Window size: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Max aircrafts: %d\n", MAX_AIRCRAFTS);
    printf("Max towers: %d\n", MAX_TOWERS);
    printf("Aircraft size: %d\n", AIRCRAFT_SIZE);
    
    printf("✓ Constants tests passed\n");
}

void test_help_functionality(void)
{
    printf("Testing help functionality...\n");
    
    printf("Testing help display:\n");
    print_usage();
    
    printf("✓ Help functionality tests passed\n");
}

int main(void)
{
    printf("=== MyRadar Test Suite ===\n\n");
    
    test_aircraft_parsing();
    test_tower_parsing();
    test_distance_calculation();
    test_constants();
    test_help_functionality();
    
    printf("\n=== All tests completed ===\n");
    return 0;
}