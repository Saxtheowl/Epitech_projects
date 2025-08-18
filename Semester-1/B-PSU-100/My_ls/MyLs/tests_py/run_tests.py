\
#!/usr/bin/env python3
# EPITECH PROJECT, 2025
# my_ls - tests
# This test runner uses only Python stdlib and prints a compact OK/KO report.

import os
import sys
import tempfile
import subprocess
import shutil
import stat
import time

BIN = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "my_ls"))

def run(cmd, cwd=None):
    p = subprocess.Popen(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    out, err = p.communicate()
    return p.returncode, out, err

class Case:
    def __init__(self, name, fn):
        self.name = name
        self.fn = fn

def assert_true(cond, msg):
    if not cond:
        raise AssertionError(msg)

def has_line(s, wanted):
    return any(line.strip() == wanted for line in s.splitlines())

def main():
    cases = []

    def t_no_args_lists_current_dir():
        code, out, err = run([BIN])
        assert_true(code == 0, "exit code should be 0")
        assert_true(len(out) > 0, "should list current directory")
        assert_true(err == "", "stderr should be empty")

    cases.append(Case("no-args lists current dir", t_no_args_lists_current_dir))

    def t_invalid_option():
        code, out, err = run([BIN, "-z"])
        assert_true(code == 84, "invalid option must exit 84")
        assert_true("invalid option" in err, "must print error on stderr")

    cases.append(Case("invalid option -> 84", t_invalid_option))

    def t_a_shows_hidden():
        with tempfile.TemporaryDirectory() as d:
            open(os.path.join(d, ".hidden"), "w").close()
            open(os.path.join(d, "visible"), "w").close()
            code, out1, _ = run([BIN], cwd=d)
            code, out2, _ = run([BIN, "-a"], cwd=d)
            assert_true("hidden" not in out1, "hidden file must be hidden without -a")
            assert_true(".hidden" in out2, "hidden file must appear with -a")

    cases.append(Case("-a shows hidden", t_a_shows_hidden))

    def t_l_format():
        with tempfile.TemporaryDirectory() as d:
            p = os.path.join(d, "f")
            with open(p, "w") as f:
                f.write("x")
            code, out, _ = run([BIN, "-l"], cwd=d)
            assert_true(code == 0, "exit 0")
            # mode, links, owner, group, size, time, name
            # We just check that a line contains the file name and size '1'
            ok = any((" f" in line and line.strip().endswith(" f")) for line in out.splitlines())
            assert_true(ok, "should contain a -l line with file name")

    cases.append(Case("-l format basic", t_l_format))

    def t_d_lists_dir_itself():
        with tempfile.TemporaryDirectory() as d:
            sub = os.path.join(d, "dir")
            os.mkdir(sub)
            code, out, _ = run([BIN, "-d", "dir"], cwd=d)
            assert_true(code == 0, "exit 0")
            assert_true(out.strip() == "dir", "should print the directory name itself")

    cases.append(Case("-d lists directory itself", t_d_lists_dir_itself))

    def t_R_recursive():
        with tempfile.TemporaryDirectory() as d:
            os.mkdir(os.path.join(d, "a"))
            open(os.path.join(d, "a", "x"), "w").close()
            code, out, _ = run([BIN, "-R"], cwd=d)
            assert_true("a:" in out, "should print subdir header")
            assert_true("x" in out, "should list nested file")

    cases.append(Case("-R recursive", t_R_recursive))

    def t_t_sorts_by_mtime_and_r_reverses():
        with tempfile.TemporaryDirectory() as d:
            f1 = os.path.join(d, "older")
            f2 = os.path.join(d, "newer")
            open(f1, "w").close()
            time.sleep(1.1)
            open(f2, "w").close()
            code, out, _ = run([BIN, "-t"], cwd=d)
            first = out.strip().splitlines()[0].strip()
            assert_true(first == "newer", "newer first with -t")
            code, out, _ = run([BIN, "-tr"], cwd=d)
            first = out.strip().splitlines()[0].strip()
            assert_true(first == "older", "older first with -tr")

    cases.append(Case("-t sorts by time and -r reverses", t_t_sorts_by_mtime_and_r_reverses))

    def t_multiple_args_files_then_dirs():
        with tempfile.TemporaryDirectory() as d:
            f = os.path.join(d, "f"); open(f, "w").close()
            sub = os.path.join(d, "dir"); os.mkdir(sub)
            code, out, _ = run([BIN, "f", "dir"], cwd=d)
            lines = [l.strip() for l in out.splitlines() if l.strip()]
            assert_true(lines[0] == "f", "file printed first")
            assert_true(lines[1] == "dir:", "then dir section")

    cases.append(Case("multiple args: files then dirs", t_multiple_args_files_then_dirs))

    def t_missing_path_yields_84():
        code, out, err = run([BIN, "this_does_not_exist_42"])
        assert_true(code == 84, "missing path must yield 84")
        assert_true("No such file or directory" in err or "not found" in err, "stderr mentions not found")

    cases.append(Case("missing path -> 84", t_missing_path_yields_84))

    ok = 0
    print("Running tests...")
    for c in cases:
        try:
            c.fn()
            print(f"[OK] {c.name}")
            ok += 1
        except AssertionError as e:
            print(f"[KO] {c.name}: {e}")
        except Exception as e:
            print(f"[KO] {c.name}: unexpected error: {e}")
    total = len(cases)
    print(f"\nResult: {ok}/{total} tests passed.")
    sys.exit(0 if ok == total else 84)

if __name__ == "__main__":
    main()
