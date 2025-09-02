/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception class - main orchestrator
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Kitchen.hpp"
#include "Pizza.hpp"
#include "IPC.hpp"
#include <vector>
#include <memory>
#include <map>
#include <sys/types.h>

struct KitchenProcess {
    pid_t pid;
    int id;
    std::unique_ptr<IPC> ipc;
    std::chrono::steady_clock::time_point lastContact;
};

class Reception {
public:
    Reception(double multiplier, int numCooks, int refillTime);
    ~Reception();

    void run();
    void stop();

private:
    double _multiplier;
    int _numCooks;
    int _refillTime;
    int _nextKitchenId;
    std::atomic<bool> _running;

    std::vector<std::unique_ptr<KitchenProcess>> _kitchens;
    std::mutex _kitchensMutex;

    void processCommand(const std::string& command);
    void processOrder(const PizzaOrder& order);
    void distributeOrders(const std::vector<Pizza>& pizzas);
    KitchenProcess* findBestKitchen();
    void createKitchen();
    void handleKitchenResponses();
    void showStatus();
    void cleanupKitchens();
    
    std::string createPipeName(int kitchenId) const;
    void sendPizzaToKitchen(const Pizza& pizza, KitchenProcess* kitchen);
    
    void readUserInput();
    void monitorKitchens();
};

#endif /* !RECEPTION_HPP_ */