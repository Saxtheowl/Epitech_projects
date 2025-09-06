/*
** EPITECH PROJECT, 2025
** Area
** File description:
** Services screen component
*/

import React, { useState, useEffect } from 'react';
import { View, StyleSheet, ScrollView, RefreshControl } from 'react-native';
import { Card, Title, Paragraph, Button, Avatar, Text, Chip } from 'react-native-paper';
import { SafeAreaView } from 'react-native-safe-area-context';
import { Ionicons } from '@expo/vector-icons';

import { serviceService } from '../services/api';

const ServicesScreen = () => {
    const [services, setServices] = useState([]);
    const [loading, setLoading] = useState(true);
    const [refreshing, setRefreshing] = useState(false);

    useEffect(() => {
        loadServices();
    }, []);

    const loadServices = async () => {
        try {
            const response = await serviceService.getAll();
            setServices(response.data.services);
        } catch (error) {
            console.error('Error loading services:', error);
        } finally {
            setLoading(false);
            setRefreshing(false);
        }
    };

    const onRefresh = () => {
        setRefreshing(true);
        loadServices();
    };

    const getServiceIcon = (serviceName) => {
        const icons = {
            gmail: 'mail',
            discord: 'chatbubbles',
            spotify: 'musical-notes',
        };
        return icons[serviceName] || 'settings';
    };

    const getServiceColor = (serviceName) => {
        const colors = {
            gmail: '#ea4335',
            discord: '#7289da',
            spotify: '#1db954',
        };
        return colors[serviceName] || '#1976d2';
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
                    <Title style={styles.title}>Available Services</Title>
                    <Paragraph style={styles.subtitle}>
                        Connect your favorite services to create powerful automations
                    </Paragraph>
                </View>

                <View style={styles.servicesContainer}>
                    {services.map((service) => (
                        <Card key={service.id} style={styles.serviceCard}>
                            <Card.Content style={styles.serviceContent}>
                                <View style={styles.serviceHeader}>
                                    <Avatar.Icon
                                        size={48}
                                        icon={getServiceIcon(service.name)}
                                        style={[
                                            styles.serviceIcon,
                                            { backgroundColor: getServiceColor(service.name) }
                                        ]}
                                    />
                                    <View style={styles.serviceInfo}>
                                        <Title style={styles.serviceName}>
                                            {service.displayName}
                                        </Title>
                                        <Paragraph style={styles.serviceDescription}>
                                            {service.description || `Connect your ${service.displayName} account`}
                                        </Paragraph>
                                    </View>
                                </View>

                                <View style={styles.serviceActions}>
                                    {service.actions && service.actions.length > 0 && (
                                        <View style={styles.actionsInfo}>
                                            <Text style={styles.actionsLabel}>Available Actions:</Text>
                                            <View style={styles.actionChips}>
                                                {service.actions.slice(0, 3).map((action) => (
                                                    <Chip
                                                        key={action.id}
                                                        mode="outlined"
                                                        compact
                                                        style={styles.actionChip}
                                                    >
                                                        {action.displayName}
                                                    </Chip>
                                                ))}
                                                {service.actions.length > 3 && (
                                                    <Chip
                                                        mode="outlined"
                                                        compact
                                                        style={styles.actionChip}
                                                    >
                                                        +{service.actions.length - 3} more
                                                    </Chip>
                                                )}
                                            </View>
                                        </View>
                                    )}

                                    <Button
                                        mode="contained"
                                        style={[
                                            styles.connectButton,
                                            { backgroundColor: getServiceColor(service.name) }
                                        ]}
                                        onPress={() => {
                                            // TODO: Implement service connection
                                            console.log('Connect to', service.name);
                                        }}
                                    >
                                        Connect Service
                                    </Button>
                                </View>
                            </Card.Content>
                        </Card>
                    ))}
                </View>

                {services.length === 0 && !loading && (
                    <View style={styles.emptyState}>
                        <Ionicons name="cloud-offline-outline" size={64} color="#ccc" />
                        <Text style={styles.emptyTitle}>No services available</Text>
                        <Text style={styles.emptyDescription}>
                            Services will appear here once they are configured
                        </Text>
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
    servicesContainer: {
        flex: 1,
    },
    serviceCard: {
        marginBottom: 16,
        elevation: 2,
    },
    serviceContent: {
        padding: 16,
    },
    serviceHeader: {
        flexDirection: 'row',
        alignItems: 'flex-start',
        marginBottom: 16,
    },
    serviceIcon: {
        marginRight: 16,
    },
    serviceInfo: {
        flex: 1,
    },
    serviceName: {
        fontSize: 18,
        fontWeight: '600',
        marginBottom: 4,
    },
    serviceDescription: {
        color: '#666',
        fontSize: 14,
        lineHeight: 20,
    },
    serviceActions: {
        marginTop: 8,
    },
    actionsInfo: {
        marginBottom: 16,
    },
    actionsLabel: {
        fontSize: 14,
        fontWeight: '500',
        marginBottom: 8,
        color: '#333',
    },
    actionChips: {
        flexDirection: 'row',
        flexWrap: 'wrap',
        gap: 6,
    },
    actionChip: {
        marginRight: 6,
        marginBottom: 6,
        height: 28,
    },
    connectButton: {
        marginTop: 8,
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
    },
});

export default ServicesScreen;