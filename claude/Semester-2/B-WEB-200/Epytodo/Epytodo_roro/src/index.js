/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Main application entry point
*/

const express = require('express');
require('dotenv').config();

// Import routes
const authRoutes = require('./routes/auth/auth');
const userRoutes = require('./routes/user/user');
const todoRoutes = require('./routes/todos/todos');

// Import middleware
const { notFound, errorHandler } = require('./middleware/notFound');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Routes
app.use('/', authRoutes);
app.use('/', userRoutes);
app.use('/', todoRoutes);

// Error handling middleware
app.use(notFound);
app.use(errorHandler);

// Start server
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

module.exports = app;