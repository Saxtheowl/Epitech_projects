/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game systems definitions
*/

#pragma once

#include "ECS.hpp"
#include "Components.hpp"

#ifdef HAS_SFML
#include <SFML/Graphics.hpp>
#endif

namespace Systems {
    class MovementSystem : public ECS::ISystem {
    public:
        void update(ECS::Registry& registry, float deltaTime) override;
    };

    class RenderSystem : public ECS::ISystem {
    private:
#ifdef HAS_SFML
        sf::RenderWindow* window_;
#endif
        
    public:
#ifdef HAS_SFML
        RenderSystem(sf::RenderWindow* window) : window_(window) {}
#else
        RenderSystem(void* window = nullptr) {}
#endif
        void update(ECS::Registry& registry, float deltaTime) override;
    };

    class CollisionSystem : public ECS::ISystem {
    public:
        void update(ECS::Registry& registry, float deltaTime) override;
    private:
        bool checkCollision(const Components::Position& pos1, const Components::Collision& col1,
                           const Components::Position& pos2, const Components::Collision& col2);
    };

    class EnemySystem : public ECS::ISystem {
    public:
        void update(ECS::Registry& registry, float deltaTime) override;
    };

    class NetworkSystem : public ECS::ISystem {
    public:
        void update(ECS::Registry& registry, float deltaTime) override;
    };

    class CleanupSystem : public ECS::ISystem {
    public:
        void update(ECS::Registry& registry, float deltaTime) override;
    };
}