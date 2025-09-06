/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Network protocol definitions
*/

#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <cstring>

namespace Network {
    enum class MessageType : uint8_t {
        CONNECT = 1,
        DISCONNECT = 2,
        PLAYER_MOVE = 3,
        PLAYER_SHOOT = 4,
        GAME_STATE = 5,
        ENTITY_UPDATE = 6,
        SPAWN_ENEMY = 7,
        DESTROY_ENTITY = 8,
        PING = 9,
        PONG = 10
    };

    struct MessageHeader {
        MessageType type;
        uint16_t size;
        uint32_t timestamp;
    } __attribute__((packed));

    struct ConnectMessage {
        char playerName[32];
    } __attribute__((packed));

    struct PlayerMoveMessage {
        uint32_t playerId;
        float x, y;
        float vx, vy;
    } __attribute__((packed));

    struct PlayerShootMessage {
        uint32_t playerId;
        float x, y;
        float dirX, dirY;
    } __attribute__((packed));

    struct EntityUpdateMessage {
        uint32_t entityId;
        float x, y;
        uint8_t entityType;
    } __attribute__((packed));

    struct SpawnEnemyMessage {
        uint32_t entityId;
        float x, y;
        uint8_t enemyType;
    } __attribute__((packed));

    struct DestroyEntityMessage {
        uint32_t entityId;
    } __attribute__((packed));

    class Packet {
    private:
        std::vector<uint8_t> data_;
        size_t read_pos_;

    public:
        Packet() : read_pos_(0) {}
        
        void clear() {
            data_.clear();
            read_pos_ = 0;
        }
        
        void write(const void* data, size_t size) {
            const uint8_t* bytes = static_cast<const uint8_t*>(data);
            data_.insert(data_.end(), bytes, bytes + size);
        }
        
        bool read(void* data, size_t size) {
            if (read_pos_ + size > data_.size()) {
                return false;
            }
            std::memcpy(data, data_.data() + read_pos_, size);
            read_pos_ += size;
            return true;
        }
        
        template<typename T>
        Packet& operator<<(const T& value) {
            write(&value, sizeof(T));
            return *this;
        }
        
        template<typename T>
        Packet& operator>>(T& value) {
            read(&value, sizeof(T));
            return *this;
        }
        
        const uint8_t* getData() const {
            return data_.data();
        }
        
        size_t getSize() const {
            return data_.size();
        }
        
        void resetReadPos() {
            read_pos_ = 0;
        }
    };
}