/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Client main entry point
*/

#include "GameClient.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string serverIp = "127.0.0.1";
    int port = 4242;
    std::string playerName = "Player";

    if (argc > 1) {
        serverIp = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Invalid port number\n";
            return 84;
        }
    }
    if (argc > 3) {
        playerName = argv[3];
    }

    std::cout << "R-Type Client\n";
    std::cout << "Connecting to " << serverIp << ":" << port << " as " << playerName << std::endl;
    std::cout << "Controls: Arrow keys to move, Space to shoot\n";

    Client::GameClient client(serverIp, port);

    if (!client.connect(playerName)) {
        std::cerr << "Failed to connect to server\n";
        return 84;
    }

    try {
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 84;
    }

    std::cout << "Client disconnected.\n";
    return 0;
}