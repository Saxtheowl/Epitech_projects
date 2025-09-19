/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Nibbler (Snake) game implementation
*/

#include "games/NibblerGame.hpp"
#include <algorithm>

namespace arcade {
    NibblerGame::NibblerGame()
        : _direction(Direction::RIGHT), _nextDirection(Direction::RIGHT),
          _gameState(GameState::MENU), _score(0), _moveTimer(0.0f), _moveInterval(0.2f),
          _generator(_randomDevice()), _xDistribution(1, BOARD_WIDTH - 2),
          _yDistribution(1, BOARD_HEIGHT - 2) {
        initializeGame();
    }

    bool NibblerGame::init() {
        reset();
        return true;
    }

    void NibblerGame::initializeGame() {
        _snake.clear();

        // Initialize snake in the middle of the board
        int startX = BOARD_WIDTH / 2;
        int startY = BOARD_HEIGHT / 2;

        for (int i = 0; i < START_LENGTH; ++i) {
            _snake.emplace_back(startX - i, startY);
        }

        _direction = Direction::RIGHT;
        _nextDirection = Direction::RIGHT;
        _score = 0;
        _moveTimer = 0.0f;
        _gameState = GameState::PLAYING;

        generateFood();
    }

    void NibblerGame::update(float deltaTime) {
        if (_gameState != GameState::PLAYING) return;

        _moveTimer += deltaTime;

        if (_moveTimer >= _moveInterval) {
            _direction = _nextDirection;
            moveSnake();
            _moveTimer = 0.0f;

            if (checkCollision()) {
                _gameState = GameState::GAME_OVER;
            }
        }
    }

    void NibblerGame::handleInput(Key key) {
        if (_gameState == GameState::MENU || _gameState == GameState::GAME_OVER) {
            if (key == Key::SPACE || key == Key::ENTER) {
                reset();
                _gameState = GameState::PLAYING;
            }
            return;
        }

        if (_gameState == GameState::PLAYING) {
            switch (key) {
                case Key::UP:
                    if (_direction != Direction::DOWN)
                        _nextDirection = Direction::UP;
                    break;
                case Key::DOWN:
                    if (_direction != Direction::UP)
                        _nextDirection = Direction::DOWN;
                    break;
                case Key::LEFT:
                    if (_direction != Direction::RIGHT)
                        _nextDirection = Direction::LEFT;
                    break;
                case Key::RIGHT:
                    if (_direction != Direction::LEFT)
                        _nextDirection = Direction::RIGHT;
                    break;
                case Key::SPACE:
                    // Speed boost
                    _moveInterval = 0.1f;
                    break;
                default:
                    break;
            }
        }
    }

