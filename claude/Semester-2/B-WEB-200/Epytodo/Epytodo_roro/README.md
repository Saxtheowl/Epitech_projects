# EpyTodo - Todo API

A RESTful API for managing todos built with Node.js, Express, and MySQL.

## Features

- User authentication with JWT tokens
- Password hashing with bcryptjs
- CRUD operations for users and todos
- Protected routes
- MySQL database integration
- Comprehensive error handling

## Setup

### Prerequisites

- Node.js (v14 or higher)
- MySQL server
- npm or yarn

### Installation

1. Install dependencies:
```bash
npm install
```

2. Configure environment variables:
Create a `.env` file with your database configuration:
```env
MYSQL_DATABASE=epytodo
MYSQL_HOST=localhost
MYSQL_USER=root
MYSQL_ROOT_PASSWORD=your_password
SECRET=your_jwt_secret
PORT=3000
```

3. Set up the database:
```bash
cat epytodo.sql | mysql -u root -p
```

4. Start the server:
```bash
npm start
# or for development with auto-reload
npm run dev
```

## API Endpoints

### Authentication Routes
- `POST /register` - Register a new user
- `POST /login` - Login user

### User Routes (Protected)
- `GET /user` - Get current user info
- `GET /user/todos` - Get user's todos
- `GET /user/:id` - Get user by ID
- `GET /user/:email` - Get user by email
- `PUT /user/:id` - Update user
- `DELETE /user/:id` - Delete user

### Todo Routes (Protected)
- `GET /todo` - Get all todos
- `GET /todo/:id` - Get todo by ID
- `POST /todo` - Create new todo
- `PUT /todo/:id` - Update todo
- `DELETE /todo/:id` - Delete todo

## Authentication

Protected routes require a valid JWT token in the `Authorization` header:
```
Authorization: Bearer <token>
```

## Database Schema

### User Table
- id (auto-increment, primary key)
- email (unique, not null)
- password (hashed, not null)
- name (not null)
- firstname (not null)
- created_at (default: current timestamp)

### Todo Table
- id (auto-increment, primary key)
- title (not null)
- description (not null)
- created_at (default: current timestamp)
- due_time (datetime, not null)
- status (enum: 'not started', 'todo', 'in progress', 'done')
- user_id (foreign key to user.id)

## Testing

Run tests with:
```bash
npm test
```

## Project Structure

```
src/
├── config/
│   └── db.js              # Database configuration
├── middleware/
│   ├── auth.js            # JWT authentication middleware
│   └── notFound.js        # Error handling middleware
├── routes/
│   ├── auth/
│   │   └── auth.js        # Authentication routes
│   ├── todos/
│   │   ├── todos.js       # Todo routes
│   │   └── todos.query.js # Todo database queries
│   └── user/
│       ├── user.js        # User routes
│       └── user.query.js  # User database queries
└── index.js               # Main application file
```