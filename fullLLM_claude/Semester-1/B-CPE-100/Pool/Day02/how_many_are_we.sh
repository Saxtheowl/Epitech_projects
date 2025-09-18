#!/bin/bash

if [ $# -eq 0 ]; then
    wc -l < /dev/stdin
else
    grep -c ";$1$" < /dev/stdin
fi