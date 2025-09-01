#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <prefix>" >&2
    exit 84
fi

prefix="$1"

while read -r line; do
    if [[ "$line" =~ ^-[rwx-]{9}[[:space:]]+[0-9]+[[:space:]]+([^[:space:]]+)[[:space:]]+[^[:space:]]+[[:space:]]+[0-9]+[[:space:]]+[^[:space:]]+[[:space:]]+[0-9]+[[:space:]]+[0-9:]+[[:space:]]+(.+)$ ]]; then
        user="${BASH_REMATCH[1]}"
        filename="${BASH_REMATCH[2]}"
        
        if [[ "$filename" == ${prefix}* ]]; then
            echo "$user $filename"
        fi
    fi
done