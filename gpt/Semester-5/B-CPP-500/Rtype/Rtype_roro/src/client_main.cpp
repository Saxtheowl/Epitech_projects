/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Client entry (UDP echo)
*/

#include <iostream>
#include <string>
#include "net.hpp"
#include "util.hpp"

static void print_usage(void)
{
    std::cout << "USAGE\n";
    std::cout << "    ./r-type_client <host> <port> <msg>\n";
}

int rtype_client_main(int ac, char **av)
{
    std::string host;
    int port;
    std::string msg;

    if (is_help(ac, av)) {
        print_usage();
        return 0;
    }
    if (ac < 4) {
        print_usage();
        return 84;
    }
    host = av[1];
    if (!parse_port(av[2], port)) {
        print_usage();
        return 84;
    }
    msg = av[3];
    return udp_client_run(host, port, msg);
}

int main(int ac, char **av)
{
    return rtype_client_main(ac, av);
}
