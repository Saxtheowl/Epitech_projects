/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game client implementation
*/

#include "GameClient.hpp"
#include "Components.hpp"
#include <iostream>
#include <cstring>

#ifdef _WIN32
    #pragma comment(lib, "ws2_32.lib")
#endif

Client::GameClient::GameClient(const std::string& serverIp, int port)
    : window_(sf::VideoMode(800, 600), "R-Type Client"), socket_(-1), 
      running_(false), player_entity_(0), player_id_(0)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port);
    inet_pton(AF_INET, serverIp.c_str(), &server_addr_.sin_addr);

    // Initialize systems
    systems_.push_back(std::make_unique<Systems::MovementSystem>());
    systems_.push_back(std::make_unique<Systems::RenderSystem>(&window_));
    systems_.push_back(std::make_unique<Systems::CollisionSystem>());
    systems_.push_back(std::make_unique<Systems::EnemySystem>());
}

Client::GameClient::~GameClient()
{
    disconnect();
}

bool Client::GameClient::connect(const std::string& playerName)
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

    // Send connect message
    Network::Packet packet;
    Network::MessageHeader header;
    header.type = Network::MessageType::CONNECT;
    header.size = sizeof(header) + sizeof(Network::ConnectMessage);
    header.timestamp = 0;

    Network::ConnectMessage connectMsg;
    strncpy(connectMsg.playerName, playerName.c_str(), sizeof(connectMsg.playerName) - 1);
    connectMsg.playerName[sizeof(connectMsg.playerName) - 1] = '\0';

    packet << header << connectMsg;
    sendMessage(packet);

    createPlayer();

    running_ = true;
    network_thread_ = std::thread(&GameClient::networkLoop, this);

    std::cout << "Connected to server as " << playerName << std::endl;
    return true;
}

void Client::GameClient::disconnect()
{
    running_ = false;

    if (network_thread_.joinable()) {
        network_thread_.join();
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

void Client::GameClient::run()
{
    sf::Clock clock;

    while (window_.isOpen() && running_) {
        float deltaTime = clock.restart().asSeconds();

        handleInput();

        {
            std::lock_guard<std::mutex> lock(registry_mutex_);
            
            for (auto& system : systems_) {
                system->update(registry_, deltaTime);
            }
        }

        // Limit frame rate
        sf::sleep(sf::milliseconds(16)); // ~60 FPS
    }
}

void Client::GameClient::networkLoop()
{
    char buffer[1024];
    sockaddr_in from_addr;
    socklen_t addr_len = sizeof(from_addr);

    while (running_) {
        int received = recvfrom(socket_, buffer, sizeof(buffer), 0,
                               (sockaddr*)&from_addr, &addr_len);
        
        if (received > 0) {
            Network::Packet packet;
            packet.write(buffer, received);
            packet.resetReadPos();
            
            handleMessage(packet);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Client::GameClient::handleMessage(const Network::Packet& packet)
{
    Network::MessageHeader header;
    if (!const_cast<Network::Packet&>(packet).read(&header, sizeof(header))) {
        return;
    }

    switch (header.type) {
        case Network::MessageType::GAME_STATE: {
            // Handle game state updates from server
            break;
        }
        
        case Network::MessageType::ENTITY_UPDATE: {
            Network::EntityUpdateMessage msg;
            if (const_cast<Network::Packet&>(packet).read(&msg, sizeof(msg))) {
                std::lock_guard<std::mutex> lock(registry_mutex_);
                // Update entity position based on server data
                // In a full implementation, you'd have entity ID mapping
            }
            break;
        }
        
        case Network::MessageType::PONG: {
            // Handle ping response
            break;
        }
        
        default:
            break;
    }
}

void Client::GameClient::sendMessage(const Network::Packet& packet)
{
    if (socket_ >= 0) {
        sendto(socket_, (const char*)packet.getData(), packet.getSize(), 0,
               (const sockaddr*)&server_addr_, sizeof(server_addr_));
    }
}

void Client::GameClient::handleInput()
{
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
            running_ = false;
        }
    }

    // Handle continuous input
    std::lock_guard<std::mutex> lock(registry_mutex_);
    auto* position = registry_.getComponent<Components::Position>(player_entity_);
    auto* velocity = registry_.getComponent<Components::Velocity>(player_entity_);

    if (position && velocity) {
        velocity->x = 0.0f;
        velocity->y = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position->x > 0) {
            velocity->x = -200.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position->x < 750) {
            velocity->x = 200.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position->y > 0) {
            velocity->y = -200.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position->y < 550) {
            velocity->y = 200.0f;
        }

        // Send movement update to server
        Network::Packet packet;
        Network::MessageHeader header;
        header.type = Network::MessageType::PLAYER_MOVE;
        header.size = sizeof(header) + sizeof(Network::PlayerMoveMessage);
        header.timestamp = 0;

        Network::PlayerMoveMessage moveMsg;
        moveMsg.playerId = player_id_;
        moveMsg.x = position->x;
        moveMsg.y = position->y;
        moveMsg.vx = velocity->x;
        moveMsg.vy = velocity->y;

        packet << header << moveMsg;
        sendMessage(packet);

        // Handle shooting
        static sf::Clock shootClock;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootClock.getElapsedTime().asMilliseconds() > 200) {
            shootClock.restart();

            Network::Packet shootPacket;
            Network::MessageHeader shootHeader;
            shootHeader.type = Network::MessageType::PLAYER_SHOOT;
            shootHeader.size = sizeof(shootHeader) + sizeof(Network::PlayerShootMessage);
            shootHeader.timestamp = 0;

            Network::PlayerShootMessage shootMsg;
            shootMsg.playerId = player_id_;
            shootMsg.x = position->x + 32.0f;
            shootMsg.y = position->y + 16.0f;
            shootMsg.dirX = 1.0f;
            shootMsg.dirY = 0.0f;

            shootPacket << shootHeader << shootMsg;
            sendMessage(shootPacket);

            // Create local bullet for immediate feedback
            auto bulletEntity = registry_.createEntity();
            registry_.addComponent(bulletEntity, Components::Position(position->x + 32.0f, position->y + 16.0f));
            registry_.addComponent(bulletEntity, Components::Velocity(300.0f, 0.0f));
            registry_.addComponent(bulletEntity, Components::Bullet(25, player_id_));
            
            Components::Sprite bulletSprite;
            bulletSprite.sprite.setColor(sf::Color::Yellow);
            bulletSprite.sprite.setScale(8.0f, 4.0f);
            registry_.addComponent(bulletEntity, bulletSprite);
        }
    }
}

void Client::GameClient::createPlayer()
{
    std::lock_guard<std::mutex> lock(registry_mutex_);
    
    player_entity_ = registry_.createEntity();
    registry_.addComponent(player_entity_, Components::Position(50.0f, 300.0f));
    registry_.addComponent(player_entity_, Components::Velocity(0.0f, 0.0f));
    registry_.addComponent(player_entity_, Components::Player(player_id_, "Local Player"));
    registry_.addComponent(player_entity_, Components::Health(100));
    registry_.addComponent(player_entity_, Components::Collision(16.0f, true));

    // Create player sprite (blue rectangle for now)
    Components::Sprite playerSprite;
    playerSprite.sprite.setColor(sf::Color::Blue);
    playerSprite.sprite.setScale(32.0f, 32.0f);
    registry_.addComponent(player_entity_, playerSprite);
}