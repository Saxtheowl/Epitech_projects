/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Kitchen process + IPC (socketpair protocol)
*/

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <cstring>
#include <sstream>
#include <chrono>
#include "plazza.hpp"
#include "kitchen.hpp"
#include "ipc.hpp"

static void write_all(int fd, const char *buf, std::size_t len)
{
    std::size_t off = 0;
    while (off < len) {
        ssize_t w = ::write(fd, buf + off, len - off);
        if (w <= 0) return;
        off += (std::size_t)w;
    }
}

static bool read_line(int fd, std::string &out)
{
    char c;
    out.clear();
    while (1) {
        ssize_t r = ::read(fd, &c, 1);
        if (r == 0) return false;
        if (r < 0) return false;
        if (c == '\n') break;
        out.push_back(c);
    }
    return true;
}

static int base_time(const Pizza &p)
{
    switch (p.type) {
        case PizzaType::Margarita: return 1;
        case PizzaType::Regina: return 2;
        case PizzaType::Americana: return 2;
        case PizzaType::Fantasia: return 4;
    }
    return 1;
}

static int size_factor(PizzaSize sz) { return (int)sz; }

static const char *type_name(PizzaType t)
{
    switch (t) {
        case PizzaType::Margarita: return "margarita";
        case PizzaType::Regina: return "regina";
        case PizzaType::Americana: return "americana";
        case PizzaType::Fantasia: return "fantasia";
    }
    return "unknown";
}

static const char *size_name(PizzaSize s)
{
    switch (s) {
        case PizzaSize::S: return "S";
        case PizzaSize::M: return "M";
        case PizzaSize::L: return "L";
        case PizzaSize::XL: return "XL";
        case PizzaSize::XXL: return "XXL";
    }
    return "?";
}

static bool needs_for(const Pizza &p, KitchenStock &need)
{
    need = {1,1,1,0,0,0,0,0,0}; /* dough, tomato, gruyere */
    if (p.type == PizzaType::Regina)
        need.ham = 1, need.mushrooms = 1;
    if (p.type == PizzaType::Americana)
        need.steak = 1;
    if (p.type == PizzaType::Fantasia)
        need.eggplant = 1, need.goat = 1, need.love = 1;
    return true;
}

Kitchen::Kitchen(int fd, const KitchenCfg &cfg)
    : m_fd(fd), m_cfg(cfg), m_active(0), m_stop(false)
{
    m_stock = {5,5,5,5,5,5,5,5,5};
    using namespace std::chrono;
    m_last_ms.store(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

Kitchen::~Kitchen() {}

void Kitchen::send_line(const std::string &line)
{
    std::string s = line + "\n";
    write_all(m_fd, s.c_str(), s.size());
}

int Kitchen::cook_time_ms(const Pizza &p) const
{
    return (int)(1000.0 * m_cfg.mult * base_time(p) * size_factor(p.size));
}

bool Kitchen::take_ingredients(const Pizza &p)
{
    KitchenStock need{};
    needs_for(p, need);
    std::lock_guard<std::mutex> lk(m_mtx.native());
    if (m_stock.dough < need.dough || m_stock.tomato < need.tomato ||
        m_stock.gruyere < need.gruyere || m_stock.ham < need.ham ||
        m_stock.mushrooms < need.mushrooms || m_stock.steak < need.steak ||
        m_stock.eggplant < need.eggplant || m_stock.goat < need.goat ||
        m_stock.love < need.love)
        return false;
    m_stock.dough -= need.dough; m_stock.tomato -= need.tomato;
    m_stock.gruyere -= need.gruyere; m_stock.ham -= need.ham;
    m_stock.mushrooms -= need.mushrooms; m_stock.steak -= need.steak;
    m_stock.eggplant -= need.eggplant; m_stock.goat -= need.goat;
    m_stock.love -= need.love;
    return true;
}

void Kitchen::refiller_loop()
{
    while (!m_stop.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_cfg.refill_ms));
        std::lock_guard<std::mutex> lk(m_mtx.native());
        m_stock.dough++; m_stock.tomato++; m_stock.gruyere++;
        m_stock.ham++; m_stock.mushrooms++; m_stock.steak++;
        m_stock.eggplant++; m_stock.goat++; m_stock.love++;
        m_cv.notify_all();
    }
}

