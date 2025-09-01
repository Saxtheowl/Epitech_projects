/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Kitchen process and cooks
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cstdio>
#include "plazza.hpp"
#include "ipc.hpp"
#include "threading.hpp"

struct Stock {
    std::map<std::string,int> st;
    std::mutex m;
    std::condition_variable cv;
    Stock() {
        const char **items = plz_ingredients();
        int n = plz_ingredients_count();
        for (int i = 0; i < n; ++i) st[items[i]] = 5;
    }
    bool take(const std::vector<std::string> &need) {
        std::unique_lock<std::mutex> lk(m);
        while (true) {
            bool ok = true;
            for (auto &i : need) if (st[i] <= 0) { ok = false; break; }
            if (ok) { for (auto &i : need) st[i]--; return true; }
            cv.wait_for(lk, std::chrono::milliseconds(50));
        }
    }
    void restock() {
        std::lock_guard<std::mutex> lk(m);
        for (auto &kv : st) kv.second += 1;
        cv.notify_all();
    }
};

static std::vector<std::string> need_for(PizzaType t)
{
    if (t == PizzaType::Margarita) return {"doe","tomato","gruyere"};
    if (t == PizzaType::Regina) return {"doe","tomato","gruyere","ham","mushrooms"};
    if (t == PizzaType::Americana) return {"doe","tomato","gruyere","steak"};
    return {"doe","tomato","eggplant","goat","love"};
}

extern int pizza_cook_time_ms(PizzaType,double);

static int kitchen_main(int fd, int cooks, int restock_ms, double mult)
{
    Channel ch(fd);
    std::atomic<int> in_progress{0};
    ThreadPool pool(cooks);
    Stock stock;
    std::atomic<bool> running{true};
    auto last_active = std::chrono::steady_clock::now();

    std::thread restocker([&]{
        while (running.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(restock_ms));
            stock.restock();
        }
    });

    std::thread idle_guard([&]{
        while (running.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if (in_progress.load() == 0 && pool.pending() == 0) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - last_active).count() >= 5) {
                    Packet p{5,0,0,0}; ch.send(p); running=false; break; }
            } else {
                last_active = std::chrono::steady_clock::now();
            }
        }
    });

    Packet pkt;
    while (running.load() && ch.recv(pkt)) {
        if (pkt.type == 1) { // assign pizza: a=type, b=size
            int cap = 2 * cooks;
            int load = (int)in_progress.load() + (int)pool.pending();
            if (load >= cap) {
                Packet deny{7,0,0,0}; ch.send(deny);
                continue;
            }
            in_progress.fetch_add(1);
            PizzaType t = static_cast<PizzaType>(pkt.a);
            pool.submit([&,t]{
                stock.take(need_for(t));
                std::this_thread::sleep_for(std::chrono::milliseconds(pizza_cook_time_ms(t, mult)));
                in_progress.fetch_sub(1);
                Packet d{4, pkt.a, pkt.b, 0}; ch.send(d);
            });
        } else if (pkt.type == 2) { // status req
            int in = (int)in_progress.load();
            int pend = (int)pool.pending();
            int n = plz_ingredients_count();
            Packet s{3, in, pend, n};
            ch.send(s);
            const char **items = plz_ingredients();
            for (int i = 0; i < n; ++i) {
                int val = 0;
                {
                    std::lock_guard<std::mutex> lk(stock.m);
                    auto it = stock.st.find(items[i]);
                    val = (it == stock.st.end()) ? 0 : it->second;
                }
                Packet si{6, i, val, 0};
                ch.send(si);
            }
        } else if (pkt.type == 5) {
            running=false; break;
        }
    }
    running = false;
    pool.stop();
    if (restocker.joinable()) restocker.join();
    if (idle_guard.joinable()) idle_guard.join();
    return 0;
}

#include "kitchen.hpp"

KitchenProc spawn_kitchen(int cooks, int restock_ms, double mult)
{
    auto ch = make_channel();
    pid_t pid = fork();
    if (pid == 0) {
        ::close(ch.first.fd);
        kitchen_main(ch.second.fd, cooks, restock_ms, mult);
        _exit(0);
    }
    ::close(ch.second.fd);
    return KitchenProc{pid, ch.first.fd, 2*cooks, 0};
}

// forward decl
int run_reception(const Args &args);
