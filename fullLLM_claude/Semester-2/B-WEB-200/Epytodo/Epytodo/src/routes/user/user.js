const express = require('express');
const bcrypt = require('bcryptjs');
const auth = require('../../middleware/auth');
const { getUserById, getUserByEmail, getUserTodos, updateUser, deleteUser } = require('./user.query');

const router = express.Router();

// Get current user
router.get('/', auth, (req, res) => {
    try {
        getUserById(req.user.id, (err, results) => {
            if (err) {
                console.error(err);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (results.length === 0) {
                return res.status(404).json({ msg: 'Not found' });
            }

            res.json(results[0]);
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Get user todos
router.get('/todos', auth, (req, res) => {
    try {
        getUserTodos(req.user.id, (err, results) => {
            if (err) {
                console.error(err);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            res.json(results);
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Get user by ID or email
router.get('/:identifier', auth, (req, res) => {
    const { identifier } = req.params;
    
    try {
        // Check if identifier is email (contains @) or ID
        const isEmail = identifier.includes('@');
        const queryFn = isEmail ? getUserByEmail : getUserById;
        
        queryFn(identifier, (err, results) => {
            if (err) {
                console.error(err);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (results.length === 0) {
                return res.status(404).json({ msg: 'Not found' });
            }

            res.json(results[0]);
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Update user
router.put('/:id', auth, async (req, res) => {
    const { id } = req.params;
    const { email, name, firstname, password } = req.body;

    try {
        let hashedPassword = password;
        if (password) {
            const salt = await bcrypt.genSalt(10);
            hashedPassword = await bcrypt.hash(password, salt);
        }

        const userData = { email, name, firstname, password: hashedPassword };
        
        updateUser(id, userData, (err, result) => {
            if (err) {
                console.error(err);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (result.affectedRows === 0) {
                return res.status(404).json({ msg: 'Not found' });
            }

            // Get updated user
            getUserById(id, (err, results) => {
                if (err) {
                    console.error(err);
                    return res.status(500).json({ msg: 'Internal server error' });
                }
                res.json(results[0]);
            });
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

// Delete user
router.delete('/:id', auth, (req, res) => {
    const { id } = req.params;

    try {
        deleteUser(id, (err, result) => {
            if (err) {
                console.error(err);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            if (result.affectedRows === 0) {
                return res.status(404).json({ msg: 'Not found' });
            }

            res.json({ msg: `Successfully deleted record number: ${id}` });
        });
    } catch (error) {
        console.error(error);
        res.status(500).json({ msg: 'Internal server error' });
    }
});

module.exports = router;