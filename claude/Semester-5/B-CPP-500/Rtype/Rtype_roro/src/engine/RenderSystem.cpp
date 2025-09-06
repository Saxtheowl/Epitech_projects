/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Render system implementation
*/

#include "Systems.hpp"
#include <typeindex>

void Systems::RenderSystem::update(ECS::Registry& registry, float deltaTime)
{
#ifdef HAS_SFML
    if (!window_) {
        return;
    }

    auto entities = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Sprite))
    });

    window_->clear(sf::Color::Black);

    for (auto entity : entities) {
        auto* position = registry.getComponent<Components::Position>(entity);
        auto* sprite = registry.getComponent<Components::Sprite>(entity);

        if (position && sprite) {
            sprite->sprite.setPosition(position->x, position->y);
            sprite->sprite.setColor(sf::Color(sprite->colorR, sprite->colorG, sprite->colorB, sprite->colorA));
            sprite->sprite.setScale(sprite->scaleX, sprite->scaleY);
            window_->draw(sprite->sprite);
        }
    }

    window_->display();
#else
    // Headless rendering - just update positions for server
    auto entities = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Sprite))
    });
    
    // Server doesn't need to render, but we can log entity counts for debugging
    static float logTimer = 0.0f;
    logTimer += deltaTime;
    if (logTimer >= 5.0f) {
        logTimer = 0.0f;
        // Could log entity count here for server debugging
    }
#endif
}