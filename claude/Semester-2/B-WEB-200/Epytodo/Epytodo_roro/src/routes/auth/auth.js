/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Authentication routes
*/

const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const db = require('../../config/db');

const router = express.Router();

// Register route
router.post('/register', async (req, res) => {
    try {
        const { email, name, firstname, password } = req.body;

        if (!email || !name || !firstname || !password) {
            return res.status(400).json({ msg: 'Please provide all required fields' });
        }

        // Check if user already exists
        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (results.length > 0) {
                return res.status(409).json({ msg: 'Account already exists' });
            }

            // Hash password
            const salt = await bcrypt.genSalt(10);
            const hashedPassword = await bcrypt.hash(password, salt);

            // Insert user
            db.query(
                'INSERT INTO user (email, name, firstname, password) VALUES (?, ?, ?, ?)',
                [email, name, firstname, hashedPassword],
                (err, result) => {
                    if (err) {
                        return res.status(500).json({ msg: 'Internal server error' });
                    }

                    // Generate JWT token
                    const token = jwt.sign(
                        { userId: result.insertId, email },
                        process.env.SECRET,
                        { expiresIn: '24h' }
                    );

                    res.status(201).json({ token });
                }
            );
        });
    } catch (error) {
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Login route
router.post('/login', (req, res) => {
    try {
        const { email, password } = req.body;

        if (!email || !password) {
            return res.status(400).json({ msg: 'Please provide email and password' });
        }

        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (results.length === 0) {
                return res.status(401).json({ msg: 'Invalid Credentials' });
            }

            const user = results[0];

            // Check password
            const isMatch = await bcrypt.compare(password, user.password);
            if (!isMatch) {
                return res.status(401).json({ msg: 'Invalid Credentials' });
            }

            // Generate JWT token
            const token = jwt.sign(
                { userId: user.id, email: user.email },
                process.env.SECRET,
                { expiresIn: '24h' }
            );

            res.status(200).json({ token });
        });
    } catch (error) {
        res.status(500).json({ msg: 'Internal server error' });
    }
});

module.exports = router;