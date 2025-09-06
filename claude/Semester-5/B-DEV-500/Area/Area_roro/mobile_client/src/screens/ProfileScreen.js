/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Profile screen component
*/

import React, { useState } from 'react';
import { View, StyleSheet, ScrollView, Alert } from 'react-native';
import { Card, Title, Paragraph, Button, TextInput, Avatar, Divider, Text } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { useForm, Controller } from 'react-hook-form';

import { useAuth } from '../contexts/AuthContext';
import { userService } from '../services/api';

const ProfileScreen = () => {
    const { user, logout } = useAuth();
    const [editing, setEditing] = useState(false);
    const [loading, setLoading] = useState(false);
    
    const { control, handleSubmit, reset, formState: { errors } } = useForm({
        defaultValues: {
            firstName: user?.firstName || '',
            lastName: user?.lastName || ''
        }
    });

    const onSave = async (data) => {
        setLoading(true);
        
        try {
            await userService.updateProfile(data);
            Alert.alert('Success', 'Profile updated successfully');
            setEditing(false);
        } catch (error) {
            Alert.alert('Error', 'Failed to update profile');
        } finally {
            setLoading(false);
        }
    };

    const onCancel = () => {
        reset({
            firstName: user?.firstName || '',
            lastName: user?.lastName || ''
        });
        setEditing(false);
    };

    const handleLogout = () => {
        Alert.alert(
            'Logout',
            'Are you sure you want to logout?',
            [
                { text: 'Cancel', style: 'cancel' },
                { text: 'Logout', style: 'destructive', onPress: logout }
            ]
        );
    };

    const handleDeleteAccount = () => {
        Alert.alert(
            'Delete Account',
            'Are you sure you want to delete your account? This action cannot be undone.',
            [
                { text: 'Cancel', style: 'cancel' },
                {
                    text: 'Delete',
                    style: 'destructive',
                    onPress: async () => {
                        try {
                            await userService.deleteAccount();
                            Alert.alert('Account Deleted', 'Your account has been deactivated');
                            logout();
                        } catch (error) {
                            Alert.alert('Error', 'Failed to delete account');
                        }
                    }
                }
            ]
        );
    };

    return (
        <SafeAreaView style={styles.container}>
            <ScrollView style={styles.scrollView}>
                <Card style={styles.profileCard}>
                    <Card.Content style={styles.profileContent}>
                        <View style={styles.avatarSection}>
                            <Avatar.Text
                                size={80}
                                label={user?.firstName?.[0]?.toUpperCase() + user?.lastName?.[0]?.toUpperCase() || 'U'}
                                style={styles.avatar}
                            />
                            <Title style={styles.userName}>
                                {user?.firstName} {user?.lastName}
                            </Title>
                            <Text style={styles.userEmail}>{user?.email}</Text>
                        </View>

                        <Divider style={styles.divider} />

                        <View style={styles.profileForm}>
                            <Title style={styles.sectionTitle}>Profile Information</Title>
                            
                            {editing ? (
                                <View>
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
                                    />
                                    {errors.firstName && (
                                        <Text style={styles.errorText}>{errors.firstName.message}</Text>
                                    )}

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
                                    />
                                    {errors.lastName && (
                                        <Text style={styles.errorText}>{errors.lastName.message}</Text>
                                    )}

                                    <TextInput
                                        label="Email"
                                        mode="outlined"
                                        value={user?.email}
                                        disabled
                                        style={styles.input}
                                    />

                                    <View style={styles.formActions}>
                                        <Button
                                            mode="outlined"
                                            onPress={onCancel}
                                            style={styles.formButton}
                                        >
                                            Cancel
                                        </Button>
                                        <Button
                                            mode="contained"
                                            onPress={handleSubmit(onSave)}
                                            loading={loading}
                                            disabled={loading}
                                            style={styles.formButton}
                                        >
                                            Save Changes
                                        </Button>
                                    </View>
                                </View>
                            ) : (
                                <View>
                                    <View style={styles.infoRow}>
                                        <Text style={styles.infoLabel}>First Name:</Text>
                                        <Text style={styles.infoValue}>{user?.firstName}</Text>
                                    </View>
                                    <View style={styles.infoRow}>
                                        <Text style={styles.infoLabel}>Last Name:</Text>
                                        <Text style={styles.infoValue}>{user?.lastName}</Text>
                                    </View>
                                    <View style={styles.infoRow}>
                                        <Text style={styles.infoLabel}>Email:</Text>
                                        <Text style={styles.infoValue}>{user?.email}</Text>
                                    </View>

                                    <Button
                                        mode="outlined"
                                        onPress={() => setEditing(true)}
                                        style={styles.editButton}
                                    >
                                        Edit Profile
                                    </Button>
                                </View>
                            )}
                        </View>
                    </Card.Content>
                </Card>

                <Card style={styles.actionsCard}>
                    <Card.Content>
                        <Title style={styles.sectionTitle}>Account Actions</Title>
                        
                        <Button
                            mode="outlined"
                            onPress={handleLogout}
                            style={styles.actionButton}
                            icon="logout"
                        >
                            Logout
                        </Button>

                        <Button
                            mode="outlined"
                            onPress={handleDeleteAccount}
                            style={[styles.actionButton, styles.dangerButton]}
                            buttonColor="#ffebee"
                            textColor="#d32f2f"
                            icon="delete"
                        >
                            Delete Account
                        </Button>
                    </Card.Content>
                </Card>

                <Card style={styles.infoCard}>
                    <Card.Content>
                        <Title style={styles.sectionTitle}>App Information</Title>
                        <View style={styles.infoRow}>
                            <Text style={styles.infoLabel}>Version:</Text>
                            <Text style={styles.infoValue}>1.0.0</Text>
                        </View>
                        <View style={styles.infoRow}>
                            <Text style={styles.infoLabel}>Build:</Text>
                            <Text style={styles.infoValue}>Mobile Client</Text>
                        </View>
                    </Card.Content>
                </Card>
            </ScrollView>
        </SafeAreaView>
    );
};

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#f5f5f5',
    },
    scrollView: {
        flex: 1,
        padding: 16,
    },
    profileCard: {
        marginBottom: 16,
        elevation: 2,
    },
    profileContent: {
        padding: 20,
    },
    avatarSection: {
        alignItems: 'center',
        marginBottom: 20,
    },
    avatar: {
        marginBottom: 16,
        backgroundColor: '#1976d2',
    },
    userName: {
        fontSize: 22,
        fontWeight: 'bold',
        marginBottom: 4,
    },
    userEmail: {
        color: '#666',
        fontSize: 16,
    },
    divider: {
        marginVertical: 20,
    },
    profileForm: {
        marginTop: 8,
    },
    sectionTitle: {
        fontSize: 18,
        fontWeight: '600',
        marginBottom: 16,
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
    formActions: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        marginTop: 16,
    },
    formButton: {
        flex: 0.48,
    },
    infoRow: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        paddingVertical: 8,
    },
    infoLabel: {
        fontSize: 16,
        color: '#666',
        fontWeight: '500',
    },
    infoValue: {
        fontSize: 16,
        color: '#333',
    },
    editButton: {
        marginTop: 16,
    },
    actionsCard: {
        marginBottom: 16,
        elevation: 2,
    },
    actionButton: {
        marginBottom: 12,
    },
    dangerButton: {
        borderColor: '#d32f2f',
    },
    infoCard: {
        marginBottom: 16,
        elevation: 2,
    },
});

export default ProfileScreen;