/*
** EPITECH PROJECT, 2025
** Panoramix Bootstrap
** File description:
** Train class implementation
*/

#include "train.hpp"
#include <vector>
#include <iomanip>

std::mutex Train::bridgeMutex;
std::mutex Train::displayMutex;
int Train::bridgeCount = 0;

Train::Train(int trainId) : id(trainId), position(0) {}

void Train::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Train::displayAllTrains(const std::vector<Train>& trains) {
    std::lock_guard<std::mutex> lock(displayMutex);
    
    clearScreen();
    std::cout << "0123456789012345\n";
    std::cout << "-------------------\n";
    
    for (const auto& train : trains) {
        std::cout << train.id << ": ";
        for (int i = 0; i <= TRACK_LENGTH; i++) {
            if (i == train.position) {
                std::cout << "#";
            } else if (i < BRIDGE_START) {
                std::cout << "=";
            } else if (i == BRIDGE_START) {
                std::cout << "|";
            } else if (i > BRIDGE_START && i < BRIDGE_END) {
                std::cout << " ";
            } else if (i == BRIDGE_END) {
                std::cout << "|";
            } else if (i > BRIDGE_END) {
                std::cout << "=";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Train::run() {
    while (position <= TRACK_LENGTH) {
        if (position == BRIDGE_START) {
            std::unique_lock<std::mutex> lock(bridgeMutex);
            while (bridgeCount >= NB_MAX) {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                lock.lock();
            }
            bridgeCount++;
        }
        
        position++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        if (position == BRIDGE_END + 1) {
            std::lock_guard<std::mutex> lock(bridgeMutex);
            bridgeCount--;
        }
        
        if (position > TRACK_LENGTH) {
            break;
        }
    }
}