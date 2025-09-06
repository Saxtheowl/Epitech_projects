/*
** EPITECH PROJECT, 2025
** Area
** File description:
** User management routes
*/

const express = require('express');
const { User, UserService, Service } = require('../models');
const { authenticateToken } = require('../middleware/auth');

const router = express.Router();

router.get('/profile', authenticateToken, async (req, res) => {
    try {
        const user = await User.findByPk(req.user.id, {
            attributes: ['id', 'email', 'firstName', 'lastName', 'createdAt'],
            include: [{
                model: UserService,
                as: 'services',
                include: [{
                    model: Service,
                    as: 'service',
                    attributes: ['id', 'name', 'displayName', 'icon']
                }]
            }]
        });
        
        if (!user) {
            return res.status(404).json({ error: 'User not found' });
        }
        
        res.json({ user });
    } catch (error) {
        console.error('Profile fetch error:', error);
        res.status(500).json({ error: 'Failed to fetch profile' });
    }
});

router.put('/profile', authenticateToken, async (req, res) => {
    try {
        const { firstName, lastName } = req.body;
        
        if (!firstName || !lastName) {
            return res.status(400).json({ 
                error: 'First name and last name are required' 
            });
        }
        
        await User.update(
            { firstName, lastName },
            { where: { id: req.user.id } }
        );
        
        const updatedUser = await User.findByPk(req.user.id, {
            attributes: ['id', 'email', 'firstName', 'lastName']
        });
        
        res.json({
            message: 'Profile updated successfully',
            user: updatedUser
        });
    } catch (error) {
        console.error('Profile update error:', error);
        res.status(500).json({ error: 'Failed to update profile' });
    }
});

router.delete('/account', authenticateToken, async (req, res) => {
    try {
        await User.update(
            { isActive: false },
            { where: { id: req.user.id } }
        );
        
        res.json({ message: 'Account deactivated successfully' });
    } catch (error) {
        console.error('Account deactivation error:', error);
        res.status(500).json({ error: 'Failed to deactivate account' });
    }
});

module.exports = router;