/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Authentication context for mobile app
*/

import React, { createContext, useContext, useState, useEffect } from 'react';
import * as SecureStore from 'expo-secure-store';
import { authService } from '../services/api';

const AuthContext = createContext({});

export const useAuth = () => {
    const context = useContext(AuthContext);
    if (!context) {
        throw new Error('useAuth must be used within an AuthProvider');
    }
    return context;
};

export const AuthProvider = ({ children }) => {
    const [user, setUser] = useState(null);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        initAuth();
    }, []);

    const initAuth = async () => {
        try {
            const token = await SecureStore.getItemAsync('area_token');
            if (token) {
                const response = await authService.verify(token);
                if (response.data.valid) {
                    setUser(response.data.user);
                } else {
                    await SecureStore.deleteItemAsync('area_token');
                }
            }
        } catch (error) {
            console.error('Auth initialization error:', error);
            await SecureStore.deleteItemAsync('area_token');
        } finally {
            setLoading(false);
        }
    };

    const login = async (credentials) => {
        try {
            const response = await authService.login(credentials);
            const { token, user: userData } = response.data;
            
            await SecureStore.setItemAsync('area_token', token);
            setUser(userData);
            
            return { success: true, user: userData };
        } catch (error) {
            const message = error.response?.data?.error || 'Login failed';
            return { success: false, error: message };
        }
    };

    const register = async (userData) => {
        try {
            const response = await authService.register(userData);
            const { token, user: newUser } = response.data;
            
            await SecureStore.setItemAsync('area_token', token);
            setUser(newUser);
            
            return { success: true, user: newUser };
        } catch (error) {
            const message = error.response?.data?.error || 'Registration failed';
            return { success: false, error: message };
        }
    };

    const logout = async () => {
        await SecureStore.deleteItemAsync('area_token');
        setUser(null);
    };

    const value = {
        user,
        loading,
        login,
        register,
        logout,
        isAuthenticated: !!user
    };

    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );
};