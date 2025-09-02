/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Kitchen process + IPC
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "rt.hpp"
#include <atomic>

enum class PizzaType { Regina=1, Margarita=2, Americana=4, Fantasia=8 };
enum class PizzaSize { S=1, M=2, L=4, XL=8, XXL=16 };

struct Pizza {
    PizzaType type;
    PizzaSize size;
};

struct KitchenStock {
    int dough;
    int tomato;
    int gruyere;
    int ham;
    int mushrooms;
    int steak;
    int eggplant;
    int goat;
    int love;
};

struct KitchenCfg {
    int cooks;
    int refill_ms;
    double mult;
};

class Kitchen {
public:
    Kitchen(int fd, const KitchenCfg &cfg);
    ~Kitchen();
    void run();
private:
    int m_fd;
    KitchenCfg m_cfg;
    std::vector<Thread> m_threads;
    Thread m_refiller;
    Thread m_watch;
    Mutex m_mtx;
    CondVar m_cv;
    std::vector<Pizza> m_queue;
    std::atomic<int> m_active;
    KitchenStock m_stock;
    std::atomic<bool> m_stop;
    std::atomic<long long> m_last_ms;

    void refiller_loop();
    void cook_loop();
    bool take_ingredients(const Pizza &p);
    int cook_time_ms(const Pizza &p) const;
    void on_line(const std::string &line);
    void send_line(const std::string &line);
};

/* Reception side helpers */
int spawn_kitchen(int cooks, int refill_ms, double mult, int &fd_parent);
std::string kitchen_status_request(int fd);
bool kitchen_queue_pizza(int fd, const Pizza &p);
bool kitchen_can_accept(int fd, int limit);

/* Parsing helpers */
bool parse_type(const std::string &s, PizzaType &t);
bool parse_size(const std::string &s, PizzaSize &sz);

#endif /* KITCHEN_HPP */