void Kitchen::cook_loop()
{
    while (!m_stop.load()) {
        Pizza p;
        {
        std::unique_lock<std::mutex> lk(m_mtx.native());
        m_cv.wait(lk);
        if (m_stop.load()) break;
        if (m_queue.empty()) continue;
        if (m_stop.load()) break;
        p = m_queue.front();
        m_queue.erase(m_queue.begin());
        }
        /* wait for ingredients */
        while (!take_ingredients(p)) {
            std::unique_lock<std::mutex> lk(m_mtx.native());
            m_cv.wait_for(lk, std::chrono::milliseconds(m_cfg.refill_ms));
            if (m_stop.load()) break;
        }
        m_active.fetch_add(1);
        m_last_ms.store((long long)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
        std::this_thread::sleep_for(std::chrono::milliseconds(cook_time_ms(p)));
        m_active.fetch_sub(1);
        {
            std::ostringstream os;
            os << "DONE " << type_name(p.type) << ' ' << size_name(p.size);
            send_line(os.str());
        }
        m_last_ms.store((long long)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
    }
}

void Kitchen::on_line(const std::string &line)
{
    if (line == "STATUS") {
        std::lock_guard<std::mutex> lk(m_mtx.native());
        std::ostringstream os;
        os << "busy " << m_active.load() << "/" << m_cfg.cooks
           << " queue " << m_queue.size()
           << " stock "
           << "dough=" << m_stock.dough << ","
           << "tomato=" << m_stock.tomato << ","
           << "gruyere=" << m_stock.gruyere << ","
           << "ham=" << m_stock.ham << ","
           << "mushrooms=" << m_stock.mushrooms << ","
           << "steak=" << m_stock.steak << ","
           << "eggplant=" << m_stock.eggplant << ","
           << "goat=" << m_stock.goat << ","
           << "love=" << m_stock.love;
        send_line(os.str());
        return;
    }
    if (line == "CAN_ACCEPT") {
        std::lock_guard<std::mutex> lk(m_mtx.native());
        int cap = m_cfg.cooks * 2;
        int load = (int)m_queue.size() + m_active.load();
        send_line(load < cap ? "YES" : "NO");
        return;
    }
    if (line.rfind("ORDER ", 0) == 0) {
        std::string t, s;
        std::istringstream is(line.substr(6));
        is >> t >> s;
        PizzaType pt; PizzaSize psz;
        if (!parse_type(t, pt) || !parse_size(s, psz)) {
            send_line("ERR"); return;
        }
        {
            std::lock_guard<std::mutex> lk(m_mtx.native());
            int load = (int)m_queue.size() + m_active.load();
            int cap = m_cfg.cooks * 2;
            if (load >= cap) { send_line("NO"); return; }
            m_queue.push_back({pt, psz});
        }
        m_cv.notify_one();
        m_last_ms.store((long long)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
        send_line("OK");
        return;
    }
}

void Kitchen::run()
{
    m_refiller = Thread(&Kitchen::refiller_loop, this);
    for (int i = 0; i < m_cfg.cooks; ++i)
        m_threads.emplace_back(&Kitchen::cook_loop, this);
    /* inactivity watcher */
    m_watch = Thread([this]{
        using namespace std::chrono;
        while (!m_stop.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            long long now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
            bool idle = false;
            {
                std::lock_guard<std::mutex> lk(m_mtx.native());
                idle = (m_queue.empty() && m_active.load() == 0);
            }
            if (idle && (now - m_last_ms.load()) > 5000) {
                m_stop.store(true);
                shutdown(m_fd, SHUT_RDWR);
                close(m_fd);
                break;
            }
        }
    });
    std::string line;
    while (read_line(m_fd, line))
        on_line(line);
    m_stop.store(true);
    m_cv.notify_all();
    for (auto &t : m_threads) t.join();
    m_refiller.join();
    m_watch.join();
}

int spawn_kitchen(int cooks, int refill_ms, double mult, int &fd_parent)
{
    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0)
        return -1;
    pid_t pid = fork();
    if (pid < 0) {
        close(sv[0]); close(sv[1]); return -1;
    }
    if (pid == 0) {
        /* child */
        close(sv[0]);
        KitchenCfg cfg{cooks, refill_ms, mult};
        Kitchen k(sv[1], cfg);
        k.run();
        _exit(0);
    }
    /* parent */
    close(sv[1]);
    fd_parent = sv[0];
    return (int)pid;
}

static bool send_cmd(int fd, const std::string &cmd, std::string &resp)
{
    std::string s = cmd + "\n";
    write_all(fd, s.c_str(), s.size());
    return read_line(fd, resp);
}

std::string kitchen_status_request(int fd)
{
    std::string r;
    if (!send_cmd(fd, "STATUS", r)) return std::string();
    return r;
}

bool kitchen_queue_pizza(int fd, const Pizza &p)
{
    std::string r;
    IpcChannel ch(fd);
    ch << p;
    if (!read_line(fd, r)) return false;
    return r == "OK";
}

bool kitchen_can_accept(int fd, int limit)
{
    std::string r;
    if (!send_cmd(fd, "CAN_ACCEPT", r)) return false;
    if (r == "YES") return true;
    (void)limit;
    return false;
}

bool parse_type(const std::string &s, PizzaType &t)
{
    if (s == "margarita" || s == "Margarita") { t = PizzaType::Margarita; return true; }
    if (s == "regina" || s == "Regina") { t = PizzaType::Regina; return true; }
    if (s == "americana" || s == "Americana") { t = PizzaType::Americana; return true; }
    if (s == "fantasia" || s == "Fantasia") { t = PizzaType::Fantasia; return true; }
    return false;
}

bool parse_size(const std::string &s, PizzaSize &sz)
{
    if (s == "S") { sz = PizzaSize::S; return true; }
    if (s == "M") { sz = PizzaSize::M; return true; }
    if (s == "L") { sz = PizzaSize::L; return true; }
    if (s == "XL") { sz = PizzaSize::XL; return true; }
    if (s == "XXL") { sz = PizzaSize::XXL; return true; }
    return false;
}
