/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Home page component
*/

import React from 'react';
import {
    Box,
    Container,
    Typography,
    Button,
    Grid,
    Card,
    CardContent,
    CardActions
} from '@mui/material';
import {
    AutoAwesome,
    ConnectWithoutContact,
    Security,
    Speed
} from '@mui/icons-material';
import { useNavigate } from 'react-router-dom';

const features = [
    {
        icon: <AutoAwesome sx={{ fontSize: 40 }} />,
        title: 'Automated Workflows',
        description: 'Create powerful automation workflows between your favorite services and applications.'
    },
    {
        icon: <ConnectWithoutContact sx={{ fontSize: 40 }} />,
        title: 'Service Integration',
        description: 'Connect Gmail, Discord, Spotify, and many other services with just a few clicks.'
    },
    {
        icon: <Security sx={{ fontSize: 40 }} />,
        title: 'Secure & Private',
        description: 'Your data is protected with industry-standard security and encryption.'
    },
    {
        icon: <Speed sx={{ fontSize: 40 }} />,
        title: 'Real-time Processing',
        description: 'Lightning-fast automation triggers and reactions for immediate results.'
    }
];

function HomePage() {
    const navigate = useNavigate();

    return (
        <Box sx={{ minHeight: '100vh', bgcolor: 'background.default' }}>
            <Container maxWidth="lg">
                <Box
                    sx={{
                        pt: 8,
                        pb: 6,
                        textAlign: 'center'
                    }}
                >
                    <Typography
                        component="h1"
                        variant="h2"
                        align="center"
                        color="text.primary"
                        gutterBottom
                        sx={{ fontWeight: 700 }}
                    >
                        AREA
                    </Typography>
                    <Typography
                        variant="h5"
                        align="center"
                        color="text.secondary"
                        paragraph
                    >
                        Action-REAction Automation Platform
                    </Typography>
                    <Typography
                        variant="h6"
                        align="center"
                        color="text.secondary"
                        paragraph
                        sx={{ maxWidth: '600px', mx: 'auto' }}
                    >
                        Connect your favorite services and create powerful automations 
                        that work seamlessly in the background.
                    </Typography>
                    <Box sx={{ mt: 4 }}>
                        <Button
                            variant="contained"
                            size="large"
                            onClick={() => navigate('/register')}
                            sx={{ mr: 2, mb: 2 }}
                        >
                            Get Started
                        </Button>
                        <Button
                            variant="outlined"
                            size="large"
                            onClick={() => navigate('/login')}
                            sx={{ mb: 2 }}
                        >
                            Sign In
                        </Button>
                    </Box>
                </Box>

                <Box sx={{ pb: 8 }}>
                    <Typography
                        component="h2"
                        variant="h4"
                        align="center"
                        color="text.primary"
                        gutterBottom
                        sx={{ mb: 4 }}
                    >
                        Why Choose AREA?
                    </Typography>
                    <Grid container spacing={4}>
                        {features.map((feature, index) => (
                            <Grid item key={index} xs={12} sm={6} md={3}>
                                <Card
                                    sx={{
                                        height: '100%',
                                        display: 'flex',
                                        flexDirection: 'column',
                                        textAlign: 'center',
                                        p: 2
                                    }}
                                >
                                    <CardContent sx={{ flexGrow: 1 }}>
                                        <Box sx={{ color: 'primary.main', mb: 2 }}>
                                            {feature.icon}
                                        </Box>
                                        <Typography
                                            gutterBottom
                                            variant="h6"
                                            component="h3"
                                            sx={{ fontWeight: 600 }}
                                        >
                                            {feature.title}
                                        </Typography>
                                        <Typography color="text.secondary">
                                            {feature.description}
                                        </Typography>
                                    </CardContent>
                                </Card>
                            </Grid>
                        ))}
                    </Grid>
                </Box>

                <Box sx={{ py: 6, textAlign: 'center', bgcolor: 'primary.main', color: 'white', borderRadius: 2, mb: 4 }}>
                    <Typography variant="h4" gutterBottom>
                        Ready to Automate?
                    </Typography>
                    <Typography variant="h6" paragraph>
                        Join thousands of users who are already saving time with AREA.
                    </Typography>
                    <Button
                        variant="contained"
                        color="secondary"
                        size="large"
                        onClick={() => navigate('/register')}
                    >
                        Start Your Free Account
                    </Button>
                </Box>
            </Container>
        </Box>
    );
}

export default HomePage;