/*
** EPITECH PROJECT, 2025
** Panoramix Bootstrap
** File description:
** Main file for train simulation
*/

#include "train.hpp"
#include <vector>

int main() {
    std::vector<Train> trains;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < NB_TRAINS; i++) {
        trains.emplace_back(i);
    }
    
    for (auto& train : trains) {
        threads.emplace_back([&train, &trains]() {
            train.run();
        });
    }
    
    std::thread displayThread([&trains]() {
        bool allFinished = false;
        while (!allFinished) {
            Train::displayAllTrains(trains);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            allFinished = true;
            for (const auto& train : trains) {
                if (train.position <= TRACK_LENGTH) {
                    allFinished = false;
                    break;
                }
            }
        }
    });
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    displayThread.join();
    
    std::cout << "All trains have crossed the bridge!" << std::endl;
    return 0;
}