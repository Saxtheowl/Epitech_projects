/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Thread pool declaration
*/

#ifndef PLAZZA_THREADING_HPP
#define PLAZZA_THREADING_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(int n);
    ~ThreadPool();
    void stop();
    template<typename F>
    void submit(F f) { submit_impl(std::function<void()>(f)); }
    size_t pending() const;
private:
    void submit_impl(std::function<void()> f);
    void loop();
    std::vector<std::thread> _threads;
    mutable std::mutex _mtx;
    std::condition_variable _cv;
    std::queue<std::function<void()>> _q;
    bool _stop;
};

#endif

