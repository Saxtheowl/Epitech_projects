/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game components definitions
*/

#pragma once

#include <string>
#include <cstdint>

#ifdef HAS_SFML
#include <SFML/Graphics.hpp>
#endif

namespace Components {
    struct Position {
        float x, y;
        Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    };

    struct Velocity {
        float x, y;
        Velocity(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    };

    struct Sprite {
        std::string texturePath;
        float scaleX, scaleY;
        uint8_t colorR, colorG, colorB, colorA;
        
#ifdef HAS_SFML
        sf::Texture texture;
        sf::Sprite sprite;
#endif
        
        Sprite(const std::string& path = "") 
            : texturePath(path), scaleX(1.0f), scaleY(1.0f), 
              colorR(255), colorG(255), colorB(255), colorA(255) {
#ifdef HAS_SFML
            if (!path.empty()) {
                loadTexture(path);
            }
#endif
        }
        
#ifdef HAS_SFML
        void loadTexture(const std::string& path) {
            if (texture.loadFromFile(path)) {
                sprite.setTexture(texture);
                texturePath = path;
            }
        }
#endif
    };

    struct Health {
        int current;
        int maximum;
        
        Health(int max = 100) : current(max), maximum(max) {}
    };

    struct Player {
        int playerId;
        std::string name;
        
        Player(int id = 0, const std::string& playerName = "Player") 
            : playerId(id), name(playerName) {}
    };

    struct Enemy {
        int enemyType;
        float shootTimer;
        
        Enemy(int type = 0) : enemyType(type), shootTimer(0.0f) {}
    };

    struct Bullet {
        int damage;
        int owner;
        
        Bullet(int dmg = 10, int ownerId = -1) : damage(dmg), owner(ownerId) {}
    };

    struct NetworkSync {
        bool needsUpdate;
        float lastSyncTime;
        
        NetworkSync() : needsUpdate(true), lastSyncTime(0.0f) {}
    };

    struct Collision {
        float radius;
        bool solid;
        
        Collision(float r = 16.0f, bool s = true) : radius(r), solid(s) {}
    };
}