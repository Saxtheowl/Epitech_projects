/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Authentication middleware
*/

const jwt = require('jsonwebtoken');

const auth = (req, res, next) => {
    try {
        const token = req.header('Authorization');
        
        if (!token) {
            return res.status(401).json({ msg: 'No token, authorization denied' });
        }

        const bearerToken = token.startsWith('Bearer ') ? token.slice(7) : token;
        
        const decoded = jwt.verify(bearerToken, process.env.SECRET);
        req.user = decoded;
        next();
    } catch (error) {
        res.status(401).json({ msg: 'Token is not valid' });
    }
};

module.exports = auth;