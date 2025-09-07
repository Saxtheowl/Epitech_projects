# Bernstein - Kubernetes Container Orchestration

This project implements a complete Kubernetes orchestration for a web poll application with microservices architecture.

## Architecture

The application consists of 5 components:
- **Poll**: Flask Python web application (frontend)
- **Redis**: Queue for vote storage
- **Worker**: Java application processing votes
- **PostgreSQL**: Database for persistent storage
- **Result**: Node.js web application displaying results

## Infrastructure

- **Traefik**: Load balancer and reverse proxy
- **cAdvisor**: Container monitoring tool
- **Kubernetes**: Container orchestration platform

## Deployment

### Prerequisites
- Kubernetes cluster (1 master + 2 worker nodes minimum)
- kubectl configured
- Access to required Docker images

### Quick Start
```bash
# Deploy all components
make deploy

# Initialize database
make init-db

# Check status
make status
```

### Manual Deployment
Follow the deployment order from the PDF:

```bash
kubectl apply -f cadvisor.daemonset.yaml

kubectl apply -f postgres.secret.yaml \
-f postgres.configmap.yaml \
-f postgres.volume.yaml \
-f postgres.deployment.yaml \
-f postgres.service.yaml

kubectl apply -f redis.configmap.yaml \
-f redis.deployment.yaml \
-f redis.service.yaml

kubectl apply -f poll.deployment.yaml \
-f worker.deployment.yaml \
-f result.deployment.yaml \
-f poll.service.yaml \
-f result.service.yaml \
-f poll.ingress.yaml \
-f result.ingress.yaml

kubectl apply -f traefik.rbac.yaml \
-f traefik.deployment.yaml \
-f traefik.service.yaml
```

### Database Initialization
```bash
echo "CREATE TABLE votes (id text PRIMARY KEY, vote text NOT NULL);" | \
kubectl exec -i deployment/postgres -- psql -U postgres
```

## Access URLs

- Poll Application: http://poll.dop.io:30021
- Results Dashboard: http://result.dop.io:30021  
- Traefik Dashboard: http://localhost:30042

## Configuration

### Environment Variables (ConfigMap)
- POSTGRES_HOST=postgres
- POSTGRES_PORT=5432
- POSTGRES_DB=postgres
- REDIS_HOST=redis

### Secrets
- POSTGRES_USER (base64 encoded)
- POSTGRES_PASSWORD (base64 encoded)

### High Availability
- Poll and Result services: 2 replicas each
- Anti-affinity rules ensure replicas run on different nodes
- Traefik: 2 replicas for load balancing

## Monitoring

cAdvisor runs as a DaemonSet on all nodes, providing container metrics at port 8080.

## Testing

```bash
# Validate YAML syntax
make tests_run

# Check deployment status
kubectl get pods --all-namespaces
kubectl get services --all-namespaces
kubectl get ingress
```

## Cleanup

```bash
make clean
```