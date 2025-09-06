/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision system implementation
*/

#include "Systems.hpp"
#include <typeindex>
#include <cmath>

bool Systems::CollisionSystem::checkCollision(
    const Components::Position& pos1, const Components::Collision& col1,
    const Components::Position& pos2, const Components::Collision& col2)
{
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    return distance < (col1.radius + col2.radius);
}

void Systems::CollisionSystem::update(ECS::Registry& registry, float deltaTime)
{
    auto entities = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Collision))
    });

    // Check collisions between bullets and enemies
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto entity1 = entities[i];
            auto entity2 = entities[j];

            auto* pos1 = registry.getComponent<Components::Position>(entity1);
            auto* col1 = registry.getComponent<Components::Collision>(entity1);
            auto* pos2 = registry.getComponent<Components::Position>(entity2);
            auto* col2 = registry.getComponent<Components::Collision>(entity2);

            if (pos1 && col1 && pos2 && col2) {
                if (checkCollision(*pos1, *col1, *pos2, *col2)) {
                    bool isBullet1 = registry.hasComponent<Components::Bullet>(entity1);
                    bool isBullet2 = registry.hasComponent<Components::Bullet>(entity2);
                    bool isEnemy1 = registry.hasComponent<Components::Enemy>(entity1);
                    bool isEnemy2 = registry.hasComponent<Components::Enemy>(entity2);
                    bool isPlayer1 = registry.hasComponent<Components::Player>(entity1);
                    bool isPlayer2 = registry.hasComponent<Components::Player>(entity2);

                    // Bullet vs Enemy collision
                    if ((isBullet1 && isEnemy2) || (isBullet2 && isEnemy1)) {
                        auto bulletEntity = isBullet1 ? entity1 : entity2;
                        auto enemyEntity = isBullet1 ? entity2 : entity1;

                        auto* bullet = registry.getComponent<Components::Bullet>(bulletEntity);
                        auto* health = registry.getComponent<Components::Health>(enemyEntity);

                        if (bullet && health) {
                            health->current -= bullet->damage;
                            registry.destroyEntity(bulletEntity);

                            if (health->current <= 0) {
                                registry.destroyEntity(enemyEntity);
                            }
                        }
                    }
                    
                    // Player vs Enemy collision
                    if ((isPlayer1 && isEnemy2) || (isPlayer2 && isEnemy1)) {
                        auto playerEntity = isPlayer1 ? entity1 : entity2;
                        auto enemyEntity = isPlayer1 ? entity2 : entity1;

                        auto* health = registry.getComponent<Components::Health>(playerEntity);
                        if (health) {
                            health->current -= 20;
                            registry.destroyEntity(enemyEntity);

                            if (health->current <= 0) {
                                // Player died - respawn logic would go here
                                health->current = health->maximum;
                                auto* pos = registry.getComponent<Components::Position>(playerEntity);
                                if (pos) {
                                    pos->x = 50.0f;
                                    pos->y = 300.0f;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}