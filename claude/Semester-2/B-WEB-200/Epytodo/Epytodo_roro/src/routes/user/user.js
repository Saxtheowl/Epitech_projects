/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** User routes
*/

const express = require('express');
const bcrypt = require('bcryptjs');
const auth = require('../../middleware/auth');
const { getUserById, getUserByEmail, getUserTodos, updateUser, deleteUser } = require('./user.query');

const router = express.Router();

// Get current user info
router.get('/user', auth, (req, res) => {
    getUserById(req.user.userId, (err, results) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }

        res.status(200).json(results[0]);
    });
});

// Get user todos
router.get('/user/todos', auth, (req, res) => {
    getUserTodos(req.user.userId, (err, results) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        res.status(200).json(results);
    });
});

// Get user by ID or email
router.get('/user/:identifier', auth, (req, res) => {
    const { identifier } = req.params;
    
    // Check if identifier is email (contains @) or ID (numeric)
    const isEmail = identifier.includes('@');
    
    const queryFunction = isEmail ? getUserByEmail : getUserById;
    
    queryFunction(identifier, (err, results) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }

        res.status(200).json(results[0]);
    });
});

// Update user
router.put('/user/:id', auth, async (req, res) => {
    try {
        const { id } = req.params;
        const { email, name, firstname, password } = req.body;

        if (!email || !name || !firstname || !password) {
            return res.status(400).json({ msg: 'Please provide all required fields' });
        }

        // Hash password if provided
        const salt = await bcrypt.genSalt(10);
        const hashedPassword = await bcrypt.hash(password, salt);

        const userData = { email, name, firstname, password: hashedPassword };

        updateUser(id, userData, (err, result) => {
            if (err) {
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (result.affectedRows === 0) {
                return res.status(404).json({ msg: 'Not found' });
            }

            // Get updated user
            getUserById(id, (err, results) => {
                if (err) {
                    return res.status(500).json({ msg: 'Internal server error' });
                }

                res.status(200).json(results[0]);
            });
        });
    } catch (error) {
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Delete user
router.delete('/user/:id', auth, (req, res) => {
    const { id } = req.params;

    deleteUser(id, (err, result) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (result.affectedRows === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }

        res.status(200).json({ msg: `Successfully deleted record number: ${id}` });
    });
});

module.exports = router;