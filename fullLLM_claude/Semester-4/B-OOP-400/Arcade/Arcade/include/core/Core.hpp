/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core engine for Arcade platform
*/

#pragma once

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "LibraryLoader.hpp"
#include "ScoreManager.hpp"
#include <memory>
#include <vector>
#include <string>

namespace arcade {
    enum class MenuState {
        MAIN_MENU,
        GAME_SELECTION,
        GRAPHICS_SELECTION,
        SCORE_DISPLAY,
        NAME_INPUT,
        IN_GAME
    };

    class Core {
    public:
        Core();
        ~Core();

        bool init(const std::string &initialGraphicsLib);
        void run();
        void shutdown();

        bool loadGraphicsLibrary(const std::string &path);
        bool loadGameLibrary(const std::string &path);

        void switchToNextGraphicsLib();
        void switchToPrevGraphicsLib();
        void switchToNextGame();
        void switchToPrevGame();

        void restartGame();
        void goToMenu();
        void exitArcade();

    private:
        void handleMenuInput(Key key);
        void handleGameInput(Key key);
        void renderMenu();
        void renderGame();
        void updateGame(float deltaTime);

        void refreshAvailableLibraries();
        std::string extractLibraryName(const std::string &path) const;

        std::unique_ptr<IDisplayModule> _displayModule;
        std::unique_ptr<IGameModule> _gameModule;
        LibraryLoader _loader;
        ScoreManager _scoreManager;

        std::vector<std::string> _availableGraphicsLibs;
        std::vector<std::string> _availableGameLibs;

        size_t _currentGraphicsIndex;
        size_t _currentGameIndex;

        MenuState _menuState;
        std::string _playerName;
        bool _running;
        bool _inGame;

        float _lastUpdateTime;
    };
}