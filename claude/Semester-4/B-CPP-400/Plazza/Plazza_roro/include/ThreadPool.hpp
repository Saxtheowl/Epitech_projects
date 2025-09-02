/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Thread pool and synchronization primitives
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <atomic>

class Mutex {
public:
    Mutex() = default;
    ~Mutex() = default;

    void lock() { _mutex.lock(); }
    void unlock() { _mutex.unlock(); }
    bool try_lock() { return _mutex.try_lock(); }

private:
    std::mutex _mutex;
};

class CondVar {
public:
    CondVar() = default;
    ~CondVar() = default;

    void wait(std::unique_lock<std::mutex>& lock) { _condvar.wait(lock); }
    void notify_one() { _condvar.notify_one(); }
    void notify_all() { _condvar.notify_all(); }

    template<typename Predicate>
    void wait(std::unique_lock<std::mutex>& lock, Predicate pred) {
        _condvar.wait(lock, pred);
    }

private:
    std::condition_variable _condvar;
};

class Thread {
public:
    template<typename Function, typename... Args>
    Thread(Function&& func, Args&&... args) 
        : _thread(std::forward<Function>(func), std::forward<Args>(args)...) {}
    
    ~Thread() = default;
    Thread(Thread&& other) : _thread(std::move(other._thread)) {}
    Thread& operator=(Thread&& other) {
        if (this != &other) {
            _thread = std::move(other._thread);
        }
        return *this;
    }

    void join() { if (_thread.joinable()) _thread.join(); }
    void detach() { _thread.detach(); }
    bool joinable() { return _thread.joinable(); }

private:
    std::thread _thread;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
};

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void enqueue(std::function<void()> task);
    void stop();
    size_t getActiveThreads() const { return _activeThreads.load(); }

private:
    std::vector<std::thread> _threads;
    std::queue<std::function<void()>> _tasks;
    std::mutex _queueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop;
    std::atomic<size_t> _activeThreads;

    void worker();
};

#endif /* !THREADPOOL_HPP_ */