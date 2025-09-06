/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Authentication middleware
*/

const jwt = require('jsonwebtoken');
const { User } = require('../models');

const authenticateToken = async (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];
    
    if (!token) {
        return res.status(401).json({ error: 'Access token required' });
    }
    
    try {
        const decoded = jwt.verify(token, process.env.JWT_SECRET || 'default-secret');
        const user = await User.findByPk(decoded.id);
        
        if (!user || !user.isActive) {
            return res.status(401).json({ error: 'Invalid or inactive user' });
        }
        
        req.user = user;
        next();
    } catch (error) {
        console.error('Token verification error:', error);
        return res.status(403).json({ error: 'Invalid token' });
    }
};

const optionalAuth = async (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];
    
    if (token) {
        try {
            const decoded = jwt.verify(token, process.env.JWT_SECRET || 'default-secret');
            const user = await User.findByPk(decoded.id);
            
            if (user && user.isActive) {
                req.user = user;
            }
        } catch (error) {
            console.error('Optional auth error:', error);
        }
    }
    
    next();
};

module.exports = {
    authenticateToken,
    optionalAuth
};