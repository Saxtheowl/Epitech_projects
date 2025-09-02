/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Thread pool implementation
*/

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t numThreads) : _stop(false), _activeThreads(0) {
    for (size_t i = 0; i < numThreads; ++i) {
        _threads.emplace_back([this] { worker(); });
    }
}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        if (_stop) return;
        _tasks.push(task);
    }
    _condition.notify_one();
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _stop = true;
    }
    
    _condition.notify_all();
    
    for (std::thread& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
            
            if (_stop && _tasks.empty()) {
                return;
            }
            
            task = _tasks.front();
            _tasks.pop();
            _activeThreads++;
        }
        
        try {
            task();
        } catch (...) {
            // Ignore task exceptions to keep worker running
        }
        
        _activeThreads--;
    }
}