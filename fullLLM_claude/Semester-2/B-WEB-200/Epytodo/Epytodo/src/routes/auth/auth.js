const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const db = require('../../config/db');
require('dotenv').config();

const router = express.Router();

// Register
router.post('/register', async (req, res) => {
    const { email, name, firstname, password } = req.body;

    if (!email || !name || !firstname || !password) {
        return res.status(400).json({ msg: 'Please provide all required fields' });
    }

    try {
        // Check if user exists
        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                console.error(err);
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
                        console.error(err);
                        return res.status(500).json({ msg: 'Internal server error' });
                    }

                    // Create token
                    const payload = {
                        user: {
                            id: result.insertId
                        }
                    };

                    jwt.sign(
                        payload,
                        process.env.SECRET,
                        { expiresIn: '1h' },
                        (err, token) => {
                            if (err) {
                                console.error(err);
                                return res.status(500).json({ msg: 'Internal server error' });
                            }
                            res.status(201).json({ token });
                        }
                    );
                }
            );
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Login
router.post('/login', (req, res) => {
    const { email, password } = req.body;

    if (!email || !password) {
        return res.status(400).json({ msg: 'Please provide email and password' });
    }

    try {
        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                console.error(err);
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

            // Create token
            const payload = {
                user: {
                    id: user.id
                }
            };

            jwt.sign(
                payload,
                process.env.SECRET,
                { expiresIn: '1h' },
                (err, token) => {
                    if (err) {
                        console.error(err);
                        return res.status(500).json({ msg: 'Internal server error' });
                    }
                    res.json({ token });
                }
            );
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

module.exports = router;