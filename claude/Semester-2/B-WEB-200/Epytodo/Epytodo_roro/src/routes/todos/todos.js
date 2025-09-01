/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Todo routes
*/

const express = require('express');
const auth = require('../../middleware/auth');
const { getAllTodos, getTodoById, createTodo, updateTodo, deleteTodo } = require('./todos.query');

const router = express.Router();

// Get all todos
router.get('/todo', auth, (req, res) => {
    getAllTodos((err, results) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        res.status(200).json(results);
    });
});

// Get todo by ID
router.get('/todo/:id', auth, (req, res) => {
    const { id } = req.params;

    getTodoById(id, (err, results) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }

        res.status(200).json(results[0]);
    });
});

// Create todo
router.post('/todo', auth, (req, res) => {
    const { title, description, due_time, user_id, status } = req.body;

    if (!title || !description || !due_time || !user_id) {
        return res.status(400).json({ msg: 'Please provide all required fields' });
    }

    const todoData = { title, description, due_time, user_id, status };

    createTodo(todoData, (err, result) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        // Get created todo
        getTodoById(result.insertId, (err, results) => {
            if (err) {
                return res.status(500).json({ msg: 'Internal server error' });
            }

            res.status(201).json(results[0]);
        });
    });
});

// Update todo
router.put('/todo/:id', auth, (req, res) => {
    const { id } = req.params;
    const { title, description, due_time, user_id, status } = req.body;

    if (!title || !description || !due_time || !user_id || !status) {
        return res.status(400).json({ msg: 'Please provide all required fields' });
    }

    const todoData = { title, description, due_time, user_id, status };

    updateTodo(id, todoData, (err, result) => {
        if (err) {
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (result.affectedRows === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }

        // Get updated todo
        getTodoById(id, (err, results) => {
            if (err) {
                return res.status(500).json({ msg: 'Internal server error' });
            }

            res.status(200).json(results[0]);
        });
    });
});

// Delete todo
router.delete('/todo/:id', auth, (req, res) => {
    const { id } = req.params;

    deleteTodo(id, (err, result) => {
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