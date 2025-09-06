/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Database models and configuration
*/

const { Sequelize, DataTypes } = require('sequelize');
const path = require('path');

const sequelize = process.env.NODE_ENV === 'test' 
    ? new Sequelize('sqlite::memory:', { logging: false })
    : process.env.DB_HOST 
        ? new Sequelize(process.env.DB_NAME, process.env.DB_USER, process.env.DB_PASSWORD, {
            host: process.env.DB_HOST,
            port: process.env.DB_PORT || 5432,
            dialect: 'postgres',
            logging: false
        })
        : new Sequelize({
            dialect: 'sqlite',
            storage: path.join(__dirname, '../../db/area.sqlite'),
            logging: false
        });

const User = sequelize.define('User', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    email: {
        type: DataTypes.STRING,
        unique: true,
        allowNull: false,
        validate: {
            isEmail: true
        }
    },
    password: {
        type: DataTypes.STRING,
        allowNull: true
    },
    firstName: {
        type: DataTypes.STRING,
        allowNull: false
    },
    lastName: {
        type: DataTypes.STRING,
        allowNull: false
    },
    googleId: {
        type: DataTypes.STRING,
        unique: true,
        allowNull: true
    },
    isActive: {
        type: DataTypes.BOOLEAN,
        defaultValue: true
    }
}, {
    timestamps: true,
    tableName: 'users'
});

const Service = sequelize.define('Service', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    name: {
        type: DataTypes.STRING,
        allowNull: false,
        unique: true
    },
    displayName: {
        type: DataTypes.STRING,
        allowNull: false
    },
    description: {
        type: DataTypes.TEXT,
        allowNull: true
    },
    icon: {
        type: DataTypes.STRING,
        allowNull: true
    },
    isActive: {
        type: DataTypes.BOOLEAN,
        defaultValue: true
    },
    config: {
        type: DataTypes.JSON,
        defaultValue: {}
    }
}, {
    timestamps: true,
    tableName: 'services'
});

const Action = sequelize.define('Action', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    serviceId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Service,
            key: 'id'
        }
    },
    name: {
        type: DataTypes.STRING,
        allowNull: false
    },
    displayName: {
        type: DataTypes.STRING,
        allowNull: false
    },
    description: {
        type: DataTypes.TEXT,
        allowNull: true
    },
    type: {
        type: DataTypes.ENUM('trigger', 'reaction'),
        allowNull: false
    },
    config: {
        type: DataTypes.JSON,
        defaultValue: {}
    },
    isActive: {
        type: DataTypes.BOOLEAN,
        defaultValue: true
    }
}, {
    timestamps: true,
    tableName: 'actions'
});

const Automation = sequelize.define('Automation', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    userId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: User,
            key: 'id'
        }
    },
    name: {
        type: DataTypes.STRING,
        allowNull: false
    },
    description: {
        type: DataTypes.TEXT,
        allowNull: true
    },
    triggerId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Action,
            key: 'id'
        }
    },
    reactionId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Action,
            key: 'id'
        }
    },
    triggerConfig: {
        type: DataTypes.JSON,
        defaultValue: {}
    },
    reactionConfig: {
        type: DataTypes.JSON,
        defaultValue: {}
    },
    isActive: {
        type: DataTypes.BOOLEAN,
        defaultValue: true
    },
    lastTriggered: {
        type: DataTypes.DATE,
        allowNull: true
    },
    triggerCount: {
        type: DataTypes.INTEGER,
        defaultValue: 0
    }
}, {
    timestamps: true,
    tableName: 'automations'
});

const UserService = sequelize.define('UserService', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    userId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: User,
            key: 'id'
        }
    },
    serviceId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Service,
            key: 'id'
        }
    },
    accessToken: {
        type: DataTypes.TEXT,
        allowNull: true
    },
    refreshToken: {
        type: DataTypes.TEXT,
        allowNull: true
    },
    config: {
        type: DataTypes.JSON,
        defaultValue: {}
    },
    isConnected: {
        type: DataTypes.BOOLEAN,
        defaultValue: true
    }
}, {
    timestamps: true,
    tableName: 'user_services'
});

User.hasMany(Automation, { foreignKey: 'userId', as: 'automations' });
User.hasMany(UserService, { foreignKey: 'userId', as: 'services' });

Service.hasMany(Action, { foreignKey: 'serviceId', as: 'actions' });
Service.hasMany(UserService, { foreignKey: 'serviceId', as: 'users' });

Action.belongsTo(Service, { foreignKey: 'serviceId', as: 'service' });
Action.hasMany(Automation, { foreignKey: 'triggerId', as: 'triggerAutomations' });
Action.hasMany(Automation, { foreignKey: 'reactionId', as: 'reactionAutomations' });

Automation.belongsTo(User, { foreignKey: 'userId', as: 'user' });
Automation.belongsTo(Action, { foreignKey: 'triggerId', as: 'trigger' });
Automation.belongsTo(Action, { foreignKey: 'reactionId', as: 'reaction' });

UserService.belongsTo(User, { foreignKey: 'userId', as: 'user' });
UserService.belongsTo(Service, { foreignKey: 'serviceId', as: 'service' });

module.exports = {
    sequelize,
    User,
    Service,
    Action,
    Automation,
    UserService
};