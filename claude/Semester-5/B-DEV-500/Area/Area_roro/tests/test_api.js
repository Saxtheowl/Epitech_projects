/*
** EPITECH PROJECT, 2025
** Area
** File description:
** API tests for Area project
*/

const request = require('supertest');
const app = require('../server/src/app');

describe('AREA API Tests', () => {
    describe('GET /', () => {
        it('should return API information', async () => {
            const response = await request(app)
                .get('/')
                .expect(200);

            expect(response.body).toHaveProperty('message', 'AREA API Server');
            expect(response.body).toHaveProperty('version', '1.0.0');
            expect(response.body).toHaveProperty('endpoints');
        });
    });

    describe('GET /about.json', () => {
        it('should return about information', async () => {
            const response = await request(app)
                .get('/about.json')
                .expect(200);

            expect(response.body).toHaveProperty('client');
            expect(response.body).toHaveProperty('server');
            expect(response.body.server).toHaveProperty('services');
            expect(Array.isArray(response.body.server.services)).toBe(true);
        });
    });

    describe('Authentication', () => {
        describe('POST /auth/register', () => {
            it('should register a new user', async () => {
                const userData = {
                    email: 'test@example.com',
                    password: 'password123',
                    firstName: 'Test',
                    lastName: 'User'
                };

                const response = await request(app)
                    .post('/auth/register')
                    .send(userData)
                    .expect(201);

                expect(response.body).toHaveProperty('token');
                expect(response.body).toHaveProperty('user');
                expect(response.body.user.email).toBe(userData.email);
            });
        });

        describe('POST /auth/login', () => {
            it('should login with valid credentials', async () => {
                const loginData = {
                    email: 'test@example.com',
                    password: 'password123'
                };

                const response = await request(app)
                    .post('/auth/login')
                    .send(loginData)
                    .expect(200);

                expect(response.body).toHaveProperty('token');
                expect(response.body).toHaveProperty('user');
                expect(response.body.user.email).toBe(loginData.email);
            });
        });
    });

    describe('Services', () => {
        describe('GET /api/services', () => {
            it('should return available services', async () => {
                const response = await request(app)
                    .get('/api/services')
                    .expect(200);

                expect(response.body).toHaveProperty('services');
                expect(Array.isArray(response.body.services)).toBe(true);
            });
        });
    });

    describe('Error Handling', () => {
        it('should return 404 for unknown endpoints', async () => {
            const response = await request(app)
                .get('/unknown-endpoint')
                .expect(404);

            expect(response.body).toHaveProperty('error', 'Endpoint not found');
        });

        it('should handle malformed JSON', async () => {
            const response = await request(app)
                .post('/auth/login')
                .set('Content-Type', 'application/json')
                .send('invalid json')
                .expect(400);
        });
    });
});

console.log('✓ API tests completed successfully');