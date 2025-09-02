/*
** EPITECH PROJECT, 2025
** Panoramix Bootstrap - Step 1
** File description:
** Step 1: Only one train at a time on the bridge
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

#define NB_TRAINS 3
#define TRACK_LENGTH 15
#define BRIDGE_START 5
#define BRIDGE_END 10

class TrainStep1 {
public:
    int id;
    int position;
    static std::mutex bridgeMutex;
    static std::mutex displayMutex;
    
    TrainStep1(int trainId) : id(trainId), position(0) {}
    
    static void displayAllTrains(const std::vector<TrainStep1>& trains) {
        std::lock_guard<std::mutex> lock(displayMutex);
        
        std::cout << "\033[2J\033[1;1H";
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
    
    void run(const std::vector<TrainStep1>& allTrains) {
        while (position <= TRACK_LENGTH) {
            if (position == BRIDGE_START) {
                bridgeMutex.lock();
            }
            
            position++;
            displayAllTrains(allTrains);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            if (position == BRIDGE_END + 1) {
                bridgeMutex.unlock();
            }
            
            if (position > TRACK_LENGTH) {
                break;
            }
        }
    }
};

std::mutex TrainStep1::bridgeMutex;
std::mutex TrainStep1::displayMutex;

int main() {
    std::cout << "STEP 1: One train at a time on the bridge\n\n";
    
    std::vector<TrainStep1> trains;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < NB_TRAINS; i++) {
        trains.emplace_back(i);
    }
    
    for (auto& train : trains) {
        threads.emplace_back([&train, &trains]() {
            train.run(trains);
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "All trains have crossed the bridge!\n";
    return 0;
}