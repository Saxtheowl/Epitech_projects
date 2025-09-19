/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core engine implementation
*/

#include "core/Core.hpp"
#include <iostream>
#include <chrono>
#include <thread>

namespace arcade {
    Core::Core()
        : _currentGraphicsIndex(0), _currentGameIndex(0),
          _menuState(MenuState::MAIN_MENU), _playerName("Player"),
          _running(false), _inGame(false), _lastUpdateTime(0.0f) {}

    Core::~Core() {
        shutdown();
    }

    bool Core::init(const std::string &initialGraphicsLib) {
        refreshAvailableLibraries();

        if (_availableGraphicsLibs.empty()) {
            std::cerr << "Error: No graphics libraries found in ./lib/" << std::endl;
            return false;
        }

        if (!loadGraphicsLibrary(initialGraphicsLib)) {
            std::cerr << "Error: Failed to load initial graphics library: "
                      << initialGraphicsLib << std::endl;
            return false;
        }

        if (!_displayModule->init()) {
            std::cerr << "Error: Failed to initialize display module" << std::endl;
            return false;
        }

        // Find the index of the loaded graphics library
        for (size_t i = 0; i < _availableGraphicsLibs.size(); ++i) {
            if (_availableGraphicsLibs[i] == initialGraphicsLib) {
                _currentGraphicsIndex = i;
                break;
            }
        }

        _running = true;
        return true;
    }

