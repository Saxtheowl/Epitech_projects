/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Pacman game implementation
*/

#include "IGameModule.hpp"
#include <vector>
#include <random>
#include <algorithm>

namespace arcade {
    class PacmanGame : public IGameModule {
    private:
        GameData _gameData;
        std::string _playerName;
        
        // Game state
        Vector2i _pacmanPos;
        Vector2i _direction;
        Vector2i _mapSize;
        
        // Game entities
        std::vector<std::vector<int>> _maze;
        std::vector<Vector2i> _ghosts;
        std::vector<Vector2i> _ghostDirections;
        int _dotsRemaining;
        
        // Timing
        float _moveTimer;
        float _moveInterval;
        float _ghostMoveTimer;
        float _ghostMoveInterval;
        
        // Random
        std::mt19937 _rng;
        
        // Maze layout (1 = wall, 0 = dot, 2 = empty, 3 = power pellet)
        void initializeMaze() {
            _maze = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
                {1,3,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,3,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1},
                {1,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1},
                {1,1,1,1,0,1,1,1,2,1,1,2,1,1,1,0,1,1,1,1},
                {1,1,1,1,0,1,2,2,2,2,2,2,2,2,1,0,1,1,1,1},
                {1,1,1,1,0,1,2,1,2,2,2,2,1,2,1,0,1,1,1,1},
                {2,2,2,2,0,2,2,1,2,2,2,2,1,2,2,0,2,2,2,2},
                {1,1,1,1,0,1,2,1,2,2,2,2,1,2,1,0,1,1,1,1},
                {1,1,1,1,0,1,2,2,2,2,2,2,2,2,1,0,1,1,1,1},
                {1,1,1,1,0,1,1,1,2,1,1,2,1,1,1,0,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
                {1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1},
                {1,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,1},
                {1,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1},
                {1,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1},
                {1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            };
            
            _mapSize = {20, 21};
            _dotsRemaining = 0;
            
            // Count dots
            for (int y = 0; y < _mapSize.y; ++y) {
                for (int x = 0; x < _mapSize.x; ++x) {
                    if (_maze[y][x] == 0 || _maze[y][x] == 3) {
                        _dotsRemaining++;
                    }
                }
            }
        }
        
        bool isValidMove(const Vector2i &pos) const {
            if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y) {
                return false;
            }
            return _maze[pos.y][pos.x] != 1; // Not a wall
        }
        
        void moveGhosts() {
            for (size_t i = 0; i < _ghosts.size(); ++i) {
                Vector2i newPos = _ghosts[i];
                newPos.x += _ghostDirections[i].x;
                newPos.y += _ghostDirections[i].y;
                
                if (!isValidMove(newPos)) {
                    // Change direction randomly
                    std::vector<Vector2i> possibleDirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
                    std::shuffle(possibleDirs.begin(), possibleDirs.end(), _rng);
                    
                    for (const auto &dir : possibleDirs) {
                        Vector2i testPos = _ghosts[i];
                        testPos.x += dir.x;
                        testPos.y += dir.y;
                        if (isValidMove(testPos)) {
                            _ghostDirections[i] = dir;
                            _ghosts[i] = testPos;
                            break;
                        }
                    }
                } else {
                    _ghosts[i] = newPos;
                }
            }
        }
        
        bool checkGhostCollision() const {
            for (const auto &ghost : _ghosts) {
                if (ghost.x == _pacmanPos.x && ghost.y == _pacmanPos.y) {
                    return true;
                }
            }
            return false;
        }
        
        void updateGameObjects() {
            _gameData.objects.clear();
            
            // Add maze walls and dots
            for (int y = 0; y < _mapSize.y; ++y) {
                for (int x = 0; x < _mapSize.x; ++x) {
                    Vector2i pos(x, y);
                    switch (_maze[y][x]) {
                        case 1: // Wall
                            _gameData.objects.emplace_back(pos, '#', Color::BLUE);
                            break;
                        case 0: // Dot
                            _gameData.objects.emplace_back(pos, '.', Color::YELLOW);
                            break;
                        case 3: // Power pellet
                            _gameData.objects.emplace_back(pos, 'O', Color::YELLOW);
                            break;
                    }
                }
            }
            
            // Add Pacman
            _gameData.objects.emplace_back(_pacmanPos, 'C', Color::YELLOW);
            
            // Add ghosts
            for (const auto &ghost : _ghosts) {
                _gameData.objects.emplace_back(ghost, 'M', Color::RED);
            }
        }

    public:
        PacmanGame() : _playerName("Player"), _moveTimer(0.0f), _moveInterval(0.3f),
                      _ghostMoveTimer(0.0f), _ghostMoveInterval(0.4f),
                      _rng(std::random_device{}()) {
            initializeMaze();
            reset();
        }
        
