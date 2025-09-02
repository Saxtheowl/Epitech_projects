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
#include <fcntl.h>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <sys/socket.h>
#include "ipc.hpp"
#include "plazza.hpp"
#include "kitchen.hpp"

struct KitchenHandle {
    int pid;
    int fd;
    std::string buf;
};

static KitchenHandle new_kitchen(const Args &args)
{
    KitchenHandle h{-1,-1};
    int fd = -1; int pid = spawn_kitchen(args.cooks_per_kitchen,
        args.refill_ms, args.multiplier, fd);
    if (pid > 0 && fd >= 0) { h.pid = pid; h.fd = fd; }
    return h;
}

static int kitchen_load(const KitchenHandle &k)
{
    // ask status to compute load minimally; fallback high value if unavailable
    std::string s = kitchen_status_request(k.fd);
    if (s.rfind("busy ", 0) == 0) {
        // format: busy A/N queue Q stock ...
        int a=0,n=1,q=0;
        std::istringstream is(s);
        std::string tok;
        is >> tok >> a; is.ignore(1, '/'); is >> n >> tok >> q;
        return a + q;
    }
    return 1e9;
}

static bool dispatch_one(std::vector<KitchenHandle> &ks, const Args &args,
    const OrderItem &it)
{
    PizzaType pt; PizzaSize ps;
    if (!parse_type(it.type, pt) || !parse_size(it.size, ps))
        return false;
    Pizza p{pt, ps};
    // choose least loaded kitchen that can accept
    int best = -1; int bestLoad = 1e9;
    for (std::size_t i=0;i<ks.size();++i) {
        auto &k = ks[i];
        if (k.fd < 0) continue;
        if (!kitchen_can_accept(k.fd, args.cooks_per_kitchen*2)) continue;
        int ld = kitchen_load(k);
        if (ld < bestLoad) { bestLoad = ld; best = (int)i; }
    }
    if (best >= 0)
        return kitchen_queue_pizza(ks[best].fd, p);
    auto kh = new_kitchen(args);
    if (kh.fd < 0) return false;
    ks.push_back(kh);
    return kitchen_queue_pizza(ks.back().fd, p);
}

void handle_status_all(std::vector<KitchenHandle> &ks)
{
    for (std::size_t i = 0; i < ks.size(); ) {
        std::string s = kitchen_status_request(ks[i].fd);
        if (s.empty()) s = "unavailable";
        std::cout << "kitchen " << i << ": " << s << "\n";
        if (s == "unavailable") {
            // drop dead kitchen: close fd and reap child
            close(ks[i].fd);
            int st = 0; (void)st;
            waitpid(ks[i].pid, &st, WNOHANG);
            ks.erase(ks.begin() + (long)i);
            continue;
        }
        ++i;
    }
}

void reception_loop(const Args &args)
{
    std::vector<KitchenHandle> kitchens;
    std::string line;
    auto drain_msgs = [&](void){
        for (auto &k : kitchens) {
            if (k.fd < 0) continue;
            IpcChannel ch(k.fd);
            std::string line;
            while (ch.recvLine(line)) {
                if (line.rfind("DONE ", 0) == 0) {
                    std::cout << "order ready: " << line.substr(5) << "\n";
                    std::ofstream log("plazza_roro.log", std::ios::app);
                    if (log) log << line << "\n";
                } else {
                    k.buf += line;
                    k.buf += '\n';
                    break;
                }
            }
        }
    };
    while (std::getline(std::cin, line)) {
        drain_msgs();
        if (line == "status") { handle_status_all(kitchens); continue; }
        if (line == "quit" || line == "exit") break;
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
        drain_msgs();
    }
    // cleanup: close fds and reap children
    for (auto &k : kitchens) {
        if (k.fd >= 0) close(k.fd);
        int st = 0; (void)st;
        waitpid(k.pid, &st, WNOHANG);
    }
}
