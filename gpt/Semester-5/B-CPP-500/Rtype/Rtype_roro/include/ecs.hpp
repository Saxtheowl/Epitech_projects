/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Minimal ECS stubs
*/

#ifndef ECS_HPP
#define ECS_HPP

#include <vector>

struct Position { float x; float y; };
struct Velocity { float vx; float vy; };

struct Entity {
    int id;
};

struct World {
    std::vector<Entity> entities;
    std::vector<Position> positions;
    std::vector<Velocity> velocities;
};

void world_tick(World &w, float dt);

#endif /* ECS_HPP */

