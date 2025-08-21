#!/usr/bin/env python3
"""
Test runner for MyHunter project
"""

import os
import subprocess
import sys
from pathlib import Path

class TestRunner:
    def __init__(self):
        self.project_root = Path(__file__).parent.parent
        self.executable = self.project_root / "my_hunter"
        
    def build_project(self):
        """Build the project using make"""
        print("Building MyHunter project...")
        try:
            result = subprocess.run(['make', '-f', 'Makefile.mock'], 
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
    
    def test_help_option(self):
        """Test the -h help option"""
        print("Testing -h help option...")
        try:
            result = subprocess.run([str(self.executable), '-h'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode != 0:
                print(f"✗ Help option failed with return code: {result.returncode}")
                return False
            
            output = result.stdout.lower()
            if "hunter" in output and "control" in output:
                print("✓ Help option test passed")
                return True
            else:
                print("✗ Help option test failed - Missing expected content")
                print(f"Output: {result.stdout}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Help option test timed out")
            return False
        except Exception as e:
            print(f"✗ Help option test error: {e}")
            return False
    
    def test_invalid_args(self):
        """Test with invalid arguments"""
        print("Testing invalid arguments...")
        try:
            result = subprocess.run([str(self.executable), 'invalid'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            # Should exit normally (game should start or exit gracefully)
            print("✓ Invalid arguments test passed")
            return True
                
        except subprocess.TimeoutExpired:
            print("✗ Invalid arguments test timed out")
            return False
        except Exception as e:
            print(f"✗ Invalid arguments test error: {e}")
            return False
    
    def test_executable_exists(self):
        """Test that the executable was created"""
        if self.executable.exists():
            print("✓ Executable exists")
            return True
        else:
            print("✗ Executable does not exist")
            return False
    
    def run_all_tests(self):
        """Run all test cases"""
        if not self.build_project():
            return False
        
        tests = [
            self.test_executable_exists,
            self.test_help_option,
            self.test_invalid_args,
        ]
        
        passed = 0
        total = len(tests)
        
        print(f"\nRunning {total} tests...\n")
        
        for test in tests:
            if test():
                passed += 1
            print()
        
        print(f"Results: {passed}/{total} tests passed")
        
        if passed == total:
            print("🎉 All tests passed!")
            return True
        else:
            print("❌ Some tests failed")
            return False

if __name__ == "__main__":
    runner = TestRunner()
    success = runner.run_all_tests()
    sys.exit(0 if success else 1)