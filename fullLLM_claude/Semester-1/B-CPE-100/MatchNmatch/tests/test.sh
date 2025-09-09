#!/bin/bash

echo "Building library..."
cd lib/my && ./build.sh && cd ../..

echo "Building match..."
gcc -o test_match match.c tests/match_main.c -I./include -L./lib/my -lmy

echo "Building nmatch..."
gcc -o test_nmatch nmatch.c tests/nmatch_main.c -I./include -L./lib/my -lmy

if [ $? -eq 0 ]; then
    echo "Running match tests..."
    ./test_match
    echo ""
    echo "Running nmatch tests..."
    ./test_nmatch
    
    rm -f test_match test_nmatch
    echo ""
    echo "Tests completed!"
else
    echo "Build failed!"
    exit 1
fi