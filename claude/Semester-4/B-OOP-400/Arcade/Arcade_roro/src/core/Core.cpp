/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core arcade engine implementation
*/

#include "Core.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace arcade {

Core::Core() 
    : _menuState(MenuState::MAIN_MENU), _playerName("Player"),
      _currentGraphicsIndex(0), _currentGameIndex(0),
      _scoresFile("scores.txt"), _selectedOption(0), _isRunning(true) {
    _lastUpdate = std::chrono::steady_clock::now();
}

Core::~Core() {
    shutdown();
}

bool Core::init(const std::string &initialGraphicsLib) {
    std::cout << "Initializing Arcade..." << std::endl;
    
    // Scan for available libraries
    scanLibraries();
    
    if (_graphicsLibs.empty()) {
        std::cerr << "No graphics libraries found!" << std::endl;
        return false;
    }
    
    if (_gameLibs.empty()) {
        std::cerr << "No game libraries found!" << std::endl;
        return false;
    }
    
    // Load initial graphics library
    if (!loadGraphicsLibrary(initialGraphicsLib)) {
        std::cerr << "Failed to load initial graphics library: " 
                  << initialGraphicsLib << std::endl;
        return false;
    }
    
    // Load first available game
    if (!loadGameLibrary(_gameLibs[0])) {
        std::cerr << "Failed to load initial game library!" << std::endl;
        return false;
    }
    
    // Initialize graphics
    auto *graphics = _currentGraphicsLoader.getInstance();
    if (!graphics || !graphics->init("Arcade - Retro Platform")) {
        std::cerr << "Failed to initialize graphics module!" << std::endl;
        return false;
    }
    
    // Initialize game
    auto *game = _currentGameLoader.getInstance();
    if (!game || !game->init()) {
        std::cerr << "Failed to initialize game module!" << std::endl;
        return false;
    }
    
    loadScores();
    
    std::cout << "Arcade initialized successfully!" << std::endl;
    std::cout << "Graphics: " << graphics->getName() << std::endl;
    std::cout << "Game: " << game->getName() << std::endl;
    
    return true;
}

void Core::run() {
    auto *graphics = _currentGraphicsLoader.getInstance();
    if (!graphics) return;
    
    while (_isRunning && graphics->isOpen()) {
        // Handle events
        if (graphics->hasEvent()) {
            Key key = graphics->getLastKey();
            
            // Global keys that work in any state
            switch (key) {
                case Key::EXIT:
                    exitProgram();
                    continue;
                case Key::PREV_GRAPH:
                    switchToPrevGraphics();
                    continue;
                case Key::NEXT_GRAPH:
                    switchToNextGraphics();
                    continue;
                case Key::PREV_GAME:
                    switchToPrevGame();
                    continue;
                case Key::NEXT_GAME:
                    switchToNextGame();
                    continue;
                case Key::RESTART:
                    if (_menuState == MenuState::GAME_RUNNING) {
                        restartGame();
                    }
                    continue;
                case Key::MENU:
                    if (_menuState == MenuState::GAME_RUNNING) {
                        returnToMenu();
                    }
                    continue;
                default:
                    break;
            }
            
            // State-specific input handling
            switch (_menuState) {
                case MenuState::MAIN_MENU:
                case MenuState::SCORE_DISPLAY:
                    handleMenuInput(key);
                    break;
                case MenuState::GAME_RUNNING:
                    handleGameInput(key);
                    break;
                case MenuState::NAME_INPUT:
                    handleNameInput(key);
                    break;
            }
        }
        
        // Update game logic
        float deltaTime = getDeltaTime();
        if (_menuState == MenuState::GAME_RUNNING) {
            auto *game = _currentGameLoader.getInstance();
            if (game) {
                game->update(deltaTime);
                
                // Check for game over
                if (game->isGameOver()) {
                    // Save score if game ended
                    int score = game->getScore();
                    if (score > 0) {
                        saveScore(_playerName, game->getName(), score);
                    }
                    returnToMenu();
                }
            }
        }
        
        // Render
        graphics->clear();
        
        switch (_menuState) {
            case MenuState::MAIN_MENU:
            case MenuState::SCORE_DISPLAY:
                renderMenu();
                break;
            case MenuState::GAME_RUNNING:
                renderGame();
                break;
            case MenuState::NAME_INPUT:
                renderNameInput();
                break;
        }
        
        graphics->display();
    }
}

