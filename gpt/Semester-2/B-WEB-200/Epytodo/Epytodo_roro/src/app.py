#!/usr/bin/env python3
#
# EPITECH PROJECT, 2025
# Epytodo
# File description:
# Minimal placeholder CLI (no external deps)
#

import sys


def main(argv: list[str]) -> int:
    if len(argv) > 1 and argv[1] in {"-h", "--help"}:
        print("Epytodo placeholder. Use 'make run' to run.")
        return 0
    # Minimal output to show the project is wired
    print("Epytodo API placeholder running (no server in this skeleton)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))

