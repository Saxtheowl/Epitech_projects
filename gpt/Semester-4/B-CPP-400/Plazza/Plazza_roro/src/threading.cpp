/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Threading primitives
*/

#include "threading.hpp"

ThreadPool::ThreadPool(int n): _stop(false)
{
    for (int i = 0; i < n; ++i)
        _threads.emplace_back([this]{ this->loop(); });
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lk(_mtx);
        _stop = true;
    }
    _cv.notify_all();
    for (auto &t : _threads) if (t.joinable()) t.join();
}

void ThreadPool::submit_impl(std::function<void()> f)
{
    {
        std::unique_lock<std::mutex> lk(_mtx);
        _q.emplace(std::move(f));
    }
    _cv.notify_one();
}

size_t ThreadPool::pending() const
{
    std::unique_lock<std::mutex> lk(_mtx);
    return _q.size();
}

void ThreadPool::loop()
{
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lk(_mtx);
            _cv.wait(lk, [this]{ return _stop || !_q.empty(); });
            if (_stop && _q.empty()) return;
            job = std::move(_q.front());
            _q.pop();
        }
        job();
    }
}

