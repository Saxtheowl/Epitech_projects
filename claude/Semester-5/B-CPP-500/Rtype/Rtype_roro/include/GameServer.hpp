/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game server header
*/

#pragma once

#include "ECS.hpp"
#include "NetworkProtocol.hpp"
#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <chrono>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

namespace Server {
    struct ClientInfo {
        sockaddr_in address;
        std::string playerName;
        ECS::Entity playerEntity;
        std::chrono::steady_clock::time_point lastPing;
    };

    class GameServer {
    private:
        int socket_;
        sockaddr_in server_addr_;
        std::atomic<bool> running_;
        std::thread network_thread_;
        std::thread game_thread_;
        
        ECS::Registry registry_;
        std::mutex registry_mutex_;
        std::unordered_map<uint32_t, ClientInfo> clients_;
        std::mutex clients_mutex_;
        
        uint32_t next_client_id_;
        
        void networkLoop();
        void gameLoop();
        void handleMessage(const sockaddr_in& client_addr, const Network::Packet& packet);
        void sendToClient(uint32_t clientId, const Network::Packet& packet);
        void sendToAllClients(const Network::Packet& packet);
        void updateClients();
        
        uint32_t findClientByAddress(const sockaddr_in& addr);
        uint32_t addClient(const sockaddr_in& addr, const std::string& name);
        void removeClient(uint32_t clientId);
        
    public:
        GameServer(int port = 4242);
        ~GameServer();
        
        bool start();
        void stop();
        void run();
    };
}