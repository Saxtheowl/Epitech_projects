/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Dashboard screen component
*/

import React, { useState, useEffect } from 'react';
import { View, StyleSheet, ScrollView, RefreshControl } from 'react-native';
import { Card, Title, Paragraph, Chip, Button, Avatar, Text } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { Ionicons } from '@expo/vector-icons';

import { useAuth } from '../contexts/AuthContext';
import { automationService, serviceService } from '../services/api';

const DashboardScreen = ({ navigation }) => {
    const { user } = useAuth();
    const [automations, setAutomations] = useState([]);
    const [services, setServices] = useState([]);
    const [loading, setLoading] = useState(true);
    const [refreshing, setRefreshing] = useState(false);

    useEffect(() => {
        loadData();
    }, []);

    const loadData = async () => {
        try {
            const [automationsRes, servicesRes] = await Promise.all([
                automationService.getAll(),
                serviceService.getAll()
            ]);
            
            setAutomations(automationsRes.data.automations);
            setServices(servicesRes.data.services);
        } catch (error) {
            console.error('Error loading data:', error);
        } finally {
            setLoading(false);
            setRefreshing(false);
        }
    };

    const onRefresh = () => {
        setRefreshing(true);
        loadData();
    };

    const activeAutomations = automations.filter(auto => auto.isActive);
    const totalTriggers = automations.reduce((sum, auto) => sum + auto.triggerCount, 0);

    const stats = [
        {
            title: 'Total Automations',
            value: automations.length,
            icon: 'settings',
            color: '#1976d2'
        },
        {
            title: 'Active',
            value: activeAutomations.length,
            icon: 'play',
            color: '#4caf50'
        },
        {
            title: 'Services',
            value: services.length,
            icon: 'build',
            color: '#ff9800'
        },
        {
            title: 'Triggers',
            value: totalTriggers,
            icon: 'trending-up',
            color: '#9c27b0'
        }
    ];

    return (
        <SafeAreaView style={styles.container}>
            <ScrollView
                style={styles.scrollView}
                refreshControl={
                    <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
                }
            >
                <View style={styles.header}>
                    <Title style={styles.welcomeText}>
                        Welcome back, {user?.firstName}!
                    </Title>
                    <Paragraph style={styles.subtitle}>
                        Here's your automation overview
                    </Paragraph>
                </View>

                <View style={styles.statsContainer}>
                    {stats.map((stat, index) => (
                        <Card key={index} style={styles.statCard}>
                            <Card.Content style={styles.statContent}>
                                <View style={styles.statHeader}>
                                    <Avatar.Icon
                                        size={40}
                                        icon={stat.icon}
                                        style={[styles.statIcon, { backgroundColor: stat.color }]}
                                    />
                                    <Text style={styles.statValue}>{stat.value}</Text>
                                </View>
                                <Text style={styles.statTitle}>{stat.title}</Text>
                            </Card.Content>
                        </Card>
                    ))}
                </View>

                <Card style={styles.automationsCard}>
                    <Card.Content>
                        <View style={styles.cardHeader}>
                            <Title>Recent Automations</Title>
                            <Button
                                mode="contained"
                                compact
                                onPress={() => navigation.navigate('Automations')}
                            >
                                View All
                            </Button>
                        </View>

                        {automations.length > 0 ? (
                            <View>
                                {automations.slice(0, 3).map((automation) => (
                                    <Card key={automation.id} style={styles.automationItem}>
                                        <Card.Content style={styles.automationContent}>
                                            <View style={styles.automationHeader}>
                                                <Text style={styles.automationName}>
                                                    {automation.name}
                                                </Text>
                                                <Chip
                                                    mode="outlined"
                                                    selected={automation.isActive}
                                                    style={[
                                                        styles.statusChip,
                                                        automation.isActive && styles.activeChip
                                                    ]}
                                                >
                                                    {automation.isActive ? 'Active' : 'Paused'}
                                                </Chip>
                                            </View>
                                            <Text style={styles.automationDescription}>
                                                {automation.trigger?.service?.displayName} → {automation.reaction?.service?.displayName}
                                            </Text>
                                            <Text style={styles.automationStats}>
                                                Triggered {automation.triggerCount} times
                                            </Text>
                                        </Card.Content>
                                    </Card>
                                ))}
                            </View>
                        ) : (
                            <View style={styles.emptyState}>
                                <Ionicons name="settings-outline" size={64} color="#ccc" />
                                <Text style={styles.emptyTitle}>No automations yet</Text>
                                <Text style={styles.emptyDescription}>
                                    Create your first automation to get started
                                </Text>
                                <Button
                                    mode="contained"
                                    style={styles.createButton}
                                    onPress={() => navigation.navigate('Automations')}
                                >
                                    Create Automation
                                </Button>
                            </View>
                        )}
                    </Card.Content>
                </Card>

                <Card style={styles.quickActionsCard}>
                    <Card.Content>
                        <Title>Quick Actions</Title>
                        <View style={styles.quickActions}>
                            <Button
                                mode="outlined"
                                style={styles.quickActionButton}
                                onPress={() => navigation.navigate('Automations')}
                            >
                                Manage Automations
                            </Button>
                            <Button
                                mode="outlined"
                                style={styles.quickActionButton}
                                onPress={() => navigation.navigate('Services')}
                            >
                                Connect Services
                            </Button>
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
    header: {
        marginBottom: 20,
    },
    welcomeText: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 4,
    },
    subtitle: {
        color: '#666',
        fontSize: 16,
    },
    statsContainer: {
        flexDirection: 'row',
        flexWrap: 'wrap',
        justifyContent: 'space-between',
        marginBottom: 20,
    },
    statCard: {
        width: '48%',
        marginBottom: 12,
        elevation: 2,
    },
    statContent: {
        alignItems: 'center',
        paddingVertical: 16,
    },
    statHeader: {
        flexDirection: 'row',
        alignItems: 'center',
        marginBottom: 8,
    },
    statIcon: {
        marginRight: 12,
    },
    statValue: {
        fontSize: 24,
        fontWeight: 'bold',
    },
    statTitle: {
        fontSize: 12,
        color: '#666',
        textAlign: 'center',
    },
    automationsCard: {
        marginBottom: 20,
        elevation: 2,
    },
    cardHeader: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        marginBottom: 16,
    },
    automationItem: {
        marginBottom: 8,
        elevation: 1,
    },
    automationContent: {
        paddingVertical: 12,
    },
    automationHeader: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        marginBottom: 4,
    },
    automationName: {
        fontSize: 16,
        fontWeight: '500',
        flex: 1,
    },
    statusChip: {
        height: 28,
    },
    activeChip: {
        backgroundColor: '#e8f5e8',
    },
    automationDescription: {
        color: '#666',
        fontSize: 14,
        marginBottom: 4,
    },
    automationStats: {
        color: '#999',
        fontSize: 12,
    },
    emptyState: {
        alignItems: 'center',
        paddingVertical: 32,
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
        marginBottom: 20,
    },
    createButton: {
        marginTop: 8,
    },
    quickActionsCard: {
        marginBottom: 20,
        elevation: 2,
    },
    quickActions: {
        marginTop: 12,
    },
    quickActionButton: {
        marginBottom: 8,
    },
});

export default DashboardScreen;