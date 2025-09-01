/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** User database queries
*/

const db = require('../../config/db');

const getUserById = (id, callback) => {
    db.query('SELECT * FROM user WHERE id = ?', [id], callback);
};

const getUserByEmail = (email, callback) => {
    db.query('SELECT * FROM user WHERE email = ?', [email], callback);
};

const getUserTodos = (userId, callback) => {
    db.query('SELECT * FROM todo WHERE user_id = ?', [userId], callback);
};

const updateUser = (id, userData, callback) => {
    const { email, name, firstname, password } = userData;
    db.query(
        'UPDATE user SET email = ?, name = ?, firstname = ?, password = ? WHERE id = ?',
        [email, name, firstname, password, id],
        callback
    );
};

const deleteUser = (id, callback) => {
    db.query('DELETE FROM user WHERE id = ?', [id], callback);
};

module.exports = {
    getUserById,
    getUserByEmail,
    getUserTodos,
    updateUser,
    deleteUser
};