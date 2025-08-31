#!/usr/bin/env sh
#
# EPITECH PROJECT, 2025
# Epytodo tests

set -eu

python3 -m py_compile src/app.py
python3 src/app.py | grep -q "Epytodo API placeholder"
echo "Epytodo tests OK"

