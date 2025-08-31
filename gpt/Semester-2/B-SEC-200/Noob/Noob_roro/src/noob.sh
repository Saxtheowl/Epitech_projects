#!/usr/bin/env sh
#
# EPITECH PROJECT, 2025
# NOOB checks
# File description:
# Minimal security checks on a directory (world-writable files)

set -eu

DIR=${1:-.}

find "$DIR" -type f -perm -0002 -print

