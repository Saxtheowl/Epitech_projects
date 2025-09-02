/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen implementation
*/

#include "Kitchen.hpp"
#include <iostream>
#include <thread>

Stock::Stock(int refillTime) : _running(true), _refillTime(refillTime) {
    initializeStock();
}

Stock::~Stock() {
    stopRefillThread();
}

void Stock::initializeStock() {
    _ingredients[Doe] = 5;
    _ingredients[Tomato] = 5;
    _ingredients[Gruyere] = 5;
    _ingredients[Ham] = 5;
    _ingredients[Mushrooms] = 5;
    _ingredients[Steak] = 5;
    _ingredients[Eggplant] = 5;
    _ingredients[GoatCheese] = 5;
    _ingredients[ChiefLove] = 5;
}

bool Stock::hasIngredients(const std::vector<IngredientType>& ingredients) {
    std::lock_guard<std::mutex> lock(_stockMutex);
    for (const auto& ingredient : ingredients) {
        if (_ingredients[ingredient].load() <= 0) {
            return false;
        }
    }
    return true;
}

void Stock::consumeIngredients(const std::vector<IngredientType>& ingredients) {
    std::lock_guard<std::mutex> lock(_stockMutex);
    for (const auto& ingredient : ingredients) {
        _ingredients[ingredient]--;
    }
}

void Stock::startRefillThread() {
    _refillThread = std::make_unique<std::thread>([this] { refillLoop(); });
}

void Stock::stopRefillThread() {
    _running = false;
    if (_refillThread && _refillThread->joinable()) {
        _refillThread->join();
    }
}

void Stock::refillLoop() {
    while (_running.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_refillTime));
        if (_running.load()) {
            refillStock();
        }
    }
}

void Stock::refillStock() {
    std::lock_guard<std::mutex> lock(_stockMutex);
    for (auto& pair : _ingredients) {
        pair.second++;
    }
}

std::map<IngredientType, int> Stock::getStock() const {
    std::lock_guard<std::mutex> lock(_stockMutex);
    std::map<IngredientType, int> result;
    for (const auto& pair : _ingredients) {
        result[pair.first] = pair.second.load();
    }
    return result;
}

Cook::Cook(int id, Stock& stock, double multiplier) 
    : _id(id), _stock(stock), _multiplier(multiplier), _busy(false) {}

void Cook::cookPizza(const Pizza& pizza, std::function<void(const Pizza&)> onComplete) {
    _busy = true;
    
    auto cookTime = static_cast<int>(pizza.getCookingTime() * _multiplier * 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(cookTime));
    
    onComplete(pizza);
    _busy = false;
}

Kitchen::Kitchen(int id, int numCooks, double multiplier, int refillTime)
    : _id(id), _numCooks(numCooks), _maxCapacity(2 * numCooks), _multiplier(multiplier),
      _activePizzas(0), _running(true), _stock(refillTime) {
    
    _threadPool = std::make_unique<ThreadPool>(numCooks);
    
    for (int i = 0; i < numCooks; ++i) {
        _cooks.push_back(std::make_unique<Cook>(i, _stock, multiplier));
    }
    
    _stock.startRefillThread();
    _lastActivity = std::chrono::steady_clock::now();
}

Kitchen::~Kitchen() {
    stop();
}

bool Kitchen::canAcceptOrder() const {
    return _activePizzas.load() < _maxCapacity;
}

void Kitchen::addPizza(const Pizza& pizza) {
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _pizzaQueue.push(pizza);
        _activePizzas++;
    }
    
    _lastActivity = std::chrono::steady_clock::now();
    _threadPool->enqueue([this] { processPizza(); });
}

void Kitchen::processPizza() {
    Pizza pizza(Margarita, S); // Default initialization
    
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        if (_pizzaQueue.empty()) return;
        
        pizza = _pizzaQueue.front();
        _pizzaQueue.pop();
    }
    
    // Wait for ingredients
    while (!_stock.hasIngredients(pizza.getIngredients()) && _running.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    if (!_running.load()) return;
    
    _stock.consumeIngredients(pizza.getIngredients());
    cookPizza(pizza);
}

void Kitchen::cookPizza(const Pizza& pizza) {
    Cook* availableCook = getAvailableCook();
    if (!availableCook) return;
    
    availableCook->cookPizza(pizza, [this](const Pizza& completedPizza) {
        sendPizzaComplete(completedPizza);
        _activePizzas--;
        _lastActivity = std::chrono::steady_clock::now();
    });
}

Cook* Kitchen::getAvailableCook() {
    for (auto& cook : _cooks) {
        if (!cook->isBusy()) {
            return cook.get();
        }
    }
    return nullptr;
}

void Kitchen::sendPizzaComplete(const Pizza& pizza) {
    if (_ipc) {
        std::string message = "PIZZA_COMPLETE:" + pizza.getTypeName() + ":" + pizza.getSizeName();
        _ipc->send(message);
    }
}

void Kitchen::run() {
    while (_running.load()) {
        checkInactivity();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Kitchen::checkInactivity() {
    auto now = std::chrono::steady_clock::now();
    auto timeSinceLastActivity = std::chrono::duration_cast<std::chrono::seconds>(now - _lastActivity).count();
    
    if (timeSinceLastActivity > 5) {
        stop();
    }
}

void Kitchen::stop() {
    _running = false;
    _stock.stopRefillThread();
    if (_threadPool) {
        _threadPool->stop();
    }
}