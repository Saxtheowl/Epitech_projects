#!/bin/bash

# skip-synthesis.sh - parse ls -l output and print user and filename for files starting with given string

if [ $# -ne 1 ]; then
    echo "Usage: $0 <prefix>" >&2
    exit 84
fi

prefix="$1"

# Read from stdin (ls -l output) and process each line
while read -r line; do
    # Skip lines that don't represent files (directories, totals, etc.)
    if [[ "$line" =~ ^-.*$ ]]; then
        # Extract user (owner) and filename from ls -l output
        # ls -l format: permissions owner group size date filename
        user=$(echo "$line" | awk '{print $3}')
        filename=$(echo "$line" | awk '{print $NF}')
        
        # Check if filename starts with the given prefix
        if [[ "$filename" == "$prefix"* ]]; then
            echo "$user $filename"
        fi
    fi
done