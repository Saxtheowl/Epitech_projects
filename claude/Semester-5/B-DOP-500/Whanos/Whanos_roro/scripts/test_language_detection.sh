#!/bin/bash
##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Test script for language detection functionality
##

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_DIR="/tmp/whanos_test_detection"

# Create test directories
mkdir -p "$TEST_DIR"/{c_project,java_project,js_project,python_project,befunge_project,unknown_project}

# Setup C project
echo "CC = gcc" > "$TEST_DIR/c_project/Makefile"
mkdir -p "$TEST_DIR/c_project/app"

# Setup Java project  
mkdir -p "$TEST_DIR/java_project/app"
echo "<project></project>" > "$TEST_DIR/java_project/app/pom.xml"

# Setup JavaScript project
echo '{"name": "test"}' > "$TEST_DIR/js_project/package.json"
mkdir -p "$TEST_DIR/js_project/app"

# Setup Python project
echo "requests==2.25.1" > "$TEST_DIR/python_project/requirements.txt"
mkdir -p "$TEST_DIR/python_project/app"

# Setup Befunge project
mkdir -p "$TEST_DIR/befunge_project/app"
echo '"Hello World">,:#v_@' > "$TEST_DIR/befunge_project/app/main.bf"

# Run tests
echo "Testing language detection..."

test_detection() {
    local project_type="$1"
    local expected="$2"
    local result
    
    result=$("$SCRIPT_DIR/detect_language.sh" "$TEST_DIR/${project_type}_project")
    
    if [ "$result" = "$expected" ]; then
        echo "✓ $project_type detection: PASS"
        return 0
    else
        echo "✗ $project_type detection: FAIL (expected: $expected, got: $result)"
        return 1
    fi
}

# Run all detection tests
test_detection "c" "c"
test_detection "java" "java" 
test_detection "js" "javascript"
test_detection "python" "python"
test_detection "befunge" "befunge"

# Test unknown project
if "$SCRIPT_DIR/detect_language.sh" "$TEST_DIR/unknown_project" >/dev/null 2>&1; then
    echo "✗ unknown project detection: FAIL (should have failed)"
    exit 1
else
    echo "✓ unknown project detection: PASS"
fi

# Cleanup
rm -rf "$TEST_DIR"

echo "All language detection tests passed!"