/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server main entry point
*/

#include "GameServer.hpp"
#include <iostream>
#include <csignal>

static Server::GameServer* g_server = nullptr;

void signalHandler(int signal)
{
    if (g_server) {
        std::cout << "\nShutting down server...\n";
        g_server->stop();
    }
}

int main(int argc, char* argv[])
{
    int port = 4242;
    
    if (argc > 1) {
        port = std::atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Invalid port number\n";
            return 84;
        }
    }

    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    Server::GameServer server(port);
    g_server = &server;

    if (!server.start()) {
        std::cerr << "Failed to start server\n";
        return 84;
    }

    std::cout << "R-Type server running on port " << port << std::endl;
    std::cout << "Press Ctrl+C to stop\n";

    server.run();

    std::cout << "Server stopped.\n";
    return 0;
}