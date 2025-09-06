/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Main App component with routing
*/

import React from 'react';
import { Routes, Route, Navigate } from 'react-router-dom';
import { Box } from '@mui/material';

import { useAuth } from './contexts/AuthContext';
import Navbar from './components/Navbar';
import ProtectedRoute from './components/ProtectedRoute';

import HomePage from './pages/HomePage';
import LoginPage from './pages/LoginPage';
import RegisterPage from './pages/RegisterPage';
import DashboardPage from './pages/DashboardPage';
import ServicesPage from './pages/ServicesPage';
import AutomationsPage from './pages/AutomationsPage';
import CreateAutomationPage from './pages/CreateAutomationPage';
import ProfilePage from './pages/ProfilePage';

function App() {
    const { user, loading } = useAuth();

    if (loading) {
        return (
            <Box 
                display="flex" 
                justifyContent="center" 
                alignItems="center" 
                minHeight="100vh"
            >
                Loading...
            </Box>
        );
    }

    return (
        <Box sx={{ minHeight: '100vh', backgroundColor: 'background.default' }}>
            {user && <Navbar />}
            
            <Routes>
                <Route 
                    path="/" 
                    element={user ? <Navigate to="/dashboard" /> : <HomePage />} 
                />
                <Route 
                    path="/login" 
                    element={user ? <Navigate to="/dashboard" /> : <LoginPage />} 
                />
                <Route 
                    path="/register" 
                    element={user ? <Navigate to="/dashboard" /> : <RegisterPage />} 
                />
                
                <Route 
                    path="/dashboard" 
                    element={
                        <ProtectedRoute>
                            <DashboardPage />
                        </ProtectedRoute>
                    } 
                />
                <Route 
                    path="/services" 
                    element={
                        <ProtectedRoute>
                            <ServicesPage />
                        </ProtectedRoute>
                    } 
                />
                <Route 
                    path="/automations" 
                    element={
                        <ProtectedRoute>
                            <AutomationsPage />
                        </ProtectedRoute>
                    } 
                />
                <Route 
                    path="/automations/create" 
                    element={
                        <ProtectedRoute>
                            <CreateAutomationPage />
                        </ProtectedRoute>
                    } 
                />
                <Route 
                    path="/profile" 
                    element={
                        <ProtectedRoute>
                            <ProfilePage />
                        </ProtectedRoute>
                    } 
                />
                
                <Route path="*" element={<Navigate to="/" />} />
            </Routes>
        </Box>
    );
}

export default App;