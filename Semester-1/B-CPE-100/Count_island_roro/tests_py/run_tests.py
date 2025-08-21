#!/usr/bin/env python3
"""
Test suite for Count_island project
Tests the count_island function implementation
"""
import os
import sys
import subprocess
import tempfile
import shutil
from pathlib import Path

class CountIslandTester:
    def __init__(self, project_dir):
        self.project_dir = Path(project_dir).resolve()
        self.executable = self.project_dir / "count_island"
        self.test_results = []
        self.total_tests = 0
        self.passed_tests = 0
        
    def create_test_main(self, test_code):
        """Create a temporary main.c for testing"""
        main_content = f'''
#include "include/my.h"

{test_code}
'''
        return main_content
    
    def compile_test(self, main_content):
        """Compile the test with custom main"""
        with tempfile.TemporaryDirectory() as temp_dir:
            temp_path = Path(temp_dir)
            
            # Copy necessary files
            test_main = temp_path / "test_main.c"
            test_main.write_text(main_content)
            
            # Copy count_island.c
            shutil.copy2(self.project_dir / "count_island.c", temp_path)
            
            # Copy include directory
            if (self.project_dir / "include").exists():
                shutil.copytree(self.project_dir / "include", temp_path / "include")
            
            # Copy lib directory
            if (self.project_dir / "lib").exists():
                shutil.copytree(self.project_dir / "lib", temp_path / "lib")
            
            # Build library first
            lib_build = subprocess.run(
                ["bash", "build.sh"],
                cwd=temp_path / "lib" / "my",
                capture_output=True,
                text=True
            )
            
            if lib_build.returncode != 0:
                return None, f"Library build failed: {lib_build.stderr}"
            
            # Compile test
            compile_cmd = [
                "gcc", "-o", "test_count_island",
                "test_main.c", "count_island.c",
                "-I./include", "-L./lib/my", "-lmy",
                "-Wall", "-Wextra", "-std=c99"
            ]
            
            result = subprocess.run(
                compile_cmd,
                cwd=temp_path,
                capture_output=True,
                text=True
            )
            
            if result.returncode != 0:
                return None, f"Compilation failed: {result.stderr}"
            
            return temp_path / "test_count_island", None
    
    def run_test(self, test_name, main_code, expected_output=None, expected_exit=0):
        """Run a single test"""
        self.total_tests += 1
        print(f"Running test: {test_name}")
        
        executable, error = self.compile_test(main_code)
        if executable is None:
            self.test_results.append({
                'name': test_name,
                'status': 'COMPILE_ERROR',
                'expected': expected_output,
                'actual': error,
                'exit_code': -1
            })
            print(f"  ❌ COMPILE ERROR: {error}")
            return False
        
        # Run the test
        try:
            result = subprocess.run(
                [str(executable)],
                capture_output=True,
                text=True,
                timeout=5
            )
            
            actual_output = result.stdout
            actual_exit = result.returncode
            
            # Check exit code
            if actual_exit != expected_exit:
                self.test_results.append({
                    'name': test_name,
                    'status': 'FAIL',
                    'expected': f"exit {expected_exit}",
                    'actual': f"exit {actual_exit}",
                    'exit_code': actual_exit,
                    'output': actual_output
                })
                print(f"  ❌ FAIL: Expected exit {expected_exit}, got {actual_exit}")
                return False
            
            # Check output if specified
            if expected_output is not None:
                if actual_output.strip() != expected_output.strip():
                    self.test_results.append({
                        'name': test_name,
                        'status': 'FAIL',
                        'expected': expected_output,
                        'actual': actual_output,
                        'exit_code': actual_exit
                    })
                    print(f"  ❌ FAIL: Output mismatch")
                    print(f"    Expected: {repr(expected_output)}")
                    print(f"    Actual: {repr(actual_output)}")
                    return False
            
            self.test_results.append({
                'name': test_name,
                'status': 'PASS',
                'expected': expected_output,
                'actual': actual_output,
                'exit_code': actual_exit
            })
            print(f"  ✅ PASS")
            self.passed_tests += 1
            return True
            
        except subprocess.TimeoutExpired:
            self.test_results.append({
                'name': test_name,
                'status': 'TIMEOUT',
                'expected': expected_output,
                'actual': "Test timed out",
                'exit_code': -1
            })
            print(f"  ❌ TIMEOUT")
            return False
        except Exception as e:
            self.test_results.append({
                'name': test_name,
                'status': 'ERROR',
                'expected': expected_output,
                'actual': str(e),
                'exit_code': -1
            })
            print(f"  ❌ ERROR: {e}")
            return False
    
    def test_single_island(self):
        """Test with a single X (island 0)"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "..X..",
        ".....",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("single_island", main_code, "1\n..0..\n.....\n")
    
    def test_multiple_islands(self):
        """Test with multiple separate islands"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "X..X",
        "....",
        "X..X",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("multiple_islands", main_code, "4\n0..1\n....\n2..3\n")
    
    def test_connected_island(self):
        """Test with connected X forming one island"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "XX.",
        ".X.",
        "...",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("connected_island", main_code, "1\n00.\n.0.\n...\n")
    
    def test_empty_world(self):
        """Test with no islands"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "...",
        "...",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("empty_world", main_code, "0\n...\n...\n")
    
    def test_null_world(self):
        """Test with NULL world"""
        main_code = '''
int main(void) {
    char **world = NULL;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    return 0;
}
'''
        self.run_test("null_world", main_code, "0\n")
    
    def test_complex_pattern(self):
        """Test with a complex island pattern"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "X.X.X",
        ".X.X.",
        "X.X.X",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("complex_pattern", main_code, "4\n0.1.2\n.0.1.\n0.1.2\n")
    
    def test_large_island(self):
        """Test with one large connected island"""
        main_code = '''
void print_world(char **world) {
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\\n');
        i++;
    }
}

int main(void) {
    char *lines[] = {
        "XXX",
        "XXX",
        "XXX",
        NULL
    };
    char **world = lines;
    int result = count_island(world);
    
    my_putnbr(result);
    my_putchar('\\n');
    print_world(world);
    return 0;
}
'''
        self.run_test("large_island", main_code, "1\n000\n000\n000\n")
    
    def run_all_tests(self):
        """Run all test cases"""
        print("=== Count Island Test Suite ===\\n")
        
        # Test basic functionality
        self.test_single_island()
        self.test_multiple_islands()
        self.test_connected_island()
        self.test_empty_world()
        self.test_null_world()
        self.test_complex_pattern()
        self.test_large_island()
        
        print(f"\\n=== Test Results ===")
        print(f"Total tests: {self.total_tests}")
        print(f"Passed: {self.passed_tests}")
        print(f"Failed: {self.total_tests - self.passed_tests}")
        print(f"Success rate: {(self.passed_tests/self.total_tests)*100:.1f}%")
        
        return self.passed_tests == self.total_tests

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 run_tests.py <project_directory>")
        sys.exit(1)
    
    project_dir = sys.argv[1]
    if not os.path.exists(project_dir):
        print(f"Error: Project directory '{project_dir}' does not exist")
        sys.exit(1)
    
    tester = CountIslandTester(project_dir)
    success = tester.run_all_tests()
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()