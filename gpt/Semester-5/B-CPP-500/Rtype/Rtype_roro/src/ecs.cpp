/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Minimal ECS stub impl
*/

#include "ecs.hpp"

static void integrate(World &w, float dt)
{
    std::size_t i;

    for (i = 0; i < w.entities.size(); ++i) {
        if (i < w.positions.size() && i < w.velocities.size()) {
            w.positions[i].x += w.velocities[i].vx * dt;
            w.positions[i].y += w.velocities[i].vy * dt;
        }
    }
}

void world_tick(World &w, float dt)
{
    integrate(w, dt);
}

