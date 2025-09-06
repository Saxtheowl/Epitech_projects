/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Authentication routes
*/

const express = require('express');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcryptjs');
const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const { User } = require('../models');

const router = express.Router();

passport.use(new GoogleStrategy({
    clientID: process.env.GOOGLE_CLIENT_ID,
    clientSecret: process.env.GOOGLE_CLIENT_SECRET,
    callbackURL: "/auth/google/callback"
}, async (accessToken, refreshToken, profile, done) => {
    try {
        let user = await User.findOne({ where: { googleId: profile.id } });
        
        if (!user) {
            user = await User.create({
                googleId: profile.id,
                email: profile.emails[0].value,
                firstName: profile.name.givenName,
                lastName: profile.name.familyName
            });
        }
        
        return done(null, user);
    } catch (error) {
        return done(error, null);
    }
}));

const generateToken = (user) => {
    return jwt.sign(
        { 
            id: user.id, 
            email: user.email 
        },
        process.env.JWT_SECRET || 'default-secret',
        { expiresIn: '24h' }
    );
};

router.post('/register', async (req, res) => {
    try {
        const { email, password, firstName, lastName } = req.body;
        
        if (!email || !password || !firstName || !lastName) {
            return res.status(400).json({ 
                error: 'All fields are required' 
            });
        }
        
        const existingUser = await User.findOne({ where: { email } });
        if (existingUser) {
            return res.status(409).json({ 
                error: 'User already exists' 
            });
        }
        
        const hashedPassword = await bcrypt.hash(password, 10);
        
        const user = await User.create({
            email,
            password: hashedPassword,
            firstName,
            lastName
        });
        
        const token = generateToken(user);
        
        res.status(201).json({
            message: 'User created successfully',
            token,
            user: {
                id: user.id,
                email: user.email,
                firstName: user.firstName,
                lastName: user.lastName
            }
        });
    } catch (error) {
        console.error('Registration error:', error);
        res.status(500).json({ error: 'Registration failed' });
    }
});

router.post('/login', async (req, res) => {
    try {
        const { email, password } = req.body;
        
        if (!email || !password) {
            return res.status(400).json({ 
                error: 'Email and password are required' 
            });
        }
        
        const user = await User.findOne({ where: { email } });
        if (!user || !user.password) {
            return res.status(401).json({ 
                error: 'Invalid credentials' 
            });
        }
        
        const isValidPassword = await bcrypt.compare(password, user.password);
        if (!isValidPassword) {
            return res.status(401).json({ 
                error: 'Invalid credentials' 
            });
        }
        
        const token = generateToken(user);
        
        res.json({
            message: 'Login successful',
            token,
            user: {
                id: user.id,
                email: user.email,
                firstName: user.firstName,
                lastName: user.lastName
            }
        });
    } catch (error) {
        console.error('Login error:', error);
        res.status(500).json({ error: 'Login failed' });
    }
});

router.get('/google', 
    passport.authenticate('google', { scope: ['profile', 'email'] })
);

router.get('/google/callback',
    passport.authenticate('google', { session: false }),
    (req, res) => {
        const token = generateToken(req.user);
        res.redirect(`${process.env.CLIENT_URL || 'http://localhost:8081'}?token=${token}`);
    }
);

router.post('/verify', (req, res) => {
    const { token } = req.body;
    
    if (!token) {
        return res.status(400).json({ error: 'Token required' });
    }
    
    try {
        const decoded = jwt.verify(token, process.env.JWT_SECRET || 'default-secret');
        res.json({ valid: true, user: decoded });
    } catch (error) {
        res.status(401).json({ valid: false, error: 'Invalid token' });
    }
});

module.exports = router;