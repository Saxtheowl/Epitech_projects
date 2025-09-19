/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for game modules
*/

#pragma once

#include "IDisplayModule.hpp"
#include <memory>
#include <string>

namespace arcade {
    enum class GameState {
        MENU,
        PLAYING,
        PAUSED,
        GAME_OVER,
        WIN
    };

    struct GameInfo {
        std::string name;
        int score;
        int highScore;
        int level;
        GameState state;

        GameInfo() : name("Unknown"), score(0), highScore(0), level(1), state(GameState::MENU) {}
    };

    class IGameModule {
    public:
        virtual ~IGameModule() = default;

        virtual bool init() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void handleInput(Key key) = 0;
        virtual void render(IDisplayModule &display) = 0;
        virtual void reset() = 0;

        virtual GameInfo getGameInfo() const = 0;
        virtual GameState getGameState() const = 0;
        virtual std::string getName() const = 0;
        virtual bool isGameOver() const = 0;
        virtual int getScore() const = 0;
    };
}