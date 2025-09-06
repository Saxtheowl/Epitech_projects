/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Dashboard page component
*/

import React from 'react';
import {
    Box,
    Container,
    Typography,
    Grid,
    Card,
    CardContent,
    Button,
    Avatar,
    Chip,
    LinearProgress
} from '@mui/material';
import {
    Add,
    AutoAwesome,
    Build,
    TrendingUp,
    PlayArrow,
    Pause
} from '@mui/icons-material';
import { useNavigate } from 'react-router-dom';
import { useQuery } from 'react-query';

import { useAuth } from '../contexts/AuthContext';
import { automationService, serviceService } from '../services/api';

function DashboardPage() {
    const { user } = useAuth();
    const navigate = useNavigate();

    const { data: automations, isLoading: loadingAutomations } = useQuery(
        'automations',
        automationService.getAll,
        {
            select: (response) => response.data.automations
        }
    );

    const { data: services, isLoading: loadingServices } = useQuery(
        'services',
        serviceService.getAll,
        {
            select: (response) => response.data.services
        }
    );

    const activeAutomations = automations?.filter(auto => auto.isActive) || [];
    const totalTriggers = automations?.reduce((sum, auto) => sum + auto.triggerCount, 0) || 0;

    const stats = [
        {
            title: 'Total Automations',
            value: automations?.length || 0,
            icon: <AutoAwesome />,
            color: 'primary'
        },
        {
            title: 'Active Automations',
            value: activeAutomations.length,
            icon: <PlayArrow />,
            color: 'success'
        },
        {
            title: 'Connected Services',
            value: services?.length || 0,
            icon: <Build />,
            color: 'info'
        },
        {
            title: 'Total Triggers',
            value: totalTriggers,
            icon: <TrendingUp />,
            color: 'warning'
        }
    ];

    if (loadingAutomations || loadingServices) {
        return (
            <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
                <LinearProgress />
            </Container>
        );
    }

    return (
        <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
            <Box sx={{ mb: 4 }}>
                <Typography variant="h4" component="h1" gutterBottom>
                    Welcome back, {user?.firstName}!
                </Typography>
                <Typography variant="body1" color="text.secondary">
                    Here's an overview of your automation dashboard
                </Typography>
            </Box>

            <Grid container spacing={3} sx={{ mb: 4 }}>
                {stats.map((stat, index) => (
                    <Grid item xs={12} sm={6} md={3} key={index}>
                        <Card>
                            <CardContent>
                                <Box sx={{ display: 'flex', alignItems: 'center', mb: 1 }}>
                                    <Avatar
                                        sx={{ 
                                            bgcolor: `${stat.color}.main`,
                                            width: 40,
                                            height: 40,
                                            mr: 2
                                        }}
                                    >
                                        {stat.icon}
                                    </Avatar>
                                    <Typography variant="h4" component="div">
                                        {stat.value}
                                    </Typography>
                                </Box>
                                <Typography color="text.secondary" variant="body2">
                                    {stat.title}
                                </Typography>
                            </CardContent>
                        </Card>
                    </Grid>
                ))}
            </Grid>

            <Grid container spacing={3}>
                <Grid item xs={12} md={8}>
                    <Card sx={{ height: '100%' }}>
                        <CardContent>
                            <Box sx={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', mb: 2 }}>
                                <Typography variant="h6" component="h2">
                                    Recent Automations
                                </Typography>
                                <Button
                                    variant="contained"
                                    startIcon={<Add />}
                                    onClick={() => navigate('/automations/create')}
                                >
                                    Create New
                                </Button>
                            </Box>
                            
                            {automations && automations.length > 0 ? (
                                <Box>
                                    {automations.slice(0, 5).map((automation) => (
                                        <Box
                                            key={automation.id}
                                            sx={{
                                                p: 2,
                                                mb: 1,
                                                border: '1px solid',
                                                borderColor: 'divider',
                                                borderRadius: 1,
                                                display: 'flex',
                                                justifyContent: 'space-between',
                                                alignItems: 'center'
                                            }}
                                        >
                                            <Box>
                                                <Typography variant="subtitle1">
                                                    {automation.name}
                                                </Typography>
                                                <Typography variant="body2" color="text.secondary">
                                                    {automation.trigger?.service?.displayName} → {automation.reaction?.service?.displayName}
                                                </Typography>
                                                <Typography variant="caption" color="text.secondary">
                                                    Triggered {automation.triggerCount} times
                                                </Typography>
                                            </Box>
                                            <Box sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
                                                <Chip
                                                    label={automation.isActive ? 'Active' : 'Paused'}
                                                    color={automation.isActive ? 'success' : 'default'}
                                                    size="small"
                                                    icon={automation.isActive ? <PlayArrow /> : <Pause />}
                                                />
                                            </Box>
                                        </Box>
                                    ))}
                                    <Button
                                        fullWidth
                                        variant="text"
                                        onClick={() => navigate('/automations')}
                                        sx={{ mt: 2 }}
                                    >
                                        View All Automations
                                    </Button>
                                </Box>
                            ) : (
                                <Box sx={{ textAlign: 'center', py: 4 }}>
                                    <Typography variant="h6" color="text.secondary" gutterBottom>
                                        No automations yet
                                    </Typography>
                                    <Typography variant="body2" color="text.secondary" sx={{ mb: 2 }}>
                                        Create your first automation to get started
                                    </Typography>
                                    <Button
                                        variant="contained"
                                        startIcon={<Add />}
                                        onClick={() => navigate('/automations/create')}
                                    >
                                        Create Your First Automation
                                    </Button>
                                </Box>
                            )}
                        </CardContent>
                    </Card>
                </Grid>

                <Grid item xs={12} md={4}>
                    <Card sx={{ height: '100%' }}>
                        <CardContent>
                            <Typography variant="h6" component="h2" gutterBottom>
                                Quick Actions
                            </Typography>
                            <Box sx={{ display: 'flex', flexDirection: 'column', gap: 1 }}>
                                <Button
                                    fullWidth
                                    variant="outlined"
                                    startIcon={<Add />}
                                    onClick={() => navigate('/automations/create')}
                                >
                                    Create Automation
                                </Button>
                                <Button
                                    fullWidth
                                    variant="outlined"
                                    startIcon={<Build />}
                                    onClick={() => navigate('/services')}
                                >
                                    Connect Services
                                </Button>
                                <Button
                                    fullWidth
                                    variant="outlined"
                                    startIcon={<AutoAwesome />}
                                    onClick={() => navigate('/automations')}
                                >
                                    Manage Automations
                                </Button>
                            </Box>
                        </CardContent>
                    </Card>
                </Grid>
            </Grid>
        </Container>
    );
}

export default DashboardPage;