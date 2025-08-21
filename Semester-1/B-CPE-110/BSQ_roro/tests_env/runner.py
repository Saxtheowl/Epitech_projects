#!/usr/bin/env python3
"""
Test runner for BSQ project
"""

import os
import sys
import subprocess
import tempfile
from pathlib import Path

def run_bsq_test(binary_path, test_map_path, expected_output_path):
    """Run BSQ binary with test map and compare output"""
    try:
        # Run the BSQ binary
        result = subprocess.run(
            [binary_path, test_map_path],
            capture_output=True,
            text=True,
            timeout=10
        )
        
        if result.returncode != 0:
            return False, f"Binary failed with code {result.returncode}: {result.stderr}"
        
        # Read expected output
        with open(expected_output_path, 'r') as f:
            expected = f.read().strip()
        
        actual = result.stdout.strip()
        
        if actual == expected:
            return True, "PASS"
        else:
            return False, f"Output mismatch\\nExpected:\\n{expected}\\nGot:\\n{actual}"
    
    except subprocess.TimeoutExpired:
        return False, "Test timed out"
    except Exception as e:
        return False, f"Error running test: {str(e)}"

def main():
    """Main test runner"""
    project_root = Path(__file__).parent.parent
    binary_path = project_root / "bsq"
    cases_dir = project_root / "tests_env" / "cases"
    
    # Check if binary exists
    if not binary_path.exists():
        print("ERROR: Binary 'bsq' not found. Run 'make' first.")
        return 1
    
    # Find all test cases
    test_cases = []
    for map_file in cases_dir.glob("*.map"):
        expected_file = map_file.with_suffix(".expected")
        if expected_file.exists():
            test_cases.append((map_file, expected_file))
    
    if not test_cases:
        print("WARNING: No test cases found in tests_env/cases/")
        return 0
    
    # Run tests
    passed = 0
    failed = 0
    
    print(f"Running {len(test_cases)} BSQ tests...")
    print("=" * 50)
    
    for map_file, expected_file in test_cases:
        test_name = map_file.stem
        success, message = run_bsq_test(str(binary_path), str(map_file), str(expected_file))
        
        if success:
            print(f"✓ {test_name}: {message}")
            passed += 1
        else:
            print(f"✗ {test_name}: {message}")
            failed += 1
    
    print("=" * 50)
    print(f"Results: {passed} passed, {failed} failed")
    
    return 0 if failed == 0 else 1

if __name__ == "__main__":
    sys.exit(main())