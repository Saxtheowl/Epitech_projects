/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Nibbler (Snake) game implementation
*/

#pragma once

#include "core/IGameModule.hpp"
#include <vector>
#include <random>

namespace arcade {
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct SnakeSegment {
        Position position;
        SnakeSegment(int x = 0, int y = 0) : position(x, y) {}
    };

    class NibblerGame : public IGameModule {
    public:
        NibblerGame();
        ~NibblerGame() override = default;

        bool init() override;
        void update(float deltaTime) override;
        void handleInput(Key key) override;
        void render(IDisplayModule &display) override;
        void reset() override;

        GameInfo getGameInfo() const override;
        GameState getGameState() const override;
        std::string getName() const override;
        bool isGameOver() const override;
        int getScore() const override;

    private:
        void initializeGame();
        void moveSnake();
        void generateFood();
        bool checkCollision();
        bool isValidPosition(const Position &pos);
        void growSnake();

        static const int BOARD_WIDTH = 40;
        static const int BOARD_HEIGHT = 20;
        static const int START_LENGTH = 4;

        std::vector<SnakeSegment> _snake;
        Position _food;
        Direction _direction;
        Direction _nextDirection;

        GameState _gameState;
        int _score;
        float _moveTimer;
        float _moveInterval;

        std::random_device _randomDevice;
        std::mt19937 _generator;
        std::uniform_int_distribution<int> _xDistribution;
        std::uniform_int_distribution<int> _yDistribution;
    };
}

extern "C" {
    arcade::IGameModule* createGame();
    void destroyGame(arcade::IGameModule* module);
}