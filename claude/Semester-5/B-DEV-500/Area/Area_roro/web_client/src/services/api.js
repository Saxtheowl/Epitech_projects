/*
** EPITECH PROJECT, 2025
** Area
** File description:
** API service functions
*/

import axios from 'axios';
import Cookies from 'js-cookie';

const API_BASE_URL = import.meta.env.VITE_API_URL || 'http://localhost:8080';

const api = axios.create({
    baseURL: API_BASE_URL,
    timeout: 10000
});

api.interceptors.request.use(
    (config) => {
        const token = Cookies.get('area_token');
        if (token) {
            config.headers.Authorization = `Bearer ${token}`;
        }
        return config;
    },
    (error) => {
        return Promise.reject(error);
    }
);

api.interceptors.response.use(
    (response) => response,
    (error) => {
        if (error.response?.status === 401) {
            Cookies.remove('area_token');
            window.location.href = '/login';
        }
        return Promise.reject(error);
    }
);

export const authService = {
    login: (credentials) => api.post('/auth/login', credentials),
    register: (userData) => api.post('/auth/register', userData),
    verify: (token) => api.post('/auth/verify', { token }),
    googleAuth: () => `${API_BASE_URL}/auth/google`
};

export const userService = {
    getProfile: () => api.get('/api/users/profile'),
    updateProfile: (data) => api.put('/api/users/profile', data),
    deleteAccount: () => api.delete('/api/users/account')
};

export const serviceService = {
    getAll: () => api.get('/api/services'),
    getById: (id) => api.get(`/api/services/${id}`),
    connect: (id, data) => api.post(`/api/services/${id}/connect`, data),
    disconnect: (id) => api.delete(`/api/services/${id}/disconnect`)
};

export const actionService = {
    getAll: (type) => api.get('/api/actions', { params: { type } }),
    getById: (id) => api.get(`/api/actions/${id}`),
    getByService: (serviceId, type) => api.get(`/api/actions/service/${serviceId}`, { params: { type } })
};

export const automationService = {
    getAll: () => api.get('/api/automations'),
    getById: (id) => api.get(`/api/automations/${id}`),
    create: (data) => api.post('/api/automations', data),
    update: (id, data) => api.put(`/api/automations/${id}`, data),
    delete: (id) => api.delete(`/api/automations/${id}`),
    trigger: (id, data) => api.post(`/api/automations/${id}/trigger`, data)
};

export const aboutService = {
    get: () => api.get('/about.json')
};

export default api;