#!/bin/bash
##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Containerization script for Whanos infrastructure
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

# Detect language
LANGUAGE=$(/scripts/detect_language.sh "$REPO_PATH")

if [ "$LANGUAGE" = "unknown" ]; then
    echo "Error: Unsupported repository format"
    exit 1
fi

echo "Detected language: $LANGUAGE"

# Determine if custom Dockerfile exists
if [ -f "Dockerfile" ]; then
    echo "Using custom Dockerfile"
    IMAGE_TAG="$REGISTRY_URL/whanos-$PROJECT_NAME:latest"
    docker build -t "$IMAGE_TAG" .
else
    echo "Using standalone Whanos image"
    IMAGE_TAG="$REGISTRY_URL/whanos-$PROJECT_NAME:latest"
    docker build -f "/images/$LANGUAGE/Dockerfile.standalone" -t "$IMAGE_TAG" .
fi

# Push to registry
echo "Pushing image to registry: $IMAGE_TAG"
docker push "$IMAGE_TAG"

echo "Containerization completed successfully"
echo "Image: $IMAGE_TAG"