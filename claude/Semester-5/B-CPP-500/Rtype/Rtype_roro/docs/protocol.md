# R-Type Network Protocol Documentation

## Overview

The R-Type network protocol is a custom binary UDP-based protocol designed for real-time multiplayer gaming. It prioritizes low latency and efficient bandwidth usage while maintaining reliability for critical game events.

## Protocol Specifications

### Transport Layer
- **Protocol**: UDP (User Datagram Protocol)
- **Port**: 4242 (default, configurable)
- **Packet Size**: Maximum 1024 bytes
- **Endianness**: Little-endian (host byte order)

### Message Structure

All messages follow this basic structure:

```
┌─────────────────┬─────────────────┬─────────────────┐
│   Message       │   Message       │   Message       │
│   Header        │   Payload       │   Checksum      │
│   (8 bytes)     │   (variable)    │   (optional)    │
└─────────────────┴─────────────────┴─────────────────┘
```

#### Message Header (8 bytes)
```c
struct MessageHeader {
    uint8_t  type;        // Message type identifier
    uint16_t size;        // Total message size including header
    uint32_t timestamp;   // Client timestamp (milliseconds)
    uint8_t  reserved;    // Reserved for future use
} __attribute__((packed));
```

## Message Types

### 1. CONNECTION MESSAGES

#### CONNECT (0x01)
**Direction**: Client → Server  
**Purpose**: Initial connection request

```c
struct ConnectMessage {
    MessageHeader header;
    char playerName[32];  // Null-terminated player name
} __attribute__((packed));
```

**Response**: Server assigns player ID and sends GAME_STATE

#### DISCONNECT (0x02)
**Direction**: Client → Server  
**Purpose**: Graceful disconnection

```c
struct DisconnectMessage {
    MessageHeader header;
    uint32_t reason;      // Disconnect reason code
} __attribute__((packed));
```

### 2. GAME ACTION MESSAGES

#### PLAYER_MOVE (0x03)
**Direction**: Client → Server  
**Purpose**: Player movement update

```c
struct PlayerMoveMessage {
    MessageHeader header;
    uint32_t playerId;    // Player identifier
    float x, y;           // Current position
    float vx, vy;         // Velocity vector
} __attribute__((packed));
```

**Frequency**: Up to 60 times per second  
**Reliability**: Best effort (UDP)

#### PLAYER_SHOOT (0x04)
**Direction**: Client → Server  
**Purpose**: Player shooting action

```c
struct PlayerShootMessage {
    MessageHeader header;
    uint32_t playerId;    // Player identifier
    float x, y;           // Shooting position
    float dirX, dirY;     // Shooting direction (normalized)
} __attribute__((packed));
```

**Frequency**: Limited by game logic (200ms cooldown)  
**Reliability**: Acknowledged (see ACK system)

### 3. GAME STATE MESSAGES

#### GAME_STATE (0x05)
**Direction**: Server → Client  
**Purpose**: Complete game state synchronization

```c
struct GameStateMessage {
    MessageHeader header;
    uint32_t frameNumber; // Game frame identifier
    uint16_t entityCount; // Number of entities in update
    // Followed by entityCount EntityUpdate structures
} __attribute__((packed));
```

**Frequency**: 20 times per second (50ms interval)  
**Reliability**: Latest state overwrites previous

#### ENTITY_UPDATE (0x06)
**Direction**: Server → Client  
**Purpose**: Individual entity state update

```c
struct EntityUpdateMessage {
    MessageHeader header;
    uint32_t entityId;    // Unique entity identifier
    float x, y;           // Entity position
    uint8_t entityType;   // Entity type (player, enemy, bullet, etc.)
    uint8_t flags;        // State flags (alive, visible, etc.)
    uint16_t health;      // Current health (if applicable)
} __attribute__((packed));
```

#### SPAWN_ENEMY (0x07)
**Direction**: Server → Client  
**Purpose**: Enemy spawn notification

```c
struct SpawnEnemyMessage {
    MessageHeader header;
    uint32_t entityId;    // New entity identifier
    float x, y;           // Spawn position
    uint8_t enemyType;    // Enemy type identifier
    uint16_t health;      // Initial health
} __attribute__((packed));
```

