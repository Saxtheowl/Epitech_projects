/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Movement system implementation
*/

#include "Systems.hpp"
#include <typeindex>

void Systems::MovementSystem::update(ECS::Registry& registry, float deltaTime)
{
    auto entities = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Velocity))
    });

    for (auto entity : entities) {
        auto* position = registry.getComponent<Components::Position>(entity);
        auto* velocity = registry.getComponent<Components::Velocity>(entity);

        if (position && velocity) {
            position->x += velocity->x * deltaTime;
            position->y += velocity->y * deltaTime;

            // Mark for network sync if needed
            if (registry.hasComponent<Components::NetworkSync>(entity)) {
                auto* netSync = registry.getComponent<Components::NetworkSync>(entity);
                if (netSync) {
                    netSync->needsUpdate = true;
                }
            }
        }
    }
}