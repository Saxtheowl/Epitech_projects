/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core arcade engine class
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <chrono>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"

namespace arcade {
    struct Score {
        std::string playerName;
        std::string gameName;
        int score;
        std::string date;

        Score(const std::string &player, const std::string &game, int s)
            : playerName(player), gameName(game), score(s) {}
    };

    enum class MenuState {
        MAIN_MENU,
        GAME_RUNNING,
        SCORE_DISPLAY,
        NAME_INPUT
    };

    class Core {
    private:
        // Current state
        MenuState _menuState;
        std::string _playerName;
        
        // Library loaders
        DLLoader<IDisplayModule> _currentGraphicsLoader;
        DLLoader<IGameModule> _currentGameLoader;
        
        // Available libraries
        std::vector<std::string> _graphicsLibs;
        std::vector<std::string> _gameLibs;
        
        // Current indices
        size_t _currentGraphicsIndex;
        size_t _currentGameIndex;
        
        // Score system
        std::vector<Score> _scores;
        std::string _scoresFile;
        
        // Timing
        std::chrono::steady_clock::time_point _lastUpdate;
        
        // Menu navigation
        int _selectedOption;
        bool _isRunning;

    public:
        Core();
        ~Core();

        // Core functionality
        bool init(const std::string &initialGraphicsLib);
        void run();
        void shutdown();

        // Library management
        bool loadGraphicsLibrary(const std::string &path);
        bool loadGameLibrary(const std::string &path);
        void scanLibraries();
        
        // Navigation
        bool switchToNextGraphics();
        bool switchToPrevGraphics();
        bool switchToNextGame();
        bool switchToPrevGame();
        
        // Game control
        void startGame();
        void restartGame();
        void returnToMenu();
        void exitProgram();
        
        // Menu system
        void handleMenuInput(Key key);
        void handleGameInput(Key key);
        void handleNameInput(Key key);
        void renderMenu();
        void renderGame();
        void renderNameInput();
        
        // Score system
        void saveScore(const std::string &player, const std::string &game, int score);
        void loadScores();
        void saveScores();
        std::vector<Score> getTopScores(const std::string &game = "") const;
        
        // Utility
        float getDeltaTime();
        bool isValidLibrary(const std::string &path, const std::string &prefix) const;
        std::string getLibraryName(const std::string &path) const;
    };
}

#endif /* !CORE_HPP_ */