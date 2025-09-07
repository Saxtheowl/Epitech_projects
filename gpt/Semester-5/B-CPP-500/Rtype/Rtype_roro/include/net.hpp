/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Simple UDP helpers
*/

#ifndef NET_HPP
#define NET_HPP

#include <string>

int udp_server_run(const std::string &host, int port);
int udp_client_run(const std::string &host, int port, const std::string &msg);

#endif /* NET_HPP */