    void NibblerGame::render(IDisplayModule &display) {
        display.clear();

        // Draw border
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            display.drawPixel(DisplayChar('#', Color::WHITE, Color::BLACK, Position(x, 0)));
            display.drawPixel(DisplayChar('#', Color::WHITE, Color::BLACK, Position(x, BOARD_HEIGHT - 1)));
        }
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            display.drawPixel(DisplayChar('#', Color::WHITE, Color::BLACK, Position(0, y)));
            display.drawPixel(DisplayChar('#', Color::WHITE, Color::BLACK, Position(BOARD_WIDTH - 1, y)));
        }

        if (_gameState == GameState::PLAYING) {
            // Draw snake
            for (size_t i = 0; i < _snake.size(); ++i) {
                char snakeChar = (i == 0) ? 'O' : 'o'; // Head vs body
                Color snakeColor = (i == 0) ? Color::YELLOW : Color::GREEN;
                display.drawPixel(DisplayChar(snakeChar, snakeColor, Color::BLACK, _snake[i].position));
            }

            // Draw food
            display.drawPixel(DisplayChar('*', Color::RED, Color::BLACK, _food));

            // Draw score
            display.drawText("Score: " + std::to_string(_score), Position(BOARD_WIDTH + 2, 1), Color::WHITE);
            display.drawText("Use arrows to move", Position(BOARD_WIDTH + 2, 3), Color::CYAN);
            display.drawText("Space for speed boost", Position(BOARD_WIDTH + 2, 4), Color::CYAN);
        }
        else if (_gameState == GameState::MENU) {
            display.drawText("NIBBLER", Position(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT / 2 - 2), Color::YELLOW);
            display.drawText("Press SPACE to start", Position(BOARD_WIDTH / 2 - 8, BOARD_HEIGHT / 2), Color::WHITE);
        }
        else if (_gameState == GameState::GAME_OVER) {
            display.drawText("GAME OVER", Position(BOARD_WIDTH / 2 - 4, BOARD_HEIGHT / 2 - 2), Color::RED);
            display.drawText("Score: " + std::to_string(_score), Position(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT / 2), Color::WHITE);
            display.drawText("Press SPACE to restart", Position(BOARD_WIDTH / 2 - 9, BOARD_HEIGHT / 2 + 2), Color::WHITE);
        }

        display.display();
    }

    void NibblerGame::reset() {
        initializeGame();
    }

    void NibblerGame::moveSnake() {
        if (_snake.empty()) return;

        Position newHead = _snake[0].position;

        switch (_direction) {
            case Direction::UP:
                newHead.y--;
                break;
            case Direction::DOWN:
                newHead.y++;
                break;
            case Direction::LEFT:
                newHead.x--;
                break;
            case Direction::RIGHT:
                newHead.x++;
                break;
        }

        _snake.insert(_snake.begin(), SnakeSegment(newHead.x, newHead.y));

        // Check if food was eaten
        if (newHead.x == _food.x && newHead.y == _food.y) {
            _score += 10;
            generateFood();

            // Increase speed slightly
            _moveInterval = std::max(0.05f, _moveInterval - 0.005f);
        } else {
            // Remove tail if no food was eaten
            _snake.pop_back();
        }

        // Reset speed boost
        if (_moveInterval < 0.15f && _moveInterval > 0.05f) {
            _moveInterval = 0.2f;
        }
    }

    void NibblerGame::generateFood() {
        Position newFood;
        bool validPosition;

        do {
            newFood.x = _xDistribution(_generator);
            newFood.y = _yDistribution(_generator);

            validPosition = true;
            for (const auto &segment : _snake) {
                if (segment.position.x == newFood.x && segment.position.y == newFood.y) {
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition);

        _food = newFood;
    }

    bool NibblerGame::checkCollision() {
        if (_snake.empty()) return false;

        Position head = _snake[0].position;

        // Check wall collision
        if (head.x <= 0 || head.x >= BOARD_WIDTH - 1 ||
            head.y <= 0 || head.y >= BOARD_HEIGHT - 1) {
            return true;
        }

        // Check self collision
        for (size_t i = 1; i < _snake.size(); ++i) {
            if (head.x == _snake[i].position.x && head.y == _snake[i].position.y) {
                return true;
            }
        }

        return false;
    }

    bool NibblerGame::isValidPosition(const Position &pos) {
        return pos.x > 0 && pos.x < BOARD_WIDTH - 1 &&
               pos.y > 0 && pos.y < BOARD_HEIGHT - 1;
    }

    GameInfo NibblerGame::getGameInfo() const {
        GameInfo info;
        info.name = "Nibbler";
        info.score = _score;
        info.highScore = 0; // Will be managed by ScoreManager
        info.level = 1;
        info.state = _gameState;
        return info;
    }

    GameState NibblerGame::getGameState() const {
        return _gameState;
    }

    std::string NibblerGame::getName() const {
        return "Nibbler";
    }

    bool NibblerGame::isGameOver() const {
        return _gameState == GameState::GAME_OVER;
    }

    int NibblerGame::getScore() const {
        return _score;
    }
}

extern "C" {
    arcade::IGameModule* createGame() {
        return new arcade::NibblerGame();
    }

    void destroyGame(arcade::IGameModule* module) {
        delete module;
    }
}