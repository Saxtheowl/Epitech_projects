/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Reception
*/

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include "plazza.hpp"
#include "ipc.hpp"
#include "kitchen.hpp"


static bool send_pkt(int fd, const Packet &p)
{
    return ::write(fd, &p, sizeof(p)) == (ssize_t)sizeof(p);
}

static bool recv_pkt(int fd, Packet &p)
{
    return ::read(fd, &p, sizeof(p)) == (ssize_t)sizeof(p);
}


int run_reception(const Args &args)
{
    std::vector<KitchenProc> kitchens;
    struct PendingInfo { int pending; };
    std::vector<PendingInfo> info;
    auto ensure_kitchen = [&](void){ if (kitchens.empty()) kitchens.push_back(spawn_kitchen(args.cooks, args.restock_ms, args.multiplier)); };
    std::cout << "Plazza reception ready. Type orders or 'status' or 'exit'." << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "exit") break;
        if (line == "status") {
            for (size_t i = 0; i < kitchens.size(); ++i) {
                auto &k = kitchens[i];
                Packet q{2,0,0,0}; send_pkt(k.fd, q);
                Packet r; if (recv_pkt(k.fd, r) && r.type==3) {
                    std::printf("Kitchen %d: inflight=%d pending=%d\n", (int)k.pid, r.a, r.b);
                    if (i >= info.size()) info.resize(kitchens.size());
                    info[i].pending = r.b;
                    int n = r.c;
                    for (int j = 0; j < n; ++j) {
                        Packet si; if (!recv_pkt(k.fd, si) || si.type != 6) break;
                        const char **ings = plz_ingredients();
                        std::printf("  %s: %d\n", ings[si.a], si.b);
                    }
                }
            }
            continue;
        }
        auto parsed = parse_order_line(line);
        if (!parsed) { std::cerr << "Invalid order." << std::endl; continue; }
        for (auto &it : *parsed) {
            for (int i = 0; i < it.count; ++i) {
                ensure_kitchen();
                // quick refresh pending
                if (info.size() < kitchens.size()) info.resize(kitchens.size());
                for (size_t j = 0; j < kitchens.size(); ++j) {
                    Packet q{2,0,0,0}; send_pkt(kitchens[j].fd, q);
                    Packet r; if (recv_pkt(kitchens[j].fd, r) && r.type==3) {
                        info[j].pending = r.b; int n = r.c; Packet si; for (int x=0;x<n;++x) recv_pkt(kitchens[j].fd, si);
                    }
                }
                // choose least loaded with capacity (inflight + pending < cap)
                int idx = -1;
                int best = 1e9;
                for (size_t j = 0; j < kitchens.size(); ++j) {
                    int load = kitchens[j].inflight + info[j].pending;
                    if (load < best && load < kitchens[j].cap) { best = load; idx = (int)j; }
                }
                if (idx < 0) { // spawn
                    kitchens.push_back(spawn_kitchen(args.cooks, args.restock_ms, args.multiplier));
                    info.resize(kitchens.size());
                    idx = (int)kitchens.size() - 1;
                }
                Packet a{1, (int)it.type, (int)it.size, 0};
                bool denied = false;
                if (send_pkt(kitchens[idx].fd, a)) kitchens[idx].inflight++;
                // process immediate replies including denial and completions
                for (auto &k : kitchens) {
                    Packet r; while (recv_pkt(k.fd, r)) {
                        if (r.type == 4) { k.inflight--; std::printf("Pizza ready: %d/%d\n", r.a, r.b);
                            // log
                            FILE *fp = std::fopen("plazza.log", "a");
                            if (fp) { std::fprintf(fp, "READY %s %s\n", plz_type_name((PizzaType)r.a), plz_size_name((PizzaSize)r.b)); std::fclose(fp);} }
                        else if (r.type == 7) { k.inflight--; denied = true; }
                        else if (r.type == 5) { ::close(k.fd); k.fd=-1; }
                        else break;
                    }
                }
                if (denied) { i--; continue; } // retry assign this pizza
            }
        }
    }
    // shutdown
    for (auto &k : kitchens) if (k.fd>=0) { Packet p{5,0,0,0}; send_pkt(k.fd,p); ::close(k.fd); }
    for (auto &k : kitchens) if (k.pid>0) waitpid(k.pid, nullptr, 0);
    return 0;
}
