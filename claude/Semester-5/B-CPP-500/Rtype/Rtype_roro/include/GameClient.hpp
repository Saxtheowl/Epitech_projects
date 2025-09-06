/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game client header
*/

#pragma once

#include "ECS.hpp"
#include "Systems.hpp"
#include "NetworkProtocol.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <atomic>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

namespace Client {
    class GameClient {
    private:
        sf::RenderWindow window_;
        ECS::Registry registry_;
        std::vector<std::unique_ptr<ECS::ISystem>> systems_;
        
        int socket_;
        sockaddr_in server_addr_;
        std::atomic<bool> running_;
        std::thread network_thread_;
        
        ECS::Entity player_entity_;
        uint32_t player_id_;
        std::mutex registry_mutex_;
        
        void networkLoop();
        void handleMessage(const Network::Packet& packet);
        void sendMessage(const Network::Packet& packet);
        void handleInput();
        void createPlayer();
        
    public:
        GameClient(const std::string& serverIp = "127.0.0.1", int port = 4242);
        ~GameClient();
        
        bool connect(const std::string& playerName);
        void run();
        void disconnect();
    };
}