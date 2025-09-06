/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Enemy system implementation
*/

#include "Systems.hpp"
#include <typeindex>
#include <random>

void Systems::EnemySystem::update(ECS::Registry& registry, float deltaTime)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    auto enemies = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Enemy))
    });

    // Update existing enemies
    for (auto entity : enemies) {
        auto* enemy = registry.getComponent<Components::Enemy>(entity);
        auto* position = registry.getComponent<Components::Position>(entity);

        if (enemy && position) {
            enemy->shootTimer += deltaTime;

            // Simple AI: shoot every 2 seconds if in range
            if (enemy->shootTimer >= 2.0f) {
                enemy->shootTimer = 0.0f;

                // Create bullet
                auto bulletEntity = registry.createEntity();
                registry.addComponent(bulletEntity, Components::Position(position->x - 20.0f, position->y));
                registry.addComponent(bulletEntity, Components::Velocity(-200.0f, 0.0f));
                registry.addComponent(bulletEntity, Components::Collision(4.0f, true));
                registry.addComponent(bulletEntity, Components::Bullet(10, -1));
                
                // Add sprite for bullet (would load from assets in real implementation)
                Components::Sprite bulletSprite;
                bulletSprite.colorR = 255;
                bulletSprite.colorG = 0;
                bulletSprite.colorB = 0;
                bulletSprite.scaleX = 4.0f;
                bulletSprite.scaleY = 2.0f;
                registry.addComponent(bulletEntity, bulletSprite);
            }
        }
    }

    // Spawn new enemies randomly
    static float spawnTimer = 0.0f;
    spawnTimer += deltaTime;

    if (spawnTimer >= 3.0f && dis(gen) < 0.3f) {
        spawnTimer = 0.0f;

        auto enemyEntity = registry.createEntity();
        float yPos = 50.0f + dis(gen) * 500.0f;
        
        registry.addComponent(enemyEntity, Components::Position(800.0f, yPos));
        registry.addComponent(enemyEntity, Components::Velocity(-50.0f, 0.0f));
        registry.addComponent(enemyEntity, Components::Enemy(0));
        registry.addComponent(enemyEntity, Components::Health(30));
        registry.addComponent(enemyEntity, Components::Collision(16.0f, true));
        registry.addComponent(enemyEntity, Components::NetworkSync());

        // Add sprite (would load proper enemy sprite in real implementation)
        Components::Sprite enemySprite;
        enemySprite.colorR = 0;
        enemySprite.colorG = 255;
        enemySprite.colorB = 0;
        enemySprite.scaleX = 32.0f;
        enemySprite.scaleY = 32.0f;
        registry.addComponent(enemyEntity, enemySprite);
    }
}