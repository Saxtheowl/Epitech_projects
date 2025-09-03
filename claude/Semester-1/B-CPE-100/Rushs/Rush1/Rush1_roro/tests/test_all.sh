#!/bin/bash

# Test script for all Rush1 assignments
# Tests various combinations as shown in the PDF

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Testing Rush1 Assignments ===${NC}"

# Function to test a specific rush assignment
test_rush() {
    local rush_dir=$1
    local rush_name=$2
    echo -e "${BLUE}Testing $rush_name${NC}"
    
    # Compile
    cd $rush_dir
    gcc -o test_rush *.c ../tests/my_putchar.c ../tests/main_test.c 2>/dev/null
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compilation failed for $rush_name${NC}"
        return 1
    fi
    
    # Test various sizes
    echo "Test 5,3:"
    ./test_rush 5 3
    echo ""
    
    echo "Test 5,1:"
    ./test_rush 5 1
    echo ""
    
    echo "Test 1,1:"
    ./test_rush 1 1
    echo ""
    
    echo "Test 1,5:"
    ./test_rush 1 5
    echo ""
    
    echo "Test 4,4:"
    ./test_rush 4 4
    echo ""
    
    # Clean up
    rm -f test_rush
    cd ..
    echo -e "${GREEN}$rush_name completed${NC}"
    echo ""
}

# Test all assignments
test_rush "rush-1-1" "Rush 1-1"
test_rush "rush-1-2" "Rush 1-2"  
test_rush "rush-1-3" "Rush 1-3"
test_rush "rush-1-4" "Rush 1-4"
test_rush "rush-1-5" "Rush 1-5"

echo -e "${GREEN}All tests completed!${NC}"