/*
** EPITECH PROJECT, 2025
** Panoramix Bootstrap
** File description:
** Train class header
*/

#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <vector>

#define NB_TRAINS 3
#define NB_MAX 2
#define TRACK_LENGTH 15
#define BRIDGE_START 5
#define BRIDGE_END 10

class Train {
public:
    int id;
    int position;
    static std::mutex bridgeMutex;
    static std::mutex displayMutex;
    static int bridgeCount;
    
    Train(int trainId);
    void run();
    void displayState();
    static void displayAllTrains(const std::vector<Train>& trains);
    void moveTrain();
    static void clearScreen();
};

#endif /* !TRAIN_HPP_ */