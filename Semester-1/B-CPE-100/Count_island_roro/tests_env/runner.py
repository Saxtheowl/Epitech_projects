#!/usr/bin/env python3
"""
Test runner for Count_island project
"""

import os
import subprocess
import sys
from pathlib import Path

class TestRunner:
    def __init__(self):
        self.project_root = Path(__file__).parent.parent
        self.test_dir = Path(__file__).parent
        self.cases_dir = self.test_dir / "cases"
        self.executable = None
        
    def build_project(self):
        """Build the project using make"""
        print("Building project...")
        try:
            result = subprocess.run(['make'], 
                                  cwd=self.project_root, 
                                  capture_output=True, 
                                  text=True)
            if result.returncode != 0:
                print(f"Build failed: {result.stderr}")
                return False
            print("Build successful!")
            return True
        except Exception as e:
            print(f"Build error: {e}")
            return False
    
    def build_test_executable(self):
        """Build test executable"""
        print("Building test executable...")
        try:
            cmd = ['gcc', '-o', 'test_main', 'test_main.c', 
                   '../count_island.c', '-I../include', '-L../lib/my', '-lmy']
            result = subprocess.run(cmd, 
                                  cwd=self.test_dir, 
                                  capture_output=True, 
                                  text=True)
            if result.returncode != 0:
                print(f"Test build failed: {result.stderr}")
                return False
            
            self.executable = self.test_dir / "test_main"
            print("Test executable built successfully!")
            return True
        except Exception as e:
            print(f"Test build error: {e}")
            return False
    
    def run_test_case(self, test_name):
        """Run a single test case"""
        input_file = self.cases_dir / f"{test_name}.txt"
        expected_file = self.cases_dir / f"{test_name}.expected"
        
        if not input_file.exists():
            print(f"Input file not found: {input_file}")
            return False
            
        if not expected_file.exists():
            print(f"Expected file not found: {expected_file}")
            return False
        
        try:
            # Run the test
            result = subprocess.run([str(self.executable), str(input_file)], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=10)
            
            if result.returncode != 0:
                print(f"Test {test_name} failed - Return code: {result.returncode}")
                print(f"Stderr: {result.stderr}")
                return False
            
            # Read expected output
            with open(expected_file, 'r') as f:
                expected = f.read().strip()
            
            actual = result.stdout.strip()
            
            if actual == expected:
                print(f"✓ Test {test_name} passed")
                return True
            else:
                print(f"✗ Test {test_name} failed")
                print(f"Expected:")
                print(expected)
                print(f"Got:")
                print(actual)
                print("---")
                return False
                
        except subprocess.TimeoutExpired:
            print(f"✗ Test {test_name} timed out")
            return False
        except Exception as e:
            print(f"✗ Test {test_name} error: {e}")
            return False
    
    def run_all_tests(self):
        """Run all test cases"""
        if not self.build_project():
            return False
            
        if not self.build_test_executable():
            return False
        
        test_cases = []
        for file in self.cases_dir.glob("*.txt"):
            test_name = file.stem
            if (self.cases_dir / f"{test_name}.expected").exists():
                test_cases.append(test_name)
        
        if not test_cases:
            print("No test cases found!")
            return False
        
        passed = 0
        total = len(test_cases)
        
        print(f"\nRunning {total} test cases...\n")
        
        for test_name in sorted(test_cases):
            if self.run_test_case(test_name):
                passed += 1
        
        print(f"\nResults: {passed}/{total} tests passed")
        
        if passed == total:
            print("🎉 All tests passed!")
            return True
        else:
            print("❌ Some tests failed")
            return False
    
    def cleanup(self):
        """Clean up test files"""
        test_executable = self.test_dir / "test_main"
        if test_executable.exists():
            test_executable.unlink()

if __name__ == "__main__":
    runner = TestRunner()
    try:
        success = runner.run_all_tests()
        sys.exit(0 if success else 1)
    finally:
        runner.cleanup()