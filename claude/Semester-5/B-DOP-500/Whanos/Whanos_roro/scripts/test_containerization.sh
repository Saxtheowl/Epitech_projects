#!/bin/bash
##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Test script for containerization functionality
##

set -e

echo "Testing Docker images build..."

# Test that all base images exist
for lang in c java javascript python befunge; do
    if docker image inspect "whanos-$lang" >/dev/null 2>&1; then
        echo "✓ whanos-$lang base image: EXISTS"
    else
        echo "✗ whanos-$lang base image: MISSING"
        exit 1
    fi
    
    if docker image inspect "whanos-$lang-standalone" >/dev/null 2>&1; then
        echo "✓ whanos-$lang-standalone image: EXISTS"  
    else
        echo "✗ whanos-$lang-standalone image: MISSING"
        exit 1
    fi
done

echo "All containerization tests passed!"