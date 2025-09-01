/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Todo database queries
*/

const db = require('../../config/db');

const getAllTodos = (callback) => {
    db.query('SELECT * FROM todo', callback);
};

const getTodoById = (id, callback) => {
    db.query('SELECT * FROM todo WHERE id = ?', [id], callback);
};

const createTodo = (todoData, callback) => {
    const { title, description, due_time, user_id, status } = todoData;
    db.query(
        'INSERT INTO todo (title, description, due_time, user_id, status) VALUES (?, ?, ?, ?, ?)',
        [title, description, due_time, user_id, status || 'not started'],
        callback
    );
};

const updateTodo = (id, todoData, callback) => {
    const { title, description, due_time, user_id, status } = todoData;
    db.query(
        'UPDATE todo SET title = ?, description = ?, due_time = ?, user_id = ?, status = ? WHERE id = ?',
        [title, description, due_time, user_id, status, id],
        callback
    );
};

const deleteTodo = (id, callback) => {
    db.query('DELETE FROM todo WHERE id = ?', [id], callback);
};

module.exports = {
    getAllTodos,
    getTodoById,
    createTodo,
    updateTodo,
    deleteTodo
};