/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Action management routes
*/

const express = require('express');
const { Action, Service } = require('../models');
const { optionalAuth } = require('../middleware/auth');

const router = express.Router();

router.get('/', optionalAuth, async (req, res) => {
    try {
        const { type } = req.query;
        const whereClause = { isActive: true };
        
        if (type && ['trigger', 'reaction'].includes(type)) {
            whereClause.type = type;
        }
        
        const actions = await Action.findAll({
            where: whereClause,
            include: [{
                model: Service,
                as: 'service',
                attributes: ['id', 'name', 'displayName', 'icon']
            }],
            order: [['serviceId', 'ASC'], ['name', 'ASC']]
        });
        
        res.json({ actions });
    } catch (error) {
        console.error('Actions fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch actions' });
    }
});

router.get('/:id', optionalAuth, async (req, res) => {
    try {
        const action = await Action.findOne({
            where: { 
                id: req.params.id, 
                isActive: true 
            },
            include: [{
                model: Service,
                as: 'service',
                attributes: ['id', 'name', 'displayName', 'icon']
            }]
        });
        
        if (!action) {
            return res.status(404).json({ error: 'Action not found' });
        }
        
        res.json({ action });
    } catch (error) {
        console.error('Action fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch action' });
    }
});

router.get('/service/:serviceId', optionalAuth, async (req, res) => {
    try {
        const { type } = req.query;
        const whereClause = { 
            serviceId: req.params.serviceId,
            isActive: true 
        };
        
        if (type && ['trigger', 'reaction'].includes(type)) {
            whereClause.type = type;
        }
        
        const actions = await Action.findAll({
            where: whereClause,
            include: [{
                model: Service,
                as: 'service',
                attributes: ['id', 'name', 'displayName', 'icon']
            }],
            order: [['name', 'ASC']]
        });
        
        res.json({ actions });
    } catch (error) {
        console.error('Service actions fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch service actions' });
    }
});

module.exports = router;