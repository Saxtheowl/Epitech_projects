/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Lightweight runtime wrappers (Process, Thread, Mutex, CondVar)
*/

#ifndef RT_HPP
#define RT_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <sys/types.h>

class Thread {
public:
    Thread() = default;
    template <typename F>
    explicit Thread(F &&f): th(std::forward<F>(f)) {}
    template <typename F, typename A>
    Thread(F &&f, A &&a): th(std::forward<F>(f), std::forward<A>(a)) {}
    void join() { if (th.joinable()) th.join(); }
    bool joinable() const { return th.joinable(); }
private:
    std::thread th;
};

class Mutex { public: void lock(){ m.lock(); } void unlock(){ m.unlock(); } std::mutex &native(){ return m; } private: std::mutex m; };
class CondVar { public: template<typename L> void wait(L &lk){ cv.wait(lk); } template<typename L> void wait_for(L &lk, const std::chrono::milliseconds &d){ cv.wait_for(lk, d); } void notify_one(){ cv.notify_one(); } void notify_all(){ cv.notify_all(); } private: std::condition_variable cv; };

class Process { public: pid_t pid = -1; int fd = -1; };

#endif /* RT_HPP */

