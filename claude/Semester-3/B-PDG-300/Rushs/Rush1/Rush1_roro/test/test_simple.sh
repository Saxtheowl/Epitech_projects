#!/bin/bash

##
## EPITECH PROJECT, 2025  
## pushswap_checker
## File description:
## Simple test script for pushswap_checker
##

# Test 1: Valid sorting sequence
echo "=== Test 1: Valid sorting sequence ==="
echo "sa pb pb pb sa pa pa pa" | ./pushswap_checker 2 1 3 6 5 8
if [ $? -eq 0 ]; then
    echo "✓ Test 1 passed"
else
    echo "✗ Test 1 failed"
fi

# Test 2: Invalid sorting sequence  
echo -e "\n=== Test 2: Invalid sorting sequence ==="
echo "sa pb pb pb" | ./pushswap_checker 2 1 3 6 5 8
if [ $? -eq 0 ]; then
    echo "✓ Test 2 passed"
else
    echo "✗ Test 2 failed"
fi

# Test 3: Already sorted
echo -e "\n=== Test 3: Already sorted ==="
echo "" | ./pushswap_checker 1 2 3 4 5
if [ $? -eq 0 ]; then
    echo "✓ Test 3 passed"
else
    echo "✗ Test 3 failed"
fi

# Test 4: Invalid arguments
echo -e "\n=== Test 4: Invalid arguments ==="
echo "sa" | ./pushswap_checker abc
if [ $? -eq 84 ]; then
    echo "✓ Test 4 passed (error code 84)"
else
    echo "✗ Test 4 failed"
fi