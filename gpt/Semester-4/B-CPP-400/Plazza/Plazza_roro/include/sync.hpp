/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Synchronization wrappers (Mutex, CondVar)
*/

#ifndef PLAZZA_SYNC_HPP
#define PLAZZA_SYNC_HPP

#include <mutex>
#include <condition_variable>
#include <chrono>

class PlzMutex {
public:
    void lock() { _m.lock(); }
    void unlock() { _m.unlock(); }
    std::mutex &native() { return _m; }
private:
    std::mutex _m;
};

class PlzLockGuard {
public:
    explicit PlzLockGuard(PlzMutex &m): _m(m) { _m.lock(); }
    ~PlzLockGuard() { _m.unlock(); }
private:
    PlzMutex &_m;
};

class PlzCondVar {
public:
    template<class Predicate>
    void wait(std::unique_lock<std::mutex> &lk, Predicate pred) { _cv.wait(lk, pred); }
    template<class Rep, class Period>
    void wait_for(std::unique_lock<std::mutex> &lk, const std::chrono::duration<Rep,Period> &d) { _cv.wait_for(lk, d); }
    void notify_one() { _cv.notify_one(); }
    void notify_all() { _cv.notify_all(); }
    std::condition_variable &native() { return _cv; }
private:
    std::condition_variable _cv;
};

#endif
