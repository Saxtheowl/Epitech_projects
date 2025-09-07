#!/bin/bash
##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Language detection script for Whanos infrastructure
##

set -e

REPO_PATH="$1"

if [ -z "$REPO_PATH" ]; then
    echo "Usage: $0 <repository_path>"
    exit 1
fi

cd "$REPO_PATH"

# Check for C
if [ -f "Makefile" ]; then
    echo "c"
    exit 0
fi

# Check for Java
if [ -f "app/pom.xml" ]; then
    echo "java"
    exit 0
fi

# Check for JavaScript
if [ -f "package.json" ]; then
    echo "javascript"
    exit 0
fi

# Check for Python
if [ -f "requirements.txt" ]; then
    echo "python"
    exit 0
fi

# Check for Befunge
if [ -f "app/main.bf" ]; then
    echo "befunge"
    exit 0
fi

echo "unknown"
exit 1