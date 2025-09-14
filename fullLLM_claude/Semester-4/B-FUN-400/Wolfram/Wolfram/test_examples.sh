#!/bin/bash

# Test script for Wolfram Elementary Cellular Automaton
# These are the examples from the PDF specification

echo "Testing Wolfram Elementary Cellular Automaton"
echo "=============================================="
echo

if [ ! -f "./wolfram" ]; then
    echo "Error: wolfram executable not found. Please build first with 'make'"
    exit 1
fi

echo "Test 1: Basic rule 30 with 20 lines"
echo "Command: ./wolfram --rule 30 --lines 20"
echo "Expected: Displays 20 generations of rule 30 starting from generation 0"
echo
./wolfram --rule 30 --lines 20
echo

echo "Test 2: Rule 90 starting from generation 100"  
echo "Command: ./wolfram --rule 90 --lines 20 --start 100"
echo "Expected: Displays 20 generations of rule 90 starting from generation 100"
echo
./wolfram --rule 90 --lines 20 --start 100
echo

echo "Test 3: Rule 30 with window movement"
echo "Command: ./wolfram --rule 30 --lines 10 --move 20" 
echo "Expected: Displays 10 generations of rule 30 with window shifted right by 20"
echo
./wolfram --rule 30 --lines 10 --move 20
echo

echo "Test 4: Error handling - missing rule"
echo "Command: ./wolfram --lines 5"
echo "Expected: Error message and exit code 84"
echo
./wolfram --lines 5
echo $?
echo

echo "Test 5: Error handling - invalid rule"
echo "Command: ./wolfram --rule 99 --lines 5"
echo "Expected: Error message and exit code 84"
echo
./wolfram --rule 99 --lines 5  
echo $?
echo

echo "Test 6: Rule 110 (Turing complete)"
echo "Command: ./wolfram --rule 110 --lines 15"
echo "Expected: Displays 15 generations of rule 110"
echo
./wolfram --rule 110 --lines 15
echo

echo "All tests completed!"