    void Core::run() {
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (_running && _displayModule && _displayModule->isOpen()) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

            // Handle input
            Key key = _displayModule->getKey();
            if (key != Key::UNKNOWN) {
                if (_inGame && _gameModule) {
                    handleGameInput(key);
                } else {
                    handleMenuInput(key);
                }
            }

            // Update game if playing
            if (_inGame && _gameModule) {
                updateGame(deltaTime);
                renderGame();
            } else {
                renderMenu();
            }

            // Limit framerate
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
        }
    }

    void Core::shutdown() {
        if (_displayModule) {
            _displayModule->close();
            _displayModule.reset();
        }
        _gameModule.reset();
        _running = false;
    }

    bool Core::loadGraphicsLibrary(const std::string &path) {
        try {
            auto newDisplay = _loader.loadDisplayLibrary(path);
            if (!newDisplay) {
                return false;
            }

            if (_displayModule) {
                _displayModule->close();
            }

            _displayModule = std::move(newDisplay);
            return _displayModule->init();
        } catch (const std::exception &e) {
            std::cerr << "Exception loading graphics library: " << e.what() << std::endl;
            return false;
        }
    }

    bool Core::loadGameLibrary(const std::string &path) {
        try {
            auto newGame = _loader.loadGameLibrary(path);
            if (!newGame) {
                return false;
            }

            _gameModule = std::move(newGame);
            return _gameModule->init();
        } catch (const std::exception &e) {
            std::cerr << "Exception loading game library: " << e.what() << std::endl;
            return false;
        }
    }

    void Core::switchToNextGraphicsLib() {
        if (_availableGraphicsLibs.empty()) return;

        _currentGraphicsIndex = (_currentGraphicsIndex + 1) % _availableGraphicsLibs.size();
        loadGraphicsLibrary(_availableGraphicsLibs[_currentGraphicsIndex]);
    }

    void Core::switchToPrevGraphicsLib() {
        if (_availableGraphicsLibs.empty()) return;

        _currentGraphicsIndex = (_currentGraphicsIndex == 0) ?
                               _availableGraphicsLibs.size() - 1 : _currentGraphicsIndex - 1;
        loadGraphicsLibrary(_availableGraphicsLibs[_currentGraphicsIndex]);
    }

    void Core::switchToNextGame() {
        if (_availableGameLibs.empty()) return;

        _currentGameIndex = (_currentGameIndex + 1) % _availableGameLibs.size();
        loadGameLibrary(_availableGameLibs[_currentGameIndex]);
    }

    void Core::switchToPrevGame() {
        if (_availableGameLibs.empty()) return;

        _currentGameIndex = (_currentGameIndex == 0) ?
                           _availableGameLibs.size() - 1 : _currentGameIndex - 1;
        loadGameLibrary(_availableGameLibs[_currentGameIndex]);
    }

    void Core::restartGame() {
        if (_gameModule) {
            _gameModule->reset();
        }
    }

    void Core::goToMenu() {
        _inGame = false;
        _menuState = MenuState::MAIN_MENU;
    }

    void Core::exitArcade() {
        _running = false;
    }

    void Core::handleMenuInput(Key key) {
        switch (key) {
            case Key::ESCAPE:
            case Key::Q:
                exitArcade();
                break;
            case Key::LEFT:
                switchToPrevGraphicsLib();
                break;
            case Key::RIGHT:
                switchToNextGraphicsLib();
                break;
            case Key::UP:
                switchToPrevGame();
                break;
            case Key::DOWN:
                switchToNextGame();
                break;
            case Key::ENTER:
            case Key::SPACE:
                if (!_availableGameLibs.empty()) {
                    loadGameLibrary(_availableGameLibs[_currentGameIndex]);
                    if (_gameModule) {
                        _inGame = true;
                        _gameModule->reset();
                    }
                }
                break;
            default:
                break;
        }
    }

    void Core::handleGameInput(Key key) {
        switch (key) {
            case Key::ESCAPE:
                goToMenu();
                break;
            case Key::R:
                restartGame();
                break;
            case Key::LEFT:
                if (!_inGame) switchToPrevGraphicsLib();
                else if (_gameModule) _gameModule->handleInput(key);
                break;
            case Key::RIGHT:
                if (!_inGame) switchToNextGraphicsLib();
                else if (_gameModule) _gameModule->handleInput(key);
                break;
            default:
                if (_gameModule) {
                    _gameModule->handleInput(key);
                }
                break;
        }

        // Check if game is over and return to menu
        if (_gameModule && _gameModule->isGameOver()) {
            // Save score
            _scoreManager.addScore(_playerName, _gameModule->getScore(), _gameModule->getName());
            goToMenu();
        }
    }

    void Core::renderMenu() {
        if (!_displayModule) return;

        _displayModule->clear();

        // Title
        _displayModule->drawText("ARCADE PLATFORM", Position(10, 2), Color::YELLOW);

        // Graphics libraries section
        _displayModule->drawText("Graphics Libraries:", Position(2, 5), Color::CYAN);
        for (size_t i = 0; i < _availableGraphicsLibs.size(); ++i) {
            Color color = (i == _currentGraphicsIndex) ? Color::GREEN : Color::WHITE;
            std::string prefix = (i == _currentGraphicsIndex) ? "> " : "  ";
            _displayModule->drawText(prefix + extractLibraryName(_availableGraphicsLibs[i]),
                                   Position(4, 6 + i), color);
        }

        // Games section
        _displayModule->drawText("Available Games:", Position(2, 10), Color::CYAN);
        for (size_t i = 0; i < _availableGameLibs.size(); ++i) {
            Color color = (i == _currentGameIndex) ? Color::GREEN : Color::WHITE;
            std::string prefix = (i == _currentGameIndex) ? "> " : "  ";
            _displayModule->drawText(prefix + extractLibraryName(_availableGameLibs[i]),
                                   Position(4, 11 + i), color);
        }

        // Controls
        _displayModule->drawText("Controls:", Position(2, 16), Color::MAGENTA);
        _displayModule->drawText("Left/Right: Switch graphics", Position(4, 17), Color::WHITE);
        _displayModule->drawText("Up/Down: Switch games", Position(4, 18), Color::WHITE);
        _displayModule->drawText("Space/Enter: Start game", Position(4, 19), Color::WHITE);
        _displayModule->drawText("ESC/Q: Quit", Position(4, 20), Color::WHITE);

        // Player name
        _displayModule->drawText("Player: " + _playerName, Position(2, 22), Color::YELLOW);

        _displayModule->display();
    }

    void Core::renderGame() {
        if (_gameModule && _displayModule) {
            _gameModule->render(*_displayModule);
        }
    }

    void Core::updateGame(float deltaTime) {
        if (_gameModule) {
            _gameModule->update(deltaTime);
        }
    }

    void Core::refreshAvailableLibraries() {
        _availableGraphicsLibs = _loader.getAvailableGraphicsLibs();
        _availableGameLibs = _loader.getAvailableGameLibs();
    }

    std::string Core::extractLibraryName(const std::string &path) const {
        size_t lastSlash = path.find_last_of('/');
        std::string filename = (lastSlash != std::string::npos) ? path.substr(lastSlash + 1) : path;

        // Remove "arcade_" prefix and ".so" suffix
        if (filename.find("arcade_") == 0) {
            filename = filename.substr(7);
        }
        if (filename.find(".so") != std::string::npos) {
            filename = filename.substr(0, filename.find(".so"));
        }

        return filename;
    }
}