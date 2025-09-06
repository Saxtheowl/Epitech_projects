/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Automation management routes
*/

const express = require('express');
const { Automation, Action, Service, User } = require('../models');
const { authenticateToken } = require('../middleware/auth');
const automationEngine = require('../services/automationEngine');

const router = express.Router();

router.get('/', authenticateToken, async (req, res) => {
    try {
        const automations = await Automation.findAll({
            where: { userId: req.user.id },
            include: [
                {
                    model: Action,
                    as: 'trigger',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                },
                {
                    model: Action,
                    as: 'reaction',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                }
            ],
            order: [['createdAt', 'DESC']]
        });
        
        res.json({ automations });
    } catch (error) {
        console.error('Automations fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch automations' });
    }
});

router.post('/', authenticateToken, async (req, res) => {
    try {
        const { 
            name, 
            description, 
            triggerId, 
            reactionId, 
            triggerConfig = {},
            reactionConfig = {} 
        } = req.body;
        
        if (!name || !triggerId || !reactionId) {
            return res.status(400).json({ 
                error: 'Name, trigger ID, and reaction ID are required' 
            });
        }
        
        const trigger = await Action.findOne({
            where: { id: triggerId, type: 'trigger', isActive: true }
        });
        
        const reaction = await Action.findOne({
            where: { id: reactionId, type: 'reaction', isActive: true }
        });
        
        if (!trigger || !reaction) {
            return res.status(400).json({ 
                error: 'Invalid trigger or reaction ID' 
            });
        }
        
        const automation = await Automation.create({
            userId: req.user.id,
            name,
            description,
            triggerId,
            reactionId,
            triggerConfig,
            reactionConfig,
            isActive: true
        });
        
        const fullAutomation = await Automation.findByPk(automation.id, {
            include: [
                {
                    model: Action,
                    as: 'trigger',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                },
                {
                    model: Action,
                    as: 'reaction',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                }
            ]
        });
        
        res.status(201).json({
            message: 'Automation created successfully',
            automation: fullAutomation
        });
    } catch (error) {
        console.error('Automation creation error:', error);
        res.status(500).json({ error: 'Failed to create automation' });
    }
});

router.get('/:id', authenticateToken, async (req, res) => {
    try {
        const automation = await Automation.findOne({
            where: { 
                id: req.params.id, 
                userId: req.user.id 
            },
            include: [
                {
                    model: Action,
                    as: 'trigger',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                },
                {
                    model: Action,
                    as: 'reaction',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                }
            ]
        });
        
        if (!automation) {
            return res.status(404).json({ error: 'Automation not found' });
        }
        
        res.json({ automation });
    } catch (error) {
        console.error('Automation fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch automation' });
    }
});

router.put('/:id', authenticateToken, async (req, res) => {
    try {
        const { name, description, triggerConfig, reactionConfig, isActive } = req.body;
        
        const automation = await Automation.findOne({
            where: { 
                id: req.params.id, 
                userId: req.user.id 
            }
        });
        
        if (!automation) {
            return res.status(404).json({ error: 'Automation not found' });
        }
        
        const updateData = {};
        if (name !== undefined) updateData.name = name;
        if (description !== undefined) updateData.description = description;
        if (triggerConfig !== undefined) updateData.triggerConfig = triggerConfig;
        if (reactionConfig !== undefined) updateData.reactionConfig = reactionConfig;
        if (isActive !== undefined) updateData.isActive = isActive;
        
        await automation.update(updateData);
        
        const updatedAutomation = await Automation.findByPk(automation.id, {
            include: [
                {
                    model: Action,
                    as: 'trigger',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                },
                {
                    model: Action,
                    as: 'reaction',
                    include: [{
                        model: Service,
                        as: 'service',
                        attributes: ['id', 'name', 'displayName', 'icon']
                    }]
                }
            ]
        });
        
        res.json({
            message: 'Automation updated successfully',
            automation: updatedAutomation
        });
    } catch (error) {
        console.error('Automation update error:', error);
        res.status(500).json({ error: 'Failed to update automation' });
    }
});

router.delete('/:id', authenticateToken, async (req, res) => {
    try {
        const automation = await Automation.findOne({
            where: { 
                id: req.params.id, 
                userId: req.user.id 
            }
        });
        
        if (!automation) {
            return res.status(404).json({ error: 'Automation not found' });
        }
        
        await automation.destroy();
        
        res.json({ message: 'Automation deleted successfully' });
    } catch (error) {
        console.error('Automation deletion error:', error);
        res.status(500).json({ error: 'Failed to delete automation' });
    }
});

router.post('/:id/trigger', authenticateToken, async (req, res) => {
    try {
        const automation = await Automation.findOne({
            where: { 
                id: req.params.id, 
                userId: req.user.id,
                isActive: true
            },
            include: [
                { model: Action, as: 'trigger' },
                { model: Action, as: 'reaction' },
                { model: User, as: 'user' }
            ]
        });
        
        if (!automation) {
            return res.status(404).json({ error: 'Active automation not found' });
        }
        
        const result = await automationEngine.executeAutomation(automation, req.body);
        
        await automation.update({
            lastTriggered: new Date(),
            triggerCount: automation.triggerCount + 1
        });
        
        res.json({
            message: 'Automation triggered successfully',
            result
        });
    } catch (error) {
        console.error('Automation trigger error:', error);
        res.status(500).json({ error: 'Failed to trigger automation' });
    }
});

module.exports = router;