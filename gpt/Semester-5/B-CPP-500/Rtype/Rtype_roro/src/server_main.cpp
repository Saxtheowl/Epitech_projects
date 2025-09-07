/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Server entry (UDP echo)
*/

#include <iostream>
#include <string>
#include "net.hpp"
#include "util.hpp"

static void print_usage(void)
{
    std::cout << "USAGE\n";
    std::cout << "    ./r-type_server <port>\n";
}

int rtype_server_main(int ac, char **av)
{
    int port;
    std::string host;

    host = "";
    if (is_help(ac, av)) {
        print_usage();
        return 0;
    }
    if (ac < 2) {
        print_usage();
        return 84;
    }
    if (!parse_port(av[1], port)) {
        print_usage();
        return 84;
    }
    return udp_server_run(host, port);
}

int main(int ac, char **av)
{
    return rtype_server_main(ac, av);
}
