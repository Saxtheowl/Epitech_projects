#!/usr/bin/env python3
"""
Test runner for Pushswap project
"""

import os
import subprocess
import sys
from pathlib import Path

class TestRunner:
    def __init__(self):
        self.project_root = Path(__file__).parent.parent
        self.executable = self.project_root / "push_swap"
        
    def build_project(self):
        """Build the project using make"""
        print("Building Pushswap project...")
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
    
    def test_sorted_list(self):
        """Test with already sorted list"""
        print("Testing sorted list (should output nothing)...")
        try:
            result = subprocess.run([str(self.executable), '1', '2', '3', '4', '5'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode != 0:
                print(f"✗ Sorted list test failed with return code: {result.returncode}")
                return False
            
            if result.stdout.strip() == "":
                print("✓ Sorted list test passed (no output)")
                return True
            else:
                print(f"✗ Sorted list test failed - Expected empty output, got: '{result.stdout}'")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Sorted list test timed out")
            return False
        except Exception as e:
            print(f"✗ Sorted list test error: {e}")
            return False
    
    def test_single_number(self):
        """Test with single number"""
        print("Testing single number...")
        try:
            result = subprocess.run([str(self.executable), '42'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode != 0:
                print(f"✗ Single number test failed with return code: {result.returncode}")
                return False
            
            if result.stdout.strip() == "":
                print("✓ Single number test passed")
                return True
            else:
                print(f"✗ Single number test failed - Expected empty output, got: '{result.stdout}'")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Single number test timed out")
            return False
        except Exception as e:
            print(f"✗ Single number test error: {e}")
            return False
    
    def test_reverse_sorted(self):
        """Test with reverse sorted list"""
        print("Testing reverse sorted list...")
        try:
            result = subprocess.run([str(self.executable), '3', '2', '1'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode != 0:
                print(f"✗ Reverse sorted test failed with return code: {result.returncode}")
                return False
            
            if result.stdout.strip():
                operations = result.stdout.strip().split()
                if len(operations) > 0 and len(operations) <= 10:  # Reasonable operation count
                    print(f"✓ Reverse sorted test passed ({len(operations)} operations)")
                    return True
                else:
                    print(f"✗ Reverse sorted test failed - Too many operations: {len(operations)}")
                    return False
            else:
                print("✗ Reverse sorted test failed - No operations output")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Reverse sorted test timed out")
            return False
        except Exception as e:
            print(f"✗ Reverse sorted test error: {e}")
            return False
    
    def test_invalid_input(self):
        """Test with invalid input"""
        print("Testing invalid input...")
        try:
            result = subprocess.run([str(self.executable), 'abc'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode == 84:
                print("✓ Invalid input test passed (exit code 84)")
                return True
            else:
                print(f"✗ Invalid input test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Invalid input test timed out")
            return False
        except Exception as e:
            print(f"✗ Invalid input test error: {e}")
            return False
    
    def test_duplicate_numbers(self):
        """Test with duplicate numbers"""
        print("Testing duplicate numbers...")
        try:
            result = subprocess.run([str(self.executable), '1', '2', '1'], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode == 84:
                print("✓ Duplicate numbers test passed (exit code 84)")
                return True
            else:
                print(f"✗ Duplicate numbers test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Duplicate numbers test timed out")
            return False
        except Exception as e:
            print(f"✗ Duplicate numbers test error: {e}")
            return False
    
    def test_no_arguments(self):
        """Test with no arguments"""
        print("Testing no arguments...")
        try:
            result = subprocess.run([str(self.executable)], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode == 0:
                print("✓ No arguments test passed")
                return True
            else:
                print(f"✗ No arguments test failed - Expected exit code 0, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ No arguments test timed out")
            return False
        except Exception as e:
            print(f"✗ No arguments test error: {e}")
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
            self.test_no_arguments,
            self.test_single_number,
            self.test_sorted_list,
            self.test_reverse_sorted,
            self.test_invalid_input,
            self.test_duplicate_numbers,
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