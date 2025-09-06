/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Authentication context provider
*/

import React, { createContext, useContext, useState, useEffect } from 'react';
import Cookies from 'js-cookie';
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
        const initAuth = async () => {
            try {
                const token = Cookies.get('area_token');
                if (token) {
                    const response = await authService.verify(token);
                    if (response.data.valid) {
                        setUser(response.data.user);
                    } else {
                        Cookies.remove('area_token');
                    }
                }
            } catch (error) {
                console.error('Auth initialization error:', error);
                Cookies.remove('area_token');
            } finally {
                setLoading(false);
            }
        };

        const urlParams = new URLSearchParams(window.location.search);
        const tokenFromUrl = urlParams.get('token');
        
        if (tokenFromUrl) {
            Cookies.set('area_token', tokenFromUrl, { expires: 1 });
            window.history.replaceState({}, document.title, window.location.pathname);
            setLoading(false);
            window.location.reload();
        } else {
            initAuth();
        }
    }, []);

    const login = async (credentials) => {
        try {
            const response = await authService.login(credentials);
            const { token, user: userData } = response.data;
            
            Cookies.set('area_token', token, { expires: 1 });
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
            
            Cookies.set('area_token', token, { expires: 1 });
            setUser(newUser);
            
            return { success: true, user: newUser };
        } catch (error) {
            const message = error.response?.data?.error || 'Registration failed';
            return { success: false, error: message };
        }
    };

    const logout = () => {
        Cookies.remove('area_token');
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