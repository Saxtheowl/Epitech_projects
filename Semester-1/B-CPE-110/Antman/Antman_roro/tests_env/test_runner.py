#!/usr/bin/env python3
"""
Test runner for Antman project
"""

import os
import subprocess
import sys
import tempfile
from pathlib import Path

class TestRunner:
    def __init__(self):
        self.project_root = Path(__file__).parent.parent
        self.antman_executable = self.project_root / "antman" / "antman"
        self.giantman_executable = self.project_root / "giantman" / "giantman"
        
    def build_project(self):
        """Build the project using make"""
        print("Building Antman project...")
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
    
    def test_executables_exist(self):
        """Test that both executables were created"""
        antman_exists = self.antman_executable.exists()
        giantman_exists = self.giantman_executable.exists()
        
        if antman_exists and giantman_exists:
            print("✓ Both executables exist")
            return True
        else:
            if not antman_exists:
                print("✗ Antman executable does not exist")
            if not giantman_exists:
                print("✗ Giantman executable does not exist")
            return False
    
    def test_compression_decompression(self):
        """Test compression and decompression round trip"""
        print("Testing compression/decompression round trip...")
        
        test_content = "Hello world Hello world test test compression"
        
        try:
            with tempfile.NamedTemporaryFile(mode='w', delete=False) as f:
                f.write(test_content)
                input_file = f.name
            
            # Compress
            compress_result = subprocess.run(
                [str(self.antman_executable), input_file, '1'], 
                capture_output=True, 
                timeout=10
            )
            
            if compress_result.returncode != 0:
                print(f"✗ Compression failed with return code: {compress_result.returncode}")
                os.unlink(input_file)
                return False
            
            compressed_data = compress_result.stdout
            
            with tempfile.NamedTemporaryFile(mode='wb', delete=False) as f:
                f.write(compressed_data)
                compressed_file = f.name
            
            # Decompress
            decompress_result = subprocess.run(
                [str(self.giantman_executable), compressed_file, '1'], 
                capture_output=True, 
                timeout=10
            )
            
            if decompress_result.returncode != 0:
                print(f"✗ Decompression failed with return code: {decompress_result.returncode}")
                os.unlink(input_file)
                os.unlink(compressed_file)
                return False
            
            decompressed_data = decompress_result.stdout.decode('utf-8', errors='ignore')
            
            if decompressed_data == test_content:
                print("✓ Compression/decompression round trip successful")
                success = True
            else:
                print("✗ Decompressed data does not match original")
                print(f"Original: '{test_content}'")
                print(f"Decompressed: '{decompressed_data}'")
                success = False
            
            os.unlink(input_file)
            os.unlink(compressed_file)
            return success
            
        except subprocess.TimeoutExpired:
            print("✗ Compression/decompression test timed out")
            return False
        except Exception as e:
            print(f"✗ Compression/decompression test error: {e}")
            return False
    
    def test_invalid_arguments_antman(self):
        """Test antman with invalid arguments"""
        print("Testing antman with invalid arguments...")
        try:
            result = subprocess.run([str(self.antman_executable)], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode == 84:
                print("✓ Antman invalid arguments test passed")
                return True
            else:
                print(f"✗ Antman invalid arguments test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Antman invalid arguments test timed out")
            return False
        except Exception as e:
            print(f"✗ Antman invalid arguments test error: {e}")
            return False
    
    def test_invalid_arguments_giantman(self):
        """Test giantman with invalid arguments"""
        print("Testing giantman with invalid arguments...")
        try:
            result = subprocess.run([str(self.giantman_executable)], 
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            
            if result.returncode == 84:
                print("✓ Giantman invalid arguments test passed")
                return True
            else:
                print(f"✗ Giantman invalid arguments test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Giantman invalid arguments test timed out")
            return False
        except Exception as e:
            print(f"✗ Giantman invalid arguments test error: {e}")
            return False
    
    def test_invalid_file_type(self):
        """Test with invalid file type"""
        print("Testing with invalid file type...")
        
        test_content = "test"
        
        try:
            with tempfile.NamedTemporaryFile(mode='w', delete=False) as f:
                f.write(test_content)
                input_file = f.name
            
            result = subprocess.run(
                [str(self.antman_executable), input_file, '5'], 
                capture_output=True, 
                text=True,
                timeout=5
            )
            
            os.unlink(input_file)
            
            if result.returncode == 84:
                print("✓ Invalid file type test passed")
                return True
            else:
                print(f"✗ Invalid file type test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Invalid file type test timed out")
            return False
        except Exception as e:
            print(f"✗ Invalid file type test error: {e}")
            return False
    
    def test_nonexistent_file(self):
        """Test with nonexistent file"""
        print("Testing with nonexistent file...")
        try:
            result = subprocess.run(
                [str(self.antman_executable), '/nonexistent/file.txt', '1'], 
                capture_output=True, 
                text=True,
                timeout=5
            )
            
            if result.returncode == 84:
                print("✓ Nonexistent file test passed")
                return True
            else:
                print(f"✗ Nonexistent file test failed - Expected exit code 84, got: {result.returncode}")
                return False
                
        except subprocess.TimeoutExpired:
            print("✗ Nonexistent file test timed out")
            return False
        except Exception as e:
            print(f"✗ Nonexistent file test error: {e}")
            return False
    
    def run_all_tests(self):
        """Run all test cases"""
        if not self.build_project():
            return False
        
        tests = [
            self.test_executables_exist,
            self.test_invalid_arguments_antman,
            self.test_invalid_arguments_giantman,
            self.test_invalid_file_type,
            self.test_nonexistent_file,
            self.test_compression_decompression,
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