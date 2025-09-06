/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Registration page component
*/

import React, { useState } from 'react';
import {
    Box,
    Container,
    Paper,
    TextField,
    Button,
    Typography,
    Link,
    Grid,
    Alert
} from '@mui/material';
import { useNavigate, Link as RouterLink } from 'react-router-dom';
import { useForm } from 'react-hook-form';
import toast from 'react-hot-toast';

import { useAuth } from '../contexts/AuthContext';

function RegisterPage() {
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState('');
    const { register: registerUser } = useAuth();
    const navigate = useNavigate();
    
    const { register, handleSubmit, watch, formState: { errors } } = useForm();
    const password = watch('password');

    const onSubmit = async (data) => {
        setLoading(true);
        setError('');
        
        try {
            const result = await registerUser({
                email: data.email,
                password: data.password,
                firstName: data.firstName,
                lastName: data.lastName
            });
            
            if (result.success) {
                toast.success('Account created successfully!');
                navigate('/dashboard');
            } else {
                setError(result.error);
            }
        } catch (err) {
            setError('An unexpected error occurred');
        } finally {
            setLoading(false);
        }
    };

    return (
        <Container maxWidth="sm">
            <Box
                sx={{
                    minHeight: '100vh',
                    display: 'flex',
                    alignItems: 'center',
                    justifyContent: 'center',
                    py: 4
                }}
            >
                <Paper
                    elevation={3}
                    sx={{
                        p: 4,
                        width: '100%',
                        maxWidth: 500
                    }}
                >
                    <Box sx={{ textAlign: 'center', mb: 3 }}>
                        <Typography variant="h4" component="h1" gutterBottom>
                            Create Account
                        </Typography>
                        <Typography color="text.secondary">
                            Join AREA and start automating today
                        </Typography>
                    </Box>

                    {error && (
                        <Alert severity="error" sx={{ mb: 2 }}>
                            {error}
                        </Alert>
                    )}

                    <form onSubmit={handleSubmit(onSubmit)}>
                        <Grid container spacing={2}>
                            <Grid item xs={12} sm={6}>
                                <TextField
                                    fullWidth
                                    label="First Name"
                                    autoFocus
                                    {...register('firstName', {
                                        required: 'First name is required',
                                        minLength: {
                                            value: 2,
                                            message: 'First name must be at least 2 characters'
                                        }
                                    })}
                                    error={!!errors.firstName}
                                    helperText={errors.firstName?.message}
                                />
                            </Grid>
                            <Grid item xs={12} sm={6}>
                                <TextField
                                    fullWidth
                                    label="Last Name"
                                    {...register('lastName', {
                                        required: 'Last name is required',
                                        minLength: {
                                            value: 2,
                                            message: 'Last name must be at least 2 characters'
                                        }
                                    })}
                                    error={!!errors.lastName}
                                    helperText={errors.lastName?.message}
                                />
                            </Grid>
                        </Grid>
                        
                        <TextField
                            fullWidth
                            label="Email"
                            type="email"
                            margin="normal"
                            {...register('email', {
                                required: 'Email is required',
                                pattern: {
                                    value: /^\S+@\S+$/i,
                                    message: 'Invalid email address'
                                }
                            })}
                            error={!!errors.email}
                            helperText={errors.email?.message}
                        />
                        
                        <TextField
                            fullWidth
                            label="Password"
                            type="password"
                            margin="normal"
                            {...register('password', {
                                required: 'Password is required',
                                minLength: {
                                    value: 6,
                                    message: 'Password must be at least 6 characters'
                                }
                            })}
                            error={!!errors.password}
                            helperText={errors.password?.message}
                        />

                        <TextField
                            fullWidth
                            label="Confirm Password"
                            type="password"
                            margin="normal"
                            {...register('confirmPassword', {
                                required: 'Please confirm your password',
                                validate: value =>
                                    value === password || 'Passwords do not match'
                            })}
                            error={!!errors.confirmPassword}
                            helperText={errors.confirmPassword?.message}
                        />

                        <Button
                            type="submit"
                            fullWidth
                            variant="contained"
                            sx={{ mt: 3, mb: 2 }}
                            disabled={loading}
                        >
                            {loading ? 'Creating Account...' : 'Create Account'}
                        </Button>
                    </form>

                    <Box sx={{ textAlign: 'center', mt: 2 }}>
                        <Typography variant="body2">
                            Already have an account?{' '}
                            <Link component={RouterLink} to="/login">
                                Sign in
                            </Link>
                        </Typography>
                    </Box>
                </Paper>
            </Box>
        </Container>
    );
}

export default RegisterPage;