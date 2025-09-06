/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Service management routes
*/

const express = require('express');
const { Service, Action, UserService } = require('../models');
const { authenticateToken, optionalAuth } = require('../middleware/auth');

const router = express.Router();

router.get('/', optionalAuth, async (req, res) => {
    try {
        const services = await Service.findAll({
            where: { isActive: true },
            include: [{
                model: Action,
                as: 'actions',
                where: { isActive: true },
                required: false
            }],
            order: [['name', 'ASC']]
        });
        
        res.json({ services });
    } catch (error) {
        console.error('Services fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch services' });
    }
});

router.get('/:id', optionalAuth, async (req, res) => {
    try {
        const service = await Service.findOne({
            where: { 
                id: req.params.id, 
                isActive: true 
            },
            include: [{
                model: Action,
                as: 'actions',
                where: { isActive: true },
                required: false
            }]
        });
        
        if (!service) {
            return res.status(404).json({ error: 'Service not found' });
        }
        
        res.json({ service });
    } catch (error) {
        console.error('Service fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch service' });
    }
});

router.post('/:id/connect', authenticateToken, async (req, res) => {
    try {
        const { accessToken, refreshToken, config = {} } = req.body;
        const serviceId = req.params.id;
        
        const service = await Service.findByPk(serviceId);
        if (!service) {
            return res.status(404).json({ error: 'Service not found' });
        }
        
        const [userService, created] = await UserService.findOrCreate({
            where: {
                userId: req.user.id,
                serviceId: serviceId
            },
            defaults: {
                accessToken,
                refreshToken,
                config,
                isConnected: true
            }
        });
        
        if (!created) {
            await userService.update({
                accessToken,
                refreshToken,
                config,
                isConnected: true
            });
        }
        
        res.json({
            message: 'Service connected successfully',
            userService: {
                id: userService.id,
                serviceId: userService.serviceId,
                isConnected: userService.isConnected
            }
        });
    } catch (error) {
        console.error('Service connection error:', error);
        res.status(500).json({ error: 'Failed to connect service' });
    }
});

router.delete('/:id/disconnect', authenticateToken, async (req, res) => {
    try {
        const serviceId = req.params.id;
        
        const userService = await UserService.findOne({
            where: {
                userId: req.user.id,
                serviceId: serviceId
            }
        });
        
        if (!userService) {
            return res.status(404).json({ error: 'Service connection not found' });
        }
        
        await userService.update({
            accessToken: null,
            refreshToken: null,
            isConnected: false
        });
        
        res.json({ message: 'Service disconnected successfully' });
    } catch (error) {
        console.error('Service disconnection error:', error);
        res.status(500).json({ error: 'Failed to disconnect service' });
    }
});

module.exports = router;