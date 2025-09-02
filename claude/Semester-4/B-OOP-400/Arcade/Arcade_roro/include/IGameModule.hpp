/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for game modules
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <vector>
#include <string>
#include <memory>
#include "IDisplayModule.hpp"

namespace arcade {
    enum class GameState {
        MENU = 0,
        PLAYING,
        PAUSED,
        GAME_OVER,
        WIN
    };

    struct GameObject {
        Vector2i position;
        char character;
        Color color;
        
        GameObject(const Vector2i &pos = {0, 0}, char ch = ' ', Color col = Color::WHITE)
            : position(pos), character(ch), color(col) {}
    };

    struct GameData {
        std::vector<GameObject> objects;
        int score;
        int lives;
        int level;
        GameState state;
        std::string statusText;
        
        GameData() : score(0), lives(3), level(1), state(GameState::MENU) {}
    };

    class IGameModule {
    public:
        virtual ~IGameModule() = default;

        // Game lifecycle
        virtual bool init() = 0;
        virtual void destroy() = 0;
        virtual void reset() = 0;

        // Game logic
        virtual void update(float deltaTime) = 0;
        virtual void handleInput(Key key) = 0;
        
        // Game state
        virtual const GameData &getGameData() const = 0;
        virtual GameState getGameState() const = 0;
        virtual bool isGameOver() const = 0;
        
        // Game info
        virtual std::string getName() const = 0;
        virtual int getScore() const = 0;
        virtual void setPlayerName(const std::string &name) = 0;
        virtual std::string getPlayerName() const = 0;

        // Map size for consistent rendering across graphics libs
        virtual Vector2i getMapSize() const = 0;
    };
}

// C-style factory functions for dynamic loading
extern "C" {
    arcade::IGameModule *createGameModule();
    void destroyGameModule(arcade::IGameModule *module);
}

#endif /* !IGAMEMODULE_HPP_ */