-- EPITECH PROJECT, 2025
-- Area
-- File description:
-- Database initialization script

-- Initialize basic services
INSERT INTO services (name, "displayName", description, icon, "isActive", config, "createdAt", "updatedAt") VALUES 
('gmail', 'Gmail', 'Google Gmail service for email automation', 'https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/gmail.svg', true, '{}', NOW(), NOW()),
('discord', 'Discord', 'Discord service for chat automation', 'https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/discord.svg', true, '{}', NOW(), NOW()),
('spotify', 'Spotify', 'Spotify service for music automation', 'https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/spotify.svg', true, '{}', NOW(), NOW())
ON CONFLICT (name) DO NOTHING;

-- Initialize actions for Gmail
INSERT INTO actions ("serviceId", name, "displayName", description, type, config, "isActive", "createdAt", "updatedAt") VALUES
((SELECT id FROM services WHERE name = 'gmail'), 'new_email_received', 'New Email Received', 'Triggered when a new email is received', 'trigger', '{"fields": [{"name": "sender", "type": "string", "required": false}, {"name": "subject", "type": "string", "required": false}]}', true, NOW(), NOW()),
((SELECT id FROM services WHERE name = 'gmail'), 'send_email', 'Send Email', 'Send an email', 'reaction', '{"fields": [{"name": "to", "type": "string", "required": true}, {"name": "subject", "type": "string", "required": true}, {"name": "body", "type": "text", "required": true}]}', true, NOW(), NOW())
ON CONFLICT (name, "serviceId") DO NOTHING;

-- Initialize actions for Discord
INSERT INTO actions ("serviceId", name, "displayName", description, type, config, "isActive", "createdAt", "updatedAt") VALUES
((SELECT id FROM services WHERE name = 'discord'), 'new_message', 'New Message', 'Triggered when a new message is posted', 'trigger', '{"fields": [{"name": "channel", "type": "string", "required": false}, {"name": "author", "type": "string", "required": false}]}', true, NOW(), NOW()),
((SELECT id FROM services WHERE name = 'discord'), 'send_message', 'Send Message', 'Send a message to a channel', 'reaction', '{"fields": [{"name": "channel", "type": "string", "required": true}, {"name": "message", "type": "text", "required": true}]}', true, NOW(), NOW())
ON CONFLICT (name, "serviceId") DO NOTHING;

-- Initialize actions for Spotify
INSERT INTO actions ("serviceId", name, "displayName", description, type, config, "isActive", "createdAt", "updatedAt") VALUES
((SELECT id FROM services WHERE name = 'spotify'), 'new_song', 'New Song Playing', 'Triggered when a new song starts playing', 'trigger', '{"fields": [{"name": "artist", "type": "string", "required": false}, {"name": "song", "type": "string", "required": false}]}', true, NOW(), NOW()),
((SELECT id FROM services WHERE name = 'spotify'), 'play_song', 'Play Song', 'Play a specific song', 'reaction', '{"fields": [{"name": "song", "type": "string", "required": true}, {"name": "artist", "type": "string", "required": false}]}', true, NOW(), NOW())
ON CONFLICT (name, "serviceId") DO NOTHING;