void Core::shutdown() {
    saveScores();
    
    if (_currentGameLoader.isLoaded()) {
        auto *game = _currentGameLoader.getInstance();
        if (game) {
            game->destroy();
        }
        _currentGameLoader.unload();
    }
    
    if (_currentGraphicsLoader.isLoaded()) {
        auto *graphics = _currentGraphicsLoader.getInstance();
        if (graphics) {
            graphics->destroy();
        }
        _currentGraphicsLoader.unload();
    }
}

void Core::scanLibraries() {
    std::string libDir = "./lib/";
    
    try {
        if (!std::filesystem::exists(libDir)) {
            std::cerr << "Library directory not found: " << libDir << std::endl;
            return;
        }
        
        for (const auto &entry : std::filesystem::directory_iterator(libDir)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                std::string filename = entry.path().filename().string();
                
                if (filename.find("arcade_") == 0 && filename.size() >= 3 && 
                    filename.substr(filename.size() - 3) == ".so") {
                    // Determine if it's a graphics or game library
                    if (isValidLibrary(path, "arcade_ncurses") ||
                        isValidLibrary(path, "arcade_sdl2") ||
                        isValidLibrary(path, "arcade_sfml") ||
                        isValidLibrary(path, "arcade_allegro") ||
                        isValidLibrary(path, "arcade_gtk") ||
                        isValidLibrary(path, "arcade_opengl")) {
                        _graphicsLibs.push_back(path);
                    } else if (isValidLibrary(path, "arcade_nibbler") ||
                               isValidLibrary(path, "arcade_pacman") ||
                               isValidLibrary(path, "arcade_qix") ||
                               isValidLibrary(path, "arcade_centipede") ||
                               isValidLibrary(path, "arcade_solarfox")) {
                        _gameLibs.push_back(path);
                    }
                }
            }
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error scanning libraries: " << e.what() << std::endl;
    }
    
    // Sort libraries alphabetically
    std::sort(_graphicsLibs.begin(), _graphicsLibs.end());
    std::sort(_gameLibs.begin(), _gameLibs.end());
    
    std::cout << "Found " << _graphicsLibs.size() << " graphics libraries" << std::endl;
    std::cout << "Found " << _gameLibs.size() << " game libraries" << std::endl;
}

bool Core::loadGraphicsLibrary(const std::string &path) {
    if (!_currentGraphicsLoader.load(path)) {
        std::cerr << "Failed to load graphics library: " << path << std::endl;
        std::cerr << "Error: " << _currentGraphicsLoader.getLastError() << std::endl;
        return false;
    }
    
    auto *graphics = _currentGraphicsLoader.getInstance();
    if (!graphics) {
        std::cerr << "Failed to create graphics module instance" << std::endl;
        return false;
    }
    
    return true;
}

bool Core::loadGameLibrary(const std::string &path) {
    if (!_currentGameLoader.load(path)) {
        std::cerr << "Failed to load game library: " << path << std::endl;
        std::cerr << "Error: " << _currentGameLoader.getLastError() << std::endl;
        return false;
    }
    
    auto *game = _currentGameLoader.getInstance();
    if (!game) {
        std::cerr << "Failed to create game module instance" << std::endl;
        return false;
    }
    
    return true;
}

float Core::getDeltaTime() {
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate);
    _lastUpdate = now;
    return delta.count() / 1000000.0f; // Convert to seconds
}

bool Core::isValidLibrary(const std::string &path, const std::string &prefix) const {
    std::string filename = std::filesystem::path(path).filename().string();
    return filename.find(prefix) != std::string::npos;
}

