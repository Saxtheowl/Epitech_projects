/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception implementation
*/

#include "Reception.hpp"
#include <iostream>
#include <sstream>
#include <thread>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <climits>

Reception::Reception(double multiplier, int numCooks, int refillTime)
    : _multiplier(multiplier), _numCooks(numCooks), _refillTime(refillTime),
      _nextKitchenId(1), _running(true) {}

Reception::~Reception() {
    cleanupKitchens();
}

void Reception::run() {
    std::cout << "Plazza Reception started. Type 'exit' to quit, 'status' for kitchen status." << std::endl;
    
    std::thread inputThread([this] { readUserInput(); });
    std::thread monitorThread([this] { monitorKitchens(); });
    
    // Handle kitchen responses in main thread
    while (_running.load()) {
        handleKitchenResponses();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    if (inputThread.joinable()) inputThread.join();
    if (monitorThread.joinable()) monitorThread.join();
}

void Reception::readUserInput() {
    std::string command;
    while (_running.load()) {
        std::cout << "> ";
        if (std::getline(std::cin, command)) {
            if (!command.empty()) {
                processCommand(command);
            }
        }
        
        if (std::cin.eof()) {
            _running = false;
            break;
        }
    }
}

void Reception::processCommand(const std::string& command) {
    if (command == "exit") {
        _running = false;
        return;
    }
    
    if (command == "status") {
        showStatus();
        return;
    }
    
    // Try to parse as pizza order
    try {
        PizzaOrder order(command);
        if (order.isValid()) {
            processOrder(order);
            std::cout << "Order received: " << order.getPizzas().size() << " pizzas" << std::endl;
        } else {
            std::cout << "Invalid order format. Example: regina XXL x2; margarita M x1" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Invalid order: " << e.what() << std::endl;
    }
}

void Reception::processOrder(const PizzaOrder& order) {
    const auto& pizzas = order.getPizzas();
    distributeOrders(pizzas);
}

void Reception::distributeOrders(const std::vector<Pizza>& pizzas) {
    for (const auto& pizza : pizzas) {
        KitchenProcess* bestKitchen = findBestKitchen();
        
        if (!bestKitchen) {
            createKitchen();
            bestKitchen = findBestKitchen();
        }
        
        if (bestKitchen) {
            sendPizzaToKitchen(pizza, bestKitchen);
        }
    }
}

KitchenProcess* Reception::findBestKitchen() {
    std::lock_guard<std::mutex> lock(_kitchensMutex);
    
    KitchenProcess* bestKitchen = nullptr;
    int minLoad = INT_MAX;
    
    for (auto& kitchen : _kitchens) {
        // Simple load balancing - choose kitchen with lowest ID (round-robin-ish)
        if (kitchen->id < minLoad) {
            bestKitchen = kitchen.get();
            minLoad = kitchen->id;
        }
    }
    
    return bestKitchen;
}

void Reception::createKitchen() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - run kitchen
        Kitchen kitchen(_nextKitchenId, _numCooks, _multiplier, _refillTime);
        
        auto ipc = std::make_unique<NamedPipe>();
        if (ipc->create(std::to_string(_nextKitchenId))) {
            kitchen.setIPC(std::move(ipc));
            kitchen.run();
        }
        
        exit(0);
    } else if (pid > 0) {
        // Parent process - register kitchen
        std::lock_guard<std::mutex> lock(_kitchensMutex);
        
        auto kitchenProcess = std::make_unique<KitchenProcess>();
        kitchenProcess->pid = pid;
        kitchenProcess->id = _nextKitchenId;
        kitchenProcess->ipc = std::make_unique<NamedPipe>();
        kitchenProcess->lastContact = std::chrono::steady_clock::now();
        
        // Give the child process time to create the pipe
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        if (kitchenProcess->ipc->connect(std::to_string(_nextKitchenId))) {
            _kitchens.push_back(std::move(kitchenProcess));
            std::cout << "Kitchen " << _nextKitchenId << " created" << std::endl;
        }
        
        _nextKitchenId++;
    }
}

void Reception::sendPizzaToKitchen(const Pizza& pizza, KitchenProcess* kitchen) {
    std::string pizzaData;
    pizza.pack(pizzaData);
    
    std::string message = "PIZZA_ORDER:" + pizzaData;
    if (kitchen->ipc->send(message)) {
        kitchen->lastContact = std::chrono::steady_clock::now();
    }
}

void Reception::handleKitchenResponses() {
    std::lock_guard<std::mutex> lock(_kitchensMutex);
    
    for (auto& kitchen : _kitchens) {
        std::string response;
        if (kitchen->ipc->receive(response)) {
            if (response.find("PIZZA_COMPLETE:") == 0) {
                std::cout << "Pizza completed in kitchen " << kitchen->id << std::endl;
                kitchen->lastContact = std::chrono::steady_clock::now();
            }
        }
    }
}

void Reception::showStatus() {
    std::lock_guard<std::mutex> lock(_kitchensMutex);
    
    std::cout << "\n=== Kitchen Status ===" << std::endl;
    std::cout << "Active kitchens: " << _kitchens.size() << std::endl;
    
    for (const auto& kitchen : _kitchens) {
        std::cout << "Kitchen " << kitchen->id << ": PID " << kitchen->pid << std::endl;
    }
    std::cout << "===================" << std::endl;
}

void Reception::monitorKitchens() {
    while (_running.load()) {
        cleanupKitchens();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Reception::cleanupKitchens() {
    std::lock_guard<std::mutex> lock(_kitchensMutex);
    
    auto it = _kitchens.begin();
    while (it != _kitchens.end()) {
        int status;
        pid_t result = waitpid((*it)->pid, &status, WNOHANG);
        
        if (result == (*it)->pid) {
            std::cout << "Kitchen " << (*it)->id << " has closed" << std::endl;
            it = _kitchens.erase(it);
        } else {
            ++it;
        }
    }
}

void Reception::stop() {
    _running = false;
    cleanupKitchens();
}