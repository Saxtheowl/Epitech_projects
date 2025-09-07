#!/usr/bin/env python3
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Tiny Befunge-93 interpreter (sufficient for tests)
#

import sys


def load(code):
    grid = [list(line.rstrip('\n')) for line in code.splitlines()]
    w = max((len(r) for r in grid), default=0)
    for r in grid:
        if len(r) < w:
            r += [' '] * (w - len(r))
    return grid, w, len(grid)


def run(path):
    with open(path, 'r') as f:
        code = f.read()
    g, w, h = load(code)
    x = y = 0
    dx, dy = 1, 0
    st = []
    string = False
    ip = 0

    def pop():
        return st.pop() if st else 0

    while ip < 100000:  # basic guard
        ip += 1
        c = g[y][x]
        if string:
            if c == '"':
                string = False
            else:
                st.append(ord(c))
        else:
            if c.isdigit():
                st.append(int(c))
            elif c == '+':
                b, a = pop(), pop(); st.append(a + b)
            elif c == '-':
                b, a = pop(), pop(); st.append(a - b)
            elif c == '*':
                b, a = pop(), pop(); st.append(a * b)
            elif c == '/':
                b, a = pop(), pop(); st.append(0 if b == 0 else a // b)
            elif c == '%':
                b, a = pop(), pop(); st.append(0 if b == 0 else a % b)
            elif c == '!':
                a = pop(); st.append(0 if a else 1)
            elif c == '`':
                b, a = pop(), pop(); st.append(1 if a > b else 0)
            elif c == '>':
                dx, dy = 1, 0
            elif c == '<':
                dx, dy = -1, 0
            elif c == '^':
                dx, dy = 0, -1
            elif c == 'v':
                dx, dy = 0, 1
            elif c == '?':
                dx, dy = 1, 0  # simple (no RNG)
            elif c == '_':
                dx, dy = (1, 0) if pop() == 0 else (-1, 0)
            elif c == '|':
                dx, dy = (0, 1) if pop() == 0 else (0, -1)
            elif c == '"':
                string = True
            elif c == ':':
                a = pop(); st.extend([a, a])
            elif c == '\\':
                b, a = pop(), pop(); st.extend([b, a])
            elif c == '$':
                pop()
            elif c == '.':
                sys.stdout.write(str(pop()) + ' ')
            elif c == ',':
                sys.stdout.write(chr(pop()))
            elif c == '#':
                x = (x + dx) % w; y = (y + dy) % h
            elif c == 'p':
                yv, xv, v = pop(), pop(), pop()
                if 0 <= yv < h and 0 <= xv < w:
                    g[yv][xv] = chr(v)
            elif c == 'g':
                yv, xv = pop(), pop()
                st.append(ord(g[yv][xv]) if 0 <= yv < h and 0 <= xv < w else 0)
            elif c == '&':
                try:
                    st.append(int(sys.stdin.readline().strip()))
                except Exception:
                    st.append(0)
            elif c == '~':
                ch = sys.stdin.read(1)
                st.append(ord(ch) if ch else 0)
            elif c == '@':
                break
        x = (x + dx) % w
        y = (y + dy) % h


def main(argv):
    if len(argv) != 2:
        print("Usage: befunge_runner.py <file>", file=sys.stderr)
        return 84
    run(argv[1])
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))

