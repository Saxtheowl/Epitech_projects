/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Pacman game implementation
*/

#include "games/PacmanGame.hpp"
#include <algorithm>

namespace arcade {
    PacmanGame::PacmanGame()
        : _pacmanPos(12, 11), _pacmanDirection(PacmanDirection::NONE), _nextDirection(PacmanDirection::NONE),
          _gameState(GameState::MENU), _score(0), _pacgumsLeft(0), _moveTimer(0.0f), _moveInterval(0.15f),
          _vulnerabilityTimer(0.0f), _generator(_randomDevice()) {
        initializeMap();
    }

    bool PacmanGame::init() {
        reset();
        return true;
    }

    void PacmanGame::initializeMap() {
        _map.assign(MAP_HEIGHT, std::vector<CellType>(MAP_WIDTH, CellType::WALL));

        // Simple Pacman-like map
        std::vector<std::string> mapLayout = {
            "#########################",
            "#...........#...........#",
            "#.##.#####.###.#####.##.#",
            "#*##.......###.......##*#",
            "#.##.#####.###.#####.##.#",
            "#.......................#",
            "#.##.#.#########.#.##.#",
            "#....#....###....#....#",
            "####.###..GGG..###.####",
            "#....#....###....#....#",
            "#.##.#.#########.#.##.#",
            "#.......................#",
            "#.##.#####.###.#####.##.#",
            "#*..........P...........*#",
            "#########################"
        };

        _pacgumsLeft = 0;
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                char cell = mapLayout[y][x];
                switch (cell) {
                    case '#':
                        _map[y][x] = CellType::WALL;
                        break;
                    case '.':
                        _map[y][x] = CellType::PACGUM;
                        _pacgumsLeft++;
                        break;
                    case '*':
                        _map[y][x] = CellType::SUPER_PACGUM;
                        _pacgumsLeft++;
                        break;
                    case 'P':
                        _map[y][x] = CellType::EMPTY;
                        _pacmanPos = Position(x, y);
                        break;
                    case 'G':
                        _map[y][x] = CellType::GHOST_ZONE;
                        break;
                    default:
                        _map[y][x] = CellType::EMPTY;
                        break;
                }
            }
        }

        // Initialize ghosts
        _ghosts.clear();
        _ghosts.emplace_back(11, 8);
        _ghosts.emplace_back(12, 8);
        _ghosts.emplace_back(13, 8);
    }

    void PacmanGame::update(float deltaTime) {
        if (_gameState != GameState::PLAYING) return;

        _moveTimer += deltaTime;
        updateVulnerability(deltaTime);

        if (_moveTimer >= _moveInterval) {
            movePlayer();
            moveGhosts();
            checkGhostCollisions();
            _moveTimer = 0.0f;

            if (isMapComplete()) {
                _gameState = GameState::WIN;
            }
        }
    }

    void PacmanGame::handleInput(Key key) {
        if (_gameState == GameState::MENU || _gameState == GameState::GAME_OVER || _gameState == GameState::WIN) {
            if (key == Key::SPACE || key == Key::ENTER) {
                reset();
                _gameState = GameState::PLAYING;
            }
            return;
        }

        if (_gameState == GameState::PLAYING) {
            switch (key) {
                case Key::UP:
                    _nextDirection = PacmanDirection::UP;
                    break;
                case Key::DOWN:
                    _nextDirection = PacmanDirection::DOWN;
                    break;
                case Key::LEFT:
                    _nextDirection = PacmanDirection::LEFT;
                    break;
                case Key::RIGHT:
                    _nextDirection = PacmanDirection::RIGHT;
                    break;
                default:
                    break;
            }
        }
    }

    void PacmanGame::render(IDisplayModule &display) {
        display.clear();

        if (_gameState == GameState::PLAYING || _gameState == GameState::WIN) {
            // Draw map
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    char cellChar = ' ';
                    Color cellColor = Color::WHITE;

                    switch (_map[y][x]) {
                        case CellType::WALL:
                            cellChar = '#';
                            cellColor = Color::BLUE;
                            break;
                        case CellType::PACGUM:
                            cellChar = '.';
                            cellColor = Color::YELLOW;
                            break;
                        case CellType::SUPER_PACGUM:
                            cellChar = '*';
                            cellColor = Color::YELLOW;
                            break;
                        case CellType::GHOST_ZONE:
                            cellChar = '-';
                            cellColor = Color::MAGENTA;
                            break;
                        default:
                            cellChar = ' ';
                            break;
                    }

                    if (cellChar != ' ') {
                        display.drawPixel(DisplayChar(cellChar, cellColor, Color::BLACK, Position(x, y)));
                    }
                }
            }

            // Draw Pacman
            display.drawPixel(DisplayChar('C', Color::YELLOW, Color::BLACK, _pacmanPos));

            // Draw ghosts
            for (const auto &ghost : _ghosts) {
                Color ghostColor = ghost.vulnerable ? Color::CYAN : Color::RED;
                display.drawPixel(DisplayChar('&', ghostColor, Color::BLACK, ghost.position));
            }

            // Draw score and info
            display.drawText("Score: " + std::to_string(_score), Position(MAP_WIDTH + 2, 1), Color::WHITE);
            display.drawText("Pacgums: " + std::to_string(_pacgumsLeft), Position(MAP_WIDTH + 2, 2), Color::WHITE);
            display.drawText("Use arrows to move", Position(MAP_WIDTH + 2, 4), Color::CYAN);

            if (_gameState == GameState::WIN) {
                display.drawText("YOU WIN!", Position(MAP_WIDTH / 2 - 4, MAP_HEIGHT / 2), Color::GREEN);
                display.drawText("Press SPACE to restart", Position(MAP_WIDTH / 2 - 9, MAP_HEIGHT / 2 + 2), Color::WHITE);
            }
        }
        else if (_gameState == GameState::MENU) {
            display.drawText("PACMAN", Position(MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2 - 2), Color::YELLOW);
            display.drawText("Press SPACE to start", Position(MAP_WIDTH / 2 - 8, MAP_HEIGHT / 2), Color::WHITE);
        }
        else if (_gameState == GameState::GAME_OVER) {
            display.drawText("GAME OVER", Position(MAP_WIDTH / 2 - 4, MAP_HEIGHT / 2 - 2), Color::RED);
            display.drawText("Score: " + std::to_string(_score), Position(MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2), Color::WHITE);
            display.drawText("Press SPACE to restart", Position(MAP_WIDTH / 2 - 9, MAP_HEIGHT / 2 + 2), Color::WHITE);
        }

        display.display();
    }

    void PacmanGame::reset() {
        initializeMap();
        _gameState = GameState::PLAYING;
        _score = 0;
        _moveTimer = 0.0f;
        _vulnerabilityTimer = 0.0f;
        _pacmanDirection = PacmanDirection::NONE;
        _nextDirection = PacmanDirection::NONE;
    }

    void PacmanGame::movePlayer() {
        Position nextPos = _pacmanPos;

        // Try to change direction if requested
        if (_nextDirection != PacmanDirection::NONE) {
            Position testPos = _pacmanPos;
            switch (_nextDirection) {
                case PacmanDirection::UP: testPos.y--; break;
                case PacmanDirection::DOWN: testPos.y++; break;
                case PacmanDirection::LEFT: testPos.x--; break;
                case PacmanDirection::RIGHT: testPos.x++; break;
                default: break;
            }

            if (canMoveTo(testPos)) {
                _pacmanDirection = _nextDirection;
                _nextDirection = PacmanDirection::NONE;
            }
        }

        // Move in current direction
        switch (_pacmanDirection) {
            case PacmanDirection::UP: nextPos.y--; break;
            case PacmanDirection::DOWN: nextPos.y++; break;
            case PacmanDirection::LEFT: nextPos.x--; break;
            case PacmanDirection::RIGHT: nextPos.x++; break;
            default: return;
        }

        // Handle tunnel effect (left-right wrap)
        if (nextPos.x < 0) nextPos.x = MAP_WIDTH - 1;
        if (nextPos.x >= MAP_WIDTH) nextPos.x = 0;

        if (canMoveTo(nextPos)) {
            _pacmanPos = nextPos;
            eatPacgum(_pacmanPos);
        } else {
            _pacmanDirection = PacmanDirection::NONE;
        }
    }

    void PacmanGame::moveGhosts() {
        for (auto &ghost : _ghosts) {
            // Simple random movement for ghosts
            std::uniform_int_distribution<int> dirDist(0, 3);
            std::vector<PacmanDirection> directions = {
                PacmanDirection::UP, PacmanDirection::DOWN,
                PacmanDirection::LEFT, PacmanDirection::RIGHT
            };

            for (int attempts = 0; attempts < 4; ++attempts) {
                PacmanDirection newDir = directions[dirDist(_generator)];
                Position nextPos = ghost.position;

                switch (newDir) {
                    case PacmanDirection::UP: nextPos.y--; break;
                    case PacmanDirection::DOWN: nextPos.y++; break;
                    case PacmanDirection::LEFT: nextPos.x--; break;
                    case PacmanDirection::RIGHT: nextPos.x++; break;
                    default: break;
                }

                if (canMoveTo(nextPos) || _map[nextPos.y][nextPos.x] == CellType::GHOST_ZONE) {
                    ghost.position = nextPos;
                    ghost.direction = newDir;
                    break;
                }
            }
        }
    }

    bool PacmanGame::canMoveTo(const Position &pos) const {
        if (pos.x < 0 || pos.x >= MAP_WIDTH || pos.y < 0 || pos.y >= MAP_HEIGHT) {
            return false;
        }
        return _map[pos.y][pos.x] != CellType::WALL;
    }

    void PacmanGame::eatPacgum(const Position &pos) {
        if (_map[pos.y][pos.x] == CellType::PACGUM) {
            _map[pos.y][pos.x] = CellType::EMPTY;
            _score += 10;
            _pacgumsLeft--;
        } else if (_map[pos.y][pos.x] == CellType::SUPER_PACGUM) {
            _map[pos.y][pos.x] = CellType::EMPTY;
            _score += 50;
            _pacgumsLeft--;
            makePacmanVulnerable();
        }
    }

    void PacmanGame::checkGhostCollisions() {
        for (auto &ghost : _ghosts) {
            if (ghost.position.x == _pacmanPos.x && ghost.position.y == _pacmanPos.y) {
                if (ghost.vulnerable) {
                    // Eat ghost
                    _score += 200;
                    ghost.vulnerable = false;
                    ghost.position = Position(12, 8); // Return to ghost zone
                } else {
                    // Game over
                    _gameState = GameState::GAME_OVER;
                }
            }
        }
    }

    void PacmanGame::makePacmanVulnerable() {
        _vulnerabilityTimer = 10.0f; // 10 seconds
        for (auto &ghost : _ghosts) {
            ghost.vulnerable = true;
            ghost.vulnerableTimer = 10.0f;
        }
    }

    void PacmanGame::updateVulnerability(float deltaTime) {
        if (_vulnerabilityTimer > 0.0f) {
            _vulnerabilityTimer -= deltaTime;
            if (_vulnerabilityTimer <= 0.0f) {
                for (auto &ghost : _ghosts) {
                    ghost.vulnerable = false;
                }
            }
        }
    }

    bool PacmanGame::isMapComplete() const {
        return _pacgumsLeft == 0;
    }

    GameInfo PacmanGame::getGameInfo() const {
        GameInfo info;
        info.name = "Pacman";
        info.score = _score;
        info.highScore = 0; // Will be managed by ScoreManager
        info.level = 1;
        info.state = _gameState;
        return info;
    }

    GameState PacmanGame::getGameState() const {
        return _gameState;
    }

    std::string PacmanGame::getName() const {
        return "Pacman";
    }

    bool PacmanGame::isGameOver() const {
        return _gameState == GameState::GAME_OVER;
    }

    int PacmanGame::getScore() const {
        return _score;
    }
}

extern "C" {
    arcade::IGameModule* createGame() {
        return new arcade::PacmanGame();
    }

    void destroyGame(arcade::IGameModule* module) {
        delete module;
    }
}