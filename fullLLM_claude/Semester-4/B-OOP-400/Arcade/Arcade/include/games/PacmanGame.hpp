/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Pacman game implementation
*/

#pragma once

#include "core/IGameModule.hpp"
#include <vector>
#include <random>

namespace arcade {
    enum class PacmanDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    enum class CellType {
        WALL,
        PACGUM,
        SUPER_PACGUM,
        EMPTY,
        GHOST_ZONE
    };

    struct Ghost {
        Position position;
        PacmanDirection direction;
        bool vulnerable;
        bool inGhostZone;
        float vulnerableTimer;

        Ghost(int x = 0, int y = 0) : position(x, y), direction(PacmanDirection::UP),
                                      vulnerable(false), inGhostZone(true), vulnerableTimer(0.0f) {}
    };

    class PacmanGame : public IGameModule {
    public:
        PacmanGame();
        ~PacmanGame() override = default;

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
        void initializeMap();
        void movePlayer();
        void moveGhosts();
        bool canMoveTo(const Position &pos) const;
        void eatPacgum(const Position &pos);
        void checkGhostCollisions();
        void makePacmanVulnerable();
        void updateVulnerability(float deltaTime);
        bool isMapComplete() const;

        static const int MAP_WIDTH = 25;
        static const int MAP_HEIGHT = 15;

        std::vector<std::vector<CellType>> _map;
        Position _pacmanPos;
        PacmanDirection _pacmanDirection;
        PacmanDirection _nextDirection;
        std::vector<Ghost> _ghosts;

        GameState _gameState;
        int _score;
        int _pacgumsLeft;
        float _moveTimer;
        float _moveInterval;
        float _vulnerabilityTimer;

        std::random_device _randomDevice;
        std::mt19937 _generator;
    };
}

extern "C" {
    arcade::IGameModule* createGame();
    void destroyGame(arcade::IGameModule* module);
}