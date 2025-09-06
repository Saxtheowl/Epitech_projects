/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Login screen component
*/

import React, { useState } from 'react';
import { View, StyleSheet, KeyboardAvoidingView, Platform, Alert } from 'react-native';
import { Text, TextInput, Button, Card, Title } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { useForm, Controller } from 'react-hook-form';

import { useAuth } from '../contexts/AuthContext';

const LoginScreen = ({ navigation }) => {
    const [loading, setLoading] = useState(false);
    const { login } = useAuth();
    const { control, handleSubmit, formState: { errors } } = useForm();

    const onSubmit = async (data) => {
        setLoading(true);
        
        try {
            const result = await login(data);
            if (!result.success) {
                Alert.alert('Login Failed', result.error);
            }
        } catch (error) {
            Alert.alert('Error', 'An unexpected error occurred');
        } finally {
            setLoading(false);
        }
    };

    return (
        <SafeAreaView style={styles.container}>
            <KeyboardAvoidingView
                behavior={Platform.OS === 'ios' ? 'padding' : 'height'}
                style={styles.keyboardView}
            >
                <View style={styles.content}>
                    <Card style={styles.card}>
                        <Card.Content style={styles.cardContent}>
                            <Title style={styles.title}>Welcome Back</Title>
                            <Text style={styles.subtitle}>Sign in to your AREA account</Text>

                            <Controller
                                control={control}
                                rules={{
                                    required: 'Email is required',
                                    pattern: {
                                        value: /^\S+@\S+$/i,
                                        message: 'Invalid email address'
                                    }
                                }}
                                render={({ field: { onChange, onBlur, value } }) => (
                                    <TextInput
                                        label="Email"
                                        mode="outlined"
                                        value={value}
                                        onBlur={onBlur}
                                        onChangeText={onChange}
                                        keyboardType="email-address"
                                        autoCapitalize="none"
                                        style={styles.input}
                                        error={!!errors.email}
                                    />
                                )}
                                name="email"
                                defaultValue=""
                            />
                            {errors.email && (
                                <Text style={styles.errorText}>{errors.email.message}</Text>
                            )}

                            <Controller
                                control={control}
                                rules={{
                                    required: 'Password is required',
                                    minLength: {
                                        value: 6,
                                        message: 'Password must be at least 6 characters'
                                    }
                                }}
                                render={({ field: { onChange, onBlur, value } }) => (
                                    <TextInput
                                        label="Password"
                                        mode="outlined"
                                        secureTextEntry
                                        value={value}
                                        onBlur={onBlur}
                                        onChangeText={onChange}
                                        style={styles.input}
                                        error={!!errors.password}
                                    />
                                )}
                                name="password"
                                defaultValue=""
                            />
                            {errors.password && (
                                <Text style={styles.errorText}>{errors.password.message}</Text>
                            )}

                            <Button
                                mode="contained"
                                onPress={handleSubmit(onSubmit)}
                                loading={loading}
                                disabled={loading}
                                style={styles.button}
                            >
                                Sign In
                            </Button>

                            <View style={styles.footer}>
                                <Text>Don't have an account? </Text>
                                <Button
                                    mode="text"
                                    onPress={() => navigation.navigate('Register')}
                                    compact
                                >
                                    Sign up
                                </Button>
                            </View>
                        </Card.Content>
                    </Card>
                </View>
            </KeyboardAvoidingView>
        </SafeAreaView>
    );
};

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#f5f5f5',
    },
    keyboardView: {
        flex: 1,
    },
    content: {
        flex: 1,
        justifyContent: 'center',
        padding: 20,
    },
    card: {
        elevation: 4,
    },
    cardContent: {
        padding: 20,
    },
    title: {
        textAlign: 'center',
        marginBottom: 8,
        fontSize: 24,
        fontWeight: 'bold',
    },
    subtitle: {
        textAlign: 'center',
        marginBottom: 24,
        color: '#666',
    },
    input: {
        marginBottom: 8,
    },
    errorText: {
        color: '#d32f2f',
        fontSize: 12,
        marginBottom: 8,
        marginLeft: 12,
    },
    button: {
        marginTop: 16,
        marginBottom: 16,
    },
    footer: {
        flexDirection: 'row',
        justifyContent: 'center',
        alignItems: 'center',
    },
});

export default LoginScreen;