        ~PacmanGame() {
            destroy();
        }

        bool init() override {
            return true;
        }

        void destroy() override {
            // Cleanup if needed
        }

        void reset() override {
            _gameData.score = 0;
            _gameData.lives = 3;
            _gameData.level = 1;
            _gameData.state = GameState::PLAYING;
            _gameData.statusText = "Use arrow keys to move. Eat all dots!";
            
            // Reset maze
            initializeMaze();
            
            // Initialize Pacman position
            _pacmanPos = {9, 15};
            _direction = {0, 0};
            
            // Initialize ghosts
            _ghosts.clear();
            _ghostDirections.clear();
            _ghosts.push_back({9, 9});   // Ghost 1
            _ghosts.push_back({10, 9});  // Ghost 2
            _ghosts.push_back({9, 10});  // Ghost 3
            _ghosts.push_back({10, 10}); // Ghost 4
            
            for (int i = 0; i < 4; ++i) {
                _ghostDirections.push_back({1, 0}); // All move right initially
            }
            
            _moveTimer = 0.0f;
            _ghostMoveTimer = 0.0f;
            
            updateGameObjects();
        }

        void update(float deltaTime) override {
            if (_gameData.state != GameState::PLAYING) return;
            
            _moveTimer += deltaTime;
            _ghostMoveTimer += deltaTime;
            
            // Move Pacman
            if (_moveTimer >= _moveInterval && (_direction.x != 0 || _direction.y != 0)) {
                _moveTimer = 0.0f;
                
                Vector2i newPos = _pacmanPos;
                newPos.x += _direction.x;
                newPos.y += _direction.y;
                
                if (isValidMove(newPos)) {
                    _pacmanPos = newPos;
                    
                    // Check for dot/pellet consumption
                    if (_maze[_pacmanPos.y][_pacmanPos.x] == 0) {
                        _gameData.score += 10;
                        _maze[_pacmanPos.y][_pacmanPos.x] = 2; // Empty
                        _dotsRemaining--;
                    } else if (_maze[_pacmanPos.y][_pacmanPos.x] == 3) {
                        _gameData.score += 50;
                        _maze[_pacmanPos.y][_pacmanPos.x] = 2; // Empty
                        _dotsRemaining--;
                    }
                    
                    // Check win condition
                    if (_dotsRemaining == 0) {
                        _gameData.state = GameState::GAME_OVER;
                        _gameData.statusText = "You Win! Press R to restart or M for menu.";
                        return;
                    }
                    
                    _gameData.statusText = "Score: " + std::to_string(_gameData.score);
                }
            }
            
            // Move ghosts
            if (_ghostMoveTimer >= _ghostMoveInterval) {
                _ghostMoveTimer = 0.0f;
                moveGhosts();
            }
            
            // Check ghost collision
            if (checkGhostCollision()) {
                _gameData.lives--;
                if (_gameData.lives <= 0) {
                    _gameData.state = GameState::GAME_OVER;
                    _gameData.statusText = "Game Over! Press R to restart or M for menu.";
                } else {
                    _gameData.statusText = "Ghost caught you! " + std::to_string(_gameData.lives) + " lives left.";
                    // Reset Pacman position
                    _pacmanPos = {9, 15};
                    _direction = {0, 0};
                }
            }
            
            updateGameObjects();
        }

        void handleInput(Key key) override {
            if (_gameData.state != GameState::PLAYING) return;
            
            switch (key) {
                case Key::UP:
                    _direction = {0, -1};
                    break;
                case Key::DOWN:
                    _direction = {0, 1};
                    break;
                case Key::LEFT:
                    _direction = {-1, 0};
                    break;
                case Key::RIGHT:
                    _direction = {1, 0};
                    break;
                default:
                    break;
            }
        }

        const GameData &getGameData() const override {
            return _gameData;
        }

        GameState getGameState() const override {
            return _gameData.state;
        }

        bool isGameOver() const override {
            return _gameData.state == GameState::GAME_OVER;
        }

        std::string getName() const override {
            return "Pacman";
        }

        int getScore() const override {
            return _gameData.score;
        }

        void setPlayerName(const std::string &name) override {
            _playerName = name;
        }

        std::string getPlayerName() const override {
            return _playerName;
        }

        Vector2i getMapSize() const override {
            return _mapSize;
        }
    };
}

// C-style factory functions
extern "C" {
    arcade::IGameModule *createGameModule() {
        return new arcade::PacmanGame();
    }

    void destroyGameModule(arcade::IGameModule *module) {
        delete module;
    }
}