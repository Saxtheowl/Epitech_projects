/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Registration screen component
*/

import React, { useState } from 'react';
import { View, StyleSheet, KeyboardAvoidingView, Platform, Alert, ScrollView } from 'react-native';
import { Text, TextInput, Button, Card, Title } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { useForm, Controller } from 'react-hook-form';

import { useAuth } from '../contexts/AuthContext';

const RegisterScreen = ({ navigation }) => {
    const [loading, setLoading] = useState(false);
    const { register: registerUser } = useAuth();
    const { control, handleSubmit, watch, formState: { errors } } = useForm();
    const password = watch('password');

    const onSubmit = async (data) => {
        setLoading(true);
        
        try {
            const result = await registerUser({
                email: data.email,
                password: data.password,
                firstName: data.firstName,
                lastName: data.lastName
            });
            
            if (!result.success) {
                Alert.alert('Registration Failed', result.error);
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
                <ScrollView contentContainerStyle={styles.scrollContent}>
                    <View style={styles.content}>
                        <Card style={styles.card}>
                            <Card.Content style={styles.cardContent}>
                                <Title style={styles.title}>Create Account</Title>
                                <Text style={styles.subtitle}>Join AREA and start automating</Text>

                                <View style={styles.row}>
                                    <View style={styles.halfInput}>
                                        <Controller
                                            control={control}
                                            rules={{
                                                required: 'First name is required',
                                                minLength: {
                                                    value: 2,
                                                    message: 'First name must be at least 2 characters'
                                                }
                                            }}
                                            render={({ field: { onChange, onBlur, value } }) => (
                                                <TextInput
                                                    label="First Name"
                                                    mode="outlined"
                                                    value={value}
                                                    onBlur={onBlur}
                                                    onChangeText={onChange}
                                                    style={styles.input}
                                                    error={!!errors.firstName}
                                                />
                                            )}
                                            name="firstName"
                                            defaultValue=""
                                        />
                                        {errors.firstName && (
                                            <Text style={styles.errorText}>{errors.firstName.message}</Text>
                                        )}
                                    </View>

                                    <View style={styles.halfInput}>
                                        <Controller
                                            control={control}
                                            rules={{
                                                required: 'Last name is required',
                                                minLength: {
                                                    value: 2,
                                                    message: 'Last name must be at least 2 characters'
                                                }
                                            }}
                                            render={({ field: { onChange, onBlur, value } }) => (
                                                <TextInput
                                                    label="Last Name"
                                                    mode="outlined"
                                                    value={value}
                                                    onBlur={onBlur}
                                                    onChangeText={onChange}
                                                    style={styles.input}
                                                    error={!!errors.lastName}
                                                />
                                            )}
                                            name="lastName"
                                            defaultValue=""
                                        />
                                        {errors.lastName && (
                                            <Text style={styles.errorText}>{errors.lastName.message}</Text>
                                        )}
                                    </View>
                                </View>

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

                                <Controller
                                    control={control}
                                    rules={{
                                        required: 'Please confirm your password',
                                        validate: value =>
                                            value === password || 'Passwords do not match'
                                    }}
                                    render={({ field: { onChange, onBlur, value } }) => (
                                        <TextInput
                                            label="Confirm Password"
                                            mode="outlined"
                                            secureTextEntry
                                            value={value}
                                            onBlur={onBlur}
                                            onChangeText={onChange}
                                            style={styles.input}
                                            error={!!errors.confirmPassword}
                                        />
                                    )}
                                    name="confirmPassword"
                                    defaultValue=""
                                />
                                {errors.confirmPassword && (
                                    <Text style={styles.errorText}>{errors.confirmPassword.message}</Text>
                                )}

                                <Button
                                    mode="contained"
                                    onPress={handleSubmit(onSubmit)}
                                    loading={loading}
                                    disabled={loading}
                                    style={styles.button}
                                >
                                    Create Account
                                </Button>

                                <View style={styles.footer}>
                                    <Text>Already have an account? </Text>
                                    <Button
                                        mode="text"
                                        onPress={() => navigation.navigate('Login')}
                                        compact
                                    >
                                        Sign in
                                    </Button>
                                </View>
                            </Card.Content>
                        </Card>
                    </View>
                </ScrollView>
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
    scrollContent: {
        flexGrow: 1,
        justifyContent: 'center',
        padding: 20,
    },
    content: {
        flex: 1,
        justifyContent: 'center',
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
    row: {
        flexDirection: 'row',
        justifyContent: 'space-between',
    },
    halfInput: {
        flex: 0.48,
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

export default RegisterScreen;