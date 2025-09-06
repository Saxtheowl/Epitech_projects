/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Automation execution engine
*/

const axios = require('axios');
const { UserService } = require('../models');

class AutomationEngine {
    constructor() {
        this.actionHandlers = new Map();
        this.initializeHandlers();
    }

    initializeHandlers() {
        this.actionHandlers.set('gmail_new_email', this.handleGmailNewEmail.bind(this));
        this.actionHandlers.set('gmail_send_email', this.handleGmailSendEmail.bind(this));
        this.actionHandlers.set('discord_new_message', this.handleDiscordNewMessage.bind(this));
        this.actionHandlers.set('discord_send_message', this.handleDiscordSendMessage.bind(this));
        this.actionHandlers.set('spotify_new_song', this.handleSpotifyNewSong.bind(this));
        this.actionHandlers.set('spotify_play_song', this.handleSpotifyPlaySong.bind(this));
    }

    async executeAutomation(automation, triggerData = {}) {
        try {
            console.log(`Executing automation: ${automation.name}`);
            
            const triggerResult = await this.executeTrigger(automation, triggerData);
            
            if (!triggerResult.triggered) {
                return {
                    success: false,
                    message: 'Trigger condition not met',
                    triggerResult
                };
            }

            const reactionResult = await this.executeReaction(automation, {
                ...triggerData,
                ...triggerResult.data
            });

            return {
                success: true,
                message: 'Automation executed successfully',
                triggerResult,
                reactionResult
            };
        } catch (error) {
            console.error('Automation execution error:', error);
            throw error;
        }
    }

    async executeTrigger(automation, triggerData) {
        const triggerKey = `${automation.trigger.service.name}_${automation.trigger.name}`;
        const handler = this.actionHandlers.get(triggerKey);

        if (!handler) {
            throw new Error(`No handler found for trigger: ${triggerKey}`);
        }

        return await handler(automation, triggerData, 'trigger');
    }

    async executeReaction(automation, data) {
        const reactionKey = `${automation.reaction.service.name}_${automation.reaction.name}`;
        const handler = this.actionHandlers.get(reactionKey);

        if (!handler) {
            throw new Error(`No handler found for reaction: ${reactionKey}`);
        }

        return await handler(automation, data, 'reaction');
    }

    async getUserServiceToken(userId, serviceName) {
        const userService = await UserService.findOne({
            where: { userId, serviceId: serviceName },
            include: [{ model: require('../models').Service, as: 'service' }]
        });

        if (!userService || !userService.isConnected) {
            throw new Error(`User not connected to ${serviceName}`);
        }

        return userService.accessToken;
    }

    async handleGmailNewEmail(automation, data, type) {
        if (type === 'trigger') {
            return {
                triggered: true,
                data: {
                    subject: data.subject || 'New Email',
                    sender: data.sender || 'unknown@example.com',
                    content: data.content || 'Email content'
                }
            };
        }
        return { success: false };
    }

    async handleGmailSendEmail(automation, data, type) {
        if (type === 'reaction') {
            try {
                const token = await this.getUserServiceToken(automation.userId, 'gmail');
                
                console.log('Sending email via Gmail API (simulated)');
                console.log('To:', automation.reactionConfig.to || data.to);
                console.log('Subject:', automation.reactionConfig.subject || 'Automated Email');
                console.log('Body:', automation.reactionConfig.body || data.content);

                return {
                    success: true,
                    message: 'Email sent successfully (simulated)',
                    data: {
                        to: automation.reactionConfig.to || data.to,
                        subject: automation.reactionConfig.subject || 'Automated Email'
                    }
                };
            } catch (error) {
                return {
                    success: false,
                    error: error.message
                };
            }
        }
        return { success: false };
    }

    async handleDiscordNewMessage(automation, data, type) {
        if (type === 'trigger') {
            return {
                triggered: true,
                data: {
                    message: data.message || 'New Discord message',
                    author: data.author || 'unknown',
                    channel: data.channel || 'general'
                }
            };
        }
        return { success: false };
    }

    async handleDiscordSendMessage(automation, data, type) {
        if (type === 'reaction') {
            try {
                console.log('Sending Discord message (simulated)');
                console.log('Channel:', automation.reactionConfig.channel || data.channel);
                console.log('Message:', automation.reactionConfig.message || data.message);

                return {
                    success: true,
                    message: 'Discord message sent successfully (simulated)',
                    data: {
                        channel: automation.reactionConfig.channel || data.channel,
                        message: automation.reactionConfig.message || data.message
                    }
                };
            } catch (error) {
                return {
                    success: false,
                    error: error.message
                };
            }
        }
        return { success: false };
    }

    async handleSpotifyNewSong(automation, data, type) {
        if (type === 'trigger') {
            return {
                triggered: true,
                data: {
                    song: data.song || 'Unknown Song',
                    artist: data.artist || 'Unknown Artist',
                    album: data.album || 'Unknown Album'
                }
            };
        }
        return { success: false };
    }

    async handleSpotifyPlaySong(automation, data, type) {
        if (type === 'reaction') {
            try {
                console.log('Playing Spotify song (simulated)');
                console.log('Song:', automation.reactionConfig.song || data.song);
                console.log('Artist:', automation.reactionConfig.artist || data.artist);

                return {
                    success: true,
                    message: 'Spotify song played successfully (simulated)',
                    data: {
                        song: automation.reactionConfig.song || data.song,
                        artist: automation.reactionConfig.artist || data.artist
                    }
                };
            } catch (error) {
                return {
                    success: false,
                    error: error.message
                };
            }
        }
        return { success: false };
    }
}

module.exports = new AutomationEngine();