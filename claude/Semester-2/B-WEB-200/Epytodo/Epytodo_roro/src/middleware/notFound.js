/*
** EPITECH PROJECT, 2024
** EpyTodo
** File description:
** Not found middleware
*/

const notFound = (req, res, next) => {
    res.status(404).json({ msg: 'Not found' });
};

const errorHandler = (err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ msg: 'Internal server error' });
};

module.exports = { notFound, errorHandler };