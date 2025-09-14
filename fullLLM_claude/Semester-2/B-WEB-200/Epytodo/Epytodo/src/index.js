const express = require('express');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());

// Routes
app.use('/register', require('./routes/auth/auth'));
app.use('/login', require('./routes/auth/auth'));
app.use('/user', require('./routes/user/user'));
app.use('/todo', require('./routes/todos/todos'));

// 404 handler
app.use(require('./middleware/notFound'));

// Error handler
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ msg: 'Internal server error' });
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});