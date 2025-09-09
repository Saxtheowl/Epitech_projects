#!/bin/bash

echo "Building test..."
cd lib/my && ./build.sh && cd ../..
gcc -o test_count_island tests/test_main.c count_island.c -I./include -L./lib/my -lmy

if [ $? -eq 0 ]; then
    echo "Running tests..."
    ./test_count_island
    TEST_RESULT=$?
    rm -f test_count_island
    exit $TEST_RESULT
else
    echo "Build failed!"
    exit 1
fi