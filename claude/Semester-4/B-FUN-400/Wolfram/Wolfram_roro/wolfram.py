#!/usr/bin/env python3
"""
EPITECH PROJECT, 2025
Wolfram
File description:
Elementary Cellular Automaton implementation
"""

import sys
import argparse

def rule_table(rule_number):
    """Create rule table for given rule number"""
    table = {}
    for i in range(8):
        left = (i >> 2) & 1
        center = (i >> 1) & 1
        right = i & 1
        bit = (rule_number >> i) & 1
        table[(left, center, right)] = bit
    return table

def next_generation(current_gen, rule_table):
    """Generate next generation from current one"""
    width = len(current_gen)
    extended = [0] * 100 + current_gen + [0] * 100
    new_gen = []
    
    for i in range(100, width + 100):
        left = extended[i-1] if i-1 >= 0 else 0
        center = extended[i]
        right = extended[i+1] if i+1 < len(extended) else 0
        new_gen.append(rule_table.get((left, center, right), 0))
    
    return new_gen

def display_generation(generation, window, move):
    """Display a generation as a string"""
    width = len(generation)
    center = width // 2
    start_pos = max(0, center - window // 2 + move)
    end_pos = min(width, start_pos + window)
    
    visible_cells = generation[start_pos:end_pos]
    return ''.join('*' if cell else ' ' for cell in visible_cells)

def show_usage():
    """Display usage message"""
    print("USAGE: wolfram --rule R [--start N] [--lines N] [--window N] [--move N]", file=sys.stderr)
    print("", file=sys.stderr)
    print("    --rule      the ruleset to use (mandatory)", file=sys.stderr)
    print("    --start     the generation number at which to start the display (default: 0)", file=sys.stderr)
    print("    --lines     the number of lines to display (default: infinite)", file=sys.stderr)
    print("    --window    the number of cells to display on each line (default: 80)", file=sys.stderr)
    print("    --move      translation to apply on the window (default: 0)", file=sys.stderr)

def main():
    """Main function"""
    try:
        # Manual argument parsing (getopt is forbidden)
        args = sys.argv[1:]
        if not args:
            show_usage()
            sys.exit(84)
        
        # Default values
        rule_num = None
        start = 0
        lines = None
        window = 80
        move = 0
        
        i = 0
        while i < len(args):
            if args[i] == '--rule':
                if i + 1 >= len(args):
                    show_usage()
                    sys.exit(84)
                try:
                    rule_num = int(args[i + 1])
                    if not (0 <= rule_num <= 255):
                        show_usage()
                        sys.exit(84)
                except ValueError:
                    show_usage()
                    sys.exit(84)
                i += 2
            elif args[i] == '--start':
                if i + 1 >= len(args):
                    show_usage()
                    sys.exit(84)
                try:
                    start = int(args[i + 1])
                    if start < 0:
                        show_usage()
                        sys.exit(84)
                except ValueError:
                    show_usage()
                    sys.exit(84)
                i += 2
            elif args[i] == '--lines':
                if i + 1 >= len(args):
                    show_usage()
                    sys.exit(84)
                try:
                    lines = int(args[i + 1])
                    if lines <= 0:
                        show_usage()
                        sys.exit(84)
                except ValueError:
                    show_usage()
                    sys.exit(84)
                i += 2
            elif args[i] == '--window':
                if i + 1 >= len(args):
                    show_usage()
                    sys.exit(84)
                try:
                    window = int(args[i + 1])
                    if window <= 0:
                        show_usage()
                        sys.exit(84)
                except ValueError:
                    show_usage()
                    sys.exit(84)
                i += 2
            elif args[i] == '--move':
                if i + 1 >= len(args):
                    show_usage()
                    sys.exit(84)
                try:
                    move = int(args[i + 1])
                except ValueError:
                    show_usage()
                    sys.exit(84)
                i += 2
            else:
                show_usage()
                sys.exit(84)
        
        if rule_num is None:
            show_usage()
            sys.exit(84)
        
        # Create initial generation with single alive cell in center
        initial_width = 200
        initial_gen = [0] * (initial_width // 2) + [1] + [0] * (initial_width // 2)
        
        # Create rule table
        rule = rule_table(rule_num)
        
        # Generate and display automaton
        current_gen = initial_gen
        gen_count = 0
        lines_displayed = 0
        
        # Skip generations until start
        for _ in range(start):
            current_gen = next_generation(current_gen, rule)
        
        # Display generations
        while lines is None or lines_displayed < lines:
            print(display_generation(current_gen, window, move))
            sys.stdout.flush()
            current_gen = next_generation(current_gen, rule)
            lines_displayed += 1
        
    except Exception:
        sys.exit(84)

if __name__ == "__main__":
    main()