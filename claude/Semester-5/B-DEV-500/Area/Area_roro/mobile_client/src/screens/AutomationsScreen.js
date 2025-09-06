/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Automations screen component
*/

import React, { useState, useEffect } from 'react';
import { View, StyleSheet, ScrollView, RefreshControl, Alert } from 'react-native';
import { Card, Title, Paragraph, Button, Chip, Text, IconButton } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { Ionicons } from '@expo/vector-icons';

import { automationService } from '../services/api';

const AutomationsScreen = () => {
    const [automations, setAutomations] = useState([]);
    const [loading, setLoading] = useState(true);
    const [refreshing, setRefreshing] = useState(false);

    useEffect(() => {
        loadAutomations();
    }, []);

    const loadAutomations = async () => {
        try {
            const response = await automationService.getAll();
            setAutomations(response.data.automations);
        } catch (error) {
            console.error('Error loading automations:', error);
        } finally {
            setLoading(false);
            setRefreshing(false);
        }
    };

    const onRefresh = () => {
        setRefreshing(true);
        loadAutomations();
    };

    const toggleAutomation = async (automation) => {
        try {
            await automationService.update(automation.id, {
                isActive: !automation.isActive
            });
            
            setAutomations(prev =>
                prev.map(auto =>
                    auto.id === automation.id
                        ? { ...auto, isActive: !auto.isActive }
                        : auto
                )
            );
        } catch (error) {
            Alert.alert('Error', 'Failed to update automation');
        }
    };

    const deleteAutomation = async (automation) => {
        Alert.alert(
            'Delete Automation',
            `Are you sure you want to delete "${automation.name}"?`,
            [
                { text: 'Cancel', style: 'cancel' },
                {
                    text: 'Delete',
                    style: 'destructive',
                    onPress: async () => {
                        try {
                            await automationService.delete(automation.id);
                            setAutomations(prev =>
                                prev.filter(auto => auto.id !== automation.id)
                            );
                        } catch (error) {
                            Alert.alert('Error', 'Failed to delete automation');
                        }
                    }
                }
            ]
        );
    };

    const triggerAutomation = async (automation) => {
        try {
            await automationService.trigger(automation.id, {});
            Alert.alert('Success', 'Automation triggered successfully');
            
            setAutomations(prev =>
                prev.map(auto =>
                    auto.id === automation.id
                        ? { ...auto, triggerCount: auto.triggerCount + 1 }
                        : auto
                )
            );
        } catch (error) {
            Alert.alert('Error', 'Failed to trigger automation');
        }
    };

    return (
        <SafeAreaView style={styles.container}>
            <ScrollView
                style={styles.scrollView}
                refreshControl={
                    <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
                }
            >
                <View style={styles.header}>
                    <Title style={styles.title}>My Automations</Title>
                    <Paragraph style={styles.subtitle}>
                        Manage your automation workflows
                    </Paragraph>
                </View>

                <View style={styles.automationsContainer}>
                    {automations.map((automation) => (
                        <Card key={automation.id} style={styles.automationCard}>
                            <Card.Content style={styles.automationContent}>
                                <View style={styles.automationHeader}>
                                    <View style={styles.automationInfo}>
                                        <Title style={styles.automationName}>
                                            {automation.name}
                                        </Title>
                                        <Paragraph style={styles.automationFlow}>
                                            {automation.trigger?.service?.displayName} → {automation.reaction?.service?.displayName}
                                        </Paragraph>
                                        {automation.description && (
                                            <Paragraph style={styles.automationDescription}>
                                                {automation.description}
                                            </Paragraph>
                                        )}
                                    </View>
                                    <View style={styles.automationActions}>
                                        <IconButton
                                            icon={automation.isActive ? 'pause' : 'play'}
                                            mode="contained"
                                            size={20}
                                            onPress={() => toggleAutomation(automation)}
                                            style={[
                                                styles.actionButton,
                                                automation.isActive ? styles.pauseButton : styles.playButton
                                            ]}
                                        />
                                        <IconButton
                                            icon="delete"
                                            mode="contained"
                                            size={20}
                                            onPress={() => deleteAutomation(automation)}
                                            style={[styles.actionButton, styles.deleteButton]}
                                        />
                                    </View>
                                </View>

                                <View style={styles.automationStats}>
                                    <Chip
                                        mode="outlined"
                                        selected={automation.isActive}
                                        style={[
                                            styles.statusChip,
                                            automation.isActive && styles.activeChip
                                        ]}
                                        icon={automation.isActive ? 'play' : 'pause'}
                                    >
                                        {automation.isActive ? 'Active' : 'Paused'}
                                    </Chip>
                                    <Text style={styles.triggerCount}>
                                        Triggered {automation.triggerCount} times
                                    </Text>
                                </View>

                                <View style={styles.automationControls}>
                                    <Button
                                        mode="outlined"
                                        onPress={() => triggerAutomation(automation)}
                                        disabled={!automation.isActive}
                                        style={styles.triggerButton}
                                    >
                                        Test Trigger
                                    </Button>
                                </View>
                            </Card.Content>
                        </Card>
                    ))}
                </View>

                {automations.length === 0 && !loading && (
                    <View style={styles.emptyState}>
                        <Ionicons name="settings-outline" size={64} color="#ccc" />
                        <Text style={styles.emptyTitle}>No automations yet</Text>
                        <Text style={styles.emptyDescription}>
                            Create your first automation to connect your services and automate your workflow
                        </Text>
                        <Button
                            mode="contained"
                            style={styles.createButton}
                            icon="plus"
                            onPress={() => {
                                // TODO: Navigate to create automation screen
                                Alert.alert('Coming Soon', 'Automation creation will be available in the next update');
                            }}
                        >
                            Create Automation
                        </Button>
                    </View>
                )}
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
    header: {
        marginBottom: 20,
    },
    title: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 4,
    },
    subtitle: {
        color: '#666',
        fontSize: 16,
    },
    automationsContainer: {
        flex: 1,
    },
    automationCard: {
        marginBottom: 16,
        elevation: 2,
    },
    automationContent: {
        padding: 16,
    },
    automationHeader: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'flex-start',
        marginBottom: 12,
    },
    automationInfo: {
        flex: 1,
        marginRight: 12,
    },
    automationName: {
        fontSize: 18,
        fontWeight: '600',
        marginBottom: 4,
    },
    automationFlow: {
        color: '#666',
        fontSize: 14,
        marginBottom: 4,
    },
    automationDescription: {
        color: '#888',
        fontSize: 12,
        fontStyle: 'italic',
    },
    automationActions: {
        flexDirection: 'row',
    },
    actionButton: {
        marginLeft: 4,
    },
    playButton: {
        backgroundColor: '#4caf50',
    },
    pauseButton: {
        backgroundColor: '#ff9800',
    },
    deleteButton: {
        backgroundColor: '#f44336',
    },
    automationStats: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        marginBottom: 12,
    },
    statusChip: {
        height: 28,
    },
    activeChip: {
        backgroundColor: '#e8f5e8',
    },
    triggerCount: {
        color: '#666',
        fontSize: 12,
    },
    automationControls: {
        marginTop: 8,
    },
    triggerButton: {
        alignSelf: 'flex-start',
    },
    emptyState: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center',
        paddingVertical: 64,
    },
    emptyTitle: {
        fontSize: 18,
        fontWeight: '500',
        marginTop: 16,
        marginBottom: 8,
    },
    emptyDescription: {
        color: '#666',
        textAlign: 'center',
        marginBottom: 24,
        paddingHorizontal: 32,
        lineHeight: 20,
    },
    createButton: {
        marginTop: 8,
    },
});

export default AutomationsScreen;