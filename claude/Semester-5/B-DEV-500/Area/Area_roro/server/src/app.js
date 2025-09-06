/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Main application server
*/

const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const rateLimit = require('express-rate-limit');
require('dotenv').config();

const { sequelize } = require('./models');
const authRoutes = require('./routes/auth');
const userRoutes = require('./routes/users');
const serviceRoutes = require('./routes/services');
const actionRoutes = require('./routes/actions');
const automationRoutes = require('./routes/automations');
const swaggerSetup = require('./config/swagger');

const app = express();
const PORT = process.env.PORT || 8080;

const limiter = rateLimit({
    windowMs: 15 * 60 * 1000,
    max: 100,
    message: 'Too many requests from this IP'
});

app.use(helmet());
app.use(cors({
    origin: process.env.NODE_ENV === 'production' 
        ? ['http://localhost:8081'] 
        : true,
    credentials: true
}));
app.use(limiter);
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));

swaggerSetup(app);

app.use('/auth', authRoutes);
app.use('/api/users', userRoutes);
app.use('/api/services', serviceRoutes);
app.use('/api/actions', actionRoutes);
app.use('/api/automations', automationRoutes);

app.get('/', (req, res) => {
    res.json({
        message: 'AREA API Server',
        version: '1.0.0',
        endpoints: {
            auth: '/auth',
            users: '/api/users',
            services: '/api/services',
            actions: '/api/actions',
            automations: '/api/automations',
            docs: '/api-docs'
        }
    });
});

app.get('/about.json', (req, res) => {
    res.json({
        client: {
            host: req.ip
        },
        server: {
            current_time: Math.floor(Date.now() / 1000),
            services: [
                {
                    name: "gmail",
                    actions: [
                        {
                            name: "new_email_received",
                            description: "Triggered when a new email is received"
                        }
                    ],
                    reactions: [
                        {
                            name: "send_email",
                            description: "Send an email"
                        }
                    ]
                },
                {
                    name: "discord",
                    actions: [
                        {
                            name: "new_message",
                            description: "Triggered when a new message is posted"
                        }
                    ],
                    reactions: [
                        {
                            name: "send_message",
                            description: "Send a message to a channel"
                        }
                    ]
                },
                {
                    name: "spotify",
                    actions: [
                        {
                            name: "new_song",
                            description: "Triggered when a new song starts playing"
                        }
                    ],
                    reactions: [
                        {
                            name: "play_song",
                            description: "Play a specific song"
                        }
                    ]
                }
            ]
        }
    });
});

app.use((req, res) => {
    res.status(404).json({ error: 'Endpoint not found' });
});

app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ 
        error: 'Internal server error',
        message: process.env.NODE_ENV === 'development' ? err.message : undefined
    });
});

const startServer = async () => {
    try {
        await sequelize.authenticate();
        console.log('Database connection established successfully.');
        
        await sequelize.sync({ force: false });
        console.log('Database synchronized.');
        
        app.listen(PORT, '0.0.0.0', () => {
            console.log(`AREA Server running on port ${PORT}`);
            console.log(`API Documentation: http://localhost:${PORT}/api-docs`);
        });
    } catch (error) {
        console.error('Unable to start server:', error);
        process.exit(1);
    }
};

if (require.main === module) {
    startServer();
}

module.exports = app;