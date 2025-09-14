/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Header file for MyRadar project
*/

#ifndef MY_RADAR_H_
    #define MY_RADAR_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    #include <string.h>
    #include <unistd.h>

    // Window constants
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define WINDOW_TITLE "MyRadar - Air Traffic Control"

    // Aircraft constants
    #define AIRCRAFT_HITBOX_SIZE 20
    #define MAX_AIRCRAFTS 100

    // Control tower constants
    #define MAX_TOWERS 50

    // Aircraft structure
    typedef struct aircraft_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfRectangleShape *hitbox;
        sfVector2f start_pos;
        sfVector2f end_pos;
        sfVector2f current_pos;
        sfVector2f velocity;
        float speed;
        int delay;
        int alive;
        int departed;
        sfClock *delay_clock;
    } aircraft_t;

    // Control tower structure
    typedef struct tower_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfCircleShape *control_area;
        sfVector2f position;
        float radius;
    } tower_t;

    // Simulation structure
    typedef struct simulation_s {
        sfRenderWindow *window;
        sfEvent event;
        sfClock *main_clock;
        sfText *timer_text;
        sfFont *font;
        aircraft_t *aircrafts;
        tower_t *towers;
        int nb_aircrafts;
        int nb_towers;
        int show_hitboxes;
        int show_sprites;
        float elapsed_time;
    } simulation_t;

    // Function prototypes
    // Main simulation functions
    int run_simulation(simulation_t *sim);
    int init_simulation(simulation_t *sim);
    void cleanup_simulation(simulation_t *sim);

    // Window functions
    int create_window(simulation_t *sim);
    void handle_events(simulation_t *sim);
    void render_simulation(simulation_t *sim);

    // Aircraft functions
    int init_aircrafts(simulation_t *sim);
    void update_aircrafts(simulation_t *sim);
    void draw_aircrafts(simulation_t *sim);
    int check_aircraft_collision(aircraft_t *a1, aircraft_t *a2);
    int check_aircraft_in_tower_area(aircraft_t *aircraft, tower_t *tower);

    // Tower functions
    int init_towers(simulation_t *sim);
    void draw_towers(simulation_t *sim);

    // Parser functions
    int parse_script_file(const char *filepath, simulation_t *sim);
    int parse_aircraft_line(char *line, aircraft_t *aircraft);
    int parse_tower_line(char *line, tower_t *tower);

    // Utility functions
    void display_help(void);
    int parse_arguments(int ac, char **av, char **script_path);
    float distance(sfVector2f a, sfVector2f b);
    sfVector2f normalize_vector(sfVector2f vec);

#endif /* MY_RADAR_H_ */