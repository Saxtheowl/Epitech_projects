/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Score management implementation
*/

#include "core/ScoreManager.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace arcade {
    ScoreManager::ScoreManager() {
        loadScores();
    }

    ScoreManager::~ScoreManager() {
        saveScores();
    }

    void ScoreManager::addScore(const std::string &playerName, int score, const std::string &gameName) {
        _scores[gameName].emplace_back(playerName, score, gameName);

        // Sort scores in descending order
        std::sort(_scores[gameName].begin(), _scores[gameName].end(),
                  [](const Score &a, const Score &b) {
                      return a.score > b.score;
                  });
    }

    int ScoreManager::getHighScore(const std::string &gameName) const {
        auto it = _scores.find(gameName);
        if (it != _scores.end() && !it->second.empty()) {
            return it->second[0].score;
        }
        return 0;
    }

    std::vector<Score> ScoreManager::getTopScores(const std::string &gameName, int count) const {
        std::vector<Score> topScores;
        auto it = _scores.find(gameName);

        if (it != _scores.end()) {
            int limit = std::min(count, static_cast<int>(it->second.size()));
            for (int i = 0; i < limit; ++i) {
                topScores.push_back(it->second[i]);
            }
        }

        return topScores;
    }

    std::vector<Score> ScoreManager::getAllScores() const {
        std::vector<Score> allScores;

        for (const auto &gameScores : _scores) {
            for (const auto &score : gameScores.second) {
                allScores.push_back(score);
            }
        }

        // Sort all scores in descending order
        std::sort(allScores.begin(), allScores.end(),
                  [](const Score &a, const Score &b) {
                      return a.score > b.score;
                  });

        return allScores;
    }

    bool ScoreManager::saveScores(const std::string &filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open " << filename << " for writing" << std::endl;
            return false;
        }

        for (const auto &gameScores : _scores) {
            for (const auto &score : gameScores.second) {
                file << score.gameName << ":" << score.playerName << ":" << score.score << std::endl;
            }
        }

        file.close();
        return true;
    }

    bool ScoreManager::loadScores(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            // File doesn't exist yet, that's okay
            return true;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t firstColon = line.find(':');
            size_t secondColon = line.find(':', firstColon + 1);

            if (firstColon != std::string::npos && secondColon != std::string::npos) {
                std::string gameName = line.substr(0, firstColon);
                std::string playerName = line.substr(firstColon + 1, secondColon - firstColon - 1);
                int score = std::stoi(line.substr(secondColon + 1));

                addScore(playerName, score, gameName);
            }
        }

        file.close();
        return true;
    }
}