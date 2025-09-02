/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen class
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "Pizza.hpp"
#include "ThreadPool.hpp"
#include "IPC.hpp"
#include <map>
#include <chrono>
#include <atomic>
#include <memory>

class Stock {
public:
    Stock(int refillTime);
    ~Stock();

    bool hasIngredients(const std::vector<IngredientType>& ingredients);
    void consumeIngredients(const std::vector<IngredientType>& ingredients);
    void refillStock();
    void startRefillThread();
    void stopRefillThread();
    
    std::map<IngredientType, int> getStock() const;

private:
    std::map<IngredientType, std::atomic<int>> _ingredients;
    std::atomic<bool> _running;
    int _refillTime;
    std::unique_ptr<std::thread> _refillThread;
    mutable std::mutex _stockMutex;

    void refillLoop();
    void initializeStock();
};

class Cook {
public:
    Cook(int id, Stock& stock, double multiplier);
    ~Cook() = default;

    void cookPizza(const Pizza& pizza, std::function<void(const Pizza&)> onComplete);
    bool isBusy() const { return _busy.load(); }
    int getId() const { return _id; }

private:
    int _id;
    Stock& _stock;
    double _multiplier;
    std::atomic<bool> _busy;
};

class Kitchen {
public:
    Kitchen(int id, int numCooks, double multiplier, int refillTime);
    ~Kitchen();

    bool canAcceptOrder() const;
    void addPizza(const Pizza& pizza);
    void run();
    void stop();

    int getId() const { return _id; }
    int getActivePizzas() const { return _activePizzas.load(); }
    int getMaxCapacity() const { return _maxCapacity; }
    std::map<IngredientType, int> getStock() const { return _stock.getStock(); }

    void setIPC(std::unique_ptr<IPC> ipc) { _ipc = std::move(ipc); }

private:
    int _id;
    int _numCooks;
    int _maxCapacity;
    double _multiplier;
    std::atomic<int> _activePizzas;
    std::atomic<bool> _running;
    std::chrono::steady_clock::time_point _lastActivity;

    std::unique_ptr<ThreadPool> _threadPool;
    std::vector<std::unique_ptr<Cook>> _cooks;
    Stock _stock;
    std::queue<Pizza> _pizzaQueue;
    std::mutex _queueMutex;
    std::unique_ptr<IPC> _ipc;

    void processPizza();
    void cookPizza(const Pizza& pizza);
    Cook* getAvailableCook();
    void sendPizzaComplete(const Pizza& pizza);
    void checkInactivity();
};

#endif /* !KITCHEN_HPP_ */