#### DESTROY_ENTITY (0x08)
**Direction**: Server → Client  
**Purpose**: Entity destruction notification

```c
struct DestroyEntityMessage {
    MessageHeader header;
    uint32_t entityId;    // Entity to destroy
    uint8_t reason;       // Destruction reason (death, cleanup, etc.)
} __attribute__((packed));
```

### 4. CONTROL MESSAGES

#### PING (0x09)
**Direction**: Client → Server  
**Purpose**: Latency measurement and keep-alive

```c
struct PingMessage {
    MessageHeader header;
    uint32_t clientTime; // Client timestamp
} __attribute__((packed));
```

#### PONG (0x0A)
**Direction**: Server → Client  
**Purpose**: Ping response

```c
struct PongMessage {
    MessageHeader header;
    uint32_t clientTime; // Original client timestamp
    uint32_t serverTime; // Server timestamp
} __attribute__((packed));
```

## Reliability Mechanisms

### Critical Messages
Messages requiring guaranteed delivery:
- CONNECT/DISCONNECT
- PLAYER_SHOOT (combat actions)
- SPAWN_ENEMY/DESTROY_ENTITY

### Acknowledgment System
```c
struct AckMessage {
    MessageHeader header;
    uint32_t messageId;   // ID of acknowledged message
    uint8_t status;       // ACK/NACK status
} __attribute__((packed));
```

### Sequence Numbers
- Each client maintains send/receive sequence numbers
- Duplicate detection and ordering
- Automatic retransmission for critical messages

## Error Handling

### Malformed Messages
- Invalid message type → Ignore packet
- Incorrect size → Drop connection
- Checksum mismatch → Request retransmission

### Network Issues
- Packet loss → Timeout and retransmit (critical messages)
- Out-of-order → Reorder using sequence numbers
- Jitter → Buffer and interpolate

### Security Considerations
- Message size validation
- Rate limiting (max 100 messages/second per client)
- Sanity checks on game data
- Connection timeout (30 seconds idle)

## Performance Optimizations

### Bandwidth Optimization
- Delta compression for repeated updates
- Message batching for small messages
- Priority-based sending (critical messages first)

### Latency Optimization
- Client-side prediction
- Server reconciliation
- Interpolation for smooth movement

### Data Format
- Packed structures (no padding)
- Fixed-point arithmetic for coordinates (future)
- Bit fields for boolean flags

## Implementation Example

### Sending a Message (C++)
```cpp
Network::Packet packet;
Network::MessageHeader header;
header.type = Network::MessageType::PLAYER_MOVE;
header.size = sizeof(header) + sizeof(Network::PlayerMoveMessage);
header.timestamp = getCurrentTime();

Network::PlayerMoveMessage moveMsg;
moveMsg.playerId = playerId;
moveMsg.x = position.x;
moveMsg.y = position.y;
moveMsg.vx = velocity.x;
moveMsg.vy = velocity.y;

packet << header << moveMsg;
sendto(socket, packet.getData(), packet.getSize(), 0, ...);
```

### Receiving a Message (C++)
```cpp
Network::Packet packet;
packet.write(buffer, receivedBytes);

Network::MessageHeader header;
if (packet >> header) {
    switch (header.type) {
        case Network::MessageType::PLAYER_MOVE: {
            Network::PlayerMoveMessage msg;
            if (packet >> msg) {
                updatePlayerPosition(msg.playerId, msg.x, msg.y);
            }
            break;
        }
        // ... other message types
    }
}
```

## Testing Tools

### Packet Analysis
- Wireshark protocol dissector (planned)
- Custom packet inspector tool
- Network statistics logging

### Simulation
- Artificial latency injection
- Packet loss simulation
- Bandwidth throttling
- Connection interruption testing

## Version Compatibility

### Protocol Versioning
- Version field in CONNECT message
- Backward compatibility for minor versions
- Graceful degradation for unsupported features

### Future Extensions
- Compression support flag
- Encryption capability negotiation
- Quality of Service markers
- Custom game mode parameters