/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Nibbler/Snake game implementation
*/

#include "IGameModule.hpp"
#include <vector>
#include <random>
#include <algorithm>

namespace arcade {
    class NibblerGame : public IGameModule {
    private:
        GameData _gameData;
        std::string _playerName;
        
        // Game state
        std::vector<Vector2i> _snake;
        Vector2i _food;
        Vector2i _direction;
        Vector2i _mapSize;
        
        // Timing
        float _moveTimer;
        float _moveInterval;
        
        // Random
        std::mt19937 _rng;
        std::uniform_int_distribution<int> _distX;
        std::uniform_int_distribution<int> _distY;
        
        void generateFood() {
            do {
                _food.x = _distX(_rng);
                _food.y = _distY(_rng);
            } while (std::find(_snake.begin(), _snake.end(), _food) != _snake.end());
        }
        
        bool isWallCollision(const Vector2i &pos) const {
            return pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y;
        }
        
        bool isSelfCollision(const Vector2i &pos) const {
            return std::find(_snake.begin(), _snake.end() - 1, pos) != (_snake.end() - 1);
        }
        
        void updateGameObjects() {
            _gameData.objects.clear();
            
            // Add snake segments
            for (size_t i = 0; i < _snake.size(); ++i) {
                char character = (i == 0) ? 'O' : 'o'; // Head vs body
                Color color = (i == 0) ? Color::YELLOW : Color::GREEN;
                _gameData.objects.emplace_back(_snake[i], character, color);
            }
            
            // Add food
            _gameData.objects.emplace_back(_food, '*', Color::RED);
            
            // Add walls (border)
            for (int x = 0; x < _mapSize.x; ++x) {
                _gameData.objects.emplace_back(Vector2i(x, 0), '#', Color::WHITE);
                _gameData.objects.emplace_back(Vector2i(x, _mapSize.y - 1), '#', Color::WHITE);
            }
            for (int y = 1; y < _mapSize.y - 1; ++y) {
                _gameData.objects.emplace_back(Vector2i(0, y), '#', Color::WHITE);
                _gameData.objects.emplace_back(Vector2i(_mapSize.x - 1, y), '#', Color::WHITE);
            }
        }

    public:
        NibblerGame() : _playerName("Player"), _mapSize(40, 24), 
                       _moveTimer(0.0f), _moveInterval(0.2f),
                       _rng(std::random_device{}()),
                       _distX(1, _mapSize.x - 2), _distY(1, _mapSize.y - 2) {
            reset();
        }
        
        ~NibblerGame() {
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
            _gameData.statusText = "Use arrow keys to move. Eat food to grow!";
            
            // Initialize snake in the center
            _snake.clear();
            Vector2i center = {_mapSize.x / 2, _mapSize.y / 2};
            for (int i = 0; i < 4; ++i) {
                _snake.push_back({center.x - i, center.y});
            }
            
            _direction = {1, 0}; // Moving right
            _moveTimer = 0.0f;
            
            generateFood();
            updateGameObjects();
        }

        void update(float deltaTime) override {
            if (_gameData.state != GameState::PLAYING) return;
            
            _moveTimer += deltaTime;
            
            if (_moveTimer >= _moveInterval) {
                _moveTimer = 0.0f;
                
                // Move snake
                Vector2i newHead = _snake.front();
                newHead.x += _direction.x;
                newHead.y += _direction.y;
                
                // Check collisions
                if (isWallCollision(newHead) || isSelfCollision(newHead)) {
                    _gameData.lives--;
                    if (_gameData.lives <= 0) {
                        _gameData.state = GameState::GAME_OVER;
                        _gameData.statusText = "Game Over! Press R to restart or M for menu.";
                    } else {
                        _gameData.statusText = "Hit! " + std::to_string(_gameData.lives) + " lives left.";
                        reset(); // Reset position but keep score
                    }
                    return;
                }
                
                // Add new head
                _snake.insert(_snake.begin(), newHead);
                
                // Check food collision
                if (newHead.x == _food.x && newHead.y == _food.y) {
                    _gameData.score += 10;
                    generateFood();
                    
                    // Increase speed slightly
                    _moveInterval = std::max(0.05f, _moveInterval * 0.98f);
                    
                    _gameData.statusText = "Score: " + std::to_string(_gameData.score);
                } else {
                    // Remove tail if no food eaten
                    _snake.pop_back();
                }
                
                updateGameObjects();
            }
        }

        void handleInput(Key key) override {
            if (_gameData.state != GameState::PLAYING) return;
            
            Vector2i newDirection = _direction;
            
            switch (key) {
                case Key::UP:
                    if (_direction.y == 0) // Can't reverse
                        newDirection = {0, -1};
                    break;
                case Key::DOWN:
                    if (_direction.y == 0)
                        newDirection = {0, 1};
                    break;
                case Key::LEFT:
                    if (_direction.x == 0)
                        newDirection = {-1, 0};
                    break;
                case Key::RIGHT:
                    if (_direction.x == 0)
                        newDirection = {1, 0};
                    break;
                default:
                    break;
            }
            
            _direction = newDirection;
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
            return "Nibbler";
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
        return new arcade::NibblerGame();
    }

    void destroyGameModule(arcade::IGameModule *module) {
        delete module;
    }
}