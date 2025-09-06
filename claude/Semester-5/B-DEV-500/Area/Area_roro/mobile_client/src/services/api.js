/*
** EPITECH PROJECT, 2025
** Area
** File description:
** API service for mobile app
*/

import axios from 'axios';
import * as SecureStore from 'expo-secure-store';
import Constants from 'expo-constants';

const API_BASE_URL = Constants.expoConfig?.extra?.apiUrl || 'http://localhost:8080';

const api = axios.create({
    baseURL: API_BASE_URL,
    timeout: 10000,
});

api.interceptors.request.use(
    async (config) => {
        try {
            const token = await SecureStore.getItemAsync('area_token');
            if (token) {
                config.headers.Authorization = `Bearer ${token}`;
            }
        } catch (error) {
            console.error('Error retrieving token:', error);
        }
        return config;
    },
    (error) => {
        return Promise.reject(error);
    }
);

api.interceptors.response.use(
    (response) => response,
    async (error) => {
        if (error.response?.status === 401) {
            await SecureStore.deleteItemAsync('area_token');
        }
        return Promise.reject(error);
    }
);

export const authService = {
    login: (credentials) => api.post('/auth/login', credentials),
    register: (userData) => api.post('/auth/register', userData),
    verify: (token) => api.post('/auth/verify', { token })
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

export const automationService = {
    getAll: () => api.get('/api/automations'),
    getById: (id) => api.get(`/api/automations/${id}`),
    create: (data) => api.post('/api/automations', data),
    update: (id, data) => api.put(`/api/automations/${id}`, data),
    delete: (id) => api.delete(`/api/automations/${id}`),
    trigger: (id, data) => api.post(`/api/automations/${id}/trigger`, data)
};

export default api;