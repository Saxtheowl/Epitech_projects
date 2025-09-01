# Popeye - Docker Containerization Project

A comprehensive Docker containerization project implementing a multi-service web polling application using Docker and Docker Compose.

## Overview

This project containerizes a voting application consisting of 5 interconnected services:
- **Poll**: Flask Python web application for vote collection
- **Redis**: Message queue for vote processing
- **Worker**: Java application that processes votes from Redis to PostgreSQL
- **PostgreSQL**: Database for persistent vote storage
- **Result**: Node.js web application for displaying results

## Architecture

```
Poll (Flask) → Redis → Worker (Java) → PostgreSQL ← Result (Node.js)
```

- **Frontend**: Poll (port 5000) and Result (port 5001) web interfaces
- **Backend**: Redis queue and PostgreSQL database with Java worker processing

## Services Configuration

### Poll Service
- **Base Image**: Python official image
- **Port**: 80 (mapped to host 5000)
- **Environment**: `REDIS_HOST=redis`
- **Network**: poll-tier

### Redis Service
- **Base Image**: redis:7
- **Port**: 6379
- **Networks**: poll-tier, back-tier

### Worker Service
- **Base Image**: Multi-stage build (Maven → Eclipse Temurin JRE)
- **Environment**: Redis and PostgreSQL connection settings
- **Network**: back-tier

### Database Service
- **Base Image**: postgres:16
- **Environment**: Database credentials
- **Volume**: db-data for persistence
- **Networks**: back-tier, result-tier

### Result Service
- **Base Image**: node:20-alpine
- **Port**: 80 (mapped to host 5001)
- **Environment**: PostgreSQL connection settings
- **Network**: result-tier

## Docker Images

### Poll Dockerfile
- Uses Python official image
- Installs dependencies with `pip3 install -r requirements.txt`
- Runs Flask on port 80

### Result Dockerfile
- Uses Node.js 20 Alpine image
- Excludes node_modules from build context
- Installs dependencies with `npm install`

### Worker Dockerfile (Multi-stage)
- **Stage 1**: maven:3.9.6-eclipse-temurin-21-alpine for compilation
- **Stage 2**: eclipse-temurin:21-jre-alpine for runtime
- Builds JAR with dependencies and runs with Java

## Networks

- **poll-tier**: Connects poll service to Redis
- **result-tier**: Connects result service to database
- **back-tier**: Connects worker to both Redis and database

## Usage

1. Start all services:
```bash
docker-compose up -d
```

2. Access the applications:
- Poll interface: http://localhost:5000
- Result interface: http://localhost:5001

3. Vote on the Poll page and see results on the Result page

4. Stop services:
```bash
docker-compose down
```

## Features

- **Multi-stage builds** for optimized Java application
- **Named volumes** for PostgreSQL data persistence
- **Custom networks** for service isolation and communication
- **Environment variables** for configuration
- **Automatic restarts** for service reliability
- **Database initialization** with schema.sql

## File Structure

```
.
├── docker-compose.yml
├── schema.sql
├── poll/
│   └── Dockerfile
├── result/
│   ├── Dockerfile
│   └── .dockerignore
└── worker/
    └── Dockerfile
```

## Requirements Met

- ✅ 3 custom Docker images (Poll, Result, Worker)
- ✅ Docker Compose version 3 syntax
- ✅ 5 services with proper configuration
- ✅ 3 networks for service segmentation
- ✅ Named volume for database persistence
- ✅ Environment variables for configuration
- ✅ Service dependencies and restart policies
- ✅ Multi-stage build for Worker service
- ✅ No ENTRYPOINT instructions (uses CMD only)