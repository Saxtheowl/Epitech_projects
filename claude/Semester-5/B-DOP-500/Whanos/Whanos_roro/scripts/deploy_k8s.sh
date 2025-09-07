#!/bin/bash
##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Kubernetes deployment script for Whanos infrastructure
##

set -e

REPO_PATH="$1"
PROJECT_NAME="$2"
REGISTRY_URL="${3:-localhost:5000}"

if [ -z "$REPO_PATH" ] || [ -z "$PROJECT_NAME" ]; then
    echo "Usage: $0 <repository_path> <project_name> [registry_url]"
    exit 1
fi

cd "$REPO_PATH"

if [ ! -f "whanos.yml" ]; then
    echo "No whanos.yml found, skipping deployment"
    exit 0
fi

# Parse whanos.yml for deployment configuration
REPLICAS=$(yq eval '.deployment.replicas // 1' whanos.yml)
PORTS=$(yq eval '.deployment.ports[]?' whanos.yml)

# Generate Kubernetes manifests
cat > /tmp/deployment.yaml << EOF
apiVersion: apps/v1
kind: Deployment
metadata:
  name: $PROJECT_NAME
  labels:
    app: $PROJECT_NAME
spec:
  replicas: $REPLICAS
  selector:
    matchLabels:
      app: $PROJECT_NAME
  template:
    metadata:
      labels:
        app: $PROJECT_NAME
    spec:
      containers:
      - name: $PROJECT_NAME
        image: $REGISTRY_URL/whanos-$PROJECT_NAME:latest
        ports:
EOF

# Add ports if they exist
if [ ! -z "$PORTS" ]; then
    echo "$PORTS" | while read port; do
        if [ ! -z "$port" ]; then
            cat >> /tmp/deployment.yaml << EOF
        - containerPort: $port
EOF
        fi
    done
fi

# Create service if ports are defined
if [ ! -z "$PORTS" ]; then
    cat > /tmp/service.yaml << EOF
apiVersion: v1
kind: Service
metadata:
  name: $PROJECT_NAME-service
spec:
  selector:
    app: $PROJECT_NAME
  type: NodePort
  ports:
EOF

    echo "$PORTS" | while read port; do
        if [ ! -z "$port" ]; then
            cat >> /tmp/service.yaml << EOF
  - protocol: TCP
    port: $port
    targetPort: $port
EOF
        fi
    done
fi

# Apply manifests
echo "Deploying to Kubernetes..."
kubectl apply -f /tmp/deployment.yaml

if [ -f /tmp/service.yaml ]; then
    kubectl apply -f /tmp/service.yaml
fi

echo "Deployment completed successfully"
echo "Application: $PROJECT_NAME"
echo "Replicas: $REPLICAS"

# Clean up
rm -f /tmp/deployment.yaml /tmp/service.yaml