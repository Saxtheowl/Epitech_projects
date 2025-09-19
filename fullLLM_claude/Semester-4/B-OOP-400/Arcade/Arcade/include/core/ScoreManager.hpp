/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Score management system
*/

#pragma once

#include <string>
#include <map>
#include <vector>

namespace arcade {
    struct Score {
        std::string playerName;
        int score;
        std::string gameName;

        Score(const std::string &name = "", int s = 0, const std::string &game = "")
            : playerName(name), score(s), gameName(game) {}
    };

    class ScoreManager {
    public:
        ScoreManager();
        ~ScoreManager();

        void addScore(const std::string &playerName, int score, const std::string &gameName);
        int getHighScore(const std::string &gameName) const;
        std::vector<Score> getTopScores(const std::string &gameName, int count = 10) const;
        std::vector<Score> getAllScores() const;

        bool saveScores(const std::string &filename = "scores.txt") const;
        bool loadScores(const std::string &filename = "scores.txt");

    private:
        std::map<std::string, std::vector<Score>> _scores; // game name -> scores
    };
}