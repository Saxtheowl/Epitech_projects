/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Header file for my_radar air traffic control simulation
*/

#ifndef MY_RADAR_H
    #define MY_RADAR_H

    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <math.h>
    #include <string.h>
    #include <sys/stat.h>

    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define MAX_AIRCRAFTS 100
    #define MAX_TOWERS 50
    #define AIRCRAFT_SIZE 20
    #define FRAME_RATE 60

    typedef enum {
        AIRCRAFT_WAITING,
        AIRCRAFT_FLYING,
        AIRCRAFT_LANDED,
        AIRCRAFT_DESTROYED
    } aircraft_state_t;

    typedef struct aircraft_s {
        int id;
        sfVector2f start_pos;
        sfVector2f end_pos;
        sfVector2f current_pos;
        sfVector2f velocity;
        int speed;
        int delay;
        aircraft_state_t state;
        sfSprite *sprite;
        sfRectangleShape *hitbox;
        sfClock *spawn_clock;
        int active;
    } aircraft_t;

    typedef struct tower_s {
        int id;
        sfVector2f position;
        int radius;
        sfSprite *sprite;
        sfCircleShape *control_area;
        int active;
    } tower_t;

    typedef struct radar_s {
        sfRenderWindow *window;
        sfEvent event;
        aircraft_t aircrafts[MAX_AIRCRAFTS];
        tower_t towers[MAX_TOWERS];
        int aircraft_count;
        int tower_count;
        sfClock *game_clock;
        sfFont *font;
        sfText *timer_text;
        int show_hitboxes;
        int show_sprites;
        int simulation_running;
        sfTexture *aircraft_texture;
        sfTexture *tower_texture;
    } radar_t;

    int my_radar(char *script_path);
    void print_usage(void);
    radar_t *init_radar(void);
    void cleanup_radar(radar_t *radar);
    int load_script(radar_t *radar, char *script_path);
    void update_simulation(radar_t *radar);
    void render_simulation(radar_t *radar);
    void handle_events(radar_t *radar);
    void update_aircrafts(radar_t *radar);
    void check_collisions(radar_t *radar);
    int check_aircraft_collision(aircraft_t *a1, aircraft_t *a2);
    int is_in_control_area(aircraft_t *aircraft, tower_t *tower);
    void spawn_aircraft(aircraft_t *aircraft);
    void update_timer(radar_t *radar);
    int parse_aircraft_line(char *line, aircraft_t *aircraft, int id);
    int parse_tower_line(char *line, tower_t *tower, int id);
    sfTexture *create_aircraft_texture(void);
    sfTexture *create_tower_texture(void);
    float calculate_distance(sfVector2f pos1, sfVector2f pos2);

#endif