std::string Core::getLibraryName(const std::string &path) const {
    std::string filename = std::filesystem::path(path).filename().string();
    // Remove "arcade_" prefix and ".so" suffix
    if (filename.find("arcade_") == 0) {
        filename = filename.substr(7);
    }
    if (filename.size() >= 3 && filename.substr(filename.size() - 3) == ".so") {
        filename = filename.substr(0, filename.length() - 3);
    }
    return filename;
}

void Core::handleMenuInput(Key key) {
    switch (key) {
        case Key::UP:
            _selectedOption = (_selectedOption > 0) ? _selectedOption - 1 : 2;
            break;
        case Key::DOWN:
            _selectedOption = (_selectedOption < 2) ? _selectedOption + 1 : 0;
            break;
        case Key::ENTER:
            if (_selectedOption == 0) {
                startGame();
            } else if (_selectedOption == 1) {
                _menuState = MenuState::NAME_INPUT;
            } else if (_selectedOption == 2) {
                _menuState = (_menuState == MenuState::SCORE_DISPLAY) ? 
                            MenuState::MAIN_MENU : MenuState::SCORE_DISPLAY;
            }
            break;
        case Key::ESCAPE:
            if (_menuState == MenuState::SCORE_DISPLAY) {
                _menuState = MenuState::MAIN_MENU;
            }
            break;
        default:
            break;
    }
}

void Core::renderMenu() {
    auto *graphics = _currentGraphicsLoader.getInstance();
    if (!graphics) return;
    
    // Title
    graphics->drawText({10, 2}, "=== ARCADE - RETRO PLATFORM ===", Color::CYAN);
    
    // Current library info
    graphics->drawText({10, 4}, "Graphics: " + graphics->getName(), Color::YELLOW);
    
    auto *game = _currentGameLoader.getInstance();
    if (game) {
        graphics->drawText({10, 5}, "Game: " + game->getName(), Color::YELLOW);
    }
    
    graphics->drawText({10, 6}, "Player: " + _playerName, Color::GREEN);
    
    if (_menuState == MenuState::MAIN_MENU) {
        // Menu options
        graphics->drawText({10, 9}, (_selectedOption == 0 ? "> " : "  ") + std::string("Start Game"), 
                          _selectedOption == 0 ? Color::WHITE : Color::GREEN);
        graphics->drawText({10, 10}, (_selectedOption == 1 ? "> " : "  ") + std::string("Change Name"), 
                          _selectedOption == 1 ? Color::WHITE : Color::GREEN);
        graphics->drawText({10, 11}, (_selectedOption == 2 ? "> " : "  ") + std::string("View Scores"), 
                          _selectedOption == 2 ? Color::WHITE : Color::GREEN);
        
        // Controls
        graphics->drawText({10, 14}, "Controls:", Color::CYAN);
        graphics->drawText({10, 15}, "Arrow Keys: Navigate / Q-A: Graphics / Z-E: Games", Color::WHITE);
        graphics->drawText({10, 16}, "R: Restart / M: Menu / ESC: Exit", Color::WHITE);
    } else if (_menuState == MenuState::SCORE_DISPLAY) {
        graphics->drawText({10, 9}, "HIGH SCORES:", Color::CYAN);
        
        auto scores = getTopScores();
        for (size_t i = 0; i < std::min(scores.size(), size_t(10)); ++i) {
            std::stringstream ss;
            ss << std::setw(2) << (i + 1) << ". " 
               << std::setw(12) << scores[i].playerName 
               << " - " << std::setw(8) << scores[i].score 
               << " (" << scores[i].gameName << ")";
            graphics->drawText({10, 11 + static_cast<int>(i)}, ss.str(), Color::WHITE);
        }
        
        graphics->drawText({10, 23}, "Press ESC to return to menu", Color::YELLOW);
    }
}

void Core::startGame() {
    auto *game = _currentGameLoader.getInstance();
    if (game) {
        game->setPlayerName(_playerName);
        game->reset();
        _menuState = MenuState::GAME_RUNNING;
    }
}

// Placeholder implementations for remaining methods
void Core::handleGameInput(Key key) {
    auto *game = _currentGameLoader.getInstance();
    if (game) {
        game->handleInput(key);
    }
}

