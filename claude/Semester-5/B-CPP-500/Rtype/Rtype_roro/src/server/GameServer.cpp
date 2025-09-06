/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game server implementation
*/

#include "GameServer.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include <iostream>
#include <cstring>

#ifdef _WIN32
    #pragma comment(lib, "ws2_32.lib")
#endif

Server::GameServer::GameServer(int port) 
    : socket_(-1), running_(false), next_client_id_(1)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    server_addr_.sin_port = htons(port);
}

Server::GameServer::~GameServer()
{
    stop();
}

bool Server::GameServer::start()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return false;
    }
#endif

    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0) {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    if (bind(socket_, (sockaddr*)&server_addr_, sizeof(server_addr_)) < 0) {
        std::cerr << "Failed to bind socket\n";
#ifdef _WIN32
        closesocket(socket_);
#else
        close(socket_);
#endif
        return false;
    }

    running_ = true;
    network_thread_ = std::thread(&GameServer::networkLoop, this);
    game_thread_ = std::thread(&GameServer::gameLoop, this);

    std::cout << "Server started on port " << ntohs(server_addr_.sin_port) << std::endl;
    return true;
}

void Server::GameServer::stop()
{
    running_ = false;

    if (network_thread_.joinable()) {
        network_thread_.join();
    }
    
    if (game_thread_.joinable()) {
        game_thread_.join();
    }

    if (socket_ >= 0) {
#ifdef _WIN32
        closesocket(socket_);
        WSACleanup();
#else
        close(socket_);
#endif
        socket_ = -1;
    }
}

