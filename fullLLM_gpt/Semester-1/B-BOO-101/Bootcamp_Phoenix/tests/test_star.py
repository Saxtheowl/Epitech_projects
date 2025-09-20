#!/usr/bin/env python3
import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
STAR_BIN = ROOT / "Day05" / "star"
EXAMPLE_FILE = ROOT / "Day05" / "star_examples.txt"

if not STAR_BIN.exists():
    print("[ERROR] star binary not found", file=sys.stderr)
    sys.exit(1)

examples = EXAMPLE_FILE.read_text().splitlines()
expected = {}
current = None
collect = False
buffer = []
for line in examples:
    if line.startswith("$> ./star "):
        parts = line.split()
        if len(parts) >= 3 and parts[2].lstrip('-').isdigit():
            current = int(parts[2])
            buffer = []
            collect = True
        else:
            collect = False
    elif collect:
        if line.startswith("$>"):
            expected[current] = "\n".join(buffer)
            collect = False
            current = None
        else:
            buffer.append(line.rstrip('$'))
if collect and current is not None:
    expected[current] = "\n".join(buffer)

success = True
for size, reference in expected.items():
    result = subprocess.run([str(STAR_BIN), str(size)], capture_output=True, text=True)
    if size != 0 and result.returncode != 0:
        print(f"[FAIL] star({size}) returned {result.returncode}", file=sys.stderr)
        success = False
        continue
    if size == 0 and result.returncode != 0:
        print(f"[FAIL] star(0) returned {result.returncode}", file=sys.stderr)
        success = False
        continue
    output = result.stdout.rstrip('\n')
    if output != reference:
        print(f"[FAIL] star({size}) output mismatch", file=sys.stderr)
        print("Expected:")
        print(reference)
        print("Got:")
        print(output)
        success = False

invalid_cases = ["toto", "-1"]
for arg in invalid_cases:
    result = subprocess.run([str(STAR_BIN), arg], capture_output=True, text=True)
    if result.returncode == 0:
        print(f"[FAIL] star({arg}) should fail", file=sys.stderr)
        success = False
    if result.stderr.strip() != "Usage: ./star <number>":
        print(f"[FAIL] star({arg}) stderr mismatch", file=sys.stderr)
        success = False

sys.exit(0 if success else 1)
