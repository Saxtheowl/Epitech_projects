/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Main entry point
*/

#include "../include/my_world.h"

int main(int argc, char **argv)
{
    world_t *world = init_world();
    
    if (!world)
        return 84;
    
    if (argc > 1) {
        if (load_map(world, argv[1]) != 0) {
            destroy_world(world);
            return 84;
        }
    } else {
        init_map(world, 32, 32);
        generate_default_map(world);
    }
    
    int result = run_world(world);
    
    destroy_world(world);
    return result;
}