void Server::GameServer::run()
{
    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Server::GameServer::networkLoop()
{
    char buffer[1024];
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (running_) {
        int received = recvfrom(socket_, buffer, sizeof(buffer), 0,
                               (sockaddr*)&client_addr, &addr_len);
        
        if (received > 0) {
            Network::Packet packet;
            packet.write(buffer, received);
            packet.resetReadPos();
            
            handleMessage(client_addr, packet);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Server::GameServer::gameLoop()
{
    auto lastTime = std::chrono::steady_clock::now();
    
    while (running_) {
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        {
            std::lock_guard<std::mutex> lock(registry_mutex_);
            
            // Update game systems would go here
            // For now, just a basic enemy spawn
            static float spawnTimer = 0.0f;
            spawnTimer += deltaTime;
            
            if (spawnTimer >= 5.0f) {
                spawnTimer = 0.0f;
                
                auto enemyEntity = registry_.createEntity();
                registry_.addComponent(enemyEntity, Components::Position(800.0f, 300.0f));
                registry_.addComponent(enemyEntity, Components::Velocity(-100.0f, 0.0f));
                registry_.addComponent(enemyEntity, Components::Enemy(0));
                registry_.addComponent(enemyEntity, Components::Health(50));
                registry_.addComponent(enemyEntity, Components::NetworkSync());
            }
        }

        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}

void Server::GameServer::handleMessage(const sockaddr_in& client_addr, const Network::Packet& packet)
{
    Network::MessageHeader header;
    if (!const_cast<Network::Packet&>(packet).read(&header, sizeof(header))) {
        return;
    }

    uint32_t clientId = findClientByAddress(client_addr);

    switch (header.type) {
        case Network::MessageType::CONNECT: {
            Network::ConnectMessage msg;
            if (const_cast<Network::Packet&>(packet).read(&msg, sizeof(msg))) {
                if (clientId == 0) {
                    clientId = addClient(client_addr, msg.playerName);
                    std::cout << "Client " << msg.playerName << " connected (ID: " << clientId << ")\n";
                }
            }
            break;
        }

        case Network::MessageType::PLAYER_MOVE: {
            if (clientId != 0) {
                Network::PlayerMoveMessage msg;
                if (const_cast<Network::Packet&>(packet).read(&msg, sizeof(msg))) {
                    std::lock_guard<std::mutex> lock(registry_mutex_);
                    std::lock_guard<std::mutex> client_lock(clients_mutex_);
                    
                    auto it = clients_.find(clientId);
                    if (it != clients_.end()) {
                        auto* pos = registry_.getComponent<Components::Position>(it->second.playerEntity);
                        auto* vel = registry_.getComponent<Components::Velocity>(it->second.playerEntity);
                        
                        if (pos && vel) {
                            pos->x = msg.x;
                            pos->y = msg.y;
                            vel->x = msg.vx;
                            vel->y = msg.vy;
                        }
                    }
                }
            }
            break;
        }

        case Network::MessageType::PLAYER_SHOOT: {
            if (clientId != 0) {
                Network::PlayerShootMessage msg;
                if (const_cast<Network::Packet&>(packet).read(&msg, sizeof(msg))) {
                    std::lock_guard<std::mutex> lock(registry_mutex_);
                    
                    // Create bullet
                    auto bulletEntity = registry_.createEntity();
                    registry_.addComponent(bulletEntity, Components::Position(msg.x, msg.y));
                    registry_.addComponent(bulletEntity, Components::Velocity(msg.dirX * 300.0f, msg.dirY * 300.0f));
                    registry_.addComponent(bulletEntity, Components::Bullet(25, clientId));
                    registry_.addComponent(bulletEntity, Components::NetworkSync());
                }
            }
            break;
        }

        case Network::MessageType::PING: {
            if (clientId != 0) {
                Network::Packet pongPacket;
                Network::MessageHeader pongHeader;
                pongHeader.type = Network::MessageType::PONG;
                pongHeader.size = sizeof(pongHeader);
                pongHeader.timestamp = header.timestamp;
                
                pongPacket << pongHeader;
                sendToClient(clientId, pongPacket);
            }
            break;
        }

        default:
            break;
    }
}

uint32_t Server::GameServer::findClientByAddress(const sockaddr_in& addr)
{
    std::lock_guard<std::mutex> lock(clients_mutex_);
    
    for (const auto& [id, client] : clients_) {
        if (client.address.sin_addr.s_addr == addr.sin_addr.s_addr &&
            client.address.sin_port == addr.sin_port) {
            return id;
        }
    }
    return 0;
}

uint32_t Server::GameServer::addClient(const sockaddr_in& addr, const std::string& name)
{
    uint32_t id = next_client_id_++;
    
    std::lock_guard<std::mutex> client_lock(clients_mutex_);
    std::lock_guard<std::mutex> registry_lock(registry_mutex_);
    
    ClientInfo client;
    client.address = addr;
    client.playerName = name;
    client.lastPing = std::chrono::steady_clock::now();
    
    // Create player entity
    client.playerEntity = registry_.createEntity();
    registry_.addComponent(client.playerEntity, Components::Position(50.0f, 300.0f));
    registry_.addComponent(client.playerEntity, Components::Velocity(0.0f, 0.0f));
    registry_.addComponent(client.playerEntity, Components::Player(id, name));
    registry_.addComponent(client.playerEntity, Components::Health(100));
    registry_.addComponent(client.playerEntity, Components::NetworkSync());
    
    clients_[id] = client;
    return id;
}

void Server::GameServer::sendToClient(uint32_t clientId, const Network::Packet& packet)
{
    std::lock_guard<std::mutex> lock(clients_mutex_);
    
    auto it = clients_.find(clientId);
    if (it != clients_.end()) {
        sendto(socket_, (const char*)packet.getData(), packet.getSize(), 0,
               (const sockaddr*)&it->second.address, sizeof(it->second.address));
    }
}

void Server::GameServer::updateClients()
{
    // Send game state updates to all clients
    Network::Packet statePacket;
    Network::MessageHeader header;
    header.type = Network::MessageType::GAME_STATE;
    header.size = sizeof(header);
    header.timestamp = static_cast<uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    
    statePacket << header;
    
    // For now, just send a simple heartbeat
    sendToAllClients(statePacket);
}

void Server::GameServer::sendToAllClients(const Network::Packet& packet)
{
    std::lock_guard<std::mutex> lock(clients_mutex_);
    
    for (const auto& [id, client] : clients_) {
        sendto(socket_, (const char*)packet.getData(), packet.getSize(), 0,
               (const sockaddr*)&client.address, sizeof(client.address));
    }
}