void Core::handleNameInput(Key key) {
    if (key == Key::ESCAPE || key == Key::ENTER) {
        _menuState = MenuState::MAIN_MENU;
        return;
    }
    
    // Simple name input handling - implement based on key mappings
}

void Core::renderGame() {
    auto *game = _currentGameLoader.getInstance();
    auto *graphics = _currentGraphicsLoader.getInstance();
    
    if (!game || !graphics) return;
    
    const auto &gameData = game->getGameData();
    
    // Render game objects
    for (const auto &obj : gameData.objects) {
        graphics->drawText(obj.position, std::string(1, obj.character), obj.color);
    }
    
    // Render UI
    std::stringstream ss;
    ss << "Score: " << gameData.score << " Lives: " << gameData.lives;
    graphics->drawText({1, 1}, ss.str(), Color::WHITE);
    
    if (!gameData.statusText.empty()) {
        graphics->drawText({10, 25}, gameData.statusText, Color::YELLOW);
    }
}

void Core::renderNameInput() {
    auto *graphics = _currentGraphicsLoader.getInstance();
    if (!graphics) return;
    
    graphics->drawText({10, 10}, "Enter your name: " + _playerName, Color::WHITE);
    graphics->drawText({10, 12}, "Press ENTER to confirm, ESC to cancel", Color::YELLOW);
}

bool Core::switchToNextGraphics() {
    if (_graphicsLibs.empty()) return false;
    
    _currentGraphicsIndex = (_currentGraphicsIndex + 1) % _graphicsLibs.size();
    return loadGraphicsLibrary(_graphicsLibs[_currentGraphicsIndex]);
}

bool Core::switchToPrevGraphics() {
    if (_graphicsLibs.empty()) return false;
    
    _currentGraphicsIndex = (_currentGraphicsIndex == 0) ? 
                           _graphicsLibs.size() - 1 : _currentGraphicsIndex - 1;
    return loadGraphicsLibrary(_graphicsLibs[_currentGraphicsIndex]);
}

bool Core::switchToNextGame() {
    if (_gameLibs.empty()) return false;
    
    _currentGameIndex = (_currentGameIndex + 1) % _gameLibs.size();
    return loadGameLibrary(_gameLibs[_currentGameIndex]);
}

bool Core::switchToPrevGame() {
    if (_gameLibs.empty()) return false;
    
    _currentGameIndex = (_currentGameIndex == 0) ? 
                       _gameLibs.size() - 1 : _currentGameIndex - 1;
    return loadGameLibrary(_gameLibs[_currentGameIndex]);
}

void Core::restartGame() {
    auto *game = _currentGameLoader.getInstance();
    if (game) {
        game->reset();
    }
}

void Core::returnToMenu() {
    _menuState = MenuState::MAIN_MENU;
    _selectedOption = 0;
}

void Core::exitProgram() {
    _isRunning = false;
}

void Core::saveScore(const std::string &player, const std::string &game, int score) {
    _scores.emplace_back(player, game, score);
    saveScores();
}

void Core::loadScores() {
    std::ifstream file(_scoresFile);
    if (!file.is_open()) return;
    
    _scores.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string player, game;
        int score;
        
        if (iss >> player >> game >> score) {
            _scores.emplace_back(player, game, score);
        }
    }
}

void Core::saveScores() {
    std::ofstream file(_scoresFile);
    if (!file.is_open()) return;
    
    for (const auto &score : _scores) {
        file << score.playerName << " " << score.gameName << " " << score.score << std::endl;
    }
}

std::vector<Score> Core::getTopScores(const std::string &game) const {
    auto scores = _scores;
    
    // Filter by game if specified
    if (!game.empty()) {
        scores.erase(std::remove_if(scores.begin(), scores.end(),
                                   [&game](const Score &s) { return s.gameName != game; }),
                    scores.end());
    }
    
    // Sort by score descending
    std::sort(scores.begin(), scores.end(),
              [](const Score &a, const Score &b) { return a.score > b.score; });
    
    return scores;
}

} // namespace arcade