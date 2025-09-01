/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Reception side: kitchen management and dispatch
*/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "plazza.hpp"
#include "kitchen.hpp"

struct KitchenHandle {
    int pid;
    int fd;
};

static KitchenHandle new_kitchen(const Args &args)
{
    KitchenHandle h{-1,-1};
    int fd = -1; int pid = spawn_kitchen(args.cooks_per_kitchen,
        args.refill_ms, args.multiplier, fd);
    if (pid > 0 && fd >= 0) { h.pid = pid; h.fd = fd; }
    return h;
}

static bool dispatch_one(std::vector<KitchenHandle> &ks, const Args &args,
    const OrderItem &it)
{
    PizzaType pt; PizzaSize ps;
    if (!parse_type(it.type, pt) || !parse_size(it.size, ps))
        return false;
    Pizza p{pt, ps};
    for (auto &k : ks) {
        if (k.fd >= 0 && kitchen_can_accept(k.fd, args.cooks_per_kitchen*2))
            return kitchen_queue_pizza(k.fd, p);
    }
    auto kh = new_kitchen(args);
    if (kh.fd < 0) return false;
    ks.push_back(kh);
    return kitchen_queue_pizza(ks.back().fd, p);
}

void handle_status_all(const std::vector<KitchenHandle> &ks)
{
    for (std::size_t i = 0; i < ks.size(); ++i) {
        std::string s = kitchen_status_request(ks[i].fd);
        if (s.empty()) s = "unavailable";
        std::cout << "kitchen " << i << ": " << s << "\n";
    }
}

void reception_loop(const Args &args)
{
    std::vector<KitchenHandle> kitchens;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "status") { handle_status_all(kitchens); continue; }
        bool ok = false;
        auto items = parse_orders_line(line, ok);
        if (!ok || items.empty()) {
            std::cerr << "Invalid command" << std::endl; continue;
        }
        for (const auto &it : items) {
            for (int i = 0; i < it.count; ++i) {
                if (!dispatch_one(kitchens, args, it)) {
                    std::cerr << "Dispatch failed" << std::endl;
                    break;
                }
            }
        }
    }
}

